/*! \file
    \brief The definition of tetengo2::gui::message::message_loop_break.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_MESSAGELOOPBREAK_H)
#define TETENGO2_GUI_MESSAGE_MESSAGELOOPBREAK_H

#include <functional>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class template for a message loop break.

        \tparam MessageLoopDetails The message loop details type.
    */
    template <typename MessageLoopDetails>
    class message_loop_break : public std::unary_function<int, void>
    {
    public:
        // types

        //! The message loop details type.
        using message_loop_details_type = MessageLoopDetails;


        // functions

        /*!
            \brief Quits the message loop.

            \param exit_code An exit status code.
        */
        void operator()(const int exit_code)
        const
        {
            message_loop_details_type::break_loop(exit_code);
        }


    };


}}}


#endif
