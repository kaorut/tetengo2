/*! \file
    \brief The definition of tetengo2::detail::windows::message_loop.

    Copyright (C) 2007-2012 kaoru

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

            \tparam AbstractWindow An abstract window type.

            \param window A window.

            \return The exit status code.
        */
        template <typename AbstractWindow>
        static int loop(AbstractWindow& window)
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
                    shortcut_keys_defined(window) &&
                    ::TranslateAcceleratorW(
                        window.details()->first.get(),
                        accelerator_table_handle(window),
                        &message
                    )
                )
                {
                    continue;
                }

                ::TranslateMessage(&message);
                ::DispatchMessageW(&message);
            }

        }

        /*!
            \brief Run the message loop for a dialog.

            \tparam AbstractWindow An abstract window type.

            \param dialog A dialog.

            \return The exit status code.
        */
        template <typename AbstractWindow>
        static int dialog_loop(AbstractWindow& dialog)
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
                    !dialog.destroyed() &&
                    ::IsDialogMessageW(
                        dialog.details()->first.get(), &message
                    ) != 0
                )
                {
                    continue;
                }

                if (
                    !dialog.destroyed() &&
                    shortcut_keys_defined(dialog) &&
                    ::TranslateAcceleratorW(
                        dialog.details()->first.get(),
                        accelerator_table_handle(dialog),
                        &message
                    )
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
        // static functions

        template <typename AbstractWindow>
        static bool shortcut_keys_defined(AbstractWindow& window)
        {
            if (!window.has_menu_bar())
                return false;
            if (!window.menu_bar().shortcut_key_table().details())
                return false;

            return true;
        }

        template <typename AbstractWindow>
        static ::HACCEL accelerator_table_handle(AbstractWindow& window)
        {
            return const_cast< ::HACCEL>(
                &*window.menu_bar().shortcut_key_table().details()
            );
        }


        // forbidden operations

        message_loop();


   };


}}}


#endif
