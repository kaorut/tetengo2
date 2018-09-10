/*! \file
    \brief The definition of tetengo2::detail::windows::message_loop.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

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
#include <tetengo2/detail/windows/menu.h>
#include <tetengo2/detail/windows/message_loop.h>
#include <tetengo2/detail/windows/widget.h>
#include <tetengo2/gui/widget/abstract_window.h>


namespace tetengo2::detail::windows {
    class message_loop::impl : private boost::noncopyable
    {
    public:
        // static functions

        static const message_loop& instance()
        {
            static const message_loop singleton;
            return singleton;
        }


        // functions

        int loop_impl(gui::widget::abstract_window& window) const
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
                    ::TranslateAcceleratorW(handle_of(window), accelerator_table_handle(window), &message))
                {
                    continue;
                }

                ::TranslateMessage(&message);
                ::DispatchMessageW(&message);
            }
        }

        int dialog_loop_impl(gui::widget::abstract_window& dialog) const
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

                if (!dialog.destroyed() && ::IsDialogMessageW(handle_of(dialog), &message) != 0)
                    continue;

                if (!dialog.destroyed() && shortcut_keys_defined(dialog) &&
                    ::TranslateAcceleratorW(handle_of(dialog), accelerator_table_handle(dialog), &message))
                {
                    continue;
                }

                ::TranslateMessage(&message);
                ::DispatchMessageW(&message);
            }
        }

        void break_loop_impl(const int exit_code) const
        {
            ::PostQuitMessage(exit_code);
        }


    private:
        // static functions

        static ::HWND handle_of(const gui::widget::widget& abstract_window)
        {
            return reinterpret_cast<::HWND>(
                static_cast<const detail::windows::widget::windows_widget_details_type&>(abstract_window.details())
                    .handle);
        }

        static bool shortcut_keys_defined(gui::widget::abstract_window& window)
        {
            if (!window.has_menu_bar())
                return false;
            if (!handle_of(window.menu_bar().get_shortcut_key_table()))
                return false;

            return true;
        }

        static ::HACCEL accelerator_table_handle(gui::widget::abstract_window& window)
        {
            return handle_of(window.menu_bar().get_shortcut_key_table());
        }

        static ::HACCEL handle_of(const gui::menu::shortcut_key_table& table)
        {
            return reinterpret_cast<::HACCEL>(
                static_cast<const detail::windows::menu::windows_shortcut_key_table_details_type&>(table.details())
                    .get());
        }
    };


    const message_loop& message_loop::instance()
    {
        return impl::instance();
    }

    message_loop::~message_loop() = default;

    message_loop::message_loop() : m_p_impl{ std::make_unique<impl>() } {}

    int message_loop::loop_impl(gui::widget::abstract_window& window) const
    {
        return m_p_impl->loop_impl(window);
    }

    int message_loop::dialog_loop_impl(gui::widget::abstract_window& dialog) const
    {
        return m_p_impl->dialog_loop_impl(dialog);
    }

    void message_loop::break_loop_impl(int exit_code) const
    {
        m_p_impl->break_loop_impl(exit_code);
    }
}
