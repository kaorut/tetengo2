/*! \file
    \brief The definition of tetengo2::gui::stub::quit_message_loop.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_STUB_QUITMESSAGELOOP_H)
#define TETENGO2_GUI_STUB_QUITMESSAGELOOP_H

#include <functional>


namespace tetengo2 { namespace gui { namespace stub
{
    /*!
        \brief The unary functor class for a message loop for testing.
    */
    class quit_message_loop : public std::unary_function<int, void>
    {
    public:
        // functions

        /*!
            \brief Quits the message loop.

            \param exit_code An exit code.
        */
        void operator()(const int exit_code)
        const
        {}


    };


}}}

#endif
