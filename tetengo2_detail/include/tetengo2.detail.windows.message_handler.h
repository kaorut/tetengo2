/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLER_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLER_H

//#include <algorithm>
//#include <cassert>
//#include <cstddef>
//#include <functional>
//#include <memory>
//#include <stdexcept>
//#include <system_error>
//#include <tuple>
#include <unordered_map>
//#include <utility>
//#include <vector>

//#include <boost/noncopyable.hpp>
//#include <boost/optional.hpp>
//#include <boost/scope_exit.hpp>
//#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.cpp11.h"
#include "tetengo2.detail.windows.error_category.h"
#include "tetengo2.detail.windows.widget.h"


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        enum message_type
        {
            WM_TETENGO2_COMMAND = WM_APP + 1,
            WM_TETENGO2_CONTROL_COLOR,
        };


        namespace widget
        {
            template <typename Widget>
            boost::optional< ::LRESULT> on_command(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                if (l_param == 0) return boost::none;

                ::PostMessageW(
                    reinterpret_cast< ::HWND>(l_param),
                    WM_TETENGO2_COMMAND,
                    w_param,
                    reinterpret_cast< ::LPARAM>(std::get<0>(*widget.details()).get())
                );
                return boost::none;
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_key_down(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                if (widget.keyboard_observer_set().key_down().empty())
                    return boost::none;

                typedef typename Widget::keyboard_observer_set_type::virtual_key_type virtual_key_type;

                const boost::optional<const virtual_key_type&> virtual_key =
                    virtual_key_type::find_by_code(static_cast<typename virtual_key_type::code_type>(w_param));
                if (!virtual_key)
                    return boost::none;

                const bool shift = ::GetKeyState(VK_SHIFT) < 0;
                const bool control = ::GetKeyState(VK_CONTROL) < 0;
                const bool meta = ::GetKeyState(VK_MENU) < 0;

                widget.keyboard_observer_set().key_down()(*virtual_key, shift, control, meta);

                return boost::make_optional< ::LRESULT>(0);
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_key_up(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                if (widget.keyboard_observer_set().key_up().empty())
                    return boost::none;

                typedef typename Widget::keyboard_observer_set_type::virtual_key_type virtual_key_type;

                const boost::optional<const virtual_key_type&> virtual_key =
                    virtual_key_type::find_by_code(static_cast<typename virtual_key_type::code_type>(w_param));
                if (!virtual_key)
                    return boost::none;

                const bool shift = ::GetKeyState(VK_SHIFT) < 0;
                const bool control = ::GetKeyState(VK_CONTROL) < 0;
                const bool meta = ::GetKeyState(VK_MENU) < 0;

                widget.keyboard_observer_set().key_up()(*virtual_key, shift, control, meta);

                return boost::make_optional< ::LRESULT>(0);
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_char(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                if (widget.keyboard_observer_set().character_input().empty())
                    return boost::none;

                typedef typename Widget::keyboard_observer_set_type::char_type char_type;

                widget.keyboard_observer_set().character_input()(static_cast<char_type>(w_param));

                return boost::make_optional< ::LRESULT>(0);
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_mouse_wheel(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                if (widget.mouse_observer_set().wheeled().empty())
                    return boost::none;

                const short delta = GET_WHEEL_DELTA_WPARAM(w_param);
                const unsigned int key_state = GET_KEYSTATE_WPARAM(w_param);

                widget.mouse_observer_set().wheeled()(
                    typename Widget::mouse_observer_set_type::delta_type(delta, WHEEL_DELTA),
                    Widget::mouse_observer_set_type::direction_vertical,
                    (key_state & MK_SHIFT) != 0,
                    (key_state & MK_CONTROL) != 0,
                    false
                );

                return boost::make_optional< ::LRESULT>(0);
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_mouse_h_wheel(
                Widget&        widget,
                const ::WPARAM w_param,
                const ::LPARAM l_param
            )
            {
                if (widget.mouse_observer_set().wheeled().empty())
                    return boost::none;

                const short delta = GET_WHEEL_DELTA_WPARAM(w_param);
                const unsigned int key_state = GET_KEYSTATE_WPARAM(w_param);

                widget.mouse_observer_set().wheeled()(
                    typename Widget::mouse_observer_set_type::delta_type(delta, WHEEL_DELTA),
                    Widget::mouse_observer_set_type::direction_horizontal,
                    (key_state & MK_SHIFT) != 0,
                    (key_state & MK_CONTROL) != 0,
                    false
                );

                return boost::make_optional< ::LRESULT>(0);
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_control_color(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                if (l_param == 0) return boost::none;

                const ::LRESULT result =
                    ::SendMessageW(reinterpret_cast< ::HWND>(l_param), WM_TETENGO2_CONTROL_COLOR, w_param, 0);

                return boost::make_optional(result, result);
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_set_cursor(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                if (!widget.cursor())
                    return boost::none;

                ::SetCursor(const_cast< ::HCURSOR>(&*widget.cursor()->details()));

                return boost::make_optional< ::LRESULT>(FALSE);
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_set_focus(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                widget.focus_observer_set().got_focus()();
                return boost::none;
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_kill_focus(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                widget.focus_observer_set().lost_focus()();
                return boost::none;
            }

            template <typename Size>
            Size new_scroll_bar_position(const ::HWND window_handle, const int scroll_code, const int style)
            {
                ::SCROLLINFO info = {};
                info.cbSize = sizeof(::SCROLLINFO);
                info.fMask = SIF_POS | SIF_RANGE | SIF_PAGE | SIF_TRACKPOS;

                if (::GetScrollInfo(window_handle, style, &info) == 0)
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(
                            std::error_code(::GetLastError(), win32_category()), "Can't obtain scroll information."
                        )
                    );
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
                    BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid scroll code."));
                }
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_vertical_scroll(
                Widget&        widget,
                const ::WPARAM w_param,
                const ::LPARAM l_param
            )
            {
                if (!widget.vertical_scroll_bar())
                    return boost::none;

                const int scroll_code = LOWORD(w_param);
                typedef typename Widget::scroll_bar_type::scroll_bar_observer_set_type::size_type size_type;
                if (scroll_code == SB_ENDSCROLL)
                {
                    return boost::none;
                }
                else if (scroll_code == SB_THUMBTRACK)
                {
                    if (widget.vertical_scroll_bar()->scroll_bar_observer_set().scrolling().empty())
                        return boost::none;
                    const size_type new_position =
                        new_scroll_bar_position<size_type>(
                            std::get<0>(*widget.details()).get(), scroll_code, SB_VERT
                        );
                    widget.vertical_scroll_bar()->scroll_bar_observer_set().scrolling()(new_position);
                }
                else
                {
                    const size_type new_position =
                        new_scroll_bar_position<size_type>(
                            std::get<0>(*widget.details()).get(), scroll_code, SB_VERT
                        );
                    if (widget.vertical_scroll_bar()->scroll_bar_observer_set().scrolled().empty())
                    {
                        widget.vertical_scroll_bar()->set_position(new_position);
                        return boost::none;
                    }
                    widget.vertical_scroll_bar()->scroll_bar_observer_set().scrolled()(new_position);
                    widget.vertical_scroll_bar()->set_position(new_position);
                }

                return boost::make_optional< ::LRESULT>(0);
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_horizontal_scroll(
                Widget&        widget,
                const ::WPARAM w_param,
                const ::LPARAM l_param
            )
            {
                if (!widget.horizontal_scroll_bar())
                    return boost::none;

                const int scroll_code = LOWORD(w_param);
                typedef typename Widget::scroll_bar_type::scroll_bar_observer_set_type::size_type size_type;
                if (scroll_code == SB_ENDSCROLL)
                {
                    return boost::none;
                }
                else if (scroll_code == SB_THUMBTRACK)
                {
                    if (widget.horizontal_scroll_bar()->scroll_bar_observer_set().scrolling().empty())
                        return boost::none;
                    const size_type new_position =
                        new_scroll_bar_position<size_type>(
                            std::get<0>(*widget.details()).get(), scroll_code, SB_HORZ
                        );
                    widget.horizontal_scroll_bar()->scroll_bar_observer_set().scrolling()(new_position);
                }
                else
                {
                    const size_type new_position =
                        new_scroll_bar_position<size_type>(
                            std::get<0>(*widget.details()).get(), scroll_code, SB_HORZ
                        );
                    if (widget.horizontal_scroll_bar()->scroll_bar_observer_set().scrolled().empty())
                    {
                        widget.horizontal_scroll_bar()->set_position(new_position);
                        return boost::none;
                    }
                    widget.horizontal_scroll_bar()->scroll_bar_observer_set().scrolled()(new_position);
                    widget.horizontal_scroll_bar()->set_position(new_position);
                }

                return boost::make_optional< ::LRESULT>(0);
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_erase_background(
                Widget&        widget,
                const ::WPARAM w_param,
                const ::LPARAM l_param
            )
            {
                if (widget.paint_observer_set().paint_background().empty())
                    return boost::none;

                typename Widget::widget_canvas_type canvas(reinterpret_cast< ::HDC>(w_param));
                if (!widget.paint_observer_set().paint_background()(canvas))
                    return boost::none;

                return boost::make_optional< ::LRESULT>(TRUE);
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_paint(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                if (widget.paint_observer_set().paint().empty())
                    return boost::none;

                ::PAINTSTRUCT paint_struct = {};
                if (!::BeginPaint(std::get<0>(*widget.details()).get(), &paint_struct))
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(
                            std::error_code(ERROR_FUNCTION_FAILED, win32_category()), "Can't begin paint."
                        )
                    );
                }
                BOOST_SCOPE_EXIT((&widget)(&paint_struct))
                {
                    ::EndPaint(std::get<0>(*widget.details()).get(), &paint_struct);
                } BOOST_SCOPE_EXIT_END;
                typename Widget::widget_canvas_type canvas(paint_struct.hdc);

                widget.paint_observer_set().paint()(canvas);

                return boost::make_optional< ::LRESULT>(0);
            }

            template <typename Widget>
            void delete_current_font(Widget& widget)
            {
                const ::HFONT font_handle =
                    reinterpret_cast< ::HFONT>(::SendMessageW(std::get<0>(*widget.details()).get(), WM_GETFONT, 0, 0));

                ::SendMessageW(std::get<0>(*widget.details()).get(), WM_SETFONT, NULL, MAKELPARAM(0, 0));

                if (font_handle && ::DeleteObject(font_handle) == 0)
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(
                            std::error_code(ERROR_FUNCTION_FAILED, win32_category()), "Can't delete previous font."
                        )
                    );
                }
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_destroy(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                delete_current_font(widget);
                return boost::make_optional< ::LRESULT>(0);
            }

            template <typename Widget, typename WidgetDetails>
            boost::optional< ::LRESULT> on_ncdestroy(Widget& widget, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                const Widget* const p_widget =
                    reinterpret_cast<const Widget*>(
                        ::RemovePropW(
                            std::get<0>(*widget.details()).get(),
                            WidgetDetails::property_key_for_cpp_instance().c_str()
                        )
                    );
                p_widget;
                assert(p_widget == &widget);

                widget.set_destroyed();

                return boost::make_optional< ::LRESULT>(0);
            }


        }


        namespace abstract_window
        {
            template <typename MenuBase>
            bool same_menu(const MenuBase& menu1, const ::UINT menu2_id)
            {
                return menu1.details()->first == menu2_id;
            }

            template <typename MenuBase>
            bool same_popup_menu(const MenuBase& menu1, const ::HMENU menu2_handle)
            {
                if (!menu1.details() || !menu2_handle) return false;
                return &*menu1.details()->second == menu2_handle;
            }

            template <typename AbstractWindow>
            boost::optional< ::LRESULT> on_command(
                AbstractWindow& abstract_window,
                const ::WPARAM  w_param,
                const ::LPARAM  l_param
            )
            {
                const ::WORD id = LOWORD(w_param);

                if (!abstract_window.has_menu_bar())
                    return boost::none;

                typedef typename AbstractWindow::menu_bar_type menu_bar_type;
                const typename menu_bar_type::recursive_iterator_type found =
                    std::find_if(
                        abstract_window.menu_bar().recursive_begin(),
                        abstract_window.menu_bar().recursive_end(),
                        TETENGO2_CPP11_BIND(
                            same_menu<typename menu_bar_type::base_type::base_type>, cpp11::placeholders_1(), id
                        )
                    );
                if (found == abstract_window.menu_bar().recursive_end())
                    return boost::none;
                found->select();

                return boost::make_optional< ::LRESULT>(0);
            }

            template <typename AbstractWindow>
            boost::optional< ::LRESULT> on_initmenupopup(
                AbstractWindow& abstract_window,
                const ::WPARAM  w_param,
                const ::LPARAM  l_param
            )
            {
                const ::HMENU handle = reinterpret_cast< ::HMENU>(w_param);

                if (!abstract_window.has_menu_bar())
                    return boost::none;

                typedef typename AbstractWindow::menu_bar_type menu_bar_type;
                const typename menu_bar_type::recursive_iterator_type found =
                    std::find_if(
                        abstract_window.menu_bar().recursive_begin(),
                        abstract_window.menu_bar().recursive_end(),
                        TETENGO2_CPP11_BIND(
                            same_popup_menu<typename menu_bar_type::base_type::base_type>,
                            cpp11::placeholders_1(),
                            handle
                        )
                    );
                if (found == abstract_window.menu_bar().recursive_end())
                    return boost::none;
                found->select();

                return boost::make_optional< ::LRESULT>(0);
            }

            template <typename AbstractWindow>
            boost::optional< ::LRESULT> on_resized(
                AbstractWindow& abstract_window,
                const ::WPARAM  w_param,
                const ::LPARAM  l_param
            )
            {
                if (abstract_window.window_observer_set().resized().empty())
                    return boost::none;

                abstract_window.window_observer_set().resized()();

                return boost::none;
            }

            template <typename AbstractWindow>
            boost::optional< ::LRESULT> on_close(
                AbstractWindow& abstract_window,
                const ::WPARAM  w_param,
                const ::LPARAM  l_param
            )
            {
                if (abstract_window.window_observer_set().closing().empty())
                    return boost::none;

                bool cancel = false;
                abstract_window.window_observer_set().closing()(cancel);
                return boost::make_optional< ::LRESULT>(cancel, 0);
            }

            template <typename AbstractWindow>
            boost::optional< ::LRESULT> on_query_end_session(
                AbstractWindow& abstract_window,
                const ::WPARAM  w_param,
                const ::LPARAM  l_param
            )
            {
                if (abstract_window.window_observer_set().closing().empty())
                    return boost::none;

                bool cancel = false;
                abstract_window.window_observer_set().closing()(cancel);
                return boost::make_optional< ::LRESULT>(cancel, FALSE);
            }

            template <typename AbstractWindow>
            boost::optional< ::LRESULT> on_destroy(
                AbstractWindow& abstract_window,
                const ::WPARAM  w_param,
                const ::LPARAM  l_param
            )
            {
                if (abstract_window.window_observer_set().destroyed().empty())
                    return boost::none;

                abstract_window.window_observer_set().destroyed()();

                return boost::none;
            }


        }


        namespace dialog
        {
            template <typename Dialog, typename WidgetDetails>
            boost::optional< ::LRESULT> on_command(Dialog& dialog, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                const ::WORD hi_wparam = HIWORD(w_param);
                const ::WORD lo_wparam = LOWORD(w_param);
                if (hi_wparam == 0 && (lo_wparam == IDOK || lo_wparam == IDCANCEL))
                {
                    const ::HWND widget_handle = reinterpret_cast< ::HWND>(l_param);
                    assert(
                        widget_handle == ::GetDlgItem(std::get<0>(*dialog.details()).get(), lo_wparam)
                    );
                    if (widget_handle)
                    {
                        WidgetDetails::p_widget_from<typename Dialog::base_type::base_type>(widget_handle)->click();
                    }
                    else
                    {
                        dialog.set_result(lo_wparam == IDOK ? Dialog::result_accepted : Dialog::result_canceled);
                        dialog.close();
                    }
                    return boost::make_optional< ::LRESULT>(0);
                }

                return boost::none;
            }

            template <typename Dialog, typename WidgetDetails>
            boost::optional< ::LRESULT> on_syscommand(Dialog& dialog, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                if (w_param == SC_CLOSE)
                {
                    const ::HWND widget_handle = ::GetDlgItem(std::get<0>(*dialog.details()).get(), IDCANCEL);
                    if (widget_handle)
                    {
                        WidgetDetails::p_widget_from<typename Dialog::base_type::base_type>(widget_handle)->click();
                    }
                    else
                    {
                        dialog.set_result(Dialog::result_canceled);
                        dialog.close();
                    }
                    return boost::make_optional< ::LRESULT>(0);
                }

                return boost::none;
            }

            ::HWND first_child_window_handle(::HWND parent_handle);

            inline ::BOOL WINAPI first_child_window_handle_iter(const ::HWND child_handle, const ::LPARAM l_param)
            {
                ::HWND* p_result = reinterpret_cast< ::HWND*>(l_param);
                if (!p_result) return FALSE;

                const ::LONG style = ::GetWindowLongW(child_handle, GWL_STYLE);
                if ((static_cast< ::DWORD>(style) & WS_TABSTOP) != 0)
                {
                    *p_result = child_handle;
                    return FALSE;
                }

                const ::HWND grandchild_handle = first_child_window_handle(child_handle);
                if (grandchild_handle)
                {
                    *p_result = grandchild_handle;
                    return FALSE;
                }

                return TRUE;
            }

            inline ::HWND first_child_window_handle(const ::HWND parent_handle)
            {
                ::HWND child_handle = NULL;
                ::EnumChildWindows(
                    parent_handle, first_child_window_handle_iter, reinterpret_cast< ::LPARAM>(&child_handle)
                );

                return child_handle;
            }

            template <typename Dialog, typename WidgetDetails>
            boost::optional< ::LRESULT> on_set_focus(Dialog& dialog, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                if (std::get<2>(*dialog.details()))
                {
                    ::SetFocus(std::get<2>(*dialog.details()));
                    return boost::make_optional< ::LRESULT>(0);
                }

                const ::HWND child_handle = first_child_window_handle(std::get<0>(*dialog.details()).get());
                if (child_handle)
                {
                    ::SetFocus(child_handle);
                    return boost::make_optional< ::LRESULT>(0);
                }

                return boost::none;
            }

            
        }


        namespace control
        {
            template <typename Button>
            boost::optional< ::LRESULT> on_tetengo2_command(
                Button&        button,
                const ::WPARAM w_param,
                const ::LPARAM l_param
            )
            {
                button.mouse_observer_set().clicked()();

                return boost::make_optional< ::LRESULT>(0);
            }

            template <typename Control>
            boost::optional< ::LRESULT> on_control_color(
                Control&       control,
                const ::WPARAM w_param,
                const ::LPARAM l_param
            )
            {
                if (!control.background() && !control.text_color())
                    return boost::none;

                const ::HDC device_context = reinterpret_cast< ::HDC>(w_param);
                if (!control.paint_observer_set().paint_background().empty())
                {
                    typename Control::base_type::widget_canvas_type canvas(device_context);
                    control.paint_observer_set().paint_background()(canvas);
                }

                if (control.text_color())
                {
                    const ::COLORREF previous_color =
                        ::SetTextColor(
                            device_context,
                            RGB(
                                control.text_color()->red(),
                                control.text_color()->green(),
                                control.text_color()->blue()
                            )
                        );
                    if (previous_color == CLR_INVALID)
                    {
                        BOOST_THROW_EXCEPTION(
                            std::system_error(
                                std::error_code(ERROR_FUNCTION_FAILED, win32_category()), "Can't set text color."
                            )
                        );
                    }
                }
                const int previous_background_mode = ::SetBkMode(device_context, TRANSPARENT);
                if (previous_background_mode == 0)
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(
                            std::error_code(ERROR_FUNCTION_FAILED, win32_category()), "Can't set background mode."
                        )
                    );
                }

                return boost::make_optional(reinterpret_cast< ::LRESULT>(::GetStockObject(NULL_BRUSH)));
            }

            template <typename Control>
            boost::optional< ::LRESULT> on_set_focus(Control& control, const ::WPARAM w_param, const ::LPARAM l_param)
            {
                if (control.has_parent())
                {
                    typename Control::base_type& dialog = control.root_ancestor();

                    std::get<2>(*dialog.details()) = std::get<0>(*control.details()).get();
                }

                return boost::none;
            }


        }


        namespace picture_box
        {
            template <typename PictureBox>
            boost::optional< ::LRESULT> on_erase_background(
                PictureBox&    picture_box,
                const ::WPARAM w_param,
                const ::LPARAM l_param
            )
            {
                if (picture_box.fast_paint_observer_set().paint().empty())
                    return boost::none;

                return boost::make_optional< ::LRESULT>(TRUE);
            }

            template <typename PictureBox>
            boost::optional< ::LRESULT> on_paint(
                PictureBox&    picture_box,
                const ::WPARAM w_param,
                const ::LPARAM l_param
            )
            {
                if (picture_box.fast_paint_observer_set().paint().empty())
                    return boost::none;

                ::PAINTSTRUCT paint_struct = {};
                if (!::BeginPaint(std::get<0>(*picture_box.details()).get(), &paint_struct))
                {
                    BOOST_THROW_EXCEPTION(
                        std::system_error(
                            std::error_code(ERROR_FUNCTION_FAILED, win32_category()), "Can't begin paint."
                        )
                    );
                }
                BOOST_SCOPE_EXIT((&picture_box)(&paint_struct))
                {
                    ::EndPaint(std::get<0>(*picture_box.details()).get(), &paint_struct);
                } BOOST_SCOPE_EXIT_END;

                const std::unique_ptr<typename PictureBox::fast_canvas_type> p_canvas =
                    picture_box.create_fast_canvas();

                picture_box.fast_paint_observer_set().paint()(*p_canvas);

                return boost::make_optional< ::LRESULT>(0);
            }


        }


    }
#endif


    /*!
        \brief The class for a detail implementation of a message handler.
    */
    class message_handler : private boost::noncopyable
    {
    public:
        // types

        //! The detail implementation type of a widget.
        typedef widget widget_details_type;

        //! The message handler type.
        typedef
            std::function<boost::optional< ::LRESULT> (::WPARAM, ::LPARAM)>
            message_handler_type;

        //! The message handler map type.
        typedef
            std::unordered_map< ::UINT, std::vector<message_handler_type>>
            message_handler_map_type;


        // static functions

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
            message_handler_map_type map(std::forward<message_handler_map_type>(initial_map));

            map[WM_COMMAND].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_command<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_KEYDOWN].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_key_down<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_KEYUP].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_key_up<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_CHAR].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_char<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_MOUSEWHEEL].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_mouse_wheel<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_MOUSEHWHEEL].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_mouse_h_wheel<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_CTLCOLORBTN].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_control_color<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_CTLCOLOREDIT].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_control_color<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_CTLCOLORLISTBOX].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_control_color<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_CTLCOLORSCROLLBAR].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_control_color<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_CTLCOLORSTATIC].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_control_color<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_SETCURSOR].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_set_cursor<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_SETFOCUS].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_set_focus<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_KILLFOCUS].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_kill_focus<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_VSCROLL].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_vertical_scroll<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_HSCROLL].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_horizontal_scroll<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_ERASEBKGND].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_erase_background<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_PAINT].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_paint<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_DESTROY].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_destroy<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_NCDESTROY].push_back(
                TETENGO2_CPP11_BIND(
                    detail::widget::on_ncdestroy<Widget, widget_details_type>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );

            return map;
        }

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
            message_handler_map_type map(std::forward<message_handler_map_type>(initial_map));

            map[WM_COMMAND].push_back(
                TETENGO2_CPP11_BIND(
                    detail::abstract_window::on_command<AbstractWindow>,
                    cpp11::ref(abstract_window),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_INITMENUPOPUP].push_back(
                TETENGO2_CPP11_BIND(
                    detail::abstract_window::on_initmenupopup<AbstractWindow>,
                    cpp11::ref(abstract_window),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_SIZE].push_back(
                TETENGO2_CPP11_BIND(
                    detail::abstract_window::on_resized<AbstractWindow>,
                    cpp11::ref(abstract_window),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_CLOSE].push_back(
                TETENGO2_CPP11_BIND(
                    detail::abstract_window::on_close<AbstractWindow>,
                    cpp11::ref(abstract_window),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_QUERYENDSESSION].push_back(
                TETENGO2_CPP11_BIND(
                    detail::abstract_window::on_query_end_session<AbstractWindow>,
                    cpp11::ref(abstract_window),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_DESTROY].push_back(
                TETENGO2_CPP11_BIND(
                    detail::abstract_window::on_destroy<AbstractWindow>,
                    cpp11::ref(abstract_window),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );

            return map;
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
            message_handler_map_type map(std::forward<message_handler_map_type>(initial_map));

            map[WM_COMMAND].push_back(
                TETENGO2_CPP11_BIND(
                    detail::dialog::on_command<Dialog, widget_details_type>,
                    cpp11::ref(dialog),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_SYSCOMMAND].push_back(
                TETENGO2_CPP11_BIND(
                    detail::dialog::on_syscommand<Dialog, widget_details_type>,
                    cpp11::ref(dialog),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_SETFOCUS].push_back(
                TETENGO2_CPP11_BIND(
                    detail::dialog::on_set_focus<Dialog, widget_details_type>,
                    cpp11::ref(dialog),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
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
            return std::forward<message_handler_map_type>(initial_map);
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
            message_handler_map_type map(std::forward<message_handler_map_type>(initial_map));

            map[detail::WM_TETENGO2_COMMAND].push_back(
                TETENGO2_CPP11_BIND(
                    detail::control::on_tetengo2_command<Control>,
                    cpp11::ref(control),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[detail::WM_TETENGO2_CONTROL_COLOR].push_back(
                TETENGO2_CPP11_BIND(
                    detail::control::on_control_color<Control>,
                    cpp11::ref(control),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_SETFOCUS].push_back(
                TETENGO2_CPP11_BIND(
                    detail::control::on_set_focus<Control>,
                    cpp11::ref(control),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
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
            return std::forward<message_handler_map_type>(initial_map);
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
            return std::forward<message_handler_map_type>(initial_map);
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
            return std::forward<message_handler_map_type>(initial_map);
        }

        /*!
            \brief Make a message handler map for a picture box.

            \tparam TextBox A picture box type.

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
            message_handler_map_type map(std::forward<message_handler_map_type>(initial_map));

            map[WM_ERASEBKGND].push_back(
                TETENGO2_CPP11_BIND(
                    detail::picture_box::on_erase_background<PictureBox>,
                    cpp11::ref(picture_box),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_PAINT].push_back(
                TETENGO2_CPP11_BIND(
                    detail::picture_box::on_paint<PictureBox>,
                    cpp11::ref(picture_box),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
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
            return std::forward<message_handler_map_type>(initial_map);
        }


    private:
        // forbidden operations

        message_handler();


   };


}}}


#endif
