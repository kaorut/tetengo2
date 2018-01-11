/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLER_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLER_H

#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/optional.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/detail/windows/message_handler_detail/abstra.h>
#include <tetengo2/detail/windows/message_handler_detail/button.h>
#include <tetengo2/detail/windows/message_handler_detail/contro.h>
#include <tetengo2/detail/windows/message_handler_detail/custom.h>
#include <tetengo2/detail/windows/message_handler_detail/dialog.h>
#include <tetengo2/detail/windows/message_handler_detail/dropdo.h>
#include <tetengo2/detail/windows/message_handler_detail/messag.h>
#include <tetengo2/detail/windows/message_handler_detail/list_b.h>
#include <tetengo2/detail/windows/message_handler_detail/pictur.h>
#include <tetengo2/detail/windows/message_handler_detail/text_b.h>
#include <tetengo2/detail/windows/message_handler_detail/widget.h>
#include <tetengo2/detail/windows/widget.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a message handler.
    */
    class message_handler : private boost::noncopyable
    {
    public:
        // types

        //! The message handler type.
        using message_handler_type = std::function<boost::optional< ::LRESULT> (::WPARAM, ::LPARAM)>;

        //! The message handler map type.
        using message_handler_map_type = std::unordered_map< ::UINT, std::vector<message_handler_type>>;


        // static functions

        /*!
            \brief Make a message handler map for an abstract window.

            \tparam AbstractWindow An abstract window type.

            \param abstract_window An abstract window.
            \param initial_map     An initial message handler map.

            \return A message handler map.
        */
        template <typename AbstractWindow>
        static message_handler_map_type make_abstract_window_message_handler_map(
            AbstractWindow&            abstract_window,
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[WM_COMMAND].push_back(
                [&abstract_window](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::abstract_window::on_command(abstract_window, w_param, l_param);
                }
            );
            map[WM_INITMENUPOPUP].push_back(
                [&abstract_window](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return
                        message_handler_detail::abstract_window::on_initmenupopup(abstract_window, w_param, l_param);
                }
            );
            map[WM_DROPFILES].push_back(
                [&abstract_window](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::abstract_window::on_drop_files(abstract_window, w_param, l_param);
                }
            );
            map[WM_CLOSE].push_back(
                [&abstract_window](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::abstract_window::on_close(abstract_window, w_param, l_param);
                }
            );
            map[WM_QUERYENDSESSION].push_back(
                [&abstract_window](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return
                        message_handler_detail::abstract_window::on_query_end_session(
                            abstract_window, w_param, l_param
                        );
                }
            );
            map[WM_DESTROY].push_back(
                [&abstract_window](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::abstract_window::on_destroy(abstract_window, w_param, l_param);
                }
            );

            return map;
        }

        /*!
            \brief Make a message handler map for a button.

            \tparam Button A button type.

            \param button      A button.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename Button>
        static message_handler_map_type make_button_message_handler_map(
            Button&                    button,
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[static_cast< ::UINT>(message_handler_detail::custom_message_type::command)].push_back(
                [&button](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::button::on_tetengo2_command(button, w_param, l_param);
                }
            );

            return map;
        }

        /*!
            \brief Make a message handler map for a control.

            \tparam Control A control type.

            \param control     A control.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename Control>
        static message_handler_map_type make_control_message_handler_map(
            Control&                   control,
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[static_cast< ::UINT>(message_handler_detail::custom_message_type::control_color)].push_back(
                [&control](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::control::on_control_color(control, w_param, l_param);
                }
            );
            map[WM_SETFOCUS].push_back(
                [&control](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::control::on_set_focus(control, w_param, l_param);
                }
            );

            return map;
        }

        /*!
            \brief Make a message handler map for a custom control.

            \tparam CustomControl A custom control type.

            \param custom_control A custom control.
            \param initial_map    An initial message handler map.

            \return A message handler map.
        */
        template <typename CustomControl>
        static message_handler_map_type make_custom_control_message_handler_map(
            CustomControl&             custom_control,
            message_handler_map_type&& initial_map
        )
        {
            boost::ignore_unused(custom_control);

            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for a dialog.

            \tparam Dialog A dialog type.

            \param dialog      A dialog.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename Dialog>
        static message_handler_map_type make_dialog_message_handler_map(
            Dialog&                    dialog,
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[WM_COMMAND].push_back(
                [&dialog](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::dialog::on_command<widget_details_type>(dialog, w_param, l_param);
                }
            );
            map[WM_SYSCOMMAND].push_back(
                [&dialog](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return
                        message_handler_detail::dialog::on_syscommand<widget_details_type>(dialog, w_param, l_param);
                }
            );
            map[WM_SETFOCUS].push_back(
                [&dialog](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::dialog::on_set_focus<widget_details_type>(dialog, w_param, l_param);
                }
            );

            return map;
        }

        /*!
            \brief Make a message handler map for a dropdown box.

            \tparam DropdownBox A dropdown box type.

            \param dropdown_box A dropdown box.
            \param initial_map  An initial message handler map.

            \return A message handler map.
        */
        template <typename DropdownBox>
        static message_handler_map_type make_dropdown_box_message_handler_map(
            DropdownBox&               dropdown_box,
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[static_cast< ::UINT>(message_handler_detail::custom_message_type::command)].push_back(
                [&dropdown_box](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::dropdown_box::on_tetengo2_command(dropdown_box, w_param, l_param);
                }
            );

            return map;
        }

        /*!
            \brief Make a message handler map for an image.

            \tparam Image An image type.

            \param image       An image.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename Image>
        static message_handler_map_type make_image_message_handler_map(
            Image&                     image,
            message_handler_map_type&& initial_map
        )
        {
            boost::ignore_unused(image);

            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for a label.

            \tparam Label A label type.

            \param label       A label.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename Label>
        static message_handler_map_type make_label_message_handler_map(
            Label&                     label,
            message_handler_map_type&& initial_map
        )
        {
            boost::ignore_unused(label);

            return std::move(initial_map);
        }

        /*!
            \brief Make a message handler map for a list box.

            \tparam ListBox A list box type.

            \param list_box    A list box.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename ListBox>
        static message_handler_map_type make_list_box_message_handler_map(
            ListBox&                   list_box,
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[static_cast< ::UINT>(message_handler_detail::custom_message_type::command)].push_back(
                [&list_box](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::list_box::on_tetengo2_command(list_box, w_param, l_param);
                }
            );

            return map;
        }

        /*!
            \brief Make a message handler map for a picture box.

            \tparam PictureBox A picture box type.

            \param picture_box    A picture box.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename PictureBox>
        static message_handler_map_type make_picture_box_message_handler_map(
            PictureBox&                picture_box,
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[WM_ERASEBKGND].push_back(
                [&picture_box](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::picture_box::on_erase_background(picture_box, w_param, l_param);
                }
            );
            map[WM_PAINT].push_back(
                [&picture_box](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::picture_box::on_paint(picture_box, w_param, l_param);
                }
            );

            return map;
        }

        /*!
            \brief Make a message handler map for a text box.

            \tparam TextBox A text box type.

            \param text_box    A text box.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename TextBox>
        static message_handler_map_type make_text_box_message_handler_map(
            TextBox&                   text_box,
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[static_cast< ::UINT>(message_handler_detail::custom_message_type::command)].push_back(
                [&text_box](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::text_box::on_tetengo2_command(text_box, w_param, l_param);
                }
            );

            return map;
        }

        /*!
            \brief Make a message handler map for a widget.

            \tparam Widget A widget type.

            \param widget      A widget.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename Widget>
        static message_handler_map_type make_widget_message_handler_map(
            Widget&                    widget,
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map{ std::move(initial_map) };

            map[WM_COMMAND].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_command(widget, w_param, l_param);
                }
            );
            map[WM_KEYDOWN].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_key_down(widget, w_param, l_param);
                }
            );
            map[WM_KEYUP].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_key_up(widget, w_param, l_param);
                }
            );
            map[WM_CHAR].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_char(widget, w_param, l_param);
                }
            );
            map[WM_LBUTTONDOWN].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_l_button_down(widget, w_param, l_param);
                }
            );
            map[WM_RBUTTONDOWN].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_r_button_down(widget, w_param, l_param);
                }
            );
            map[WM_LBUTTONUP].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_l_button_up(widget, w_param, l_param);
                }
            );
            map[WM_RBUTTONUP].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_r_button_up(widget, w_param, l_param);
                }
            );
            map[WM_MOUSEMOVE].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_mouse_move(widget, w_param, l_param);
                }
            );
            map[WM_LBUTTONDBLCLK].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_l_doubleclick(widget, w_param, l_param);
                }
            );
            map[WM_MOUSEWHEEL].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_mouse_wheel(widget, w_param, l_param);
                }
            );
            map[WM_MOUSEHWHEEL].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_mouse_h_wheel(widget, w_param, l_param);
                }
            );
            map[WM_CTLCOLORBTN].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_control_color(widget, w_param, l_param);
                }
            );
            map[WM_CTLCOLOREDIT].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_control_color(widget, w_param, l_param);
                }
            );
            map[WM_CTLCOLORLISTBOX].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_control_color(widget, w_param, l_param);
                }
            );
            map[WM_CTLCOLORSCROLLBAR].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_control_color(widget, w_param, l_param);
                }
            );
            map[WM_CTLCOLORSTATIC].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_control_color(widget, w_param, l_param);
                }
            );
            map[WM_SETCURSOR].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_set_cursor(widget, w_param, l_param);
                }
            );
            map[WM_SIZE].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_resized(widget, w_param, l_param);
                }
            );
            map[WM_SETFOCUS].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_set_focus(widget, w_param, l_param);
                }
            );
            map[WM_KILLFOCUS].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_kill_focus(widget, w_param, l_param);
                }
            );
            map[WM_VSCROLL].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_vertical_scroll(widget, w_param, l_param);
                }
            );
            map[WM_HSCROLL].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_horizontal_scroll(widget, w_param, l_param);
                }
            );
            map[WM_ERASEBKGND].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_erase_background(widget, w_param, l_param);
                }
            );
            map[WM_PAINT].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_paint(widget, w_param, l_param);
                }
            );
            map[WM_DESTROY].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_destroy(widget, w_param, l_param);
                }
            );
            map[WM_NCDESTROY].push_back(
                [&widget](const ::WPARAM w_param, const ::LPARAM l_param)
                {
                    return message_handler_detail::widget::on_ncdestroy<widget_details_type>(widget, w_param, l_param);
                }
            );

            return map;
        }

        /*!
            \brief Make a message handler map for a window.

            \tparam Window A window type.

            \param window      A window.
            \param initial_map An initial message handler map.

            \return A message handler map.
        */
        template <typename Window>
        static message_handler_map_type make_window_message_handler_map(
            Window&                    window,
            message_handler_map_type&& initial_map
        )
        {
            boost::ignore_unused(window);

            return std::move(initial_map);
        }


    private:
        // types

        using widget_details_type = widget;


        // forbidden operations

        message_handler()
        = delete;


   };


}}}


#endif
