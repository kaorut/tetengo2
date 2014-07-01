/*! \file
    \brief The definition of test_tetengo2::gui::detail_type_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_DETAILTYPELIST_H)
#define TESTTETENGO2_GUI_DETAILTYPELIST_H

#include <boost/mpl/pair.hpp>
#include <boost/predef.h>

#include <tetengo2.h>
#include <tetengo2/detail/stub/alert.h>
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
#include <tetengo2/detail/stub/unit.h>
#include <tetengo2/detail/stub/virtual_key.h>
#include <tetengo2/detail/stub/widget.h>
#if BOOST_COMP_MSVC
#   include <tetengo2/detail/windows/encoding.h>
#else
#   include <tetengo2/detail/unixos/encoding.h>
#endif


namespace test_tetengo2 { namespace gui
{
    namespace type { namespace detail
    {
        struct alert;           //!< The alert type.
        struct common_dialog;   //!< The common dialog type.
        struct cursor;          //!< The cursor type.
        struct drawing;         //!< The drawing type.
        struct encoding;        //!< The encoding type.
        struct icon;            //!< The icon type.
        struct menu;            //!< The menu type.
        struct message_handler; //!< The message handler type.
        struct message_loop;    //!< The message loop type.
        struct mouse_capture;   //!< The mouse_capture_type.
        struct scroll;          //!< The scroll type.
        struct shell;           //!< The shell type.
        struct system_color;    //!< The system color type.
        struct timer;           //!< The timer type.
        struct unit;            //!< The unit type.
        struct virtual_key;     //!< The virtual key type.
        struct widget;          //!< The widget type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace detail
    {
        using alert_details_type = tetengo2::detail::stub::alert;
        using common_dialog_details_type = tetengo2::detail::stub::common_dialog;
        using cursor_details_type = tetengo2::detail::stub::cursor;
        using drawing_details_type = tetengo2::detail::stub::drawing;
#if BOOST_COMP_MSVC
        using encoding_details_type = tetengo2::detail::windows::encoding;
#else
        using encoding_details_type = tetengo2::detail::unixos::encoding;
#endif
        using icon_details_type = tetengo2::detail::stub::icon;
        using menu_details_type = tetengo2::detail::stub::menu;
        using message_handler_details_type = tetengo2::detail::stub::message_handler;
        using message_loop_details_type = tetengo2::detail::stub::message_loop;
        using mouse_capture_details_type = tetengo2::detail::stub::mouse_capture;
        using scroll_details_type = tetengo2::detail::stub::scroll;
        using shell_details_type = tetengo2::detail::stub::shell;
        using system_color_details_type = tetengo2::detail::stub::system_color;
        using timer_details_type = tetengo2::detail::stub::timer;
        using unit_details_type = tetengo2::detail::stub::unit;
        using virtual_key_details_type = tetengo2::detail::stub::virtual_key;
        using widget_details_type = tetengo2::detail::stub::widget;
    }}
#endif

    //! The detail type list.
    using detail_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::alert, detail::detail::alert_details_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::detail::common_dialog, detail::detail::common_dialog_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::cursor, detail::detail::cursor_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::drawing, detail::detail::drawing_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::encoding, detail::detail::encoding_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::icon, detail::detail::icon_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::menu, detail::detail::menu_details_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::detail::message_handler, detail::detail::message_handler_details_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::detail::message_loop, detail::detail::message_loop_details_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::detail::mouse_capture, detail::detail::mouse_capture_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::scroll, detail::detail::scroll_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::shell, detail::detail::shell_details_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::detail::system_color, detail::detail::system_color_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::timer, detail::detail::timer_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::unit, detail::detail::unit_details_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::detail::virtual_key, detail::detail::virtual_key_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::detail::widget, detail::detail::widget_details_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>>>>>>>;


}}


#endif
