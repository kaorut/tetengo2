/*! \file
    \brief The definition of tetengo2::gui::popup_menu.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_POPUPMENU_H)
#define TETENGO2_GUI_WIN32_POPUPMENU_H

//#include <cstddef>
//#include <memory>
//#include <stdexcept>
//#include <string>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MenuItemList.h"
#include "tetengo2.gui.menu_item.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a popup menu.

        \tparam Id           A ID type to the native interface. It must
                             conform to boost::UnsignedInteger<Id>.
        \tparam Handle       A handle type to the native interface. It must
                             conform to concept_tetengo2::gui::Handle<Handle>.
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
        \tparam MenuItemList A menu item list type. It must conform to
                             concept_tetengo2::gui::MenuItemList<MenuItemList>.
   */
    template <
        typename Id,
        typename Handle,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename MenuObserver,
        typename MenuItemList
    >
    class popup_menu :
        public menu_item<Id, Handle, String, Encode, MenuObserver>
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
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::MenuItemList<MenuItemList>
        ));


    public:
        // types

        //! The menu item type.
        typedef
            menu_item<
                id_type, handle_type, string_type, Encode, menu_observer_type
            >
            menu_item_type;

        //! The menu items type.
        typedef MenuItemList menu_items_type;

        //! The menu item iterator type.
        typedef typename menu_items_type::iterator menu_item_iterator;

        //! The const menu item iterator type.
        typedef
            typename menu_items_type::const_iterator const_menu_item_iterator;


        // constructors and destructor

        /*!
            \brief Creates a popup menu.

            \param text A text.
        */
        popup_menu(const string_type& text)
        :
        menu_item(text),
        m_handle(create_menu()),
        m_menu_items(m_handle)
        {}

        /*!
            \brief Destroys the popup menu.
        */
        virtual ~popup_menu()
        throw ()
        {
            if (::IsMenu(m_handle) != 0)
                ::DestroyMenu(m_handle);
        }


        // functions

        // The document will be derived from
        // tetengo2::gui::menu_item::is_command.
        virtual bool is_command()
        const
        {
            return false;
        }

        // The document will be derived from
        // tetengo2::gui::menu_item::is_popup.
        virtual bool is_popup()
        const
        {
            return true;
        }

        // The document will be derived from
        // tetengo2::gui::menu_item::is_separator.
        virtual bool is_separator()
        const
        {
            return false;
        }

        /*!
            \brief Returns the handle.

            \return The handle.
        */
        virtual handle_type handle()
        const
        {
            return m_handle;
        }

        /*!
            \brief Returns the first immutable iterator to the menu items.

            \return The first immutable iterator.
        */
        const_menu_item_iterator menu_item_begin()
        const
        {
            return m_menu_items.begin();
        }

        /*!
            \brief Returns the first mutable iterator to the menu items.

            \return The first mutable iterator.
        */
        menu_item_iterator menu_item_begin()
        {
            return m_menu_items.begin();
        }

        /*!
            \brief Returns the last immutable iterator to the menu items.

            \return The last immutable iterator.
        */
        const_menu_item_iterator menu_item_end()
        const
        {
            return m_menu_items.end();
        }

        /*!
            \brief Returns the last mutable iterator to the menu items.

            \return The last mutable iterator.
        */
        menu_item_iterator menu_item_end()
        {
            return m_menu_items.end();
        }

        /*!
            \brief Inserts a menu item.

            \param offset      An offset where a menu item is inserted.
            \param p_menu_item An auto pointer to a menu item. It must not be
                               NULL.
        */
        void insert(
            menu_item_iterator            offset,
            std::auto_ptr<menu_item_type> p_menu_item
        )
        {
            m_menu_items.insert(offset, p_menu_item);
        }

        /*!
            \brief Erases the menu items.

            \param first The first iterator to the erased items.
            \param last  The last iterator to the eraed items.
        */
        void erase(menu_item_iterator first, menu_item_iterator last)
        {
            m_menu_items.erase(first, last);
        }

        /*!
            \brief Finds a menu item by the specified id.

            If the menu item does not exist, it returns NULL.

            \param id An id.

            \return The pointer to the menu item.
        */
        const menu_item_type* find_by_id(const id_type id)
        const
        {
            return m_menu_items.find_by_id<popup_menu>(id);
        }

        /*!
            \brief Finds a menu item by the specified id.

            If the menu item does not exist, it returns NULL.

            \param id An id.

            \return The pointer to the menu item.
        */
        menu_item_type* find_by_id(const id_type id)
        {
            return m_menu_items.find_by_id<popup_menu>(id);
        }

        /*!
            \brief Finds a menu item by the specified handle.

            If the menu item does not exist, it returns NULL.

            \param handle A handle.

            \return The pointer to the menu item.
        */
        const menu_item_type* find_by_handle(const handle_type handle)
        const
        {
            return m_menu_items.find_by_handle<popup_menu>(handle);
        }

        /*!
            \brief Finds a menu item by the specified handle.

            If the menu item does not exist, it returns NULL.

            \param handle A handle.

            \return The pointer to the menu item.
        */
        menu_item_type* find_by_handle(const handle_type handle)
        {
            return m_menu_items.find_by_handle<popup_menu>(handle);
        }


    private:
        // static functions

        handle_type create_menu()
        {
            const handle_type handle = ::CreatePopupMenu();

            if (handle == NULL)
                throw std::runtime_error("Can't create a main menu.");

            return handle;
        }


        // variables

        const handle_type m_handle;

        menu_items_type m_menu_items;


    };


}}}

#endif
