/*! \file
    \brief The definition of bobura::load_save::save_to_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_SAVETOFILE_H)
#define BOBURA_LOADSAVE_SAVETOFILE_H

#include <utility>

#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/optional.hpp>

#include <tetengo2.text.h>


namespace bobura { namespace load_save
{
    /*!
        \brief The class template for a file saving.

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
            \brief Creates a file saving.

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
            \brief Saves the model to a file.

            \param model  A model.
            \param parent A parent window.

            \retval true   When the model has been saved.
            \retval false  Otherwise.
        */
        bool operator()(model_type& model, abstract_window_type& parent)
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
                if (path.empty())
                    return false;
            }
            else
            {
                path = model.path();
            }

            const boost::filesystem::path temporary_path =
                make_temporary_path();
            boost::filesystem::ofstream output_stream(
                temporary_path, std::ios_base::binary
            );
            if (!output_stream)
            {
                create_cant_create_file_message_box(
                    temporary_path, parent
                )->do_modal();
                return false;
            }

            //m_writer.write(model.timetable(), output_stream);

            boost::filesystem::rename(temporary_path, path);

            return true;
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

        std::unique_ptr<message_box_type> create_cant_create_file_message_box(
            const path_type&      path,
            abstract_window_type& parent
        )
        const
        {
            return tetengo2::make_unique<message_box_type>(
                parent,
                m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                m_message_catalog.get(
                    TETENGO2_TEXT("Message:File:Can't create the file.")
                ),
                path.template string<string_type>(),
                message_box_type::button_style_type::ok(false),
                message_box_type::icon_style_error
            );
        }

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

        boost::filesystem::path make_temporary_path()
        const
        {
            const boost::filesystem::path temporary_directory =
                boost::filesystem::temp_directory_path();
            const boost::filesystem::path unique_path =
                boost::filesystem::unique_path();

            return temporary_directory / unique_path;
        }


    };


}}


#endif
