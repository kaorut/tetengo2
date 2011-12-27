/*! \file
    \brief The definition of bobura::command::load_from_file.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_LOADFROMFILE_H)
#define BOBURA_COMMAND_LOADFROMFILE_H

#include <utility>

#include <tetengo2.text.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a load-from-file command.

        \tparam FileOpenDialog A file open dialog type.
        \tparam MessageCatalog A message catalog type.
    */
    template <typename FileOpenDialog, typename MessageCatalog>
    class load_from_file
    {
    public:
        // types

        //! The file open dialog type.
        typedef FileOpenDialog file_open_dialog_type;

        //! The window type.
        typedef typename file_open_dialog_type::widget_type window_type;

        //! The message catalog type.
        typedef MessageCatalog message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates a load-from-file command.

            \param window A parent window.
            \param message_catalog
        */
        load_from_file(
            window_type&                window,
            const message_catalog_type& message_catalog
        )
        :
        m_window(window),
        m_message_catalog(message_catalog)
        {}


        // functions

        /*!
            \brief Executes the command.
        */
        void operator()()
        const
        {
            file_open_dialog_type dialog(
                m_message_catalog.get(TETENGO2_TEXT("Dialog:FileOpen:Open")),
                make_file_filters(),
                m_window
            );
            dialog.do_modal();

            dialog.result();
        }


    private:
        // types

        typedef typename window_type::string_type string_type;



        // variables

        window_type& m_window;

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
            filters.push_back(
                std::make_pair(
                    m_message_catalog.get(
                        TETENGO2_TEXT(
                            "Dialog:FileOpen:Timetable Files (Compressed)"
                        )
                    ),
                    string_type(TETENGO2_TEXT("*.btt.bz2"))
                )
            );
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
