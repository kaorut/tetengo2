/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::widget.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_WIDGET_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_WIDGET_H

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/stdalt.h>

namespace tetengo2 { namespace gui { namespace widget {
    class widget;
}}}


namespace tetengo2::detail::windows::message_handler_detail::widget {
    tetengo2::stdalt::optional<::LRESULT> on_command(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT> on_key_down(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT> on_key_up(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT> on_char(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT> on_button_down_impl(
        gui::widget::widget&                                widget,
        gui::message::mouse_observer_set::mouse_button_type button,
        ::WPARAM                                            w_param,
        ::LPARAM                                            l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_l_button_down(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_r_button_down(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT> on_button_up_impl(
        gui::widget::widget&                                widget,
        gui::message::mouse_observer_set::mouse_button_type button,
        ::WPARAM                                            w_param,
        ::LPARAM                                            l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_l_button_up(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_r_button_up(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_mouse_move(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_l_doubleclick(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_mouse_wheel(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_mouse_h_wheel(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_control_color(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_set_cursor(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT> on_resized(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT> on_set_focus(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_kill_focus(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_vertical_scroll(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_horizontal_scroll(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT>
    on_erase_background(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT> on_paint(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT> on_destroy(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);

    tetengo2::stdalt::optional<::LRESULT> on_ncdestroy(gui::widget::widget& widget, ::WPARAM w_param, ::LPARAM l_param);
}


#endif
#endif
