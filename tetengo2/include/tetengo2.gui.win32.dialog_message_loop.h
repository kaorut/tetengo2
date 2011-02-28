/*! \file
    \brief The definition of tetengo2::gui::win32::dialog_message_loop.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_DIALOGMESSAGELOOP_H)
#define TETENGO2_GUI_WIN32_DIALOGMESSAGELOOP_H

#include <cstddef>
#include <sstream>
#include <stdexcept>

#include <boost/throw_exception.hpp>

#include "tetengo2.generator.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a message loop for dialogs.

        \tparam MessageLoopDetails The detail implementationf of a message
                                   loop.
    */
    template <typename MessageLoopDetails>
    class dialog_message_loop : public tetengo2::generator<int>
    {
    public:
        // types

        //! The detail implementation of a message loop.
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
