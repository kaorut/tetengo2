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
            tetengo2::text::encoding::locale<
                boost::mpl::at<detail_type_list, type::detail::widget>::type::string_type, encoding_details_type
            >;
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
        using system_color_details_type = boost::mpl::at<detail_type_list, type::detail::system_color>::type;
        using drawing_details_type = boost::mpl::at<detail_type_list, type::detail::drawing>::type;
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
                    boost::mpl::at<detail_type_list, type::detail::icon>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::widget_canvas,
                tetengo2::gui::drawing::widget_canvas<
                    detail::drawing::canvas_traits_type,
                    detail::drawing::drawing_details_type,
                    boost::mpl::at<detail_type_list, type::detail::icon>::type
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

#if !defined(DOCUMENTATION)
    namespace detail { namespace observer_set
    {
        using virtual_key_type =
            tetengo2::gui::virtual_key<
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
            >;
    }}
#endif

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
                    detail::observer_set::virtual_key_type, boost::mpl::at<type_list, type::string>::type::value_type
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
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<detail_type_list,
                type::detail::virtual_key>::type
            >;
        using menu_details_type = boost::mpl::at<detail_type_list, type::detail::menu>::type;
        using menu_base_type =
            tetengo2::gui::menu::menu_base<
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<type_list, type::ui_encoder>::type,
                menu_details_type,
                boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
                >;
        using shortcut_key_table_type =
            tetengo2::gui::menu::shortcut_key_table<
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<type_list, type::ui_encoder>::type,
                menu_details_type,
                boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
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
                    boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
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
                    boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::popup,
                tetengo2::gui::menu::popup<
                    boost::mpl::at<type_list, type::string>::type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::menu::menu_details_type,
                    boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::command,
                tetengo2::gui::menu::command<
                    boost::mpl::at<type_list, type::string>::type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::menu::menu_details_type,
                    boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::separator,
                tetengo2::gui::menu::separator<
                    boost::mpl::at<type_list, type::string>::type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::menu::menu_details_type,
                    boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
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
                    boost::mpl::at<detail_type_list, type::detail::scroll>::type
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
            tetengo2::gui::widget::widget_traits<
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
        using widget_details_traits_type =
            tetengo2::gui::widget::widget_details_traits<
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::drawing>::type,
                boost::mpl::at<detail_type_list, type::detail::icon>::type,
                boost::mpl::at<detail_type_list, type::detail::alert>::type,
                boost::mpl::at<detail_type_list, type::detail::cursor>::type,
                boost::mpl::at<detail_type_list, type::detail::scroll>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type,
                boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
            >;
        using fast_drawing_details_type = boost::mpl::at<detail_type_list, type::detail::drawing>::type;
        using widget_type = tetengo2::gui::widget::widget<widget_traits_type, widget_details_traits_type>;
        using details_font_type = boost::mpl::at<detail_type_list, type::detail::widget>::type::details_font_type;
        using menu_details_type = boost::mpl::at<detail_type_list, type::detail::menu>::type;
        using abstract_window_type =
            tetengo2::gui::widget::abstract_window<widget_traits_type, widget_details_traits_type, menu_details_type>;
        using message_loop_details_type = boost::mpl::at<detail_type_list, type::detail::message_loop>::type;
        using message_loop_type =
            tetengo2::gui::message::message_loop<abstract_window_type, message_loop_details_type>;
        using dialog_message_loop_type =
            tetengo2::gui::message::dialog_message_loop<abstract_window_type, message_loop_details_type>;
        using message_loop_break_type = tetengo2::gui::message::message_loop_break<message_loop_details_type>;
        using shell_details_type = boost::mpl::at<detail_type_list, type::detail::shell>::type;
        using mouse_capture_details_type = boost::mpl::at<detail_type_list, type::detail::mouse_capture>::type;
        using system_color_details_type = boost::mpl::at<detail_type_list, type::detail::system_color>::type;
        using timer_details_type = boost::mpl::at<detail_type_list, type::detail::timer>::type;
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
                    detail::widget::widget_traits_type,
                    detail::widget::widget_details_traits_type,
                    detail::widget::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::dialog,
                tetengo2::gui::widget::dialog<
                    detail::widget::widget_traits_type,
                    detail::widget::widget_details_traits_type,
                    detail::widget::menu_details_type,
                    detail::widget::message_loop_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::control,
                tetengo2::gui::widget::control<
                    detail::widget::widget_traits_type, detail::widget::widget_details_traits_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::custom_control,
                tetengo2::gui::widget::custom_control<
                    detail::widget::widget_traits_type,
                    detail::widget::widget_details_traits_type,
                    detail::widget::mouse_capture_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::button,
                tetengo2::gui::widget::button<
                    detail::widget::widget_traits_type, detail::widget::widget_details_traits_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::dropdown_box,
                tetengo2::gui::widget::dropdown_box<
                    detail::widget::widget_traits_type, detail::widget::widget_details_traits_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::image,
                tetengo2::gui::widget::image<
                    detail::widget::widget_traits_type, detail::widget::widget_details_traits_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::label,
                tetengo2::gui::widget::label<
                    detail::widget::widget_traits_type, detail::widget::widget_details_traits_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::link_label,
                tetengo2::gui::widget::link_label<
                    detail::widget::widget_traits_type,
                    detail::widget::widget_details_traits_type,
                    detail::widget::system_color_details_type,
                    detail::widget::shell_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::list_box,
                tetengo2::gui::widget::list_box<
                    detail::widget::widget_traits_type, detail::widget::widget_details_traits_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::map_box,
                tetengo2::gui::widget::map_box<
                    detail::widget::widget_traits_type,
                    detail::widget::widget_details_traits_type,
                    detail::widget::mouse_capture_details_type,
                    detail::widget::system_color_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::picture_box,
                tetengo2::gui::widget::picture_box<
                    detail::widget::widget_traits_type,
                    detail::widget::widget_details_traits_type,
                    detail::widget::fast_drawing_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::side_bar,
                tetengo2::gui::widget::side_bar<
                    detail::widget::widget_traits_type,
                    detail::widget::widget_details_traits_type,
                    detail::widget::mouse_capture_details_type,
                    detail::widget::system_color_details_type,
                    detail::widget::timer_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::text_box,
                tetengo2::gui::widget::text_box<
                    detail::widget::widget_traits_type, detail::widget::widget_details_traits_type
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
        using common_dialog_details_type = boost::mpl::at<detail_type_list, type::detail::common_dialog>::type;
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
