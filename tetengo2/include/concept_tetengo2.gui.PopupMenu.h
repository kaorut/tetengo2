/*! \file
    \brief The definition of concept_tetengo2::gui::PopupMenu.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_POPUPMENU_H)
#define CONCEPTTETENGO2_GUI_POPUPMENU_H

#include "concept_tetengo2.gui.Menu.h"
#include "concept_tetengo2.gui.MenuItem.h"


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a popup menu.

        \tparam Type A type.
    */
    template <typename Type>
    class PopupMenu :
        private concept_tetengo2::gui::Menu<Type>,
        private concept_tetengo2::gui::MenuItem<Type>
    {};


}}

#endif
