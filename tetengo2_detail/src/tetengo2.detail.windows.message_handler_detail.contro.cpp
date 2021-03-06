/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::control.

    The file name is truncated due to the path length limitation of tar command on UNIX.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <system_error>

#include <boost/throw_exception.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/detail/windows/message_handler_detail/contro.h>
#include <tetengo2/detail/windows/widget.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/stdalt.h>


namespace tetengo2::detail::windows::message_handler_detail::control {
    tetengo2::stdalt::optional<::LRESULT> on_control_color(
        gui::widget::control&                       control,
        const ::WPARAM                              w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (!control.p_background() && !control.text_color())
            return TETENGO2_STDALT_NULLOPT;

        const auto device_context = reinterpret_cast<::HDC>(w_param);
        if (!control.paint_observer_set().paint_background().empty())
        {
            gui::widget::widget::widget_canvas_type canvas{ detail::gui_detail_impl_set().drawing_(),
                                                            reinterpret_cast<std::intptr_t>(device_context) };
            control.paint_observer_set().paint_background()(canvas);
        }

        if (control.text_color())
        {
            const auto previous_color = ::SetTextColor(
                device_context,
                RGB(control.text_color()->red(), control.text_color()->green(), control.text_color()->blue()));
            if (previous_color == CLR_INVALID)
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() },
                                                          "Can't set text color." }));
            }
        }
        const auto previous_background_mode = ::SetBkMode(device_context, TRANSPARENT);
        if (previous_background_mode == 0)
        {
            BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ ERROR_FUNCTION_FAILED, win32_category() },
                                                      "Can't set background mode." }));
        }

        return tetengo2::stdalt::make_optional(reinterpret_cast<::LRESULT>(::GetStockObject(NULL_BRUSH)));
    }

    tetengo2::stdalt::optional<::LRESULT> on_set_focus(
        gui::widget::control&                       control,
        TETENGO2_STDALT_MAYBE_UNUSED const ::WPARAM w_param,
        TETENGO2_STDALT_MAYBE_UNUSED const ::LPARAM l_param)
    {
        if (control.has_parent())
        {
            auto& dialog = control.root_ancestor();

            static_cast<detail::windows::widget::windows_widget_details_type&>(dialog.details()).first_child_handle =
                static_cast<detail::windows::widget::windows_widget_details_type&>(control.details()).handle;
        }

        return TETENGO2_STDALT_NULLOPT;
    }
}
