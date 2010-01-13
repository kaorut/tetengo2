/*! \file
    \brief The definition of concept_tetengo2::gui::PopupMenu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_POPUPMENU_H)
#define CONCEPTTETENGO2_GUI_POPUPMENU_H

#include <cstddef>
//#include <memory>

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MenuItem.h"


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a popup menu.

        \tparam Type A type.
    */
    template <typename Type>
    class PopupMenu : private MenuItem<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // usage checks

        BOOST_CONCEPT_USAGE(PopupMenu)
        {}

        
#endif
    };


}}

#endif
