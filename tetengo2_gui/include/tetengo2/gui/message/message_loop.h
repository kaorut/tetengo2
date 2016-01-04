/*! \file
    \brief The definition of tetengo2::gui::message::message_loop.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_MESSAGELOOP_H)
#define TETENGO2_GUI_MESSAGE_MESSAGELOOP_H

#include <boost/core/noncopyable.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class template for a message loop.

        \tparam AbstractWindow     An abstract window type.
        \tparam MessageLoopDetails The message loop details type.
    */
    template <typename AbstractWindow, typename MessageLoopDetails>
    class message_loop : private boost::noncopyable
    {
    public:
        // types

        //! The abstract window type.
        using abstract_window_type = AbstractWindow;

        //! The message loop details type.
        using message_loop_details_type = MessageLoopDetails;


        // constructors and destructor

        /*!
            \brief Creats a message loop.

            \param window A window.
        */
        explicit message_loop(abstract_window_type& window)
        :
        m_window(window)
        {}


        // functions

        /*!
            \brief Runs the message loop.

            \return The exit status code.
        */
        int operator()()
        const
        {
            return message_loop_details_type::loop(m_window);
        }


    private:
        // variables

        abstract_window_type& m_window;


    };


}}}


#endif
