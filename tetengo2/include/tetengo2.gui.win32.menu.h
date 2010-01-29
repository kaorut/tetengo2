/*! \file
    \brief The definition of tetengo2::gui::win32::menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MENU_H)
#define TETENGO2_GUI_WIN32_MENU_H

#include <cassert>
//#include <cstddef>
#include <memory>
#include <stdexcept>
//#include <string>
#include <vector>

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
#include "tetengo2.gui.recursive_menu_iterator.h"


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

        //! The iterator type.
        typedef typename boost::ptr_vector<menu>::iterator iterator;

        //! The const iterator type.
        typedef
            typename boost::ptr_vector<menu>::const_iterator const_iterator;

        //! The recursive iterator type.
        typedef recursive_menu_iterator<menu> recursive_iterator;

        //! The const recursive iterator type.
        typedef recursive_menu_iterator<const menu> const_recursive_iterator;


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

            \return Always NULL.
        */
        virtual handle_type handle()
        const
        {
            return NULL;
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
        virtual const_iterator begin()
        const
        {
            return empty_children().begin();
        }

        /*!
            \brief Returns the first mutable iterator to the children.

            \return The first mutable iterator.
        */
        virtual iterator begin()
        {
            return empty_children().begin();
        }

        /*!
            \brief Returns the last immutable iterator to the children.

            \return The last immutable iterator.
        */
        virtual const_iterator end()
        const
        {
            return empty_children().end();
        }

        /*!
            \brief Returns the last mutable iterator to the children.

            \return The last mutable iterator.
        */
        virtual iterator end()
        {
            return empty_children().end();
        }

        /*!
            \brief Returns the recursive first immutable iterator to this menu
                   and the children.

            The first iterator points to this menu.

            \return The recursive first immutable iterator.
        */
        virtual const_recursive_iterator recursive_begin()
        const
        {
            return const_recursive_iterator();
        }

        /*!
            \brief Returns the recursive first mutable iterator to this menu
                   and the children.

            The first iterator points to this menu.

            \return The recursive first mutable iterator.
        */
        virtual recursive_iterator recursive_begin()
        {
            return recursive_iterator();
        }

        /*!
            \brief Returns the recursive last immutable iterator to this menu
                   and the children.

            \return The recursive last immutable iterator.
        */
        virtual const_recursive_iterator recursive_end()
        const
        {
            return const_recursive_iterator();
        }

        /*!
            \brief Returns the recursive last mutable iterator to this menu
                   and the children.

            \return The recursive last mutable iterator.
        */
        virtual recursive_iterator recursive_end()
        {
            return recursive_iterator();
        }

        /*!
            \brief Inserts a menu as a child.

            \param offset An offset where a menu is inserted.
            \param p_menu An auto pointer to a menu. It must not be NULL.

            \throw std::logic_error Always.
        */
        virtual void insert(const iterator offset, std::auto_ptr<menu> p_menu)
        {
            assert(false);
            throw std::logic_error("Can't insert any menus.");
        }

        /*!
            \brief Erases the menus from the children.

            \param first The first iterator to the erased menus.
            \param last  The last iterator to the eraed menus.

            \throw std::logic_error Always.
        */
        virtual void erase(const iterator first, const iterator last)
        {
            assert(false);
            throw std::logic_error("Can't erase any menus.");
        }

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


    protected:
        // constructors

        /*!
            \brief Creates a menu.

            \param text A text.
        */
        menu(const string_type& text)
        :
        m_id(get_and_increment_id()),
        m_text(text),
        m_menu_observers(),
        m_menu_selected_handler()
        {}


    private:
        // static functions

        static id_type get_and_increment_id()
        {
            static id_type id = 40001;

            return id++;
        }

        static boost::ptr_vector<menu>& empty_children()
        {
            static boost::ptr_vector<menu> singleton;
            assert(singleton.empty());
            return singleton;
        }


        // variables

        id_type m_id;

        string_type m_text;

        boost::ptr_vector<menu_observer_type> m_menu_observers;

        boost::signal<void ()> m_menu_selected_handler;


    };


}}}

#endif
