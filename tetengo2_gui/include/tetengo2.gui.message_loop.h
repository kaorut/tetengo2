/*! \file
    \brief The definition of tetengo2::gui::message_loop.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGELOOP_H)
#define TETENGO2_GUI_MESSAGELOOP_H


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a message loop.

        \tparam MessageLoopDetails The detail implementation type of a message
                                   loop.
    */
    template <typename MessageLoopDetails>
    class message_loop
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
            return message_loop_details_type::loop();
        }


    };


}}

#endif
