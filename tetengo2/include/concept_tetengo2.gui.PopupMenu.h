/*! \file
    \brief The definition of concept_tetengo2::gui::PopupMenu.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_POPUPMENU_H)
#define CONCEPTTETENGO2_GUI_POPUPMENU_H

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Menu.h"


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a popup menu.

        \tparam Type A type.
    */
    template <typename Type>
    class PopupMenu : private Menu<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::base_type base_type;


        // usage checks

        BOOST_CONCEPT_USAGE(PopupMenu)
        {}

        
#endif
    };


}}

#endif
