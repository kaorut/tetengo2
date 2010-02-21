/*! \file
    \brief The definition of tetengo2::gui::win32::message_loop.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_MESSAGELOOP_H)
#define TETENGO2_GUI_WIN32_MESSAGELOOP_H

#include <cstddef>
#include <sstream>
#include <stdexcept>

#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>

#include "tetengo2.generator.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The generator class for a message loop for Win32 platforms.
    */
    class message_loop : public tetengo2::generator<int>
    {
    public:
        // functions

        /*!
            \brief Runs the message loop.

            \return The exit status code.

            \throw std::runtime_error When an error occurred in the message
                                      loop.
        */
        int operator()()
        const
        {
            ::MSG message;
            for (;;)
            {
                const ::BOOL result = ::GetMessageW(&message, NULL, 0, 0);
                if      (result == 0)
                {
                    return static_cast<int>(message.wParam);
                }
                else if (result == -1)
                {
                    std::ostringstream error_text;
                    error_text
                        << "Win32 Message Loop Error: "
                        << ::GetLastError();
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error(error_text.str())
                    );
                }

                ::TranslateMessage(&message);
                ::DispatchMessageW(&message);
            }
        }


    };


}}}

#endif
