/*! \file
    \brief The definition of concept_tetengo2::gui::MenuCommand.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MENUCOMMAND_H)
#define CONCEPTTETENGO2_GUI_MENUCOMMAND_H

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.Menu.h"


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a menu command.

        \tparam Type A type.
    */
    template <typename Type>
    class MenuCommand : private Menu<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::base_type base_type;


        // usage checks

        BOOST_CONCEPT_USAGE(MenuCommand)
        {}

        
#endif
    };


}}

#endif
