/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::dialog.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cassert>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/message_handler_detail/dialog.h>
#include <tetengo2/detail/windows/widget.h>
#include <tetengo2/gui/widget/dialog.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::detail::windows::message_handler_detail::dialog {
    tetengo2::stdalt::optional<::LRESULT>
    on_command(gui::widget::dialog& dialog, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        const ::WORD hi_wparam = HIWORD(w_param);
        const ::WORD lo_wparam = LOWORD(w_param);
        if (hi_wparam == 0 && (lo_wparam == IDOK || lo_wparam == IDCANCEL))
        {
            const auto widget_handle = reinterpret_cast<::HWND>(l_param);
#if !NDEBUG
            auto& dialog_details = static_cast<detail::windows::widget::windows_widget_details_type&>(dialog.details());
            assert(widget_handle == ::GetDlgItem(reinterpret_cast<::HWND>(dialog_details.handle), lo_wparam));
#endif
            if (widget_handle)
            {
                detail::windows::widget::instance()
                    .p_widget_from(reinterpret_cast<std::intptr_t>(widget_handle))
                    ->click();
            }
            else
            {
                dialog.set_result(
                    lo_wparam == IDOK ? gui::widget::dialog::result_type::accepted :
                                        gui::widget::dialog::result_type::canceled);
                dialog.close();
            }
            return tetengo2::stdalt::make_optional<::LRESULT>(0);
        }

        return TETENGO2_STDALT_NULLOPT;
    }

    tetengo2::stdalt::optional<::LRESULT> on_syscommand(
        gui::widget::dialog&                        dialog,
        const ::WPARAM                              w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (w_param == SC_CLOSE)
        {
            const auto widget_handle = ::GetDlgItem(
                reinterpret_cast<::HWND>(
                    static_cast<detail::windows::widget::windows_widget_details_type&>(dialog.details()).handle),
                IDCANCEL);
            if (widget_handle)
            {
                detail::windows::widget::instance()
                    .p_widget_from(reinterpret_cast<std::intptr_t>(widget_handle))
                    ->click();
            }
            else
            {
                dialog.set_result(gui::widget::dialog::result_type::canceled);
                dialog.close();
            }
            return tetengo2::stdalt::make_optional<::LRESULT>(0);
        }

        return TETENGO2_STDALT_NULLOPT;
    }

    namespace {
        ::HWND first_child_window_handle(::HWND parent_handle);

        ::BOOL WINAPI first_child_window_handle_iter(const ::HWND child_handle, const ::LPARAM l_param)
        {
            auto* p_result = reinterpret_cast<::HWND*>(l_param);
            if (!p_result)
                return FALSE;

            const auto style = ::GetWindowLongW(child_handle, GWL_STYLE);
            if ((static_cast<::DWORD>(style) & WS_TABSTOP) != 0)
            {
                *p_result = child_handle;
                return FALSE;
            }

            const auto grandchild_handle = first_child_window_handle(child_handle);
            if (grandchild_handle)
            {
                *p_result = grandchild_handle;
                return FALSE;
            }

            return TRUE;
        }

        ::HWND first_child_window_handle(const ::HWND parent_handle)
        {
            ::HWND child_handle = nullptr;
            ::EnumChildWindows(
                parent_handle, first_child_window_handle_iter, reinterpret_cast<::LPARAM>(&child_handle));

            return child_handle;
        }
    }

    tetengo2::stdalt::optional<::LRESULT> on_set_focus(
        gui::widget::dialog&                        dialog,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        auto& dialog_details = static_cast<detail::windows::widget::windows_widget_details_type&>(dialog.details());
        if (dialog_details.first_child_handle)
        {
            ::SetFocus(reinterpret_cast<::HWND>(dialog_details.first_child_handle));
            return tetengo2::stdalt::make_optional<::LRESULT>(0);
        }

        const auto child_handle = first_child_window_handle(reinterpret_cast<::HWND>(dialog_details.handle));
        if (child_handle)
        {
            ::SetFocus(child_handle);
            return tetengo2::stdalt::make_optional<::LRESULT>(0);
        }

        return TETENGO2_STDALT_NULLOPT;
    }
}
