/*! \file
    \brief The definition of bobura::command::exit.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_EXIT_H)
#define BOBURA_COMMAND_EXIT_H

#include <algorithm>

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
        explicit exit(window_type* const p_window)
        :
        m_p_window(p_window)
        {}

        /*!
            \brief Copies an exit command.

            \param another Another exit command object.
        */
        exit(const exit& another)
        :
        m_p_window(another.m_p_window)
        {}

        /*!
            \brief Destroys the exit command.
        */
        virtual ~exit()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another exit command object.

            \param another Another exit command object.
        */
        void swap(exit& another)
        throw ()
        {
            std::swap(m_p_window, another.m_p_window);
        }

        /*!
            \brief Assigns another exit command object.

            \param another Another exit command object.

            \return this object.
        */
        exit& operator=(const exit& another)
        {
            exit(another).swap(*this);
            return *this;
        }

        /*!
            \brief Executes the command.
        */
        void operator()()
        {
            m_p_window->close();
        }


    private:
        // variables

        window_type* const m_p_window;


    };


}}

#endif
