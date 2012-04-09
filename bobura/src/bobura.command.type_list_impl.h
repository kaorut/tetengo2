/*! \file
    \brief The definition of bobura::command::type_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_TYPELISTIMPL_H)
#define BOBURA_COMMAND_TYPELISTIMPL_H

#include <boost/mpl/pair.hpp>

#include <tetengo2.meta.assoc_list.h>

#include "bobura.command.about.h"
#include "bobura.command.exit.h"
#include "bobura.command.file_property.h"
#include "bobura.command.load_from_file.h"
#include "bobura.command.new_file.h"
#include "bobura.command.nop.h"
#include "bobura.command.save_to_file.h"
#include "bobura.command.type_list.h"


namespace bobura { namespace command
{
    /*!
        \brief The meta function for the type list of the commands.

        \tparam Command            A command type.
        \tparam Model              A model type.
        \tparam AbstractWindow     An abstract window type.
        \tparam FilePropertyDialog A file property dialog type.
        \tparam AboutDialog        An about dialog type.
        \tparam NewFile            A file initialization type.
        \tparam LoadFromFile       A file loading type.
        \tparam SaveToFile         A file saving type.
    */
    template <
        typename Command,
        typename Model,
        typename AbstractWindow,
        typename FilePropertyDialog,
        typename AboutDialog,
        typename NewFile,
        typename LoadFromFile,
        typename SaveToFile
    >
    class type_list
    {
    public:
        // types

        //! The type list for the commands.
        typedef
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::command, Command>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::about, about<Model, AbstractWindow, AboutDialog>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::exit, exit<Model, AbstractWindow>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::file_property, file_property<Model, AbstractWindow, FilePropertyDialog>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::load_from_file, load_from_file<Model, AbstractWindow, LoadFromFile>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::new_file, new_file<Model, AbstractWindow, NewFile>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::nop, nop<Model, AbstractWindow>>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::save_to_file, save_to_file<Model, AbstractWindow, SaveToFile>>,
            tetengo2::meta::assoc_list_end
            >>>>>>>>
            type;


    };


}}


#endif
