/*! \file
    \brief The definition of bobura::command::exit.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_EXIT_H)
#define BOBURA_COMMAND_EXIT_H

#include <algorithm>
#include <cstddef>

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

            \param window A window.
        */
        explicit exit(window_type& window)
        :
        m_p_window(&window)
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
        ~exit()
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

        window_type* m_p_window;


    };


}}

namespace std
{
    /*!
        \brief Swaps two exit objects.

        \tparam Window A window type. It must conform to
                       concept_tetengo2::gui::Window<Window>.

        \param exit1 An exit object #1.
        \param exit2 An exit object #2.
    */
    template <typename Window>
    void swap(
        bobura::command::exit<Window>& exit1,
        bobura::command::exit<Window>& exit2
    )
    throw ()
    {
        BOOST_CONCEPT_ASSERT((concept_tetengo2::gui::Window<Window>));

        exit1.swap(exit2);
    }


}

#endif
