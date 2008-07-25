/*! \file
    \brief The definition of stub_tetengo2::gui::win32::main_menu.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_MAINMENU_H)
#define STUBTETENGO2_GUI_MAINMENU_H

#include <cstddef>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Handle.h"
#include "concept_tetengo2.gui.MenuItem.h"


namespace stub_tetengo2 { namespace gui
{
    template <typename Handle, typename MenuItem>
    class main_menu
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Handle<Handle>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::MenuItem<MenuItem>));


    public:
        // types

        typedef Handle handle_type;

        typedef MenuItem menu_item_type;


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


    };


}}

#endif
