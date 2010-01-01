/*! \file
    \brief The definition of tetengo2::gui::win32::main_menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MAINMENU_H)
#define TETENGO2_GUI_WIN32_MAINMENU_H

//#include <cstddef>
//#include <memory>
//#include <stdexcept>

//#include <boost/concept_check.hpp>
//#include <boost/noncopyable.hpp>

#include "concept_tetengo2.gui.PopupMenu.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a main menu for Win32 platforms.

        \tparam PopupMenu A popup menu type. It must conform to
                          concept_tetengo2::gui::PopupMenu<PopupMenu>.
   */
    template <typename PopupMenu>
    class main_menu : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::PopupMenu<PopupMenu>));


    public:
        // types

        //! The popup menu type.
        typedef PopupMenu popup_menu_type;

        //! The menu item type.
        typedef typename popup_menu_type::menu_item_type menu_item_type;

        //! The menu item id type.
        typedef typename menu_item_type::id_type menu_item_id_type;

        //! The handle type.
        typedef typename menu_item_type::handle_type handle_type;

        //! The menu items type.
        typedef typename popup_menu_type::menu_items_type menu_items_type;

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
            if (::IsMenu(m_handle) != 0)
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
        const menu_item_type* find_by_id(const menu_item_id_type id)
        const
        {
            return m_menu_items.find_by_id<popup_menu_type>(id);
        }

        /*!
            \brief Finds a menu item by the specified id.

            If the menu item does not exist, it returns NULL.

            \param id An id.

            \return The pointer to the menu item.
        */
        menu_item_type* find_by_id(const menu_item_id_type id)
        {
            return m_menu_items.find_by_id<popup_menu_type>(id);
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
            return m_menu_items.find_by_handle<popup_menu_type>(handle);
        }

        /*!
            \brief Finds a menu item by the specified handle.

            If the menu item does not exist, it returns NULL.

            \param handle A handle.

            \return The pointer to the menu item.
        */
        menu_item_type* find_by_handle(const handle_type handle)
        {
            return m_menu_items.find_by_handle<popup_menu_type>(handle);
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
