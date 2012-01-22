/*! \file
    \brief The definition of bobura::command::load_from_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_LOADFROMFILE_H)
#define BOBURA_COMMAND_LOADFROMFILE_H

#include <ios>
//#include <memory>
//#include <utility>

#include <boost/filesystem/fstream.hpp>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a load-from-file command.

        \tparam MessageBox     A message box type.
        \tparam FileOpenDialog A file open dialog type.
        \tparam Model          A model type.
        \tparam Reader         A reader type.
        \tparam MessageCatalog A message catalog type.
    */
    template <
        typename MessageBox,
        typename FileOpenDialog,
        typename Model,
        typename Reader,
        typename MessageCatalog
    >
    class load_from_file
    {
    public:
        // types

        //! The message box type.
        typedef MessageBox message_box_type;

        //! The file open dialog type.
        typedef FileOpenDialog file_open_dialog_type;

        //! The window type.
        typedef typename file_open_dialog_type::widget_type window_type;

        //! The model type.
        typedef Model model_type;

        //! The reader type.
        typedef Reader reader_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a load-from-file command.

            \param window          A parent window.
            \param model           A model.
            \param reader          A reader.
            \param message_catalog A message catalog.
        */
        load_from_file(
            window_type&                 window,
            model_type&                  model,
            reader_type&                 reader,
            const message_catalog_type&  message_catalog
        )
        :
        m_window(window),
        m_model(model),
        m_reader(reader),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Executes the command.
        */
        void operator()()
        const
        {
            const typename message_box_type::button_id_type selected_button =
                message_box_type(
                    m_window,
                    m_message_catalog.get(TETENGO2_TEXT("App:Bobura")),
                    m_message_catalog.get(
                        TETENGO2_TEXT(
                            "Message:File:The file has been changed. Do you want to save the changes?"
                        )
                    ),
                    string_type(),
                    message_box_type::button_style_type::yes_no(
                        true,
                        string_type(TETENGO2_TEXT("&Save")),
                        string_type(TETENGO2_TEXT("&Don't save"))
                    ),
                    message_box_type::icon_style_warning
                ).do_modal();
            if (selected_button == message_box_type::button_cancel)
                return;

            file_open_dialog_type dialog(
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpen:Open")),
                make_file_filters(),
                m_window
            );
            dialog.do_modal();

            const typename file_open_dialog_type::path_type path =
                dialog.result();
            if (path.empty()) return;

            boost::filesystem::ifstream input_stream(
                path, std::ios_base::binary
            );
            if (!input_stream)
                return;

            std::unique_ptr<timetable_type> p_timetable =
                m_reader.read(input_stream);
            if (!p_timetable)
                return;

            m_model.reset_timetable(std::move(p_timetable));
        }


    private:
        // types

        typedef typename window_type::string_type string_type;

        typedef typename model_type::timetable_type timetable_type;


        // variables

        window_type& m_window;

        model_type& m_model;

        reader_type& m_reader;

        const message_catalog_type& m_message_catalog;


        // functions

        typename file_open_dialog_type::file_filters_type
        make_file_filters()
        const
        {
            typename file_open_dialog_type::file_filters_type filters;

            filters.push_back(
                std::make_pair(
                    m_message_catalog.get(
                        TETENGO2_TEXT("Dialog:FileOpen:Timetable Files")
                    ),
                    string_type(TETENGO2_TEXT("*.btt"))
                )
            );
            //filters.push_back(
            //    std::make_pair(
            //        m_message_catalog.get(
            //            TETENGO2_TEXT(
            //                "Dialog:FileOpen:Timetable Files (Compressed)"
            //            )
            //        ),
            //        string_type(TETENGO2_TEXT("*.btt.bz2"))
            //    )
            //);
            filters.push_back(
                std::make_pair(
                    m_message_catalog.get(
                        TETENGO2_TEXT("Dialog:FileOpen:All Files")
                    ),
                    string_type(TETENGO2_TEXT("*.*"))
                )
            );

            return filters;
        }


    };


}}


#endif
