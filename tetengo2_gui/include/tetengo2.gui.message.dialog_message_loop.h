/*! \file
    \brief The definition of tetengo2::gui::message::dialog_message_loop.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_DIALOGMESSAGELOOP_H)
#define TETENGO2_GUI_MESSAGE_DIALOGMESSAGELOOP_H


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class template for a message loop for dialogs.

        \tparam MessageLoopDetails The detail implementation type of a message
                                   loop.
    */
    template <typename MessageLoopDetails>
    class dialog_message_loop
    {
    public:
        // types

        //! The detail implementation type of a message loop.
        typedef MessageLoopDetails message_loop_details_type;


        // functions

        /*!
            \brief Runs the message loop.

            \return The exit status code.
        */
        int operator()()
        const
        {
            return message_loop_details_type::dialog_loop();
        }


    };


}}}


#endif
