/*! \file
    \brief The definition of bobura::load_save::save_to_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_SAVETOFILE_H)
#define BOBURA_LOADSAVE_SAVETOFILE_H

#include <ios>
#include <memory>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/optional.hpp>
#include <boost/system/system_error.hpp>

#include <tetengo2.text.h>


namespace bobura { namespace load_save
{
    /*!
        \brief The class template for a file saving.

        \tparam Model           A model type.
        \tparam AbstractWindow  An abstract window type.
        \tparam MessageBox      A message box type.
        \tparam FileSaveDialog  A file save dialog type.
        \tparam WriterSelector  A writer selector type.
        \tparam WriterSet       A writer set type.
        \tparam MessageCatalog  A message catalog type.
    */
    template <
        typename Model,
        typename AbstractWindow,
        typename MessageBox,
        typename FileSaveDialog,
        typename WriterSelector,
        typename WriterSet,
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

        //! The writer selector type.
        typedef WriterSelector writer_selector_type;

        //! The writer set type.
        typedef WriterSet writer_set_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a file saving.

            \param ask_file_path     Set true to show a file selection dialog.
                                     When the model does not have a path, a file selection dialog is always shown.
            \param message_catalog   A message catalog.
        */
        save_to_file(const bool ask_file_path, const message_catalog_type& message_catalog)
        :
        m_ask_file_path(ask_file_path),
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
                    m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:SaveAs")),
                    model.has_path() ? boost::make_optional(model.path()) : boost::none,
                    make_file_filters(),
                    parent
                );
                const bool ok = dialog.do_modal();
                if (!ok)
                    return false;

                path = dialog.result();
            }
            else
            {
                if (!model.changed())
                    return false;

                path = model.path();
            }

            const path_type temporary_path = path.parent_path() / boost::filesystem::unique_path();
            {
                writer_selector_type writer(writer_set_type::create_writers(), path);
                if (!writer.selects(path))
                {
                    if (m_ask_file_path)
                        return false;
                    else
                        return save_to_file(true, m_message_catalog)(model, parent);
                }

                boost::filesystem::ofstream output_stream(temporary_path, std::ios_base::binary);
                if (!output_stream)
                {
                    create_cant_create_temporary_file_message_box(temporary_path, parent)->do_modal();
                    return false;
                }

                writer.write(model.timetable(), output_stream);
            }

            {
                boost::system::error_code error_code;
                boost::filesystem::rename(temporary_path, path, error_code);
                if (error_code)
                {
                    create_cant_write_to_file_message_box(path, parent)->do_modal();
                    return false;
                }
            }

            model.set_path(path);

            return true;
        }


    private:
        // types

        typedef typename abstract_window_type::string_type string_type;

        typedef typename file_save_dialog_type::path_type path_type;

        typedef typename model_type::timetable_type timetable_type;


        // variables

        const bool m_ask_file_path;

        const message_catalog_type& m_message_catalog;


        // functions

        std::unique_ptr<message_box_type> create_cant_create_temporary_file_message_box(
            const path_type&      path,
            abstract_window_type& parent
        )
        const
        {
            return
                tetengo2::make_unique<message_box_type>(
                    parent,
                    m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                    m_message_catalog.get(TETENGO2_TEXT("Message:File:Can't create a temporary file.")),
                    path.template string<string_type>(),
                    message_box_type::button_style_type::ok(false),
                    message_box_type::icon_style_type::error
                );
        }

        std::unique_ptr<message_box_type> create_cant_write_to_file_message_box(
            const path_type&      path,
            abstract_window_type& parent
        )
        const
        {
            return
                tetengo2::make_unique<message_box_type>(
                    parent,
                    m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                    m_message_catalog.get(TETENGO2_TEXT("Message:File:Can't write to the file.")),
                    path.template string<string_type>(),
                    message_box_type::button_style_type::ok(false),
                    message_box_type::icon_style_type::error
                );
        }

        typename file_save_dialog_type::file_filters_type make_file_filters()
        const
        {
            typename file_save_dialog_type::file_filters_type filters;

            filters.emplace_back(
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:Timetable Files")),
                string_type(TETENGO2_TEXT("btt"))
            );
            filters.emplace_back(
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:Timetable Files (Compressed)")),
                string_type(TETENGO2_TEXT("btt_bz2"))
            );
            filters.emplace_back(
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpenSave:All Files")), string_type(TETENGO2_TEXT("*"))
            );

            return filters;
        }


    };


}}


#endif
