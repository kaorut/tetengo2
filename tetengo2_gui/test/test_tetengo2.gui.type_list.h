/*! \file
    \brief The definition of test_tetengo2::gui::type_list.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_TYPELIST_H)
#define TESTTETENGO2_GUI_TYPELIST_H

#include <cstddef>
#include <string>
#include <utility>

#include <boost/filesystem.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/pair.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>
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

#include "test_tetengo2.gui.detail_type_list.h"


namespace test_tetengo2 { namespace gui
{
    /**** Common ************************************************************/

    namespace type
    {
        struct size;           //!< The size type.
        struct difference;     //!< The difference type.
        struct position;       //!< The position type.
        struct dimension;      //!< The dimension type.
        struct string;         //!< The string type.
        struct exception_string; //!< The exception string type.
        struct path;           //!< The path type.
        struct ui_encoder;     //!< The UI encoder type.
        struct exception_encoder; //!< The exception encoder type.
    }

#if !defined(DOCUMENTATION)
    namespace detail
    {
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using string_type = std::string;
        using exception_string_type = std::string;
        using encoding_details_type = boost::mpl::at<detail_type_list, type::detail::encoding>::type;
        using internal_encoding_type = tetengo2::text::encoding::locale<string_type, encoding_details_type>;
        using ui_encoding_type =
            tetengo2::text::encoding::locale<tetengo2::detail::stub::widget::string_type, encoding_details_type>;
        using exception_encoding_type = tetengo2::text::encoding::locale<exception_string_type, encoding_details_type>;
    }
#endif

    //! The common type list.
    using type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::size, detail::size_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::difference, detail::difference_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::position,
                std::pair<
                    tetengo2::gui::unit::pixel<detail::difference_type>,
                    tetengo2::gui::unit::pixel<detail::difference_type>
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::dimension,
                std::pair<
                    tetengo2::gui::unit::pixel<detail::size_type>, tetengo2::gui::unit::pixel<detail::size_type>
                >
            >,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::string, detail::string_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::exception_string, detail::exception_string_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::path, boost::filesystem::path>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::ui_encoder, tetengo2::text::encoder<detail::internal_encoding_type, detail::ui_encoding_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::exception_encoder,
                tetengo2::text::encoder<detail::internal_encoding_type, detail::exception_encoding_type>
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>;


    /**** GUI Common ********************************************************/

    namespace type { namespace gui_common
    {
        struct alert;          //!< The alert type.
        struct icon;           //!< The icon type.
        struct virtual_key;    //!< The virtual key type.
    }}

    //! The GUI common type list.
    using gui_common_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::gui_common::alert,
                tetengo2::gui::alert<
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    boost::mpl::at<type_list, type::exception_encoder>::type,
                    tetengo2::detail::stub::alert
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::gui_common::icon,
                tetengo2::gui::icon<
                    boost::mpl::at<type_list, type::path>::type,
                    boost::mpl::at<type_list, type::dimension>::type,
                    tetengo2::detail::stub::icon
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::gui_common::virtual_key,
                tetengo2::gui::virtual_key<
                    boost::mpl::at<type_list, type::string>::type, tetengo2::detail::stub::virtual_key
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>;


    /**** Cursor ************************************************************/

    namespace type { namespace cursor
    {
        struct cursor_base;    //!< The cursor base type.
        struct system;         //!< The system cursor type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace cursor
    {
        using cursor_details_type = tetengo2::detail::stub::cursor;
    }}
#endif

    //! The cursor type list.
    using cursor_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::cursor::cursor_base, tetengo2::gui::cursor::cursor_base<detail::cursor::cursor_details_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::cursor::system, tetengo2::gui::cursor::system<detail::cursor::cursor_details_type>>,
        tetengo2::meta::assoc_list_end
        >>;


    /**** Unit **************************************************************/

    namespace type { namespace unit
    {
        struct unit_details;   //!< The unit details type.
        struct em;             //!< The em unit type.
        struct another_em;     //!< The another em unit type.
        struct pixel;          //!< The pixel unit type.
        struct point;          //!< The point unit type.
        struct another_point;  //!< The another point unit type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace unit
    {
        using unit_details_type = tetengo2::detail::stub::unit;
    }}
#endif

    //! The unit type list.
    using unit_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::unit::unit_details, detail::unit::unit_details_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::unit::em, tetengo2::gui::unit::em<int, detail::unit::unit_details_type>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::unit::another_em, tetengo2::gui::unit::em<unsigned short, detail::unit::unit_details_type>
            >,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::unit::pixel, tetengo2::gui::unit::pixel<int>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::unit::point, tetengo2::gui::unit::point<int, detail::unit::unit_details_type>>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::unit::another_point, tetengo2::gui::unit::point<unsigned short, detail::unit::unit_details_type>
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>;


    /**** Drawing ***********************************************************/

    namespace type { namespace drawing
    {
        struct color;          //!< The color type.
        struct system_color_set; //!< The system color set type.
        struct background;     //!< The background type.
        struct solid_background; //!< The solid background type.
        struct transparent_background; //!< The transparent background type.
        struct font;           //!< The font type.
        struct picture;        //!< The picture type.
        struct picture_reader; //!< The picture reader type.
        struct canvas_details; //!< The canvas details type.
        struct canvas_details_ptr; //!< The canvas details pointer type.
        struct canvas;         //!< The canvas type.
        struct widget_canvas;  //!< The widget canvas type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace drawing
    {
        using system_color_details_type = tetengo2::detail::stub::system_color;
        using drawing_details_type = tetengo2::detail::stub::drawing;
        using background_type = tetengo2::gui::drawing::background<drawing_details_type>;
        using solid_background_type = tetengo2::gui::drawing::solid_background<drawing_details_type>;
        using transparent_background_type = tetengo2::gui::drawing::transparent_background<drawing_details_type>;
        using font_type =
            tetengo2::gui::drawing::font<
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<type_list, type::size>::type,
                drawing_details_type
            >;
        using picture_type =
            tetengo2::gui::drawing::picture<boost::mpl::at<type_list, type::dimension>::type, drawing_details_type>;
        using color_type = tetengo2::gui::drawing::color;
        using canvas_traits_type =
            tetengo2::gui::drawing::canvas_traits<
                boost::mpl::at<type_list, type::size>::type,
                boost::mpl::at<type_list, type::size>::type,
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<type_list, type::path>::type,
                boost::mpl::at<type_list, type::position>::type,
                boost::mpl::at<type_list, type::dimension>::type,
                boost::mpl::at<type_list, type::ui_encoder>::type
            >;
        using canvas_details_type = drawing_details_type::canvas_details_type;
        using canvas_details_ptr_type = drawing_details_type::canvas_details_ptr_type;
    }}
#endif

    //! The drawing type list.
    using drawing_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::drawing::color, detail::drawing::color_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::system_color_set,
                tetengo2::gui::drawing::system_color_set<detail::drawing::system_color_details_type>
            >,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::drawing::background, detail::drawing::background_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::drawing::solid_background, detail::drawing::solid_background_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::drawing::transparent_background, detail::drawing::transparent_background_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::drawing::font, detail::drawing::font_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::drawing::picture, detail::drawing::picture_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::picture_reader,
                tetengo2::gui::drawing::picture_reader<
                    boost::mpl::at<type_list, type::path>::type,
                    boost::mpl::at<type_list, type::dimension>::type,
                    detail::drawing::drawing_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::drawing::canvas_details, detail::drawing::canvas_details_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::drawing::canvas_details_ptr, detail::drawing::canvas_details_ptr_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::canvas,
                tetengo2::gui::drawing::canvas<
                    detail::drawing::canvas_traits_type,
                    detail::drawing::drawing_details_type,
                    boost::mpl::at<gui_common_type_list, type::gui_common::icon>::type::details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::widget_canvas,
                tetengo2::gui::drawing::widget_canvas<
                    detail::drawing::canvas_traits_type,
                    detail::drawing::drawing_details_type,
                    boost::mpl::at<gui_common_type_list, type::gui_common::icon>::type::details_type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>>;


    /**** Observer Set ******************************************************/

    namespace type { namespace observer_set
    {
        struct window_observer_set; //!< The window observer set type.
        struct size_observer_set;   //!< The size observer set type.
        struct list_selection_observer_set; //!< The list selection observer set type.
        struct file_drop_observer_set; //!< The file drop observer set type.
        struct focus_observer_set; //!< The focus observer set type.
        struct paint_observer_set; //!< The paint observer set type.
        struct keyboard_observer_set; //!< The keyboard observer set type.
        struct mouse_observer_set; //!< The mouse observer set type.
        struct menu_observer_set; //!< The menu observer set type.
        struct scroll_bar_observer_set; //!< The scroll bar observer set type.
        struct text_box_observer_set; //!< The text box observer set type.
    }}

    //! The observer set type list.
    using observer_set_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::observer_set::window_observer_set, tetengo2::gui::message::window_observer_set>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::observer_set::size_observer_set, tetengo2::gui::message::size_observer_set>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::observer_set::list_selection_observer_set, tetengo2::gui::message::list_selection_observer_set
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::observer_set::file_drop_observer_set,
                tetengo2::gui::message::file_drop_observer_set<boost::mpl::at<type_list, type::path>::type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::observer_set::focus_observer_set, tetengo2::gui::message::focus_observer_set>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::observer_set::paint_observer_set,
                tetengo2::gui::message::paint_observer_set<
                    boost::mpl::at<drawing_type_list, type::drawing::canvas>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::observer_set::keyboard_observer_set,
                tetengo2::gui::message::keyboard_observer_set<
                    boost::mpl::at<gui_common_type_list, type::gui_common::virtual_key>::type,
                    boost::mpl::at<type_list, type::string>::type::value_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::observer_set::mouse_observer_set,
                tetengo2::gui::message::mouse_observer_set<
                    boost::mpl::at<type_list, type::position>::type, boost::mpl::at<type_list, type::difference>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::observer_set::menu_observer_set, tetengo2::gui::message::menu_observer_set>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::observer_set::scroll_bar_observer_set,
                tetengo2::gui::message::scroll_bar_observer_set<boost::mpl::at<type_list, type::size>::type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::observer_set::text_box_observer_set, tetengo2::gui::message::text_box_observer_set
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>;


    /**** Menu **************************************************************/

    namespace type { namespace menu
    {
        struct shortcut_key;   //!< The shortcut key type.
        struct menu_details;   //!< The menu details type.
        struct menu_base;      //!< The menu base type.
        struct abstract_popup; //!< The abstract popup type.
        struct menu_bar;       //!< The menu bar type.
        struct popup;          //!< The popup type.
        struct command;        //!< The command type.
        struct separator;      //!< The seprator type.
        struct recursive_iterator; //!< The recursive iterator type.
        struct shortcut_key_table; //!< The shortcut key table type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace menu
    {
        using shortcut_key_type =
            tetengo2::gui::menu::shortcut_key<
                boost::mpl::at<type_list, type::string>::type, tetengo2::detail::stub::virtual_key
            >;
        using menu_details_type = tetengo2::detail::stub::menu;
        using menu_base_type =
            tetengo2::gui::menu::menu_base<
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<type_list, type::ui_encoder>::type,
                menu_details_type,
                tetengo2::detail::stub::virtual_key
                >;
        using shortcut_key_table_type =
            tetengo2::gui::menu::shortcut_key_table<
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<type_list, type::ui_encoder>::type,
                menu_details_type,
                tetengo2::detail::stub::virtual_key
            >;
    }}
#endif

    //! The menu type list.
    using menu_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::menu::shortcut_key, detail::menu::shortcut_key_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::menu::menu_details, detail::menu::menu_details_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::menu::menu_base, detail::menu::menu_base_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::abstract_popup,
                tetengo2::gui::menu::abstract_popup<
                    boost::mpl::at<type_list, type::string>::type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::menu::menu_details_type,
                    tetengo2::detail::stub::virtual_key
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::menu_bar,
                tetengo2::gui::menu::menu_bar<
                    boost::mpl::at<type_list, type::string>::type,
                    detail::menu::shortcut_key_table_type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::menu::menu_details_type,
                    tetengo2::detail::stub::virtual_key
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::popup,
                tetengo2::gui::menu::popup<
                    boost::mpl::at<type_list, type::string>::type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::menu::menu_details_type,
                    tetengo2::detail::stub::virtual_key
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::command,
                tetengo2::gui::menu::command<
                    boost::mpl::at<type_list, type::string>::type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::menu::menu_details_type,
                    tetengo2::detail::stub::virtual_key
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::separator,
                tetengo2::gui::menu::separator<
                    boost::mpl::at<type_list, type::string>::type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::menu::menu_details_type,
                    tetengo2::detail::stub::virtual_key
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::recursive_iterator, tetengo2::gui::menu::recursive_iterator<detail::menu::menu_base_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::menu::shortcut_key_table, detail::menu::shortcut_key_table_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>;


    /**** Scroll ************************************************************/

    namespace type { namespace scroll
    {
        struct scroll_bar;     //!< The scroll bar type.
    }}

    //! The scroll type list.
    using scroll_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::scroll::scroll_bar,
                tetengo2::gui::scroll_bar<
                    boost::mpl::at<type_list, type::size>::type,
                    tetengo2::detail::stub::scroll
                >
            >,
        tetengo2::meta::assoc_list_end
        >;


    /**** Widget ************************************************************/

    namespace type { namespace widget
    {
        struct message_loop;   //!< The message loop type.
        struct dialog_message_loop; //!< The dialog message loop type.
        struct message_loop_break; //!< The message loop break type.
        struct details_font;   //!< The font type for widget details.
        struct widget;         //!< The widget type.
        struct abstract_window; //!< The abstract window type.
        struct window;         //!< The window type.
        struct dialog;         //!< The dialog type.
        struct control;        //!< The control type.
        struct custom_control; //!< The custom control type.
        struct button;         //!< The button type.
        struct dropdown_box;   //!< The dropdown box type.
        struct image;          //!< The image type.
        struct label;          //!< The label type.
        struct link_label;     //!< The link label type.
        struct list_box;       //!< The list box type.
        struct map_box;        //!< The map box type.
        struct picture_box;    //!< The picture box type.
        struct side_bar;       //!< The side bar type.
        struct text_box;       //!< The text box type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace widget
    {
        using widget_traits_type =
            tetengo2::gui::widget::traits::widget_traits<
                boost::mpl::at<type_list, type::size>::type,
                boost::mpl::at<type_list, type::size>::type,
                boost::mpl::at<type_list, type::difference>::type,
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<type_list, type::path>::type,
                boost::mpl::at<type_list, type::position>::type,
                boost::mpl::at<type_list, type::dimension>::type,
                boost::mpl::at<type_list, type::ui_encoder>::type,
                boost::mpl::at<type_list, type::exception_encoder>::type
            >;
        using widget_details_type = tetengo2::detail::stub::widget;
        using drawing_details_type = tetengo2::detail::stub::drawing;
        using icon_details_type = tetengo2::detail::stub::icon;
        using alert_details_type = tetengo2::detail::stub::alert;
        using cursor_details_type = tetengo2::detail::stub::cursor;
        using scroll_details_type = tetengo2::detail::stub::scroll;
        using message_handler_details_type = tetengo2::detail::stub::message_handler;
        using virtual_key_details_type = tetengo2::detail::stub::virtual_key;
        using widget_type =
            tetengo2::gui::widget::widget<
                widget_traits_type,
                widget_details_type,
                drawing_details_type,
                icon_details_type,
                alert_details_type,
                cursor_details_type,
                scroll_details_type,
                message_handler_details_type,
                virtual_key_details_type
            >;
        using abstract_window_traits_type = tetengo2::gui::widget::traits::abstract_window_traits<widget_traits_type>;
        using window_traits_type = tetengo2::gui::widget::traits::window_traits<abstract_window_traits_type>;
        using details_font_type = tetengo2::detail::stub::widget::details_font_type;
        using menu_details_type = tetengo2::detail::stub::menu;
        using abstract_window_type =
            tetengo2::gui::widget::abstract_window<
                abstract_window_traits_type,
                widget_details_type,
                drawing_details_type,
                icon_details_type,
                alert_details_type,
                cursor_details_type,
                scroll_details_type,
                message_handler_details_type,
                virtual_key_details_type,
                menu_details_type
            >;
        using message_loop_details_type = tetengo2::detail::stub::message_loop;
        using message_loop_type =
            tetengo2::gui::message::message_loop<abstract_window_type, message_loop_details_type>;
        using dialog_message_loop_type =
            tetengo2::gui::message::dialog_message_loop<abstract_window_type, message_loop_details_type>;
        using message_loop_break_type = tetengo2::gui::message::message_loop_break<message_loop_details_type>;
        using dialog_traits_type = tetengo2::gui::widget::traits::dialog_traits<abstract_window_traits_type>;
        using control_traits_type = tetengo2::gui::widget::traits::control_traits<widget_traits_type>;
        using button_traits_type = tetengo2::gui::widget::traits::button_traits<control_traits_type>;
        using dropdown_box_traits_type = tetengo2::gui::widget::traits::dropdown_box_traits<control_traits_type>;
        using image_traits_type = tetengo2::gui::widget::traits::image_traits<control_traits_type>;
        using label_traits_type = tetengo2::gui::widget::traits::label_traits<control_traits_type>;
        using shell_details_type = tetengo2::detail::stub::shell;
        using link_label_traits_type = tetengo2::gui::widget::traits::link_label_traits<label_traits_type>;
        using list_box_traits_type =
            tetengo2::gui::widget::traits::list_box_traits<
                control_traits_type,
                boost::mpl::at<type_list, type::size>::type,
                boost::mpl::at<observer_set_type_list, type::observer_set::list_selection_observer_set>::type
            >;
        using custom_control_traits_type = tetengo2::gui::widget::traits::custom_control_traits<control_traits_type>;
        using mouse_capture_details_type = tetengo2::detail::stub::mouse_capture;
        using map_box_traits_type = tetengo2::gui::widget::traits::map_box_traits<custom_control_traits_type>;
        using system_color_details_type = tetengo2::detail::stub::system_color;
        using picture_box_traits_type =
            tetengo2::gui::widget::traits::picture_box_traits<
                control_traits_type,
                boost::mpl::at<drawing_type_list, type::drawing::widget_canvas>::type,
                boost::mpl::at<observer_set_type_list, type::observer_set::paint_observer_set>::type
            >;
        using side_bar_traits_type =
            tetengo2::gui::widget::traits::side_bar_traits<custom_control_traits_type>;
        using timer_details_type = tetengo2::detail::stub::timer;
        using text_box_traits_type =
            tetengo2::gui::widget::traits::text_box_traits<
                control_traits_type,
                boost::mpl::at<observer_set_type_list, type::observer_set::text_box_observer_set>::type
            >;
    }}
#endif

    //! The widget type list.
    using widget_type_list =
        tetengo2::meta::assoc_list<boost::mpl::pair<type::widget::message_loop, detail::widget::message_loop_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::widget::dialog_message_loop, detail::widget::dialog_message_loop_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::widget::message_loop_break, detail::widget::message_loop_break_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::widget::details_font, detail::widget::details_font_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::widget::widget, detail::widget::widget_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::widget::abstract_window, detail::widget::abstract_window_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::window,
                tetengo2::gui::widget::window<
                    detail::widget::window_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::drawing_details_type,
                    detail::widget::icon_details_type,
                    detail::widget::alert_details_type,
                    detail::widget::cursor_details_type,
                    detail::widget::scroll_details_type,
                    detail::widget::message_handler_details_type,
                    detail::widget::virtual_key_details_type,
                    detail::widget::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::dialog,
                tetengo2::gui::widget::dialog<
                    detail::widget::dialog_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::drawing_details_type,
                    detail::widget::icon_details_type,
                    detail::widget::alert_details_type,
                    detail::widget::cursor_details_type,
                    detail::widget::scroll_details_type,
                    detail::widget::message_handler_details_type,
                    detail::widget::virtual_key_details_type,
                    detail::widget::menu_details_type,
                    detail::widget::message_loop_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::control,
                tetengo2::gui::widget::control<
                    detail::widget::control_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::drawing_details_type,
                    detail::widget::icon_details_type,
                    detail::widget::alert_details_type,
                    detail::widget::cursor_details_type,
                    detail::widget::scroll_details_type,
                    detail::widget::message_handler_details_type,
                    detail::widget::virtual_key_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::custom_control,
                tetengo2::gui::widget::custom_control<
                    detail::widget::custom_control_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::drawing_details_type,
                    detail::widget::icon_details_type,
                    detail::widget::alert_details_type,
                    detail::widget::cursor_details_type,
                    detail::widget::scroll_details_type,
                    detail::widget::message_handler_details_type,
                    detail::widget::virtual_key_details_type,
                    detail::widget::mouse_capture_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::button,
                tetengo2::gui::widget::button<
                    detail::widget::button_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::drawing_details_type,
                    detail::widget::icon_details_type,
                    detail::widget::alert_details_type,
                    detail::widget::cursor_details_type,
                    detail::widget::scroll_details_type,
                    detail::widget::message_handler_details_type,
                    detail::widget::virtual_key_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::dropdown_box,
                tetengo2::gui::widget::dropdown_box<
                    detail::widget::dropdown_box_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::drawing_details_type,
                    detail::widget::icon_details_type,
                    detail::widget::alert_details_type,
                    detail::widget::cursor_details_type,
                    detail::widget::scroll_details_type,
                    detail::widget::message_handler_details_type,
                    detail::widget::virtual_key_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::image,
                tetengo2::gui::widget::image<
                    detail::widget::image_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::drawing_details_type,
                    detail::widget::icon_details_type,
                    detail::widget::alert_details_type,
                    detail::widget::cursor_details_type,
                    detail::widget::scroll_details_type,
                    detail::widget::message_handler_details_type,
                    detail::widget::virtual_key_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::label,
                tetengo2::gui::widget::label<
                    detail::widget::label_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::drawing_details_type,
                    detail::widget::icon_details_type,
                    detail::widget::alert_details_type,
                    detail::widget::cursor_details_type,
                    detail::widget::scroll_details_type,
                    detail::widget::message_handler_details_type,
                    detail::widget::virtual_key_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::link_label,
                tetengo2::gui::widget::link_label<
                    detail::widget::link_label_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::drawing_details_type,
                    detail::widget::icon_details_type,
                    detail::widget::alert_details_type,
                    detail::widget::cursor_details_type,
                    detail::widget::scroll_details_type,
                    detail::widget::message_handler_details_type,
                    detail::widget::virtual_key_details_type,
                    detail::widget::system_color_details_type,
                    detail::widget::shell_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::list_box,
                tetengo2::gui::widget::list_box<
                    detail::widget::list_box_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::drawing_details_type,
                    detail::widget::icon_details_type,
                    detail::widget::alert_details_type,
                    detail::widget::cursor_details_type,
                    detail::widget::scroll_details_type,
                    detail::widget::message_handler_details_type,
                    detail::widget::virtual_key_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::map_box,
                tetengo2::gui::widget::map_box<
                    detail::widget::map_box_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::drawing_details_type,
                    detail::widget::icon_details_type,
                    detail::widget::alert_details_type,
                    detail::widget::cursor_details_type,
                    detail::widget::scroll_details_type,
                    detail::widget::message_handler_details_type,
                    detail::widget::virtual_key_details_type,
                    detail::widget::mouse_capture_details_type,
                    detail::widget::system_color_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::picture_box,
                tetengo2::gui::widget::picture_box<
                    detail::widget::picture_box_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::drawing_details_type,
                    detail::widget::icon_details_type,
                    detail::widget::alert_details_type,
                    detail::widget::cursor_details_type,
                    detail::widget::scroll_details_type,
                    detail::widget::message_handler_details_type,
                    detail::widget::virtual_key_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::side_bar,
                tetengo2::gui::widget::side_bar<
                    detail::widget::side_bar_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::drawing_details_type,
                    detail::widget::icon_details_type,
                    detail::widget::alert_details_type,
                    detail::widget::cursor_details_type,
                    detail::widget::scroll_details_type,
                    detail::widget::message_handler_details_type,
                    detail::widget::virtual_key_details_type,
                    detail::widget::mouse_capture_details_type,
                    detail::widget::system_color_details_type,
                    detail::widget::timer_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::text_box,
                tetengo2::gui::widget::text_box<
                    detail::widget::text_box_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::drawing_details_type,
                    detail::widget::icon_details_type,
                    detail::widget::alert_details_type,
                    detail::widget::cursor_details_type,
                    detail::widget::scroll_details_type,
                    detail::widget::message_handler_details_type,
                    detail::widget::virtual_key_details_type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>>>>>>>>>>;


    /**** Common Dialog *****************************************************/

    namespace type { namespace common_dialog
    {
        struct color;          //!< The color dialog type.
        struct file_open;      //!< The file open dialog type.
        struct file_save;      //!< The file save dialog type.
        struct font;           //!< The font dialog type.
        struct message_box;    //!< The message box type.
        struct button_style;   //!< The button style type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace common_dialog
    {
        using common_dialog_details_type = tetengo2::detail::stub::common_dialog;
    }}
#endif

    //! The common dialog type list.
    using common_dialog_type_list =
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::color,
                tetengo2::gui::common_dialog::color<
                    boost::mpl::at<widget_type_list, type::widget::abstract_window>::type,
                    boost::mpl::at<drawing_type_list, type::drawing::color>::type,
                    detail::common_dialog::common_dialog_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::file_open,
                tetengo2::gui::common_dialog::file_open<
                    boost::mpl::at<widget_type_list, type::widget::abstract_window>::type,
                    boost::mpl::at<type_list, type::string>::type,
                    boost::mpl::at<type_list, type::path>::type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::common_dialog::common_dialog_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::file_save,
                tetengo2::gui::common_dialog::file_save<
                    boost::mpl::at<widget_type_list, type::widget::abstract_window>::type,
                    boost::mpl::at<type_list, type::string>::type,
                    boost::mpl::at<type_list, type::path>::type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::common_dialog::common_dialog_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::font,
                tetengo2::gui::common_dialog::font<
                    boost::mpl::at<widget_type_list, type::widget::abstract_window>::type,
                    boost::mpl::at<drawing_type_list, type::drawing::font>::type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::common_dialog::common_dialog_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::message_box,
                tetengo2::gui::common_dialog::message_box<
                    boost::mpl::at<widget_type_list, type::widget::abstract_window>::type,
                    boost::mpl::at<type_list, type::string>::type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::common_dialog::common_dialog_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::button_style,
                tetengo2::gui::common_dialog::message_box_style::button_style<
                    boost::mpl::at<type_list, type::string>::type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>;


}}


#endif
