/*! \file
    \brief The definition of bobura::command::type_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_TYPELISTIMPL_H)
#define BOBURA_COMMAND_TYPELISTIMPL_H

#include <functional>

#include <boost/mpl/pair.hpp>

#include <tetengo2.meta.assoc_list.h>

#include "bobura.command.about.h"
#include "bobura.command.exit.h"
#include "bobura.command.nop.h"
#include "bobura.command.type_list.h"


namespace bobura { namespace command
{
    /*!
        \brief The meta function for the type list of the commands.

        \tparam Window      A window type.
        \tparam AboutDialog An about dialog type.
    */
    template <typename Window, typename AboutDialog>
    class type_list
    {
    public:
        // types

        //! The type list for the commands.
        typedef
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::command, std::function<void ()> >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::about, about<AboutDialog>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::exit, exit<Window>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::nop, nop>,
            tetengo2::meta::assoc_list_end
            >>>>
            type;
                

    };




}}


#endif
