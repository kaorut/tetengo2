/*! \file
    \brief The definition of stub_tetengo2::gui::popup_menu.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_POPUPMENU_H)
#define STUBTETENGO2_GUI_POPUPMENU_H

#include <cstddef>
#include <memory>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.String.h"
#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.MenuItem.h"
#include "concept_tetengo2.gui.MenuItemList.h"
#include "tetengo2.gui.menu_item.h"
#include "tetengo2.gui.win32.menu_item_list.h"


namespace stub_tetengo2 { namespace gui
{
    template <
        typename Id,
        typename Handle,
        typename String,
        template <typename MenuItem> class MenuItemList
    >
    class popup_menu : public tetengo2::gui::menu_item<Id, Handle, String>
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

        const menu_item_type* find(const id_type id)
        const
        {
            return NULL;
        }

        menu_item_type* find(const id_type id)
        {
            return NULL;
        }


    };


}}

#endif
