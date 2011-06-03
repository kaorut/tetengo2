/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLER_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLER_H

#include <algorithm>
#include <cassert>
#include <cstddef>
//#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

#include <boost/optional.hpp>
#include <boost/scope_exit.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.cpp0x.h"


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
            boost::optional< ::LRESULT> on_command(
                Widget&        widget,
                const ::WPARAM wParam,
                const ::LPARAM lParam
            )
            {
                if (lParam == 0) return boost::optional< ::LRESULT>();

                ::PostMessageW(
                    reinterpret_cast< ::HWND>(lParam),
                    WM_TETENGO2_COMMAND,
                    wParam,
                    reinterpret_cast< ::LPARAM>(widget.details()->first.get())
                );
                return boost::optional< ::LRESULT>();
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_erase_background(
                Widget&        widget,
                const ::WPARAM wParam,
                const ::LPARAM lParam
            )
            {
                if (!widget.background())
                    return boost::optional< ::LRESULT>();

                typename Widget::canvas_type canvas(
                    reinterpret_cast< ::HDC>(wParam)
                );
                widget.erase_background(canvas);

                return boost::optional< ::LRESULT>(TRUE);
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_control_color(
                Widget&        widget,
                const ::WPARAM wParam,
                const ::LPARAM lParam
            )
            {
                if (lParam == 0) return boost::optional< ::LRESULT>();

                const ::LRESULT result =
                    ::SendMessageW(
                        reinterpret_cast< ::HWND>(lParam),
                        WM_TETENGO2_CONTROL_COLOR,
                        wParam,
                        0
                    );

                return
                    !result ?
                    boost::optional< ::LRESULT>() :
                    boost::optional< ::LRESULT>(result);
            }

            ::HCURSOR default_cursor_handle(const ::HWND window_handle)
            {
                const ::HCURSOR cursor_handle =
                    reinterpret_cast< ::HCURSOR>(
                        ::GetClassLongPtrW(window_handle, GCLP_HCURSOR)
                    );
                if (!cursor_handle)
                {
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error("Can't get default cursor handle.")
                    );
                }

                return cursor_handle;
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_set_cursor(
                Widget&        widget,
                const ::WPARAM wParam,
                const ::LPARAM lParam
            )
            {
                if (
                    LOWORD(lParam) != HTCLIENT || HIWORD(lParam) == 0
                )
                {
                    ::SetCursor(
                        default_cursor_handle(&*widget.details()->first)
                    );
                    return boost::optional< ::LRESULT>(FALSE);
                }

                ::SetCursor(
                    const_cast< ::HCURSOR>(&*widget.cursor().details())
                );

                return boost::optional< ::LRESULT>(TRUE);
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_paint(
                Widget&        widget,
                const ::WPARAM wParam,
                const ::LPARAM lParam
            )
            {
                if (widget.paint_observer_set().paint().empty())
                    return boost::optional< ::LRESULT>();

                ::PAINTSTRUCT paint_struct = {};
                if (
                    !::BeginPaint(
                        widget.details()->first.get(), &paint_struct
                    )
                )
                {
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error("Can't begin paint.")
                    );
                }
                BOOST_SCOPE_EXIT((&widget)(&paint_struct))
                {
                    ::EndPaint(widget.details()->first.get(), &paint_struct);
                } BOOST_SCOPE_EXIT_END;
                typename Widget::canvas_type canvas(paint_struct.hdc);

                widget.paint_observer_set().paint()(canvas);

                return boost::optional< ::LRESULT>(0);
            }

            template <typename Widget>
            void delete_current_font(Widget& widget)
            {
                const ::HFONT font_handle =
                    reinterpret_cast< ::HFONT>(
                        ::SendMessageW(
                            widget.details()->first.get(), WM_GETFONT, 0, 0
                        )
                    );

                ::SendMessageW(
                    widget.details()->first.get(),
                    WM_SETFONT,
                    NULL,
                    MAKELPARAM(0, 0)
                );

                if (font_handle && ::DeleteObject(font_handle) == 0)
                {
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error("Can't delete previous font.")
                    );
                }
            }

            template <typename Widget>
            boost::optional< ::LRESULT> on_destroy(
                Widget&        widget,
                const ::WPARAM wParam,
                const ::LPARAM lParam
            )
            {
                delete_current_font(widget);
                return boost::optional< ::LRESULT>(0);
            }

            template <typename Widget, typename WidgetDetails>
            boost::optional< ::LRESULT> on_ncdestroy(
                Widget&        widget,
                const ::WPARAM wParam,
                const ::LPARAM lParam
            )
            {
                const Widget* const p_widget =
                    reinterpret_cast<const Widget*>(
                        ::RemovePropW(
                            widget.details()->first.get(),
                            WidgetDetails::property_key_for_cpp_instance().c_str()
                        )
                    );
                assert(p_widget == &widget);

                widget.set_destroyed();

                return boost::optional< ::LRESULT>(0);
            }


        }


        namespace abstract_window
        {
            template <typename Menu>
            bool same_menu(const Menu& menu1, const ::UINT menu2_id)
            {
                return menu1.details()->first == menu2_id;
            }

            template <typename Menu>
            bool same_popup_menu(
                const Menu&   menu1,
                const ::HMENU menu2_handle
            )
            {
                if (!menu1.details() || !menu2_handle) return false;
                return &*menu1.details()->second == menu2_handle;
            }

            template <typename AbstractWindow>
            boost::optional< ::LRESULT> on_command(
                AbstractWindow& abstract_window,
                const ::WPARAM  wParam,
                const ::LPARAM  lParam
            )
            {
                const ::WORD source = HIWORD(wParam);
                const ::WORD id = LOWORD(wParam);

                if (source != 0)
                    return boost::optional< ::LRESULT>();

                if (!abstract_window.has_main_menu())
                    return boost::optional< ::LRESULT>();

                typedef
                    typename AbstractWindow::main_menu_type main_menu_type;
                const typename main_menu_type::recursive_iterator
                found = std::find_if(
                    abstract_window.main_menu().recursive_begin(),
                    abstract_window.main_menu().recursive_end(),
                    TETENGO2_CPP0X_BIND(
                        same_menu<
                            typename main_menu_type::base_type::base_type
                        >,
                        tetengo2::cpp0x::placeholders_1(),
                        id
                    )
                );
                if (found == abstract_window.main_menu().recursive_end())
                    return boost::optional< ::LRESULT>();
                found->select();

                return boost::optional< ::LRESULT>(0);
            }

            template <typename AbstractWindow>
            boost::optional< ::LRESULT> on_initmenupopup(
                AbstractWindow& abstract_window,
                const ::WPARAM  wParam,
                const ::LPARAM  lParam
            )
            {
                const ::HMENU handle = reinterpret_cast< ::HMENU>(wParam);

                if (!abstract_window.has_main_menu())
                    return boost::optional< ::LRESULT>();

                typedef
                    typename AbstractWindow::main_menu_type main_menu_type;
                const typename main_menu_type::recursive_iterator
                found = std::find_if(
                    abstract_window.main_menu().recursive_begin(),
                    abstract_window.main_menu().recursive_end(),
                    TETENGO2_CPP0X_BIND(
                        same_popup_menu<
                            typename main_menu_type::base_type::base_type
                        >,
                        tetengo2::cpp0x::placeholders_1(),
                        handle
                    )
                );
                if (found == abstract_window.main_menu().recursive_end())
                    return boost::optional< ::LRESULT>();
                found->select();

                return boost::optional< ::LRESULT>(0);
            }

            template <typename AbstractWindow>
            boost::optional< ::LRESULT> on_destroy(
                AbstractWindow& abstract_window,
                const ::WPARAM  wParam,
                const ::LPARAM  lParam
            )
            {
                if (abstract_window.window_observer_set().destroyed().empty())
                    return boost::optional< ::LRESULT>();

                abstract_window.window_observer_set().destroyed()();

                return boost::optional< ::LRESULT>();
            }


        }


        namespace dialog
        {
            template <typename Dialog, typename WidgetDetails>
            boost::optional< ::LRESULT> on_command(
                Dialog&        dialog,
                const ::WPARAM wParam,
                const ::LPARAM lParam
            )
            {
                const ::WORD hi_wparam = HIWORD(wParam);
                const ::WORD lo_wparam = LOWORD(wParam);
                if (
                    hi_wparam == 0 &&
                    (lo_wparam == IDOK || lo_wparam == IDCANCEL)
                )
                {
                    const ::HWND widget_handle =
                        reinterpret_cast< ::HWND>(lParam);
                    assert(
                        widget_handle ==
                        ::GetDlgItem(dialog.details()->first.get(), lo_wparam)
                    );
                    if (widget_handle)
                    {
                        WidgetDetails::p_widget_from<
                            typename Dialog::base_type::base_type
                        >(widget_handle)->click();
                    }
                    else
                    {
                        dialog.set_result(
                            lo_wparam == IDOK ?
                            Dialog::result_accepted : Dialog::result_canceled
                        );
                        dialog.close();
                    }
                    return boost::optional< ::LRESULT>(0);
                }

                return boost::optional< ::LRESULT>();
            }


        }


        namespace control
        {
            template <typename Button>
            static boost::optional< ::LRESULT> on_tetengo2_command(
                Button&        button,
                const ::WPARAM wParam,
                const ::LPARAM lParam
            )
            {
                button.mouse_observer_set().clicked()();

                return boost::optional< ::LRESULT>(0);
            }

            template <typename Control>
            boost::optional< ::LRESULT> on_control_color(
                Control&       control,
                const ::WPARAM wParam,
                const ::LPARAM lParam
            )
            {
                if (!control.background())
                    return boost::optional< ::LRESULT>();

                const ::HDC device_context = reinterpret_cast< ::HDC>(wParam);
                typename Control::base_type::canvas_type canvas(
                    device_context
                );
                control.erase_background(canvas);

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
                            std::runtime_error("Can't set text color.")
                        );
                    }
                }
                const int previous_background_mode =
                    ::SetBkMode(device_context, TRANSPARENT);
                if (previous_background_mode == 0)
                {
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error("Can't set background mode.")
                    );
                }

                return boost::optional< ::LRESULT>(
                    reinterpret_cast< ::LRESULT>(::GetStockObject(NULL_BRUSH))
                );
            }


        }


    }
#endif


    /*!
        \brief The class template for a detail implementation of a message
               handler.

        \tparam WidgetDetails A detail implementation type of a widget.
    */
    template <typename WidgetDetails>
    class message_handler
    {
    public:
        // types

        //! The detail implementation type of a widget.
        typedef WidgetDetails widget_details_type;

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
            message_handler_map_type map(
                std::forward<message_handler_map_type>(initial_map)
            );

            map[WM_COMMAND].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::widget::on_command<Widget>,
                    tetengo2::cpp0x::ref(widget),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
                )
            );
            map[WM_ERASEBKGND].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::widget::on_erase_background<Widget>,
                    tetengo2::cpp0x::ref(widget),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
                )
            );
            map[WM_CTLCOLORBTN].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::widget::on_control_color<Widget>,
                    tetengo2::cpp0x::ref(widget),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
                )
            );
            map[WM_CTLCOLOREDIT].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::widget::on_control_color<Widget>,
                    tetengo2::cpp0x::ref(widget),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
                )
            );
            map[WM_CTLCOLORLISTBOX].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::widget::on_control_color<Widget>,
                    tetengo2::cpp0x::ref(widget),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
                )
            );
            map[WM_CTLCOLORSCROLLBAR].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::widget::on_control_color<Widget>,
                    tetengo2::cpp0x::ref(widget),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
                )
            );
            map[WM_CTLCOLORSTATIC].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::widget::on_control_color<Widget>,
                    tetengo2::cpp0x::ref(widget),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
                )
            );
            map[WM_SETCURSOR].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::widget::on_set_cursor<Widget>,
                    tetengo2::cpp0x::ref(widget),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
                )
            );
            map[WM_PAINT].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::widget::on_paint<Widget>,
                    tetengo2::cpp0x::ref(widget),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
                )
            );
            map[WM_DESTROY].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::widget::on_destroy<Widget>,
                    tetengo2::cpp0x::ref(widget),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
                )
            );
            map[WM_NCDESTROY].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::widget::on_ncdestroy<Widget, widget_details_type>,
                    tetengo2::cpp0x::ref(widget),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
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
        static message_handler_map_type
        make_abstract_window_message_handler_map(
            AbstractWindow&            abstract_window,
            message_handler_map_type&& initial_map
        )
        {
            message_handler_map_type map(
                std::forward<message_handler_map_type>(initial_map)
            );

            map[WM_COMMAND].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::abstract_window::on_command<AbstractWindow>,
                    tetengo2::cpp0x::ref(abstract_window),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
                )
            );
            map[WM_INITMENUPOPUP].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::abstract_window::on_initmenupopup<AbstractWindow>,
                    tetengo2::cpp0x::ref(abstract_window),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
                )
            );
            map[WM_DESTROY].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::abstract_window::on_destroy<AbstractWindow>,
                    tetengo2::cpp0x::ref(abstract_window),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
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
            message_handler_map_type map(
                std::forward<message_handler_map_type>(initial_map)
            );

            map[WM_COMMAND].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::dialog::on_command<Dialog, widget_details_type>,
                    tetengo2::cpp0x::ref(dialog),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
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
            message_handler_map_type map(
                std::forward<message_handler_map_type>(initial_map)
            );

            map[detail::WM_TETENGO2_COMMAND].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::control::on_tetengo2_command<Control>,
                    tetengo2::cpp0x::ref(control),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
                )
            );

            map[detail::WM_TETENGO2_CONTROL_COLOR].push_back(
                TETENGO2_CPP0X_BIND(
                    detail::control::on_control_color<Control>,
                    tetengo2::cpp0x::ref(control),
                    tetengo2::cpp0x::placeholders_1(),
                    tetengo2::cpp0x::placeholders_2()
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


    private:
        // forbidden operations

        message_handler();


   };


}}}


#endif
