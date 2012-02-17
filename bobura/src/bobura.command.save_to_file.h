/*! \file
    \brief The definition of bobura::command::save_to_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_SAVETOFILE_H)
#define BOBURA_COMMAND_SAVETOFILE_H

#include <utility>

#include <tetengo2.text.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a save-to-file command.

        \tparam Model           A model type.
        \tparam AbstractWindow  An abstract window type.
        \tparam MessageBox      A message box type.
        \tparam FileSaveDialog  A file save dialog type.
        \tparam Writer          A writer type.
        \tparam MessageCatalog  A message catalog type.
    */
    template <
        typename Model,
        typename AbstractWindow,
        typename MessageBox,
        typename FileSaveDialog,
        typename Writer,
        typename MessageCatalog
    >
    class save_to_file
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The message box type.
        typedef MessageBox message_box_type;

        //! The file save dialog type.
        typedef FileSaveDialog file_save_dialog_type;

        //! The writer type.
        typedef Writer writer_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a save-to-file command.

            \param ask_file_path     Set true to show a file selection dialog.
                                     When the model does not have a path, a
                                     file selection dialog is always shown.
            \param writer            A writer.
            \param message_catalog   A message catalog.
        */
        save_to_file(
            const bool                    ask_file_path,
            writer_type&                  writer,
            const message_catalog_type&   message_catalog
        )
        :
        m_ask_file_path(ask_file_path),
        m_writer(writer),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Executes the command.

            \param model  A model.
            \param parent A parent window.
        */
        void operator()(model_type& model, abstract_window_type& parent)
        const
        {
            path_type path;
            if (!model.has_path() || m_ask_file_path)
            {
                file_save_dialog_type dialog(
                    m_message_catalog.get(
                        TETENGO2_TEXT("Dialog:FileOpenSave:SaveAs")
                    ),
                    model.has_path() ?
                        boost::make_optional(model.path()) : boost::none,
                    make_file_filters(),
                    parent
                );
                dialog.do_modal();

                path = dialog.result();
                if (path.empty()) return;
            }
            else
            {
                path = model.path();
            }

        }


    private:
        // types

        typedef typename abstract_window_type::string_type string_type;

        typedef typename file_save_dialog_type::path_type path_type;

        typedef typename model_type::timetable_type timetable_type;


        // variables

        const bool m_ask_file_path;

        writer_type& m_writer;

        const message_catalog_type& m_message_catalog;


        // functions

        typename file_save_dialog_type::file_filters_type
        make_file_filters()
        const
        {
            typename file_save_dialog_type::file_filters_type filters;

            filters.push_back(
                std::make_pair(
                    m_message_catalog.get(
                        TETENGO2_TEXT("Dialog:FileOpenSave:Timetable Files")
                    ),
                    string_type(TETENGO2_TEXT("*.btt"))
                )
            );
            filters.push_back(
                std::make_pair(
                    m_message_catalog.get(
                        TETENGO2_TEXT("Dialog:FileOpenSave:All Files")
                    ),
                    string_type(TETENGO2_TEXT("*.*"))
                )
            );

            return filters;
        }


    };


}}


#endif
