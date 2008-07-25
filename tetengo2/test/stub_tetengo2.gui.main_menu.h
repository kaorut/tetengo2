/*! \file
    \brief The definition of stub_tetengo2::gui::win32::main_menu.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MAINMENU_H)
#define STUBTETENGO2_GUI_MAINMENU_H

#include <cstddef>
#include <memory>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.MenuItem.h"
#include "concept_tetengo2.gui.MenuItemList.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename Handle,
        typename MenuItem,
        template <typename MenuHandle, typename MenuItem> class MenuItemList
    >
    class main_menu
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

        typedef Handle handle_type;

        typedef MenuItem menu_item_type;

        typedef MenuItemList<handle_type, menu_item_type> menu_items_type;

        typedef typename menu_items_type::iterator menu_item_iterator;

        typedef
            typename menu_items_type::const_iterator const_menu_item_iterator;


        // constructors and destructor

        main_menu()
        {}

        virtual ~main_menu()
        throw ()
        {}


        // functions

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


    };


}}

#endif
