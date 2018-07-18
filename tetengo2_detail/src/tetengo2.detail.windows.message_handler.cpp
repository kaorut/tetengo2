/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/detail/windows/message_handler.h>
#include <tetengo2/detail/windows/message_handler_detail/abstra.h>
#include <tetengo2/detail/windows/message_handler_detail/button.h>
#include <tetengo2/detail/windows/message_handler_detail/contro.h>
#include <tetengo2/detail/windows/message_handler_detail/custom.h>
#include <tetengo2/detail/windows/message_handler_detail/dialog.h>
#include <tetengo2/detail/windows/message_handler_detail/dropdo.h>
#include <tetengo2/detail/windows/message_handler_detail/list_b.h>
#include <tetengo2/detail/windows/message_handler_detail/messag.h>
#include <tetengo2/detail/windows/message_handler_detail/pictur.h>
#include <tetengo2/detail/windows/message_handler_detail/text_b.h>
#include <tetengo2/detail/windows/message_handler_detail/widget.h>
#include <tetengo2/detail/windows/widget.h>
#include <tetengo2/stdalt.h>



namespace tetengo2::detail::windows {
    class message_handler::impl : private boost::noncopyable
    {
    public:
        // types

        using message_handler_type = message_handler::message_handler_type;

        using message_handler_map_type = message_handler::message_handler_map_type;

        using windows_message_handler_type = message_handler::windows_message_handler_type;


        // functions

        message_handler_map_type make_abstract_window_message_handler_map_impl(
            gui::widget::abstract_window& abstract_window,
            message_handler_map_type&&    initial_map) const
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[WM_COMMAND].push_back(std::make_unique<windows_message_handler_type>(
                [&abstract_window](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::abstract_window::on_command(abstract_window, w_param, l_param);
                }));
            map[WM_INITMENUPOPUP].push_back(std::make_unique<windows_message_handler_type>(
                [&abstract_window](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::abstract_window::on_initmenupopup(abstract_window, w_param, l_param);
                }));
            map[WM_DROPFILES].push_back(std::make_unique<windows_message_handler_type>(
                [&abstract_window](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::abstract_window::on_drop_files(abstract_window, w_param, l_param);
                }));
            map[WM_CLOSE].push_back(std::make_unique<windows_message_handler_type>(
                [&abstract_window](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::abstract_window::on_close(abstract_window, w_param, l_param);
                }));
            map[WM_QUERYENDSESSION].push_back(std::make_unique<windows_message_handler_type>(
                [&abstract_window](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::abstract_window::on_query_end_session(
                        abstract_window, w_param, l_param);
                }));
            map[WM_DESTROY].push_back(std::make_unique<windows_message_handler_type>(
                [&abstract_window](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::abstract_window::on_destroy(abstract_window, w_param, l_param);
                }));

            return map;
        }

        message_handler_map_type
        make_button_message_handler_map_impl(gui::widget::button& button, message_handler_map_type&& initial_map) const
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[static_cast<::UINT>(message_handler_detail::custom_message_type::command)].push_back(
                std::make_unique<windows_message_handler_type>(
                    [&button](const ::WPARAM w_param, const ::LPARAM l_param) {
                        return message_handler_detail::button::on_tetengo2_command(button, w_param, l_param);
                    }));

            return map;
        }

        message_handler_map_type make_control_message_handler_map_impl(
            gui::widget::control&      control,
            message_handler_map_type&& initial_map) const
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[static_cast<::UINT>(message_handler_detail::custom_message_type::control_color)].push_back(
                std::make_unique<windows_message_handler_type>(
                    [&control](const ::WPARAM w_param, const ::LPARAM l_param) {
                        return message_handler_detail::control::on_control_color(control, w_param, l_param);
                    }));
            map[WM_SETFOCUS].push_back(std::make_unique<windows_message_handler_type>(
                [&control](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::control::on_set_focus(control, w_param, l_param);
                }));

            return map;
        }

        message_handler_map_type make_custom_control_message_handler_map_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::custom_control& custom_control,
            message_handler_map_type&&                                initial_map) const
        {
            return std::move(initial_map);
        }

        message_handler_map_type
        make_dialog_message_handler_map_impl(gui::widget::dialog& dialog, message_handler_map_type&& initial_map) const
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[WM_COMMAND].push_back(std::make_unique<windows_message_handler_type>(
                [&dialog](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::dialog::on_command<widget_details_type>(dialog, w_param, l_param);
                }));
            map[WM_SYSCOMMAND].push_back(std::make_unique<windows_message_handler_type>(
                [&dialog](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::dialog::on_syscommand<widget_details_type>(dialog, w_param, l_param);
                }));
            map[WM_SETFOCUS].push_back(std::make_unique<windows_message_handler_type>(
                [&dialog](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::dialog::on_set_focus<widget_details_type>(dialog, w_param, l_param);
                }));

            return map;
        }

        message_handler_map_type make_dropdown_box_message_handler_map_impl(
            gui::widget::dropdown_box& dropdown_box,
            message_handler_map_type&& initial_map) const
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[static_cast<::UINT>(message_handler_detail::custom_message_type::command)].push_back(
                std::make_unique<windows_message_handler_type>([&dropdown_box](
                                                                   const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::dropdown_box::on_tetengo2_command(dropdown_box, w_param, l_param);
                }));

            return map;
        }

        message_handler_map_type make_image_message_handler_map_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::image& image,
            message_handler_map_type&&                       initial_map) const
        {
            return std::move(initial_map);
        }

        message_handler_map_type make_label_message_handler_map_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::label& label,
            message_handler_map_type&&                       initial_map) const
        {
            return std::move(initial_map);
        }

        message_handler_map_type make_list_box_message_handler_map_impl(
            gui::widget::list_box&     list_box,
            message_handler_map_type&& initial_map) const
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[static_cast<::UINT>(message_handler_detail::custom_message_type::command)].push_back(
                std::make_unique<windows_message_handler_type>(
                    [&list_box](const ::WPARAM w_param, const ::LPARAM l_param) {
                        return message_handler_detail::list_box::on_tetengo2_command(list_box, w_param, l_param);
                    }));

            return map;
        }

        message_handler_map_type make_picture_box_message_handler_map_impl(
            gui::widget::picture_box&  picture_box,
            message_handler_map_type&& initial_map) const
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[WM_ERASEBKGND].push_back(std::make_unique<windows_message_handler_type>(
                [&picture_box](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::picture_box::on_erase_background(picture_box, w_param, l_param);
                }));
            map[WM_PAINT].push_back(std::make_unique<windows_message_handler_type>(
                [&picture_box](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::picture_box::on_paint(picture_box, w_param, l_param);
                }));

            return map;
        }

        message_handler_map_type make_progress_bar_message_handler_map_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::progress_bar& progress_bar,
            message_handler_map_type&&                              initial_map) const
        {
            return std::move(initial_map);
        }

        message_handler_map_type make_text_box_message_handler_map_impl(
            gui::widget::text_box&     text_box,
            message_handler_map_type&& initial_map) const
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[static_cast<::UINT>(message_handler_detail::custom_message_type::command)].push_back(
                std::make_unique<windows_message_handler_type>(
                    [&text_box](const ::WPARAM w_param, const ::LPARAM l_param) {
                        return message_handler_detail::text_box::on_tetengo2_command(text_box, w_param, l_param);
                    }));

            return map;
        }

        message_handler_map_type
        make_widget_message_handler_map_impl(gui::widget::widget& widget, message_handler_map_type&& initial_map) const
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[WM_COMMAND].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_command(widget, w_param, l_param);
                }));
            map[WM_KEYDOWN].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_key_down(widget, w_param, l_param);
                }));
            map[WM_KEYUP].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_key_up(widget, w_param, l_param);
                }));
            map[WM_CHAR].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_char(widget, w_param, l_param);
                }));
            map[WM_LBUTTONDOWN].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_l_button_down(widget, w_param, l_param);
                }));
            map[WM_RBUTTONDOWN].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_r_button_down(widget, w_param, l_param);
                }));
            map[WM_LBUTTONUP].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_l_button_up(widget, w_param, l_param);
                }));
            map[WM_RBUTTONUP].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_r_button_up(widget, w_param, l_param);
                }));
            map[WM_MOUSEMOVE].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_mouse_move(widget, w_param, l_param);
                }));
            map[WM_LBUTTONDBLCLK].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_l_doubleclick(widget, w_param, l_param);
                }));
            map[WM_MOUSEWHEEL].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_mouse_wheel(widget, w_param, l_param);
                }));
            map[WM_MOUSEHWHEEL].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_mouse_h_wheel(widget, w_param, l_param);
                }));
            map[WM_CTLCOLORBTN].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_control_color(widget, w_param, l_param);
                }));
            map[WM_CTLCOLOREDIT].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_control_color(widget, w_param, l_param);
                }));
            map[WM_CTLCOLORLISTBOX].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_control_color(widget, w_param, l_param);
                }));
            map[WM_CTLCOLORSCROLLBAR].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_control_color(widget, w_param, l_param);
                }));
            map[WM_CTLCOLORSTATIC].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_control_color(widget, w_param, l_param);
                }));
            map[WM_SETCURSOR].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_set_cursor(widget, w_param, l_param);
                }));
            map[WM_SIZE].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_resized(widget, w_param, l_param);
                }));
            map[WM_SETFOCUS].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_set_focus(widget, w_param, l_param);
                }));
            map[WM_KILLFOCUS].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_kill_focus(widget, w_param, l_param);
                }));
            map[WM_VSCROLL].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_vertical_scroll(widget, w_param, l_param);
                }));
            map[WM_HSCROLL].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_horizontal_scroll(widget, w_param, l_param);
                }));
            map[WM_ERASEBKGND].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_erase_background(widget, w_param, l_param);
                }));
            map[WM_PAINT].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_paint(widget, w_param, l_param);
                }));
            map[WM_DESTROY].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_destroy(widget, w_param, l_param);
                }));
            map[WM_NCDESTROY].push_back(std::make_unique<windows_message_handler_type>(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param) {
                    return message_handler_detail::widget::on_ncdestroy<widget_details_type>(widget, w_param, l_param);
                }));

            return map;
        }

        message_handler_map_type make_window_message_handler_map_impl(
            TETENGO2_STDALT_MAYBE_UNUSED gui::widget::window& window,
            message_handler_map_type&&                        initial_map) const
        {
            return std::move(initial_map);
        }


    private:
        // types

        using widget_details_type = widget;
    };


    const message_handler& message_handler::instance()
    {
        static const message_handler singleton;
        return singleton;
    }

    message_handler::~message_handler() = default;

    message_handler::message_handler() : m_p_impl{ std::make_unique<impl>() } {}

    message_handler::message_handler_map_type message_handler::make_abstract_window_message_handler_map_impl(
        gui::widget::abstract_window& abstract_window,
        message_handler_map_type&&    initial_map) const
    {
        return m_p_impl->make_abstract_window_message_handler_map_impl(abstract_window, std::move(initial_map));
    }

    message_handler::message_handler_map_type message_handler::make_button_message_handler_map_impl(
        gui::widget::button&       button,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_button_message_handler_map_impl(button, std::move(initial_map));
    }

    message_handler::message_handler_map_type message_handler::make_control_message_handler_map_impl(
        gui::widget::control&      control,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_control_message_handler_map_impl(control, std::move(initial_map));
    }

    message_handler::message_handler_map_type message_handler::make_custom_control_message_handler_map_impl(
        gui::widget::custom_control& custom_control,
        message_handler_map_type&&   initial_map) const
    {
        return m_p_impl->make_custom_control_message_handler_map_impl(custom_control, std::move(initial_map));
    }

    message_handler::message_handler_map_type message_handler::make_dialog_message_handler_map_impl(
        gui::widget::dialog&       dialog,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_dialog_message_handler_map_impl(dialog, std::move(initial_map));
    }

    message_handler::message_handler_map_type message_handler::make_dropdown_box_message_handler_map_impl(
        gui::widget::dropdown_box& dropdown_box,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_dropdown_box_message_handler_map_impl(dropdown_box, std::move(initial_map));
    }

    message_handler::message_handler_map_type message_handler::make_image_message_handler_map_impl(
        gui::widget::image&        image,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_image_message_handler_map_impl(image, std::move(initial_map));
    }

    message_handler::message_handler_map_type message_handler::make_label_message_handler_map_impl(
        gui::widget::label&        label,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_label_message_handler_map_impl(label, std::move(initial_map));
    }

    message_handler::message_handler_map_type message_handler::make_list_box_message_handler_map_impl(
        gui::widget::list_box&     list_box,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_list_box_message_handler_map_impl(list_box, std::move(initial_map));
    }

    message_handler::message_handler_map_type message_handler::make_picture_box_message_handler_map_impl(
        gui::widget::picture_box&  picture_box,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_picture_box_message_handler_map_impl(picture_box, std::move(initial_map));
    }

    message_handler::message_handler_map_type message_handler::make_progress_bar_message_handler_map_impl(
        gui::widget::progress_bar& progress_bar,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_progress_bar_message_handler_map_impl(progress_bar, std::move(initial_map));
    }

    message_handler::message_handler_map_type message_handler::make_text_box_message_handler_map_impl(
        gui::widget::text_box&     text_box,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_text_box_message_handler_map_impl(text_box, std::move(initial_map));
    }

    message_handler::message_handler_map_type message_handler::make_widget_message_handler_map_impl(
        gui::widget::widget&       widget,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_widget_message_handler_map_impl(widget, std::move(initial_map));
    }

    message_handler::message_handler_map_type message_handler::make_window_message_handler_map_impl(
        gui::widget::window&       window,
        message_handler_map_type&& initial_map) const
    {
        return m_p_impl->make_window_message_handler_map_impl(window, std::move(initial_map));
    }
}