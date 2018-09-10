/*! \file
    \brief The definition of tetengo2::gui::message::message_loop_break.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_MESSAGELOOPBREAK_H)
#define TETENGO2_GUI_MESSAGE_MESSAGELOOPBREAK_H

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_loop.h>


namespace tetengo2::gui::message {
    /*!
        \brief The class for a message loop break.
    */
    class message_loop_break
    {
    public:
        // functions

        /*!
            \brief Quits the message loop.

            \param exit_code An exit status code.
        */
        void operator()(const int exit_code) const
        {
            detail::gui_detail_impl_set().message_loop_().break_loop(exit_code);
        }
    };
}


#endif
