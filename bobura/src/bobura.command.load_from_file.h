/*! \file
    \brief The definition of bobura::command::load_from_file.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_LOADFROMFILE_H)
#define BOBURA_COMMAND_LOADFROMFILE_H

#include <tetengo2.cpp11.h>
#include <tetengo2.text.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a load-from-file command.

        \tparam FileOpenDialog A file open dialog type.
    */
    template <typename FileOpenDialog>
    class load_from_file
    {
    public:
        // types

        //! The file open dialog type.
        typedef FileOpenDialog file_open_dialog_type;

        //! The window type.
        typedef typename file_open_dialog_type::widget_type window_type;


        // constructors and destructor

        /*!
            \brief Creates a load-from-file command.

            \param window A parent window.
        */
        explicit load_from_file(window_type& window)
        :
        m_window(window)
        {}


        // functions

        /*!
            \brief Executes the command.
        */
        void operator()()
        const
        {
            file_open_dialog_type dialog(
                string_type(TETENGO2_TEXT("Open")),
                make_file_filters(),
                m_window
            );
            dialog.do_modal();

            dialog.result();
        }


    private:
        // types

        typedef typename window_type::string_type string_type;


        // static functions

        static typename file_open_dialog_type::file_filters_type
        make_file_filters()
        {
            typename file_open_dialog_type::file_filters_type filters;

            filters.push_back(
                std::make_pair(
                    string_type(TETENGO2_TEXT("Timetable Files")),
                    string_type(TETENGO2_TEXT("*.btt"))
                )
            );
            filters.push_back(
                std::make_pair(
                    string_type(TETENGO2_TEXT("All Files")),
                    string_type(TETENGO2_TEXT("*.*"))
                )
            );

            return filters;
        }


        // variables

        typename tetengo2::cpp11::reference_wrapper<window_type>::type
        m_window;


    };


}}


#endif
