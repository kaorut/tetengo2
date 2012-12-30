/*! \file
    \brief The definition of tetengo2::detail::windows::message_handler.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLER_H)
#define TETENGO2_DETAIL_WINDOWS_MESSAGEHANDLER_H

//#include <functional>
#include <unordered_map>
//#include <utility>
//#include <vector>

//#include <boost/noncopyable.hpp>
//#include <boost/optional.hpp>

//#pragma warning (push)
//#pragma warning (disable: 4005)
//#include <intsafe.h>
//#include <stdint.h>
//#pragma warning(pop)
//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.cpp11.h"
#include "tetengo2.detail.windows.error_category.h"
#include "tetengo2.detail.windows.message_handler_detail.abstra.h"
#include "tetengo2.detail.windows.message_handler_detail.button.h"
#include "tetengo2.detail.windows.message_handler_detail.contro.h"
#include "tetengo2.detail.windows.message_handler_detail.dialog.h"
#include "tetengo2.detail.windows.message_handler_detail.messag.h"
#include "tetengo2.detail.windows.message_handler_detail.list_b.h"
#include "tetengo2.detail.windows.message_handler_detail.pictur.h"
#include "tetengo2.detail.windows.message_handler_detail.widget.h"
#include "tetengo2.detail.windows.widget.h"


namespace tetengo2 { namespace detail { namespace windows
{
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
            message_handler_map_type map(std::move(initial_map));

            map[WM_COMMAND].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_command<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_KEYDOWN].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_key_down<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_KEYUP].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_key_up<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_CHAR].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_char<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_MOUSEWHEEL].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_mouse_wheel<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_MOUSEHWHEEL].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_mouse_h_wheel<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_CTLCOLORBTN].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_control_color<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_CTLCOLOREDIT].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_control_color<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_CTLCOLORLISTBOX].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_control_color<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_CTLCOLORSCROLLBAR].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_control_color<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_CTLCOLORSTATIC].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_control_color<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_SETCURSOR].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_set_cursor<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_SETFOCUS].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_set_focus<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_KILLFOCUS].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_kill_focus<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_VSCROLL].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_vertical_scroll<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_HSCROLL].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_horizontal_scroll<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_ERASEBKGND].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_erase_background<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_PAINT].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_paint<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_DESTROY].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_destroy<Widget>,
                    cpp11::ref(widget),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_NCDESTROY].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::widget::on_ncdestroy<Widget, widget_details_type>,
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
            message_handler_map_type map(std::move(initial_map));

            map[WM_COMMAND].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::abstract_window::on_command<AbstractWindow>,
                    cpp11::ref(abstract_window),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_INITMENUPOPUP].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::abstract_window::on_initmenupopup<AbstractWindow>,
                    cpp11::ref(abstract_window),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_SIZE].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::abstract_window::on_resized<AbstractWindow>,
                    cpp11::ref(abstract_window),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_CLOSE].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::abstract_window::on_close<AbstractWindow>,
                    cpp11::ref(abstract_window),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_QUERYENDSESSION].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::abstract_window::on_query_end_session<AbstractWindow>,
                    cpp11::ref(abstract_window),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_DESTROY].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::abstract_window::on_destroy<AbstractWindow>,
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
            message_handler_map_type map(std::move(initial_map));

            map[WM_COMMAND].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::dialog::on_command<Dialog, widget_details_type>,
                    cpp11::ref(dialog),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_SYSCOMMAND].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::dialog::on_syscommand<Dialog, widget_details_type>,
                    cpp11::ref(dialog),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_SETFOCUS].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::dialog::on_set_focus<Dialog, widget_details_type>,
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
            return std::move(initial_map);
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
            message_handler_map_type map(std::move(initial_map));

            map[message_handler_detail::custom_message_type::control_color].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::control::on_control_color<Control>,
                    cpp11::ref(control),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_SETFOCUS].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::control::on_set_focus<Control>,
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
            message_handler_map_type map(std::move(initial_map));

            map[message_handler_detail::custom_message_type::command].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::button::on_tetengo2_command<Button>,
                    cpp11::ref(button),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
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
            message_handler_map_type map(std::move(initial_map));

            map[message_handler_detail::custom_message_type::command].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::list_box::on_tetengo2_command<ListBox>,
                    cpp11::ref(list_box),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );

            return map;
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
            message_handler_map_type map(std::move(initial_map));

            map[WM_ERASEBKGND].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::picture_box::on_erase_background<PictureBox>,
                    cpp11::ref(picture_box),
                    cpp11::placeholders_1(),
                    cpp11::placeholders_2()
                )
            );
            map[WM_PAINT].push_back(
                TETENGO2_CPP11_BIND(
                    message_handler_detail::picture_box::on_paint<PictureBox>,
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
            return std::move(initial_map);
        }


    private:
        // forbidden operations

        message_handler();


   };


}}}


#endif
