/*! \file
    \brief The definition of test_tetengo2::gui::detail_type_list.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_DETAILTYPELIST_H)
#define TESTTETENGO2_GUI_DETAILTYPELIST_H

#include <tetengo2/detail/stub/common_dialog.h>
#include <tetengo2/detail/stub/cursor.h>
#include <tetengo2/detail/stub/drawing.h>
#include <tetengo2/detail/stub/icon.h>
#include <tetengo2/detail/stub/menu.h>
#include <tetengo2/detail/stub/message_handler.h>
#include <tetengo2/detail/stub/message_loop.h>
#include <tetengo2/detail/stub/mouse_capture.h>
#include <tetengo2/detail/stub/scroll.h>
#include <tetengo2/detail/stub/shell.h>
#include <tetengo2/detail/stub/system_color.h>
#include <tetengo2/detail/stub/timer.h>
#include <tetengo2/detail/stub/virtual_key.h>
#include <tetengo2/detail/stub/widget.h>


namespace test_tetengo2 { namespace gui {
    namespace type_list {
    /**** Detail Implementation **************************************************************************************/

#if !defined(DOCUMENTATION)
        namespace detail { namespace detail { namespace test {
            using common_dialog_details_type = tetengo2::detail::stub::common_dialog;

            using drawing_details_type = tetengo2::detail::stub::drawing;

            using icon_details_type = tetengo2::detail::stub::icon;

            using cursor_details_type = tetengo2::detail::stub::cursor;

            using menu_details_type = tetengo2::detail::stub::menu;

            using message_handler_details_type = tetengo2::detail::stub::message_handler;

            using message_loop_details_type = tetengo2::detail::stub::message_loop;

            using mouse_capture_details_type = tetengo2::detail::stub::mouse_capture;

            using scroll_details_type = tetengo2::detail::stub::scroll;

            using shell_details_type = tetengo2::detail::stub::shell;

            using system_color_details_type = tetengo2::detail::stub::system_color;

            using timer_details_type = tetengo2::detail::stub::timer;

            using virtual_key_details_type = tetengo2::detail::stub::virtual_key;

            using widget_details_type = tetengo2::detail::stub::widget;

        }}}
#endif

        /*!
            \brief The detail type list for the testing.
        */
        struct detail_for_test
        {
            //! The common dialog type.
            using common_dialog_type = detail::detail::test::common_dialog_details_type;

            //! The drawing type.
            using drawing_type = detail::detail::test::drawing_details_type;

            //! The icon type.
            using icon_type = detail::detail::test::icon_details_type;

            //! The cursor type.
            using cursor_type = detail::detail::test::cursor_details_type;

            //! The menu type.
            using menu_type = detail::detail::test::menu_details_type;

            //! The message handler type.
            using message_handler_type = detail::detail::test::message_handler_details_type;

            //! The message loop type.
            using message_loop_type = detail::detail::test::message_loop_details_type;

            //! The mouse_capture_type.
            using mouse_capture_type = detail::detail::test::mouse_capture_details_type;

            //! The scroll type.
            using scroll_type = detail::detail::test::scroll_details_type;

            //! The shell type.
            using shell_type = detail::detail::test::shell_details_type;

            //! The system color type.
            using system_color_type = detail::detail::test::system_color_details_type;

            //! The timer type.
            using timer_type = detail::detail::test::timer_details_type;

            //! The virtual key type.
            using virtual_key_type = detail::detail::test::virtual_key_details_type;

            //! The widget type.
            using widget_type = detail::detail::test::widget_details_type;
        };
    }
}}


#endif
