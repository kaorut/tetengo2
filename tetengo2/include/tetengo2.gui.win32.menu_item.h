/*! \file
    \brief The definition of tetengo2::gui::win32::menu_item.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MENUITEM_H)
#define TETENGO2_GUI_WIN32_MENUITEM_H

#include <cstddef>
#include <memory>
//#include <string>

#include <boost/bind.hpp>
//#include <boost/concept_check.hpp>
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
        \brief The base class template for a menu item.

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
    class menu_item : boost::noncopyable
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

        //! The menu item iterator type.
        typedef typename boost::ptr_vector<menu_item>::iterator iterator;

        //! The const menu item iterator type.
        typedef
            typename boost::ptr_vector<menu_item>::const_iterator
            const_iterator;


        // constructors and destructor

        /*!
            \brief Destroys the menu item.
        */
        virtual ~menu_item()
        throw ()
        {}


        // functions

        /*!
            \brief Returns whether the menu item is a menu command.

            \retval true  When the menu item is a menu command.
            \retval false Otherwise.
        */
        virtual bool is_command()
        const = 0;

        /*!
            \brief Returns whether the menu item is a popup menu.

            \retval true  When the menu item is a popup menu.
            \retval false Otherwise.
        */
        virtual bool is_popup()
        const = 0;

        /*!
            \brief Returns whether the menu item is a menu separator.

            \retval true  When the menu item is a menu separator.
            \retval false Otherwise.
        */
        virtual bool is_separator()
        const = 0;

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

            If the value of is_popup() is false, this function may return
            NULL.

            \return The handle.
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
            \brief Sets the text.

            \param text A text.
        */
        void set_text(const string_type& text)
        {
            m_text = text;
        }

        /*!
            \brief Selects this menu item.
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
                    &menu_observer_type::selected,
                    p_menu_observer.get()
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
            \brief Finds a menu item among the children by the specified id.

            If no menu is found, it returns end().

            \param id An id.

            \return The immutable iterator to the menu item.
        */
        const_iterator find_by_id(const id_type id)
        const
        {
            return end();
        }

        /*!
            \brief Finds a menu item among the children by the specified id.

            If no menu is found, it returns end().

            \param id An id.

            \return The mutable iterator to the menu item.
        */
        iterator find_by_id(const id_type id)
        {
            return end();
        }

        /*!
            \brief Finds a menu item among the children by the specified
                   handle.

            If no menu is found, it returns end().

            \param handle A handle.

            \return The immutable iterator to the menu item.
        */
        const_iterator find_by_handle(const handle_type handle)
        const
        {
            return end();
        }

        /*!
            \brief Finds a menu item among the children by the specified
                   handle.

            If no menu is found, it returns end().

            \param handle A handle.

            \return The mutable iterator to the menu item.
        */
        iterator find_by_handle(const handle_type handle)
        {
            return end();
        }

        /*!
            \brief Inserts a menu item as a child.

            \param offset      An offset where a menu item is inserted.
            \param p_menu_item An auto pointer to a menu item. It must not be
                               NULL.
        */
        void insert(
            const iterator           offset,
            std::auto_ptr<menu_item> p_menu_item
        )
        {
            if (p_menu_item.get() == NULL)
            {
                throw std::invalid_argument(
                    "The auto pointer to a menu item is NULL."
                );
            }

            insert_native_menu_item(offset, *p_menu_item);

            m_children.insert(offset, p_menu_item);
        }

        /*!
            \brief Erases the menu items from the children.

            \param first The first iterator to the erased items.
            \param last  The last iterator to the eraed items.
        */
        void erase(const iterator first, const iterator last)
        {

        }


    protected:
        // constructors

        /*!
            \brief Creates a menu item.

            \param handle A handle.
            \param text   A text.
        */
        menu_item(const handle_type handle, const string_type& text)
        :
        m_id(get_and_increment_id()),
        m_handle(handle),
        m_text(text),
        m_menu_observers(),
        m_menu_selected_handler(),
        m_children()
        {}


    private:
        // static functions

        static id_type get_and_increment_id()
        {
            static id_type id = 40001;

            return id++;
        }


        // variables

        id_type m_id;

        handle_type m_handle;

        string_type m_text;

        boost::ptr_vector<menu_observer_type> m_menu_observers;

        boost::signal<void ()> m_menu_selected_handler;

        boost::ptr_vector<menu_item> m_children;


        // functions

        void insert_native_menu_item(
            const_iterator offset,
            menu_item&     menu_item
        )
        const
        {
            std::vector< ::WCHAR> duplicated_text =
                duplicate_text(menu_item.text());

            ::MENUITEMINFOW menu_item_info;
            std::memset(&menu_item_info, 0, sizeof(::MENUITEMINFO));
            menu_item_info.cbSize = sizeof(::MENUITEMINFO);

            if      (menu_item.is_command())
            {
                set_menu_item_info_for_command(
                    menu_item, menu_item_info, duplicated_text
                );
            }
            else if (menu_item.is_popup())
            {
                set_menu_item_info_for_popup(
                    menu_item, menu_item_info, duplicated_text
                );
            }
            else if (menu_item.is_separator())
            {
                set_menu_item_info_for_separator(menu_item, menu_item_info);
            }
            else
            {
                set_menu_item_info_for_unknown(
                    menu_item, menu_item_info, duplicated_text
                );
            }

            const ::BOOL result = ::InsertMenuItem(
                m_handle,
                static_cast< ::UINT>(
                    std::distance(m_children.begin(), offset)
                ),
                TRUE,
                &menu_item_info
            );
            if (result == 0)
            {
                throw std::runtime_error(
                    "Can't insert a native menu command."
                );
            }
        }

        const std::vector< ::WCHAR> duplicate_text(const string_type& text)
        const
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

        void set_menu_item_info_for_command(
            menu_item&             menu_item,
            ::MENUITEMINFOW&       menu_item_info,
            std::vector< ::WCHAR>& text
        )
        const
        {
            menu_item_info.fMask = MIIM_STRING | MIIM_ID;
            menu_item_info.dwTypeData = &text[0];
            menu_item_info.wID = menu_item.id();
        }

        void set_menu_item_info_for_popup(
            menu_item&             menu_item,
            ::MENUITEMINFOW&       menu_item_info,
            std::vector< ::WCHAR>& text
        )
        const
        {
            menu_item_info.fMask = MIIM_STRING | MIIM_SUBMENU;
            menu_item_info.dwTypeData = &text[0];
            menu_item_info.hSubMenu = menu_item.handle();
        }

        void set_menu_item_info_for_separator(
            menu_item&       menu_item,
            ::MENUITEMINFOW& menu_item_info
        )
        const
        {
            menu_item_info.fMask = MIIM_FTYPE;
            menu_item_info.fType = MFT_SEPARATOR;
        }

        void set_menu_item_info_for_unknown(
            menu_item&             menu_item,
            ::MENUITEMINFOW&       menu_item_info,
            std::vector< ::WCHAR>& text
        )
        const
        {
            menu_item_info.fMask = MIIM_STRING | MIIM_STATE;
            menu_item_info.dwTypeData = &text[0];
            menu_item_info.fState = MFS_DISABLED;
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
