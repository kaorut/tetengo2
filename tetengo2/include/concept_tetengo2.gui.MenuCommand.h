/*! \file
    \brief The definition of concept_tetengo2::gui::MenuCommand.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MENUCOMMAND_H)
#define CONCEPTTETENGO2_GUI_MENUCOMMAND_H

#include "concept_tetengo2.gui.MenuItem.h"


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a menu command.

        \tparam Type A type.
    */
    template <typename Type>
    class MenuCommand : private MenuItem<Type>
    {};


}}

#endif
