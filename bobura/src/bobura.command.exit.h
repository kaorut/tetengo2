/*! \file
    \brief The definition of bobura::command::exit.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_EXIT_H)
#define BOBURA_COMMAND_EXIT_H

//#include <boost/concept_check.hpp>

#include <concept_tetengo2.gui.Window.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for an exit command.

        \tparam Window A window type. It must conform to
                       concept_tetengo2::gui::Window<Window>.
    */
    template <typename Window>
    class exit
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Window<Window>));


    public:
        // types

        //! The window type.
        typedef Window window_type;


        // constructors and destructor

        /*!
            \brief Creates an exit command.

            \param p_window A pointer to a window.
        */
        explicit exit(const window_type* const p_window)
        :
        m_p_window(p_window)
        {}

        /*!
            \brief Destroys the exit command.
        */
        virtual ~exit()
        throw ()
        {}


        // functions

        /*!
            \brief Executes the command.
        */
        void operator()()
        const
        {
            m_p_window->close();
        }


    private:
        // variables

        const window_type* const m_p_window;


    };


}}

#endif
