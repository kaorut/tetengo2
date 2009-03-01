/*! \file
    \brief The definition of bobura::command::command_type_list.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_COMMANDTYPELIST_H)
#define BOBURA_COMMAND_COMMANDTYPELIST_H

//#include <boost/concept_check.hpp>
#include <boost/function.hpp>

#include "bobura.command.about.h"
#include "bobura.command.exit.h"
#include "bobura.command.nop.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for a command type list.

        \tparam Window A window type. It must conform to
                       concept_tetengo2::gui::Window<Window>.
        \tparam Dialog A dialog type. It must conform to
                       concept_tetengo2::gui::Dialog<Dialog>.
    */
    template <typename Window, typename Dialog>
    class command_type_list
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Window<Window>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Dialog<Dialog>));


    public:
        // types

        //! The command type;
        typedef boost::function<void ()> command_type;

        //! The about command type.
        typedef about<Dialog> about_type;

        //! The exit command type.
        typedef exit<Window> exit_type;

        //! The nop command type.
        typedef nop nop_type;


    private:
        // forbidden operations

        command_type_list();


    };


}}

#endif
