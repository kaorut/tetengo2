/*! \file
    \brief The definition of tetengo2::detail::windows::message_loop.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGELOOP_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGELOOP_H

#include <cstddef>
#include <sstream>
#include <stdexcept>

#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a message loop.
    */
    class message_loop
    {
    public:
        // static functions

        /*!
            \brief Run the message loop.

            \return The exit status code.
        */
        static int loop()
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

        /*!
            \brief Run the message loop for a dialog box.

            \return The exit status code.
        */
        static int dialog_loop()
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

                if (
                    ::IsDialogMessageW(message.hwnd, &message) != 0 ||
                    ::IsDialogMessageW(
                        ::GetAncestor(message.hwnd, GA_ROOT), &message
                    ) != 0
                )
                {
                    continue;
                }

                ::TranslateMessage(&message);
                ::DispatchMessageW(&message);
            }
        }

        /*!
            \brief Breaks the message loop.

            \param exit_code An exit code.
        */
        static void break_loop(const int exit_code)
        {
            ::PostQuitMessage(exit_code);
        }


    private:
        // forbidden operations

        message_loop();


   };


}}}


#endif
