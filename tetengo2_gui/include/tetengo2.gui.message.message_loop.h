/*! \file
    \brief The definition of tetengo2::gui::message::message_loop.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_MESSAGELOOP_H)
#define TETENGO2_GUI_MESSAGE_MESSAGELOOP_H

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class template for a message loop.

        \tparam AbstractWindow     An abstract window type.
        \tparam MessageLoopDetails The detail implementation type of a message loop.
    */
    template <typename AbstractWindow, typename MessageLoopDetails>
    class message_loop : boost::noncopyable
    {
    public:
        // types

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The detail implementation type of a message loop.
        typedef MessageLoopDetails message_loop_details_type;


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
