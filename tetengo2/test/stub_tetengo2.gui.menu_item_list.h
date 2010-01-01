/*! \file
    \brief The definition of stub_tetengo2::gui::menu_item_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MENUITEMLIST_H)
#define STUBTETENGO2_GUI_MENUITEMLIST_H

#include <cstddef>
#include <memory>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MenuItem.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename MenuItem>
    class menu_item_list
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MenuItem<MenuItem>));


    public:
        // types

        typedef MenuItem menu_item_type;

        typedef typename menu_item_type::id_type menu_id_type;

        typedef typename menu_item_type::handle_type menu_handle_type;

        typedef void* iterator;

        typedef const void* const_iterator;


        // constructors and destructor

        menu_item_list(const menu_handle_type menu_handle)
        {}

        virtual ~menu_item_list()
        throw ()
        {}


        // functions

        const_iterator begin()
        const
        {
            return NULL;
        }

        iterator begin()
        {
            return NULL;
        }

        const_iterator end()
        const
        {
            return NULL;
        }

        iterator end()
        {
            return NULL;
        }

        void insert(
            iterator                      offset,
            std::auto_ptr<menu_item_type> p_menu_item
        )
        {}

        void erase(iterator first, iterator last)
        {}

        template <typename PopupMenu>
        menu_item_type* find_by_id(const menu_id_type id)
        {
            return NULL;
        }

        template <typename PopupMenu>
        const menu_item_type* find_by_id(const menu_id_type id)
        const
        {
            return NULL;
        }

        template <typename PopupMenu>
        menu_item_type* find_by_handle(const menu_handle_type handle)
        {
            return NULL;
        }

        template <typename PopupMenu>
        const menu_item_type* find_by_handle(const menu_handle_type handle)
        const
        {
            return NULL;
        }


    };


}}

#endif
