/*! \file
    \brief The definition of bobura::command::exit.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_EXIT_H)
#define BOBURA_COMMAND_EXIT_H

#include <tetengo2.cpp11.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for an exit command.

        \tparam Window A window type.
    */
    template <typename Window>
    class exit
    {
    public:
        // types

        //! The window type.
        typedef Window window_type;


        // constructors and destructor

        /*!
            \brief Creates an exit command.

            \param window A window.
        */
        explicit exit(window_type& window)
        :
        m_window(window)
        {}


        // functions

        /*!
            \brief Executes the command.
        */
        void operator()()
        {
            m_window.get().close();
        }


    private:
        // variables

        typename tetengo2::cpp11::reference_wrapper<window_type>::type
        m_window;


    };


}}


#endif
