/*! \file
    \brief The definition of concept_tetengo2::gui::MenuSeparator.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MENUSEPARATOR_H)
#define CONCEPTTETENGO2_GUI_MENUSEPARATOR_H

#include "concept_tetengo2.gui.MenuItem.h"


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a menu separator.

        \tparam Type A type.
    */
    template <typename Type>
    class MenuSeparator : private MenuItem<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::base_type base_type;


        // usage checks

        BOOST_CONCEPT_USAGE(MenuSeparator)
        {}

        
#endif
    };


}}

#endif
