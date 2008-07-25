/*! \file
    \brief The definition of stub_tetengo2::gui::win32::menu_item_list.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MENUITEMLIST_H)
#define STUBTETENGO2_GUI_MENUITEMLIST_H

#include <cstddef>
#include <memory>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.MenuItem.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename MenuHandle, typename MenuItem>
    class menu_item_list
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<MenuHandle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MenuItem<MenuItem>));


    public:
        // types

        typedef MenuHandle menu_handle_type;

        typedef MenuItem menu_item_type;

        //! The iterator type.
        typedef void* iterator;

        //! The const iterator type.
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


    };


}}

#endif
