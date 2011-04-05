/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLER_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLER_H

#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

#include <boost/bind.hpp>
#include <boost/optional.hpp>
#include <boost/ref.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>


namespace tetengo2 { namespace detail { namespace windows
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
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
        \brief The class for a detail implementation of a message handler.
    */
    class message_handler
    {
    public:
        // types

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
