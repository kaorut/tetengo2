/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLER_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLER_H

#include <cassert>
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

#include <boost/bind.hpp>
#include <boost/optional.hpp>
#include <boost/ref.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        namespace dialog
        {
            template <typename Dialog, typename WidgetDetails>
            boost::optional< ::LRESULT> on_command(
                Dialog&         dialog,
                const ::WPARAM  wParam,
                const ::LPARAM  lParam
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
                        ::GetDlgItem(&*dialog.details(), lo_wparam)
                    );
                    if (widget_handle != NULL)
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
            template <typename Control>
            boost::optional< ::LRESULT> on_control_color(
                Control&        control,
                const ::WPARAM  wParam,
                const ::LPARAM  lParam
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


        namespace button
        {
            template <typename Button>
            static boost::optional< ::LRESULT> on_tetengo2_command(
                Button&         button,
                const ::WPARAM  wParam,
                const ::LPARAM  lParam
            )
            {
                button.mouse_observer_set().clicked()();
            
                return boost::optional< ::LRESULT>(0);
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
                boost::bind(
                    detail::dialog::on_command<Dialog, widget_details_type>,
                    boost::ref(dialog),
                    _1,
                    _2
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

            map[WM_TETENGO2_CONTROL_COLOR].push_back(
                boost::bind(
                    detail::control::on_control_color<Control>,
                    boost::ref(control),
                    _1,
                    _2
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
            message_handler_map_type map(
                std::forward<message_handler_map_type>(initial_map)
            );

            map[WM_TETENGO2_COMMAND].push_back(
                boost::bind(
                    detail::button::on_tetengo2_command<Button>,
                    boost::ref(button),
                    _1,
                    _2
                )
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
        // types

        enum message_type
        {
            WM_TETENGO2_COMMAND = WM_APP + 1,
            WM_TETENGO2_CONTROL_COLOR,
        };


        // forbidden operations

        message_handler();


   };


}}}


#endif
