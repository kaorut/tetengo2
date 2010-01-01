/*! \file
    \brief The definition of stub_tetengo2::gui::popup_menu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_POPUPMENU_H)
#define STUBTETENGO2_GUI_POPUPMENU_H

//#include <cstddef>
//#include <memory>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MenuItem.h"
#include "concept_tetengo2.gui.MenuItemList.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename MenuItem, typename MenuItemList>
    class popup_menu : public MenuItem
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MenuItem<MenuItem>));
        BOOST_CONCEPT_ASSERT((
            concept_tetengo2::gui::MenuItemList<MenuItemList>
        ));


    public:
        // types

        typedef typename MenuItem::id_type id_type;

        typedef typename MenuItem::handle_type handle_type;

        typedef typename MenuItem::string_type string_type;

        typedef
            typename MenuItem::encode_from_native_type
            encode_from_native_type;

        typedef
            typename MenuItem::encode_to_native_type encode_to_native_type;

        typedef typename MenuItem::menu_observer_type menu_observer_type;

        typedef MenuItem menu_item_type;

        typedef MenuItemList menu_items_type;

        typedef typename menu_items_type::iterator menu_item_iterator;

        typedef
            typename menu_items_type::const_iterator const_menu_item_iterator;


        // constructors and destructor

        popup_menu(const string_type& text)
        :
        menu_item(text)
        {}

        virtual ~popup_menu()
        throw ()
        {}


        // functions

        virtual bool is_command()
        const
        {
            return false;
        }

        virtual bool is_popup()
        const
        {
            return false;
        }

        virtual bool is_separator()
        const
        {
            return false;
        }

        virtual handle_type handle()
        const
        {
            return NULL;
        }

        const_menu_item_iterator menu_item_begin()
        const
        {
            return NULL;
        }

        menu_item_iterator menu_item_begin()
        {
            return NULL;
        }

        const_menu_item_iterator menu_item_end()
        const
        {
            return NULL;
        }

        menu_item_iterator menu_item_end()
        {
            return NULL;
        }

        void insert(
            menu_item_iterator            offset,
            std::auto_ptr<menu_item_type> p_menu_item
        )
        {}

        void erase(menu_item_iterator first, menu_item_iterator last)
        {}

        const menu_item_type* find_by_id(const id_type id)
        const
        {
            return NULL;
        }

        menu_item_type* find_by_id(const id_type id)
        {
            return NULL;
        }

        const menu_item_type* find_by_handle(const handle_type handle)
        const
        {
            return NULL;
        }

        menu_item_type* find_by_handle(const handle_type handle)
        {
            return NULL;
        }


    };


}}

#endif
