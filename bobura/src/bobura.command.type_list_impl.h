/*! \file
    \brief The definition of bobura::type_list.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_TYPELISTIMPL_H)
#define BOBURA_COMMAND_TYPELISTIMPL_H

//#include <boost/concept_check.hpp>
#include <boost/function.hpp>
#include <boost/mpl/pair.hpp>

#include <concept_tetengo2.gui.Window.h>
#include <tetengo2.meta.assoc_list.h>

#include "bobura.command.about.h"
#include "bobura.command.exit.h"
#include "bobura.command.nop.h"
#include "bobura.command.type_list.h"
#include "concept_bobura.AboutDialog.h"


namespace bobura { namespace command
{
    /*!
        \brief The meta function for the type list of bobura::command.

        \tparam Window      A window type. It must conform to
                            concept_tetengo2::gui::Window<Window>.
        \tparam AboutDialog An about dialog type. It must conform to
                            concept_bobura::AboutDialog<AboutDialog>.
    */
    template <typename Window, typename AboutDialog>
    class type_list
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Window<Window>));
        BOOST_CONCEPT_ASSERT((concept_bobura::AboutDialog<AboutDialog>));


    public:
        // types

        typedef
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::command, boost::function<void ()> >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::about, about<AboutDialog> >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::exit, exit<Window> >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::nop, nop >,
            tetengo2::meta::assoc_list_end
            > > > >
            type;
                

    };




}}


#endif
