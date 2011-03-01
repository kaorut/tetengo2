/*! \file
    \brief The definition of tetengo2::gui::dialog_message_loop.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_DIALOGMESSAGELOOP_H)
#define TETENGO2_GUI_DIALOGMESSAGELOOP_H

#include "tetengo2.generator.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a message loop for dialogs.

        \tparam MessageLoopDetails The detail implementation type of a message
                                   loop.
    */
    template <typename MessageLoopDetails>
    class dialog_message_loop : public tetengo2::generator<int>
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


}}

#endif
