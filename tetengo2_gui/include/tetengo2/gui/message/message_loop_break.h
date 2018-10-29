/*! \file
    \brief The definition of tetengo2::gui::message::message_loop_break.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_MESSAGELOOPBREAK_H)
#define TETENGO2_GUI_MESSAGE_MESSAGELOOPBREAK_H


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
        void operator()(int exit_code) const;
    };
}


#endif
