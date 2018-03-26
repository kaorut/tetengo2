/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler_detail::control.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(DOCUMENTATION)
#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_CONTROL_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLERDETAIL_CONTROL_H

#include <system_error> // IWYU pragma: keep

#include <boost/core/ignore_unused.hpp> // IWYU pragma: keep
#include <boost/optional.hpp> // IWYU pragma: keep
#include <boost/throw_exception.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2::detail::windows::message_handler_detail::control {
    template <typename Control>
    boost::optional<::LRESULT> on_control_color(Control& control, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        boost::ignore_unused(l_param);

        if (!control.p_background() && !control.text_color())
            return boost::none;

        const auto device_context = reinterpret_cast<::HDC>(w_param);
        if (!control.paint_observer_set().paint_background().empty())
        {
            typename Control::base_type::widget_canvas_type canvas{ device_context };
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

        return boost::make_optional(reinterpret_cast<::LRESULT>(::GetStockObject(NULL_BRUSH)));
    }

    template <typename Control>
    boost::optional<::LRESULT> on_set_focus(Control& control, const ::WPARAM w_param, const ::LPARAM l_param)
    {
        boost::ignore_unused(w_param, l_param);

        if (control.has_parent())
        {
            auto& dialog = control.root_ancestor();

            dialog.details().first_child_handle = control.details().handle.get();
        }

        return boost::none;
    }
}


#endif
#endif
