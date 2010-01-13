/*! \file
    \brief The definition of concept_tetengo2::gui::MainMenu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MAINMENU_H)
#define CONCEPTTETENGO2_GUI_MAINMENU_H

#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MenuItem.h"


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a main menu.

        \tparam Type A type.
    */
    template <typename Type>
    class MainMenu : private MenuItem<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(MainMenu)
        {}

        
#endif
    };


}}

#endif
