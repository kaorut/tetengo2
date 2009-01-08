/*! \file
    \brief The definition of bobura::command::about.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_ABOUT_H)
#define BOBURA_COMMAND_ABOUT_H

#include <algorithm>

//#include <boost/concept_check.hpp>

#include <concept_tetengo2.gui.Window.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for an about command.

        \tparam Window A window type. It must conform to
                       concept_tetengo2::gui::Window<Window>.
    */
    template <typename Window>
    class about
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
            \brief Creates an about command.

            \param p_window A pointer to a window.
        */
        explicit about(window_type* const p_window)
        :
        m_p_window(p_window)
        {}

        /*!
            \brief Copies an about command.

            \param another Another about command object.
        */
        about(const about& another)
        :
        m_p_window(another.m_p_window)
        {}

        /*!
            \brief Destroys the about command.
        */
        virtual ~about()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another about command object.

            \param another Another about command object.
        */
        void swap(about& another)
        throw ()
        {
            std::swap(m_p_window, another.m_p_window);
        }

        /*!
            \brief Assigns another about command object.

            \param another Another about command object.

            \return this object.
        */
        about& operator=(const about& another)
        {
            about(another).swap(*this);
            return *this;
        }

        /*!
            \brief Executes the command.
        */
        void operator()()
        {
            m_p_window->set_text(L"‚ ‚Î‚¤‚Æ");
        }


    private:
        // variables

        window_type* const m_p_window;


    };


}}

#endif
