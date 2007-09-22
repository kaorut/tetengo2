/*! \file
    \brief The definition of tetengo2::gui::stub::message_loop.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_STUB_MESSAGELOOP_H)
#define TETENGO2_GUI_STUB_MESSAGELOOP_H

#include "tetengo2.generator.h"


namespace tetengo2 { namespace gui { namespace stub
{
    /*!
        \brief The generator class for a message loop for testing.
    */
    class message_loop : public tetengo2::generator<int>
    {
    public:
        // functions

        /*!
            \brief Runs the message loop.

            \return The exit status code. Always 0.
        */
        int operator()()
        const
        {
            return 0;
        }


    };


}}}

#endif
