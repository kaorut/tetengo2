/*! \file
    \brief The definition of bobura::command::type_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_TYPELISTIMPL_H)
#define BOBURA_COMMAND_TYPELISTIMPL_H

#include <functional>

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

        \tparam AbstractWindow     An abstract window type.
        \tparam Window             A window type.
        \tparam MessageBox         A message box type.
        \tparam FileOpenDialog     A file open dialog type.
        \tparam FileSaveDialog     A file save dialog type.
        \tparam FilePropertyDialog A file property dialog type.
        \tparam AboutDialog        An about dialog type.
        \tparam Model              A model type.
        \tparam ConfirmFileSave    A file save confirmation type.
        \tparam Reader             A reader type.
        \tparam Writer             A writer type.
        \tparam MessageCatalog     A message catalog type.
    */
    template <
        typename AbstractWindow,
        typename Window,
        typename MessageBox,
        typename FileOpenDialog,
        typename FileSaveDialog,
        typename FilePropertyDialog,
        typename AboutDialog,
        typename Model,
        typename ConfirmFileSave,
        typename Reader,
        typename Writer,
        typename MessageCatalog
    >
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
                boost::mpl::pair<
                    type::file_property, file_property<
                        FilePropertyDialog, Model
                    >
                >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::load_from_file,
                    load_from_file<
                        MessageBox,
                        FileOpenDialog,
                        Model,
                        ConfirmFileSave,
                        Reader,
                        MessageCatalog
                    >
                >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::new_file,
                    new_file<typename Window::base_type, Model, ConfirmFileSave>
                >,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<type::nop, nop>,
            tetengo2::meta::assoc_list<
                boost::mpl::pair<
                    type::save_to_file,
                    save_to_file<
                        MessageBox,
                        FileSaveDialog,
                        Model,
                        Writer,
                        MessageCatalog
                    >
                >,
            tetengo2::meta::assoc_list_end
            >>>>>>>>
            type;


    };




}}


#endif
