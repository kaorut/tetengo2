/*! \file
    \brief The definition of tetengo2::gui::message::message_loop.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_MESSAGELOOP_H)
#define TETENGO2_GUI_MESSAGE_MESSAGELOOP_H

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_loop.h>


namespace tetengo2::gui::message {
    /*!
        \brief The class for a message loop.
    */
    class message_loop : private boost::noncopyable
    {
    public:
        // types

        //! The abstract window type.
        using abstract_window_type = widget::abstract_window;


        // constructors and destructor

        /*!
            \brief Creats a message loop.

            \param window A window.
        */
        explicit message_loop(abstract_window_type& window) : m_window{ window } {}


        // functions

        /*!
            \brief Runs the message loop.

            \return The exit status code.
        */
        int operator()() const
        {
            return detail::gui_detail_impl_set().message_loop_().loop(m_window);
        }


    private:
        // variables

        abstract_window_type& m_window;
    };
}


#endif
