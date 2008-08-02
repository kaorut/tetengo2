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

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MenuItemList.h"
#include "tetengo2.gui.menu_item.h"
#include "tetengo2.gui.win32.menu_item_list.h"


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
        \tparam MenuItemList A menu item list type. The type
                             MenuItemList<Handle, MenuItem, PopupMenu> must
                             conform to
                             concept_tetengo2::gui::MenuItemList<MenuItemList<Handle, MenuItem, PopupMenu> >.
   */
    template <
        typename Id,
        typename Handle,
        typename String,
        template <typename MenuItem> class MenuItemList
    >
    class popup_menu : public menu_item<Id, Handle, String>
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Id>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::MenuItemList<
                MenuItemList<menu_item<Id, Handle, String> >
            >
        ));


    public:
        // types

        //! The menu item type.
        typedef menu_item<id_type, handle_type, string_type> menu_item_type;

        //! The menu items type.
        typedef MenuItemList<menu_item_type> menu_items_type;

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

        /*!
            \brief Find the menu item with the specified id.

            If the menu item does not exist, it returns NULL.

            \param id An id.

            \return The pointer to the menu item.
        */
        const menu_item_type* find(const id_type id)
        const
        {
            for (
                const_menu_item_iterator i = menu_item_begin();
                i != menu_item_end();
                ++i
            )
            {
                if (i->id() == id) return &*i;

                if (i->is_popup())
                {
                    assert(dynamic_cast<const popup_menu*>(&*i) != NULL);

                    const popup_menu& popup =
                        static_cast<const popup_menu&>(*i);
                    const menu_item_type* const p_found = popup.find(id);
                    if (p_found != NULL) return p_found;
                }
            }

            return NULL;
        }

        /*!
            \brief Find the menu item with the specified id.

            If the menu item does not exist, it returns NULL.

            \param id An id.

            \return The pointer to the menu item.
        */
        menu_item_type* find(const id_type id)
        {
            for (
                menu_item_iterator i = menu_item_begin();
                i != menu_item_end();
                ++i
            )
            {
                if (i->id() == id) return &*i;

                if (i->is_popup())
                {
                    assert(dynamic_cast<popup_menu*>(&*i) != NULL);

                    popup_menu& popup = static_cast<popup_menu&>(*i);
                    menu_item_type* const p_found = popup.find(id);
                    if (p_found != NULL) return p_found;
                }
            }

            return NULL;
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
