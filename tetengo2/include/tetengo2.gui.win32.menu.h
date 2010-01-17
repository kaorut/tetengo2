/*! \file
    \brief The definition of tetengo2::gui::win32::menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MENU_H)
#define TETENGO2_GUI_WIN32_MENU_H

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <functional>
#include <iterator>
#include <memory>
#include <stdexcept>
//#include <string>
#include <vector>

#include <boost/bind.hpp>
//#include <boost/concept_check.hpp>
#include <boost/mem_fn.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signal.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "concept_tetengo2.String.h"
#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.MenuObserver.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The base class template for a menu.

        \tparam Id           A ID type. It must conform to
                             boost::UnsignedInteger<Id>.
        \tparam Handle       A handle type. It must conform to
                             concept_tetengo2::gui::Handle<Handle>.
        \tparam String       A string type. It must conform to
                             concept_tetengo2::String<String>.
        \tparam Encode       An encoding unary functor type. The types
                             Encode<String, std::wstring> and
                             Encode<std::wstring, String> must conform to
                             boost::UnaryFunction<Encode, String, std::wstring>
                             and
                             boost::UnaryFunction<Encode, std::wstring, String>.
        \tparam MenuObserver A menu observer type. It must conform to
                             concept_tetengo2::gui::MenuObserver<MenuObserver>.
   */
    template <
        typename Id,
        typename Handle,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename MenuObserver
    >
    class menu : boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Id>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        struct concept_check_Encode
        {
            typedef std::wstring native_string_type;
            typedef Encode<String, std::wstring> encode_from_native_type;
            typedef Encode<std::wstring, String> encode_to_native_type;
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_from_native_type, String, native_string_type
                >
            ));
            BOOST_CONCEPT_ASSERT((
                boost::UnaryFunction<
                    encode_to_native_type, native_string_type, String
                >
            ));
        };
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::MenuObserver<MenuObserver>
        ));


    public:
        // types

        //! The ID type.
        typedef Id id_type;

        //! The handle type.
        typedef Handle handle_type;

        //! The string type.
        typedef String string_type;

        //! The unary functor type for encoding from the native.
        typedef Encode<String, std::wstring> encode_from_native_type;

        //! The unary functor type for encoding to the native.
        typedef Encode<std::wstring, String> encode_to_native_type;

        //! The menu observer type.
        typedef MenuObserver menu_observer_type;

        //! The menu iterator type.
        typedef typename boost::ptr_vector<menu>::iterator iterator;

        //! The const menu iterator type.
        typedef
            typename boost::ptr_vector<menu>::const_iterator const_iterator;


        // constructors and destructor

        /*!
            \brief Destroys the menu.
        */
        virtual ~menu()
        throw ()
        {}


        // functions

        /*!
            \brief Returns the ID.

            \return The ID.
        */
        id_type id()
        const
        {
            return m_id;
        }

        /*!
            \brief Returns the handle.

            \return The handle. It may be NULL.
        */
        handle_type handle()
        const
        {
            return m_handle;
        }

        /*!
            \brief Returns the text.

            \return The text.
        */
        const string_type& text()
        const
        {
            return m_text;
        }

        /*!
            \brief Selects this menu.
        */
        void select()
        {
            m_menu_selected_handler();
        }

        /*!
            \brief Adds a menu observer.

            \param p_menu_observer An auto pointer to a menu observer.
        */
        void add_menu_observer(
            std::auto_ptr<menu_observer_type> p_menu_observer
        )
        {
            m_menu_selected_handler.connect(
                boost::bind(
                    &menu_observer_type::selected, p_menu_observer.get()
                )
            );

            m_menu_observers.push_back(p_menu_observer);
        }

        /*!
            \brief Returns the first immutable iterator to the children.

            \return The first immutable iterator.
        */
        const_iterator begin()
        const
        {
            return m_children.begin();
        }

        /*!
            \brief Returns the first mutable iterator to the children.

            \return The first mutable iterator.
        */
        iterator begin()
        {
            return m_children.begin();
        }

        /*!
            \brief Returns the last immutable iterator to the children.

            \return The last immutable iterator.
        */
        const_iterator end()
        const
        {
            return m_children.end();
        }

        /*!
            \brief Returns the last mutable iterator to the children.

            \return The last mutable iterator.
        */
        iterator end()
        {
            return m_children.end();
        }

        /*!
            \brief Finds a menu among the children by the specified id.

            If no menu is found, it returns end().

            \param id An id.

            \return The immutable iterator to the menu.
        */
        const menu* find_by_id(const id_type id)
        const
        {
            return find_impl<const menu>(
                begin(), end(), id, boost::mem_fn(&menu::id)
            );
        }

        /*!
            \brief Finds a menu among the children by the specified id.

            If no menu is found, it returns end().

            \param id An id.

            \return The mutable iterator to the menu.
        */
        menu* find_by_id(const id_type id)
        {
            return find_impl<menu>(
                begin(), end(), id, boost::mem_fn(&menu::id)
            );
        }

        /*!
            \brief Finds a menu among the children by the specified handle.

            If no menu is found, it returns end().

            \param handle A handle.

            \return The immutable iterator to the menu.
        */
        const menu* find_by_handle(const handle_type handle)
        const
        {
            return find_impl<const menu>(
                begin(), end(), handle, boost::mem_fn(&menu::handle)
            );
        }

        /*!
            \brief Finds a menu among the children by the specified handle.

            If no menu is found, it returns end().

            \param handle A handle.

            \return The mutable iterator to the menu.
        */
        menu* find_by_handle(const handle_type handle)
        {
            return find_impl<menu>(
                begin(), end(), handle, boost::mem_fn(&menu::handle)
            );
        }

        /*!
            \brief Inserts a menu as a child.

            \param offset An offset where a menu is inserted.
            \param p_menu An auto pointer to a menu. It must not be NULL.
        */
        void insert(const iterator offset, std::auto_ptr<menu> p_menu)
        {
            if (p_menu.get() == NULL)
            {
                throw std::invalid_argument(
                    "The auto pointer to a menu is NULL."
                );
            }

            insert_native_menu(offset, *p_menu);

            m_children.insert(offset, p_menu);
        }

        /*!
            \brief Erases the menu items from the children.

            \param first The first iterator to the erased items.
            \param last  The last iterator to the eraed items.
        */
        void erase(const iterator first, const iterator last)
        {
            erase_native_menus(first, last);

            m_children.erase(first, last);
        }


    protected:
        // constructors

        /*!
            \brief Creates a menu.

            \param handle A handle.
            \param text   A text.
        */
        menu(const handle_type handle, const string_type& text)
        :
        m_id(get_and_increment_id()),
        m_handle(handle),
        m_text(text),
        m_menu_observers(),
        m_menu_selected_handler(),
        m_children()
        {}


        // functions

        /*!
            \brief Sets the Win32 menu information.

            \param menu_info       A menu information.
            \param duplicated_text A duplicated text.
        */
        virtual void set_menu_info(
            ::MENUITEMINFOW&       menu_info,
            std::vector< ::WCHAR>& duplicated_text
        )
        const = 0;


    private:
        // static functions

        static id_type get_and_increment_id()
        {
            static id_type id = 40001;

            return id++;
        }

        static std::vector< ::WCHAR> duplicate_text(
            const string_type& text
        )
        {
            const std::wstring native_string = encode_to_native_type()(text);

            std::vector< ::WCHAR> duplicated;
            duplicated.reserve(native_string.length() + 1);
            std::copy(
                native_string.begin(),
                native_string.end(),
                std::back_inserter(duplicated)
            );
            duplicated.push_back(L'\0');

            return duplicated;
        }


        // static functions

        template <
            typename Menu,
            typename ForwardIterator,
            typename Target,
            typename GetTarget
        >
        static Menu* find_impl(
            const ForwardIterator first,
            const ForwardIterator last,
            const Target          target,
            const GetTarget       get_target
        )
        {
            const ForwardIterator found = std::find_if(
                first,
                last,
                boost::bind(
                    std::equal_to<Target>(),
                    boost::bind(get_target, _1),
                    target
                )
            );
            if (found != last) return &*found;

            for (ForwardIterator i = first; i != last; ++i)
            {
                Menu* const p_found = find_impl<Menu>(
                    i->begin(),
                    i->end(),
                    target,
                    get_target
                );
                if (p_found != NULL) return p_found;
            }

            return NULL;
        }


        // variables

        id_type m_id;

        handle_type m_handle;

        string_type m_text;

        boost::ptr_vector<menu_observer_type> m_menu_observers;

        boost::signal<void ()> m_menu_selected_handler;

        boost::ptr_vector<menu> m_children;


        // functions

        void insert_native_menu(const const_iterator offset, menu& menu)
        const
        {
            ::MENUITEMINFOW menu_info;
            std::memset(&menu_info, 0, sizeof(::MENUITEMINFO));
            menu_info.cbSize = sizeof(::MENUITEMINFO);
            std::vector< ::WCHAR> duplicated_text =
                duplicate_text(menu.text());
            menu.set_menu_info(menu_info, duplicated_text);

            const ::BOOL result = ::InsertMenuItem(
                m_handle,
                static_cast< ::UINT>(
                    std::distance(m_children.begin(), offset)
                ),
                TRUE,
                &menu_info
            );
            if (result == 0)
            {
                throw std::runtime_error(
                    "Can't insert a native menu command."
                );
            }
        }

        void erase_native_menus(const_iterator first, const_iterator last)
        const
        {
            for (const_iterator i = first; i != last; ++i)
                erase_native_menu(i);
        }

        void erase_native_menu(const_iterator offset)
        const
        {
            ::RemoveMenu(
                m_handle,
                static_cast< ::UINT>(
                    std::distance(m_children.begin(), offset)
                ),
                MF_BYPOSITION
            );
        }


    };


}}}

#endif
