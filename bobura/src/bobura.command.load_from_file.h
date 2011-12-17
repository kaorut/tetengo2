/*! \file
    \brief The definition of bobura::command::load_from_file.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_LOADFROMFILE_H)
#define BOBURA_COMMAND_LOADFROMFILE_H

#include <tetengo2.cpp11.h>


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
        {

        }


        // functions

        /*!
            \brief Executes the command.
        */
        void operator()()
        const
        {
        
        }


    private:
        // variables

        typename tetengo2::cpp11::reference_wrapper<window_type>::type
        m_window;


    };


}}


#endif
