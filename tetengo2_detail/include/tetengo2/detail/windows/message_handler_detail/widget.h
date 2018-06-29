/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::widget.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_WIDGET_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_WIDGET_H

#include <algorithm> // IWYU pragma: keep
#include <cassert>
#include <stdexcept>
#include <system_error> // IWYU pragma: keep

#include <boost/preprocessor.hpp>
#include <boost/scope_exit.hpp>
#include <boost/throw_exception.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <windowsx.h>

#include <tetengo2/detail/windows/cursor.h> // IWYU pragma: keep
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2::detail::windows::message_handler_detail::widget {
    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_command(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        if (l_param == 0)
            return TETENGO2_STDALT_NULLOPT;

        ::PostMessageW(
            reinterpret_cast<::HWND>(l_param),
            static_cast<::UINT>(custom_message_type::command),
            w_param,
            reinterpret_cast<::LPARAM>(widget.details().handle.get()));
        return TETENGO2_STDALT_NULLOPT;
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT>
    on_key_down(Widget& widget, const ::WPARAM w_param, TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (widget.keyboard_observer_set().key_down().empty())
            return TETENGO2_STDALT_NULLOPT;

        using virtual_key_type = typename Widget::keyboard_observer_set_type::virtual_key_type;

        const auto virtual_key =
            virtual_key_type::find_by_code(static_cast<typename virtual_key_type::code_type>(w_param));
        if (!virtual_key)
            return TETENGO2_STDALT_NULLOPT;

        const auto shift = ::GetKeyState(VK_SHIFT) < 0;
        const auto control = ::GetKeyState(VK_CONTROL) < 0;
        const auto meta = ::GetKeyState(VK_MENU) < 0;

        widget.keyboard_observer_set().key_down()(*virtual_key, shift, control, meta);

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT>
    on_key_up(Widget& widget, const ::WPARAM w_param, TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (widget.keyboard_observer_set().key_up().empty())
            return TETENGO2_STDALT_NULLOPT;

        using virtual_key_type = typename Widget::keyboard_observer_set_type::virtual_key_type;

        const auto virtual_key =
            virtual_key_type::find_by_code(static_cast<typename virtual_key_type::code_type>(w_param));
        if (!virtual_key)
            return TETENGO2_STDALT_NULLOPT;

        const auto shift = ::GetKeyState(VK_SHIFT) < 0;
        const auto control = ::GetKeyState(VK_CONTROL) < 0;
        const auto meta = ::GetKeyState(VK_MENU) < 0;

        widget.keyboard_observer_set().key_up()(*virtual_key, shift, control, meta);

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT>
    on_char(Widget& widget, const ::WPARAM w_param, TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (widget.keyboard_observer_set().character_input().empty())
            return TETENGO2_STDALT_NULLOPT;

        using char_type = typename Widget::keyboard_observer_set_type::char_type;

        widget.keyboard_observer_set().character_input()(static_cast<char_type>(w_param));

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }

    template <typename Position>
    Position l_param_to_position(const ::LPARAM l_param)
    {
        return { Position::unit_type::from_pixels(GET_X_LPARAM(l_param)),
                 Position::unit_type::from_pixels(GET_Y_LPARAM(l_param)) };
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_button_down_impl(
        Widget&                                                           widget,
        const typename Widget::mouse_observer_set_type::mouse_button_type button,
        const ::WPARAM                                                    w_param,
        const ::LPARAM                                                    l_param)
    {
        if (widget.mouse_observer_set().pressed().empty())
            return TETENGO2_STDALT_NULLOPT;

        widget.mouse_observer_set().pressed()(
            button,
            l_param_to_position<typename Widget::position_type>(l_param),
            (w_param & MK_SHIFT) != 0,
            (w_param & MK_CONTROL) != 0,
            ::GetKeyState(VK_MENU) < 0);

        return TETENGO2_STDALT_NULLOPT;
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT>
    on_l_button_down(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        return on_button_down_impl(widget, Widget::mouse_observer_set_type::mouse_button_type::left, w_param, l_param);
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT>
    on_r_button_down(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        return on_button_down_impl(widget, Widget::mouse_observer_set_type::mouse_button_type::right, w_param, l_param);
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_button_up_impl(
        Widget&                                                           widget,
        const typename Widget::mouse_observer_set_type::mouse_button_type button,
        const ::WPARAM                                                    w_param,
        const ::LPARAM                                                    l_param)
    {
        if (widget.mouse_observer_set().released().empty())
            return TETENGO2_STDALT_NULLOPT;

        widget.mouse_observer_set().released()(
            button,
            l_param_to_position<typename Widget::position_type>(l_param),
            (w_param & MK_SHIFT) != 0,
            (w_param & MK_CONTROL) != 0,
            ::GetKeyState(VK_MENU) < 0);

        return TETENGO2_STDALT_NULLOPT;
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_l_button_up(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        return on_button_up_impl(widget, Widget::mouse_observer_set_type::mouse_button_type::left, w_param, l_param);
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_r_button_up(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        return on_button_up_impl(widget, Widget::mouse_observer_set_type::mouse_button_type::right, w_param, l_param);
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_mouse_move(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        if (widget.mouse_observer_set().moved().empty())
            return TETENGO2_STDALT_NULLOPT;

        widget.mouse_observer_set().moved()(
            l_param_to_position<typename Widget::position_type>(l_param),
            (w_param & MK_SHIFT) != 0,
            (w_param & MK_CONTROL) != 0,
            ::GetKeyState(VK_MENU) < 0);

        return TETENGO2_STDALT_NULLOPT;
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_l_doubleclick(
        Widget&                                     widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (widget.mouse_observer_set().doubleclicked().empty())
            return TETENGO2_STDALT_NULLOPT;

        widget.mouse_observer_set().doubleclicked()();

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_mouse_wheel(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        const ::POINT point{ GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param) };
        const ::HWND  pointing_window_handle = ::WindowFromPoint(point);
        if (pointing_window_handle && pointing_window_handle != widget.details().handle.get())
        {
            ::PostMessageW(pointing_window_handle, WM_MOUSEWHEEL, w_param, l_param);
            return tetengo2::stdalt::make_optional<::LRESULT>(0);
        }

        if (widget.mouse_observer_set().wheeled().empty())
            return TETENGO2_STDALT_NULLOPT;

        const short        delta = GET_WHEEL_DELTA_WPARAM(w_param);
        const unsigned int key_state = GET_KEYSTATE_WPARAM(w_param);

        widget.mouse_observer_set().wheeled()(
            typename Widget::mouse_observer_set_type::delta_type{ delta, WHEEL_DELTA },
            Widget::mouse_observer_set_type::direction_type::vertical,
            (key_state & MK_SHIFT) != 0,
            (key_state & MK_CONTROL) != 0,
            ::GetKeyState(VK_MENU) < 0);

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT>
    on_mouse_h_wheel(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        const ::POINT point{ GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param) };
        const ::HWND  pointing_window_handle = ::WindowFromPoint(point);
        if (pointing_window_handle && pointing_window_handle != widget.details().handle.get())
        {
            ::PostMessageW(pointing_window_handle, WM_MOUSEHWHEEL, w_param, l_param);
            return tetengo2::stdalt::make_optional<::LRESULT>(0);
        }

        if (widget.mouse_observer_set().wheeled().empty())
            return TETENGO2_STDALT_NULLOPT;

        const short        delta = GET_WHEEL_DELTA_WPARAM(w_param);
        const unsigned int key_state = GET_KEYSTATE_WPARAM(w_param);

        widget.mouse_observer_set().wheeled()(
            typename Widget::mouse_observer_set_type::delta_type{ delta, WHEEL_DELTA },
            Widget::mouse_observer_set_type::direction_type::horizontal,
            (key_state & MK_SHIFT) != 0,
            (key_state & MK_CONTROL) != 0,
            ::GetKeyState(VK_MENU) < 0);

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT>
    on_control_color(TETENGO2_STDALT_MAYBE_UNUSED Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        if (l_param == 0)
            return TETENGO2_STDALT_NULLOPT;

        auto result = ::SendMessageW(
            reinterpret_cast<::HWND>(l_param), static_cast<::UINT>(custom_message_type::control_color), w_param, 0);

        return result != 0 ? tetengo2::stdalt::make_optional(std::move(result)) : TETENGO2_STDALT_NULLOPT;
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_set_cursor(
        Widget&                                     widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (!widget.p_cursor())
            return TETENGO2_STDALT_NULLOPT;

        ::SetCursor(
            reinterpret_cast<::HCURSOR>(const_cast<cursor::cursor_details_type*>(&widget.p_cursor()->details())));

        return tetengo2::stdalt::make_optional<::LRESULT>(FALSE);
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_resized(
        Widget&                                     widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (widget.size_observer_set().resized().empty())
            return TETENGO2_STDALT_NULLOPT;

        widget.size_observer_set().resized()();

        return TETENGO2_STDALT_NULLOPT;
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_set_focus(
        Widget&                                     widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        widget.focus_observer_set().got_focus()();
        return TETENGO2_STDALT_NULLOPT;
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_kill_focus(
        Widget&                                     widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        widget.focus_observer_set().lost_focus()();
        return TETENGO2_STDALT_NULLOPT;
    }

    type_list::size_type new_scroll_bar_position(const ::HWND window_handle, const int scroll_code, const int style)
    {
        ::SCROLLINFO info{};
        info.cbSize = sizeof(::SCROLLINFO);
        info.fMask = SIF_POS | SIF_RANGE | SIF_PAGE | SIF_TRACKPOS;

        if (::GetScrollInfo(window_handle, style, &info) == 0)
        {
            BOOST_THROW_EXCEPTION(
                (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                    "Can't obtain scroll information." }));
        }

        switch (scroll_code)
        {
        case SB_LINEUP:
            static_assert(SB_LINELEFT == SB_LINEUP, "SB_LINELEFT != SB_LINEUP");
            return std::max<int>(info.nMin, info.nPos - 1);
        case SB_LINEDOWN:
            static_assert(SB_LINERIGHT == SB_LINEDOWN, "SB_LINERIGHT != SB_LINEDOWN");
            return std::min<int>(info.nMax - info.nPage + 1, info.nPos + 1);
        case SB_PAGEUP:
            static_assert(SB_PAGELEFT == SB_PAGEUP, "SB_PAGELEFT != SB_PAGEUP");
            return std::max<int>(info.nMin, info.nPos - info.nPage);
        case SB_PAGEDOWN:
            static_assert(SB_PAGERIGHT == SB_PAGEDOWN, "SB_PAGERIGHT != SB_PAGEDOWN");
            return std::min<int>(info.nMax - info.nPage + 1, info.nPos + info.nPage);
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            return info.nTrackPos;
        case SB_TOP:
            static_assert(SB_LEFT == SB_TOP, "SB_LEFT != SB_TOP");
            return info.nMin;
        case SB_BOTTOM:
            static_assert(SB_RIGHT == SB_BOTTOM, "SB_RIGHT != SB_BOTTOM");
            return info.nMax - info.nPage + 1;
        default:
            assert(false);
            BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid scroll code." }));
        }
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT>
    on_vertical_scroll(Widget& widget, const ::WPARAM w_param, TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (!widget.has_vertical_scroll_bar())
            return TETENGO2_STDALT_NULLOPT;

        const int scroll_code = LOWORD(w_param);
        if (scroll_code == SB_ENDSCROLL)
        {
            return TETENGO2_STDALT_NULLOPT;
        }
        else if (scroll_code == SB_THUMBTRACK)
        {
            if (widget.vertical_scroll_bar().scroll_bar_observer_set().scrolling().empty())
                return TETENGO2_STDALT_NULLOPT;
            const auto new_position = new_scroll_bar_position(widget.details().handle.get(), scroll_code, SB_VERT);
            widget.vertical_scroll_bar().scroll_bar_observer_set().scrolling()(new_position);
        }
        else
        {
            const auto new_position = new_scroll_bar_position(widget.details().handle.get(), scroll_code, SB_VERT);
            if (widget.vertical_scroll_bar().scroll_bar_observer_set().scrolled().empty())
            {
                widget.vertical_scroll_bar().set_position(new_position);
                return TETENGO2_STDALT_NULLOPT;
            }
            widget.vertical_scroll_bar().set_position(new_position);
            widget.vertical_scroll_bar().scroll_bar_observer_set().scrolled()(new_position);
        }

        return TETENGO2_STDALT_NULLOPT;
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT>
    on_horizontal_scroll(Widget& widget, const ::WPARAM w_param, TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (!widget.has_horizontal_scroll_bar())
            return TETENGO2_STDALT_NULLOPT;

        const int scroll_code = LOWORD(w_param);
        if (scroll_code == SB_ENDSCROLL)
        {
            return TETENGO2_STDALT_NULLOPT;
        }
        else if (scroll_code == SB_THUMBTRACK)
        {
            if (widget.horizontal_scroll_bar().scroll_bar_observer_set().scrolling().empty())
                return TETENGO2_STDALT_NULLOPT;
            const auto new_position = new_scroll_bar_position(widget.details().handle.get(), scroll_code, SB_HORZ);
            widget.horizontal_scroll_bar().scroll_bar_observer_set().scrolling()(new_position);
        }
        else
        {
            const auto new_position = new_scroll_bar_position(widget.details().handle.get(), scroll_code, SB_HORZ);
            if (widget.horizontal_scroll_bar().scroll_bar_observer_set().scrolled().empty())
            {
                widget.horizontal_scroll_bar().set_position(new_position);
                return TETENGO2_STDALT_NULLOPT;
            }
            widget.horizontal_scroll_bar().scroll_bar_observer_set().scrolled()(new_position);
            widget.horizontal_scroll_bar().set_position(new_position);
        }

        return TETENGO2_STDALT_NULLOPT;
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT>
    on_erase_background(Widget& widget, const ::WPARAM w_param, TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (widget.paint_observer_set().paint_background().empty())
            return TETENGO2_STDALT_NULLOPT;

        typename Widget::widget_canvas_type canvas{ reinterpret_cast<::HDC>(w_param) };
        if (!widget.paint_observer_set().paint_background()(canvas))
            return TETENGO2_STDALT_NULLOPT;

        return tetengo2::stdalt::make_optional<::LRESULT>(TRUE);
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_paint(
        Widget&                                     widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (widget.paint_observer_set().paint().empty())
            return TETENGO2_STDALT_NULLOPT;

        ::PAINTSTRUCT paint_struct{};
        if (!::BeginPaint(widget.details().handle.get(), &paint_struct))
        {
            BOOST_THROW_EXCEPTION((
                std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() }, "Can't begin paint." }));
        }
        BOOST_SCOPE_EXIT((&widget)(&paint_struct))
        {
            ::EndPaint(widget.details().handle.get(), &paint_struct);
        }
        BOOST_SCOPE_EXIT_END;
        typename Widget::widget_canvas_type canvas{ paint_struct.hdc };

        widget.paint_observer_set().paint()(canvas);

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }

    template <typename Widget>
    void delete_current_font(Widget& widget)
    {
        const auto font_handle =
            reinterpret_cast<::HFONT>(::SendMessageW(widget.details().handle.get(), WM_GETFONT, 0, 0));

        ::SendMessageW(widget.details().handle.get(), WM_SETFONT, 0, MAKELPARAM(0, 0));

        if (font_handle && ::DeleteObject(font_handle) == 0)
        {
            BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() },
                                                      "Can't delete previous font." }));
        }
    }

    template <typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_destroy(
        Widget&                                     widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        delete_current_font(widget);
        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }

    template <typename WidgetDetails, typename Widget>
    tetengo2::stdalt::optional<::LRESULT> on_ncdestroy(
        Widget&                                     widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        const auto* const p_widget = reinterpret_cast<const Widget*>(
            ::RemovePropW(widget.details().handle.get(), WidgetDetails::property_key_for_cpp_instance().c_str()));
        p_widget;
        assert(p_widget == &widget);

        widget.set_destroyed();

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }
}


#endif
#endif
