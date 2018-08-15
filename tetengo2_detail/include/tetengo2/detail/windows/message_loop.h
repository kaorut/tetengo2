/*! \file
    \brief The definition of tetengo2::detail::windows::message_loop.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGELOOP_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGELOOP_H

#include <system_error>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/error_category.h>


namespace tetengo2::detail::windows {
    /*!
        \brief The class for a detail implementation of a message loop.
    */
    class message_loop : private boost::noncopyable
    {
    public:
        // static functions

        /*!
            \brief Run the message loop.

            \tparam AbstractWindow An abstract window type.

            \param window A window.

            \return The exit status code.

            \throw std::system_error When a message loop error has happened.
        */
        template <typename AbstractWindow>
        static int loop(AbstractWindow& window)
        {
            ::MSG message;
            for (;;)
            {
                const auto result = ::GetMessageW(&message, nullptr, 0, 0);
                if (result == 0)
                {
                    return static_cast<int>(message.wParam);
                }
                else if (result == -1)
                {
                    BOOST_THROW_EXCEPTION(
                        (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                            "Win32 Message Loop Error" }));
                }

                if (shortcut_keys_defined(window) &&
                    ::TranslateAcceleratorW(window.details().handle.get(), accelerator_table_handle(window), &message))
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

            \throw std::system_error When a message loop error has happened.
        */
        template <typename AbstractWindow>
        static int dialog_loop(AbstractWindow& dialog)
        {
            ::MSG message;
            for (;;)
            {
                const auto result = ::GetMessageW(&message, nullptr, 0, 0);
                if (result == 0)
                {
                    return static_cast<int>(message.wParam);
                }
                else if (result == -1)
                {
                    BOOST_THROW_EXCEPTION(
                        (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                            "Win32 Message Loop Error" }));
                }

                if (!dialog.destroyed() && ::IsDialogMessageW(dialog.details().handle.get(), &message) != 0)
                    continue;

                if (!dialog.destroyed() && shortcut_keys_defined(dialog) &&
                    ::TranslateAcceleratorW(dialog.details().handle.get(), accelerator_table_handle(dialog), &message))
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
            if (!window.menu_bar().get_shortcut_key_table().details().get())
                return false;

            return true;
        }

        template <typename AbstractWindow>
        static ::HACCEL accelerator_table_handle(AbstractWindow& window)
        {
            return window.menu_bar().get_shortcut_key_table().details().get();
        }


        // forbidden operations

        message_loop() = delete;
    };
}


#endif
