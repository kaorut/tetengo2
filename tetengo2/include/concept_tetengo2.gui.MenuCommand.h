/*! \file
    \brief The definition of concept_tetengo2::gui::MenuCommand.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(CONCEPTTETENGO2_GUI_MENUCOMMAND_H)
#define CONCEPTTETENGO2_GUI_MENUCOMMAND_H

//#include <boost/concept_check.hpp>

#include "concept_tetengo2.gui.MenuItem.h"


namespace concept_tetengo2 { namespace gui
{
    /*!
        \brief The concept check class template for a menu command.

        \tparam Type A type.
    */
    template <typename Type>
    class MenuCommand : private MenuItem<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::command_type command_type;


        // usage checks

        BOOST_CONCEPT_USAGE(MenuCommand)
        {
            m_object.set_command(command_type());

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const command_type command = object.command();
            boost::ignore_unused_variable_warning(command);
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
