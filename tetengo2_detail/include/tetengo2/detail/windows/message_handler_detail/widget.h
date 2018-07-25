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
#include <tetengo2/gui/type_list.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/type_list.h>


namespace tetengo2::detail::windows::message_handler_detail::widget {
    tetengo2::stdalt::optional<::LRESULT>
    on_command(gui::widget::widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        if (l_param == 0)
            return TETENGO2_STDALT_NULLOPT;

        ::PostMessageW(
            reinterpret_cast<::HWND>(l_param),
            static_cast<::UINT>(custom_message_type::command),
            w_param,
            reinterpret_cast<::LPARAM>(reinterpret_cast<::HWND>(
                static_cast<detail::windows::widget::windows_widget_details_type&>(widget.details()).handle)));
        return TETENGO2_STDALT_NULLOPT;
    }

    tetengo2::stdalt::optional<::LRESULT> on_key_down(
        gui::widget::widget&                        widget,
        const ::WPARAM                              w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (widget.keyboard_observer_set().key_down().empty())
            return TETENGO2_STDALT_NULLOPT;

        using virtual_key_type = gui::widget::widget::keyboard_observer_set_type::virtual_key_type;

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

    tetengo2::stdalt::optional<::LRESULT>
    on_key_up(gui::widget::widget& widget, const ::WPARAM w_param, TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (widget.keyboard_observer_set().key_up().empty())
            return TETENGO2_STDALT_NULLOPT;

        using virtual_key_type = gui::widget::widget::keyboard_observer_set_type::virtual_key_type;

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

    tetengo2::stdalt::optional<::LRESULT>
    on_char(gui::widget::widget& widget, const ::WPARAM w_param, TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (widget.keyboard_observer_set().character_input().empty())
            return TETENGO2_STDALT_NULLOPT;

        using char_type = gui::widget::widget::keyboard_observer_set_type::char_type;

        widget.keyboard_observer_set().character_input()(static_cast<char_type>(w_param));

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }

    inline gui::type_list::position_type l_param_to_position(const ::LPARAM l_param)
    {
        return { gui::type_list::position_type::unit_type::from_pixels(GET_X_LPARAM(l_param)),
                 gui::type_list::position_type::unit_type::from_pixels(GET_Y_LPARAM(l_param)) };
    }

    tetengo2::stdalt::optional<::LRESULT> on_button_down_impl(
        gui::widget::widget&                                                  widget,
        const gui::widget::widget::mouse_observer_set_type::mouse_button_type button,
        const ::WPARAM                                                        w_param,
        const ::LPARAM                                                        l_param)
    {
        if (widget.mouse_observer_set().pressed().empty())
            return TETENGO2_STDALT_NULLOPT;

        widget.mouse_observer_set().pressed()(
            button,
            l_param_to_position(l_param),
            (w_param & MK_SHIFT) != 0,
            (w_param & MK_CONTROL) != 0,
            ::GetKeyState(VK_MENU) < 0);

        return TETENGO2_STDALT_NULLOPT;
    }

    tetengo2::stdalt::optional<::LRESULT>
    on_l_button_down(gui::widget::widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        return on_button_down_impl(
            widget, gui::widget::widget::mouse_observer_set_type::mouse_button_type::left, w_param, l_param);
    }

    tetengo2::stdalt::optional<::LRESULT>
    on_r_button_down(gui::widget::widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        return on_button_down_impl(
            widget, gui::widget::widget::mouse_observer_set_type::mouse_button_type::right, w_param, l_param);
    }

    tetengo2::stdalt::optional<::LRESULT> on_button_up_impl(
        gui::widget::widget&                                                  widget,
        const gui::widget::widget::mouse_observer_set_type::mouse_button_type button,
        const ::WPARAM                                                        w_param,
        const ::LPARAM                                                        l_param)
    {
        if (widget.mouse_observer_set().released().empty())
            return TETENGO2_STDALT_NULLOPT;

        widget.mouse_observer_set().released()(
            button,
            l_param_to_position(l_param),
            (w_param & MK_SHIFT) != 0,
            (w_param & MK_CONTROL) != 0,
            ::GetKeyState(VK_MENU) < 0);

        return TETENGO2_STDALT_NULLOPT;
    }

    tetengo2::stdalt::optional<::LRESULT>
    on_l_button_up(gui::widget::widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        return on_button_up_impl(
            widget, gui::widget::widget::mouse_observer_set_type::mouse_button_type::left, w_param, l_param);
    }

    tetengo2::stdalt::optional<::LRESULT>
    on_r_button_up(gui::widget::widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        return on_button_up_impl(
            widget, gui::widget::widget::mouse_observer_set_type::mouse_button_type::right, w_param, l_param);
    }

    tetengo2::stdalt::optional<::LRESULT>
    on_mouse_move(gui::widget::widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        if (widget.mouse_observer_set().moved().empty())
            return TETENGO2_STDALT_NULLOPT;

        widget.mouse_observer_set().moved()(
            l_param_to_position(l_param),
            (w_param & MK_SHIFT) != 0,
            (w_param & MK_CONTROL) != 0,
            ::GetKeyState(VK_MENU) < 0);

        return TETENGO2_STDALT_NULLOPT;
    }

    tetengo2::stdalt::optional<::LRESULT> on_l_doubleclick(
        gui::widget::widget&                        widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (widget.mouse_observer_set().doubleclicked().empty())
            return TETENGO2_STDALT_NULLOPT;

        widget.mouse_observer_set().doubleclicked()();

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }

    tetengo2::stdalt::optional<::LRESULT>
    on_mouse_wheel(gui::widget::widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        const ::POINT point{ GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param) };
        const ::HWND  pointing_window_handle = ::WindowFromPoint(point);
        if (pointing_window_handle &&
            pointing_window_handle !=
                reinterpret_cast<::HWND>(
                    static_cast<detail::windows::widget::windows_widget_details_type&>(widget.details()).handle))
        {
            ::PostMessageW(pointing_window_handle, WM_MOUSEWHEEL, w_param, l_param);
            return tetengo2::stdalt::make_optional<::LRESULT>(0);
        }

        if (widget.mouse_observer_set().wheeled().empty())
            return TETENGO2_STDALT_NULLOPT;

        const short        delta = GET_WHEEL_DELTA_WPARAM(w_param);
        const unsigned int key_state = GET_KEYSTATE_WPARAM(w_param);

        widget.mouse_observer_set().wheeled()(
            gui::widget::widget::mouse_observer_set_type::delta_type{ delta, WHEEL_DELTA },
            gui::widget::widget::mouse_observer_set_type::direction_type::vertical,
            (key_state & MK_SHIFT) != 0,
            (key_state & MK_CONTROL) != 0,
            ::GetKeyState(VK_MENU) < 0);

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }

    tetengo2::stdalt::optional<::LRESULT>
    on_mouse_h_wheel(gui::widget::widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        const ::POINT point{ GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param) };
        const ::HWND  pointing_window_handle = ::WindowFromPoint(point);
        if (pointing_window_handle &&
            pointing_window_handle !=
                reinterpret_cast<::HWND>(
                    static_cast<detail::windows::widget::windows_widget_details_type&>(widget.details()).handle))
        {
            ::PostMessageW(pointing_window_handle, WM_MOUSEHWHEEL, w_param, l_param);
            return tetengo2::stdalt::make_optional<::LRESULT>(0);
        }

        if (widget.mouse_observer_set().wheeled().empty())
            return TETENGO2_STDALT_NULLOPT;

        const short        delta = GET_WHEEL_DELTA_WPARAM(w_param);
        const unsigned int key_state = GET_KEYSTATE_WPARAM(w_param);

        widget.mouse_observer_set().wheeled()(
            gui::widget::widget::mouse_observer_set_type::delta_type{ delta, WHEEL_DELTA },
            gui::widget::widget::mouse_observer_set_type::direction_type::horizontal,
            (key_state & MK_SHIFT) != 0,
            (key_state & MK_CONTROL) != 0,
            ::GetKeyState(VK_MENU) < 0);

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }

    tetengo2::stdalt::optional<::LRESULT> on_control_color(
        TETENGO2_STDALT_MAYBE_UNUSED gui::widget::widget& widget,
        const ::WPARAM                                    w_param,
        const ::LPARAM                                    l_param)
    {
        if (l_param == 0)
            return TETENGO2_STDALT_NULLOPT;

        auto result = ::SendMessageW(
            reinterpret_cast<::HWND>(l_param), static_cast<::UINT>(custom_message_type::control_color), w_param, 0);

        return result != 0 ? tetengo2::stdalt::make_optional(std::move(result)) : TETENGO2_STDALT_NULLOPT;
    }

    tetengo2::stdalt::optional<::LRESULT> on_set_cursor(
        gui::widget::widget&                        widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (!widget.p_cursor())
            return TETENGO2_STDALT_NULLOPT;

        ::SetCursor(
            reinterpret_cast<::HCURSOR>(const_cast<cursor::cursor_details_type*>(&widget.p_cursor()->details())));

        return tetengo2::stdalt::make_optional<::LRESULT>(FALSE);
    }

    tetengo2::stdalt::optional<::LRESULT> on_resized(
        gui::widget::widget&                        widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (widget.size_observer_set().resized().empty())
            return TETENGO2_STDALT_NULLOPT;

        widget.size_observer_set().resized()();

        return TETENGO2_STDALT_NULLOPT;
    }

    tetengo2::stdalt::optional<::LRESULT> on_set_focus(
        gui::widget::widget&                        widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        widget.focus_observer_set().got_focus()();
        return TETENGO2_STDALT_NULLOPT;
    }

    tetengo2::stdalt::optional<::LRESULT> on_kill_focus(
        gui::widget::widget&                        widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        widget.focus_observer_set().lost_focus()();
        return TETENGO2_STDALT_NULLOPT;
    }

    inline type_list::size_type
    new_scroll_bar_position(const ::HWND window_handle, const int scroll_code, const int style)
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

    tetengo2::stdalt::optional<::LRESULT> on_vertical_scroll(
        gui::widget::widget&                        widget,
        const ::WPARAM                              w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (!widget.has_vertical_scroll_bar())
            return TETENGO2_STDALT_NULLOPT;

        auto&     widget_details = static_cast<detail::windows::widget::windows_widget_details_type&>(widget.details());
        const int scroll_code = LOWORD(w_param);
        if (scroll_code == SB_ENDSCROLL)
        {
            return TETENGO2_STDALT_NULLOPT;
        }
        else if (scroll_code == SB_THUMBTRACK)
        {
            if (widget.vertical_scroll_bar().scroll_bar_observer_set().scrolling().empty())
                return TETENGO2_STDALT_NULLOPT;
            const auto new_position =
                new_scroll_bar_position(reinterpret_cast<::HWND>(widget_details.handle), scroll_code, SB_VERT);
            widget.vertical_scroll_bar().scroll_bar_observer_set().scrolling()(new_position);
        }
        else
        {
            const auto new_position =
                new_scroll_bar_position(reinterpret_cast<::HWND>(widget_details.handle), scroll_code, SB_VERT);
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

    tetengo2::stdalt::optional<::LRESULT> on_horizontal_scroll(
        gui::widget::widget&                        widget,
        const ::WPARAM                              w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (!widget.has_horizontal_scroll_bar())
            return TETENGO2_STDALT_NULLOPT;

        auto&     widget_details = static_cast<detail::windows::widget::windows_widget_details_type&>(widget.details());
        const int scroll_code = LOWORD(w_param);
        if (scroll_code == SB_ENDSCROLL)
        {
            return TETENGO2_STDALT_NULLOPT;
        }
        else if (scroll_code == SB_THUMBTRACK)
        {
            if (widget.horizontal_scroll_bar().scroll_bar_observer_set().scrolling().empty())
                return TETENGO2_STDALT_NULLOPT;
            const auto new_position =
                new_scroll_bar_position(reinterpret_cast<::HWND>(widget_details.handle), scroll_code, SB_HORZ);
            widget.horizontal_scroll_bar().scroll_bar_observer_set().scrolling()(new_position);
        }
        else
        {
            const auto new_position =
                new_scroll_bar_position(reinterpret_cast<::HWND>(widget_details.handle), scroll_code, SB_HORZ);
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

    tetengo2::stdalt::optional<::LRESULT> on_erase_background(
        gui::widget::widget&                        widget,
        const ::WPARAM                              w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (widget.paint_observer_set().paint_background().empty())
            return TETENGO2_STDALT_NULLOPT;

        gui::widget::widget::widget_canvas_type canvas{ reinterpret_cast<::HDC>(w_param) };
        if (!widget.paint_observer_set().paint_background()(canvas))
            return TETENGO2_STDALT_NULLOPT;

        return tetengo2::stdalt::make_optional<::LRESULT>(TRUE);
    }

    tetengo2::stdalt::optional<::LRESULT> on_paint(
        gui::widget::widget&                        widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (widget.paint_observer_set().paint().empty())
            return TETENGO2_STDALT_NULLOPT;

        auto& widget_details = static_cast<detail::windows::widget::windows_widget_details_type&>(widget.details());
        ::PAINTSTRUCT paint_struct{};
        if (!::BeginPaint(reinterpret_cast<::HWND>(widget_details.handle), &paint_struct))
        {
            BOOST_THROW_EXCEPTION((
                std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() }, "Can't begin paint." }));
        }
        BOOST_SCOPE_EXIT((&widget_details)(&paint_struct))
        {
            ::EndPaint(reinterpret_cast<::HWND>(widget_details.handle), &paint_struct);
        }
        BOOST_SCOPE_EXIT_END;
        gui::widget::widget::widget_canvas_type canvas{ paint_struct.hdc };

        widget.paint_observer_set().paint()(canvas);

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }

    void delete_current_font(gui::widget::widget& widget)
    {
        auto& widget_details = static_cast<detail::windows::widget::windows_widget_details_type&>(widget.details());
        const auto font_handle = reinterpret_cast<::HFONT>(
            ::SendMessageW(reinterpret_cast<::HWND>(widget_details.handle), WM_GETFONT, 0, 0));

        ::SendMessageW(reinterpret_cast<::HWND>(widget_details.handle), WM_SETFONT, 0, MAKELPARAM(0, 0));

        if (font_handle && ::DeleteObject(font_handle) == 0)
        {
            BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() },
                                                      "Can't delete previous font." }));
        }
    }

    tetengo2::stdalt::optional<::LRESULT> on_destroy(
        gui::widget::widget&                        widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        delete_current_font(widget);
        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }

    tetengo2::stdalt::optional<::LRESULT> on_ncdestroy(
        gui::widget::widget&                        widget,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        const auto* const p_widget = reinterpret_cast<const gui::widget::widget*>(::RemovePropW(
            reinterpret_cast<::HWND>(
                static_cast<detail::windows::widget::windows_widget_details_type&>(widget.details()).handle),
            detail::windows::widget::property_key_for_cpp_instance().c_str()));
        p_widget;
        assert(p_widget == &widget);

        widget.set_destroyed();

        return tetengo2::stdalt::make_optional<::LRESULT>(0);
    }
}


#endif
#endif
