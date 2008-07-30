/*! \file
    \brief The definition of tetengo2::gui::win32::main_menu.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MAINMENU_H)
#define TETENGO2_GUI_WIN32_MAINMENU_H

//#include <cstddef>
//#include <memory>
//#include <stdexcept>

//#include <boost/concept_check.hpp>
//#include <boost/noncopyable.hpp>

#include "concept_tetengo2.gui.MenuItemList.h"
#include "tetengo2.gui.win32.menu_item_list.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a main menu for Win32 platforms.

        \tparam Handle       A handle type to the native interface. It must
                             conform to concept_tetengo2::gui::Handle<Handle>.
        \tparam MenuItem     A menu item type. It must conform to
                             concept_tetengo2::gui::MenuItem<MenuItem>.
        \tparam MenuItemList A menu item list type. The type
                             MenuItemList<Handle, MenuItem> must conform to
                             concept_tetengo2::gui::MenuItemList<MenuItemList<Handle, MenuItem> >.
   */
    template <
        typename Handle,
        typename MenuItem,
        template <typename MenuHandle, typename MenuItem> class MenuItemList
    >
    class main_menu : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MenuItem<MenuItem>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::MenuItemList<
                MenuItemList<Handle, MenuItem>
            >
        ));


    public:
        // types

        //! The handle type.
        typedef Handle handle_type;

        //! The menu item type.
        typedef MenuItem menu_item_type;

        //! The menu items type.
        typedef MenuItemList<handle_type, menu_item_type> menu_items_type;

        //! The menu item iterator type.
        typedef typename menu_items_type::iterator menu_item_iterator;

        //! The const menu item iterator type.
        typedef
            typename menu_items_type::const_iterator const_menu_item_iterator;


        // constructors and destructor

        /*!
            \brief Creates a main menu.
        */
        main_menu()
        :
        m_handle(create_menu()),
        m_menu_items(m_handle)
        {}

        /*!
            \brief Destroys the main menu.
        */
        ~main_menu()
        throw ()
        {
            ::DestroyMenu(m_handle);
        }


        // functions

        /*!
            \brief Returns the handle.

            \return The handle.
        */
        handle_type handle()
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
            \brief Insers a menu item.

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


    private:
        // static functions

        handle_type create_menu()
        {
            const handle_type handle = ::CreateMenu();

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
