/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::dialog.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_DIALOG_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_DIALOG_H

#include <cassert>

#include <boost/core/ignore_unused.hpp> // IWYU pragma: keep
#include <boost/optional.hpp> // IWYU pragma: keep

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2 { namespace detail { namespace windows { namespace message_handler_detail { namespace dialog {
    template <typename WidgetDetails, typename Dialog>
    boost::optional<::LRESULT> on_command(Dialog& dialog, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        const ::WORD hi_wparam = HIWORD(w_param);
        const ::WORD lo_wparam = LOWORD(w_param);
        if (hi_wparam == 0 && (lo_wparam == IDOK || lo_wparam == IDCANCEL))
        {
            const auto widget_handle = reinterpret_cast<::HWND>(l_param);
            assert(widget_handle == ::GetDlgItem(dialog.details().handle.get(), lo_wparam));
            if (widget_handle)
            {
                WidgetDetails::p_widget_from<typename Dialog::base_type::base_type>(widget_handle)->click();
            }
            else
            {
                dialog.set_result(lo_wparam == IDOK ? Dialog::result_type::accepted : Dialog::result_type::canceled);
                dialog.close();
            }
            return boost::make_optional<::LRESULT>(0);
        }

        return boost::none;
    }

    template <typename WidgetDetails, typename Dialog>
    boost::optional<::LRESULT> on_syscommand(Dialog& dialog, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        boost::ignore_unused(l_param);

        if (w_param == SC_CLOSE)
        {
            const auto widget_handle = ::GetDlgItem(dialog.details().handle.get(), IDCANCEL);
            if (widget_handle)
            {
                WidgetDetails::p_widget_from<typename Dialog::base_type::base_type>(widget_handle)->click();
            }
            else
            {
                dialog.set_result(Dialog::result_type::canceled);
                dialog.close();
            }
            return boost::make_optional<::LRESULT>(0);
        }

        return boost::none;
    }

    ::HWND first_child_window_handle(::HWND parent_handle);

    inline ::BOOL WINAPI first_child_window_handle_iter(const ::HWND child_handle, const ::LPARAM l_param)
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

    inline ::HWND first_child_window_handle(const ::HWND parent_handle)
    {
        ::HWND child_handle = nullptr;
        ::EnumChildWindows(parent_handle, first_child_window_handle_iter, reinterpret_cast<::LPARAM>(&child_handle));

        return child_handle;
    }

    template <typename WidgetDetails, typename Dialog>
    boost::optional<::LRESULT> on_set_focus(Dialog& dialog, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        boost::ignore_unused(w_param, l_param);

        if (dialog.details().first_child_handle)
        {
            ::SetFocus(dialog.details().first_child_handle);
            return boost::make_optional<::LRESULT>(0);
        }

        const auto child_handle = first_child_window_handle(dialog.details().handle.get());
        if (child_handle)
        {
            ::SetFocus(child_handle);
            return boost::make_optional<::LRESULT>(0);
        }

        return boost::none;
    }


}}}}}


#endif
#endif
