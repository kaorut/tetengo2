/*! \file
    \brief The definition of test_tetengo2::gui::type_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_TYPELIST_H)
#define TESTTETENGO2_GUI_TYPELIST_H

//#include <cstddef>
//#include <string>
//#include <utility>

#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
#include <boost/mpl/pair.hpp>

#include "tetengo2.detail.stub.alert.h"
#include "tetengo2.detail.stub.common_dialog.h"
#include "tetengo2.detail.stub.cursor.h"
#include "tetengo2.detail.stub.drawing.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.menu.h"
#include "tetengo2.detail.stub.message_handler.h"
#include "tetengo2.detail.stub.message_loop.h"
#include "tetengo2.detail.stub.unit.h"
#include "tetengo2.detail.stub.virtual_key.h"
#include "tetengo2.detail.stub.widget.h"
#include "tetengo2.gui.alert.h"
#include "tetengo2.gui.common_dialog.file_open.h"
#include "tetengo2.gui.common_dialog.file_save.h"
#include "tetengo2.gui.cursor.cursor_base.h"
#include "tetengo2.gui.cursor.system.h"
#include "tetengo2.gui.drawing.background.h"
#include "tetengo2.gui.drawing.canvas.h"
#include "tetengo2.gui.drawing.color.h"
#include "tetengo2.gui.drawing.font.h"
#include "tetengo2.gui.drawing.picture.h"
#include "tetengo2.gui.drawing.picture_reader.h"
#include "tetengo2.gui.drawing.solid_background.h"
#include "tetengo2.gui.drawing.system_color_set.h"
#include "tetengo2.gui.drawing.transparent_background.h"
#include "tetengo2.gui.drawing.widget_canvas.h"
#include "tetengo2.gui.menu.abstract_popup.h"
#include "tetengo2.gui.menu.command.h"
#include "tetengo2.gui.menu.menu_bar.h"
#include "tetengo2.gui.menu.menu_base.h"
#include "tetengo2.gui.menu.popup.h"
#include "tetengo2.gui.menu.recursive_iterator.h"
#include "tetengo2.gui.menu.separator.h"
#include "tetengo2.gui.menu.shortcut_key.h"
#include "tetengo2.gui.menu.shortcut_key_table.h"
#include "tetengo2.gui.menu.traits.h"
#include "tetengo2.gui.message.dialog_message_loop.h"
#include "tetengo2.gui.message.focus_observer_set.h"
#include "tetengo2.gui.message.keyboard_observer_set.h"
#include "tetengo2.gui.message.menu_observer_set.h"
#include "tetengo2.gui.message.message_loop_break.h"
#include "tetengo2.gui.message.mouse_observer_set.h"
#include "tetengo2.gui.message.paint_observer_set.h"
#include "tetengo2.gui.message.window_observer_set.h"
#include "tetengo2.gui.unit.em.h"
#include "tetengo2.gui.unit.pixel.h"
#include "tetengo2.gui.virtual_key.h"
#include "tetengo2.gui.widget.abstract_window.h"
#include "tetengo2.gui.widget.button.h"
#include "tetengo2.gui.widget.control.h"
#include "tetengo2.gui.widget.dialog.h"
#include "tetengo2.gui.widget.image.h"
#include "tetengo2.gui.widget.label.h"
#include "tetengo2.gui.widget.link_label.h"
#include "tetengo2.gui.widget.text_box.h"
#include "tetengo2.gui.widget.traits.abstract_window_traits.h"
#include "tetengo2.gui.widget.traits.button_traits.h"
#include "tetengo2.gui.widget.traits.control_traits.h"
#include "tetengo2.gui.widget.traits.dialog_traits.h"
#include "tetengo2.gui.widget.traits.image_traits.h"
#include "tetengo2.gui.widget.traits.label_traits.h"
#include "tetengo2.gui.widget.traits.link_label_traits.h"
#include "tetengo2.gui.widget.traits.text_box_traits.h"
#include "tetengo2.gui.widget.traits.widget_traits.h"
#include "tetengo2.gui.widget.traits.window_traits.h"
#include "tetengo2.gui.widget.widget.h"
#include "tetengo2.gui.widget.window.h"
#include "tetengo2.meta.assoc_list.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"


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
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::string string_type;
        typedef std::string exception_string_type;
        typedef tetengo2::detail::stub::encoding encoding_details_type;
        typedef
            tetengo2::text::encoding::locale<
                string_type, encoding_details_type
            >
            internal_encoding_type;
        typedef
            tetengo2::text::encoding::locale<
                tetengo2::detail::stub::widget::string_type,
                encoding_details_type
            >
            ui_encoding_type;
        typedef
            tetengo2::text::encoding::locale<
                exception_string_type, encoding_details_type
            >
            exception_encoding_type;
    }
#endif

    //! The common type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::size, detail::size_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::difference, detail::difference_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::position,
                std::pair<detail::difference_type, detail::difference_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::dimension,
                std::pair<detail::size_type, detail::size_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::string, detail::string_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::exception_string, detail::exception_string_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::path, boost::filesystem::path>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::ui_encoder,
                tetengo2::text::encoder<
                    detail::internal_encoding_type, detail::ui_encoding_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::exception_encoder,
                tetengo2::text::encoder<
                    detail::internal_encoding_type,
                    detail::exception_encoding_type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>
        type_list;


    /**** GUI Common ********************************************************/

    namespace type { namespace gui_common
    {
        struct alert;          //!< The alert type.
        struct virtual_key;    //!< The virtual key type.
        struct dimension;      //!< The dimmension type.
    }}

    //! The GUI common type list.
    typedef
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
                type::gui_common::virtual_key,
                tetengo2::gui::virtual_key<
                    boost::mpl::at<type_list, type::string>::type,
                    tetengo2::detail::stub::virtual_key
                >
            >,
        tetengo2::meta::assoc_list_end
        >>
        gui_common_type_list;


    /**** Cursor ************************************************************/

    namespace type { namespace cursor
    {
        struct cursor_base;    //!< The cursor base type.
        struct system;         //!< The system cursor type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace cursor
    {
        typedef tetengo2::detail::stub::cursor cursor_details_type;
    }}
#endif

    //! The cursor type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::cursor::cursor_base,
                tetengo2::gui::cursor::cursor_base<
                    detail::cursor::cursor_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::cursor::system,
                tetengo2::gui::cursor::system<
                    detail::cursor::cursor_details_type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>
        cursor_type_list;


    /**** Unit **************************************************************/

    namespace type { namespace unit
    {
        struct unit_details;   //!< The unit details type.
        struct em;             //!< The em unit type.
        struct pixel;          //!< The pixel unit type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace unit
    {
        typedef tetengo2::detail::stub::unit unit_details_type;
    }}
#endif

    //! The unit type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::unit::unit_details, detail::unit::unit_details_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::unit::em,
                tetengo2::gui::unit::em<
                    int, int, detail::unit::unit_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::unit::pixel,
                 tetengo2::gui::unit::pixel<int, int>
            >,
        tetengo2::meta::assoc_list_end
        >>>
        unit_type_list;


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
        typedef tetengo2::gui::drawing::color<unsigned char> color_type;
        typedef tetengo2::detail::stub::drawing drawing_details_type;
        typedef
            tetengo2::gui::drawing::background<drawing_details_type>
            background_type;
        typedef
            tetengo2::gui::drawing::transparent_background<
                drawing_details_type
            >
            transparent_background_type;
        typedef
            tetengo2::gui::drawing::font<
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<type_list, type::size>::type,
                drawing_details_type
            >
            font_type;
        typedef
            tetengo2::gui::drawing::picture<
                boost::mpl::at<type_list, type::size>::type,
                drawing_details_type
            >
            picture_type;
        typedef drawing_details_type::canvas_details_type canvas_details_type;
        typedef
            drawing_details_type::canvas_details_ptr_type
            canvas_details_ptr_type;
    }}
#endif

    //! The drawing type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::color, detail::drawing::color_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::system_color_set,
                tetengo2::gui::drawing::system_color_set<
                    detail::drawing::color_type,
                    detail::drawing::drawing_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::background, detail::drawing::background_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::solid_background,
                tetengo2::gui::drawing::solid_background<
                    detail::drawing::color_type,
                    detail::drawing::drawing_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::transparent_background,
                detail::drawing::transparent_background_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::font, detail::drawing::font_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::picture, detail::drawing::picture_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::picture_reader,
                tetengo2::gui::drawing::picture_reader<
                    detail::drawing::picture_type,
                    boost::mpl::at<type_list, type::path>::type,
                    detail::drawing::drawing_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::canvas_details,
                detail::drawing::canvas_details_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::canvas_details_ptr,
                detail::drawing::canvas_details_ptr_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::canvas,
                tetengo2::gui::drawing::canvas<
                    boost::mpl::at<type_list, type::size>::type,
                    boost::mpl::at<type_list, type::string>::type,
                    boost::mpl::at<type_list, type::dimension>::type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::drawing::background_type,
                    detail::drawing::font_type,
                    detail::drawing::picture_type,
                    detail::drawing::drawing_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::drawing::widget_canvas,
                tetengo2::gui::drawing::widget_canvas<
                    boost::mpl::at<type_list, type::size>::type,
                    boost::mpl::at<type_list, type::string>::type,
                    boost::mpl::at<type_list, type::dimension>::type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::drawing::background_type,
                    detail::drawing::font_type,
                    detail::drawing::picture_type,
                    detail::drawing::drawing_details_type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>>
        drawing_type_list;


    /**** Observer Set ******************************************************/

    namespace type { namespace observer_set
    {
        struct window_observer_set; //!< The window observer set type.
        struct focus_observer_set; //!< The focus observer set type.
        struct paint_observer_set; //!< The paint observer set type.
        struct keyboard_observer_set; //!< The keyboard observer set type.
        struct mouse_observer_set; //!< The mouse observer set type.
        struct menu_observer_set; //!< The menu observer set type.
    }}

    //! The observer set type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::observer_set::window_observer_set,
                tetengo2::gui::message::window_observer_set
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::observer_set::focus_observer_set,
                tetengo2::gui::message::focus_observer_set
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::observer_set::paint_observer_set,
                tetengo2::gui::message::paint_observer_set<
                    boost::mpl::at<
                        drawing_type_list, type::drawing::canvas
                    >::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::observer_set::keyboard_observer_set,
                tetengo2::gui::message::keyboard_observer_set<
                    boost::mpl::at<
                        gui_common_type_list, type::gui_common::virtual_key
                    >::type,
                    boost::mpl::at<type_list, type::string>::type::value_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::observer_set::mouse_observer_set,
                tetengo2::gui::message::mouse_observer_set
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::observer_set::menu_observer_set,
                tetengo2::gui::message::menu_observer_set
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>
        observer_set_type_list;


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
        typedef
            tetengo2::gui::menu::shortcut_key<
                boost::mpl::at<
                    gui_common_type_list, type::gui_common::virtual_key
                >::type
            >
            shortcut_key_type;
        typedef
            tetengo2::gui::menu::traits<
                boost::mpl::at<type_list, type::string>::type,
                shortcut_key_type,
                boost::mpl::at<type_list, type::ui_encoder>::type,
                boost::mpl::at<
                    observer_set_type_list,
                    type::observer_set::menu_observer_set
                >::type
            >
            menu_traits_type;
        typedef tetengo2::detail::stub::menu menu_details_type;
        typedef
            tetengo2::gui::menu::menu_base<
                menu_traits_type, menu_details_type
            >
            menu_base_type;
        typedef
            tetengo2::gui::menu::shortcut_key_table<
                shortcut_key_type, menu_base_type, menu_details_type
            >
            shortcut_key_table_type;
    }}
#endif

    //! The menu type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::shortcut_key, detail::menu::shortcut_key_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::menu_details, detail::menu::menu_details_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::menu_base, detail::menu::menu_base_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::abstract_popup,
                tetengo2::gui::menu::abstract_popup<
                    detail::menu::menu_traits_type,
                    detail::menu::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::menu_bar,
                tetengo2::gui::menu::menu_bar<
                    detail::menu::menu_traits_type,
                    detail::menu::shortcut_key_table_type,
                    detail::menu::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::popup,
                tetengo2::gui::menu::popup<
                    detail::menu::menu_traits_type,
                    detail::menu::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::command,
                tetengo2::gui::menu::command<
                    detail::menu::menu_traits_type,
                    detail::menu::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::separator,
                tetengo2::gui::menu::separator<
                    detail::menu::menu_traits_type,
                    detail::menu::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::recursive_iterator,
                tetengo2::gui::menu::recursive_iterator<
                    detail::menu::menu_base_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu::shortcut_key_table,
                detail::menu::shortcut_key_table_type
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>
        menu_type_list;


    /**** Widget ************************************************************/

    namespace type { namespace widget
    {
        struct widget;         //!< The widget type.
        struct abstract_window; //!< The abstract window type.
        struct window;         //!< The window type.
        struct dialog;         //!< The dialog type.
        struct control;        //!< The control type.
        struct button;         //!< The button type.
        struct image;          //!< The image type.
        struct label;          //!< The label type.
        struct link_label;     //!< The link label type.
        struct text_box;       //!< The text box type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace widget
    {
        typedef
            tetengo2::gui::widget::traits::widget_traits<
                boost::mpl::at<
                    drawing_type_list, type::drawing::widget_canvas
                >::type,
                boost::mpl::at<
                    gui_common_type_list, type::gui_common::alert
                >::type,
                boost::mpl::at<type_list, type::position>::type,
                boost::mpl::at<type_list, type::dimension>::type,
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<type_list, type::ui_encoder>::type,
                boost::mpl::at<
                    drawing_type_list, type::drawing::background
                >::type,
                boost::mpl::at<drawing_type_list, type::drawing::font>::type,
                boost::mpl::at<cursor_type_list, type::cursor::system>::type,
                boost::mpl::at<
                    observer_set_type_list,
                    type::observer_set::focus_observer_set
                >::type,
                boost::mpl::at<
                    observer_set_type_list,
                    type::observer_set::paint_observer_set
                >::type,
                boost::mpl::at<
                    observer_set_type_list,
                    type::observer_set::keyboard_observer_set
                >::type,
                boost::mpl::at<
                    observer_set_type_list,
                    type::observer_set::mouse_observer_set
                >::type
            >
            widget_traits_type;
        typedef
            tetengo2::gui::widget::traits::abstract_window_traits<
                widget_traits_type,
                boost::mpl::at<menu_type_list, type::menu::menu_bar>::type,
                tetengo2::gui::message::window_observer_set
            >
            abstract_window_traits_type;
        typedef
            tetengo2::gui::widget::traits::window_traits<
                abstract_window_traits_type
            >
            window_traits_type;
        typedef tetengo2::detail::stub::widget widget_details_type;
        typedef
            tetengo2::detail::stub::message_handler
            message_handler_details_type;
        typedef
            tetengo2::gui::widget::abstract_window<
                abstract_window_traits_type,
                widget_details_type,
                message_handler_details_type
            >
            abstract_window_type;
        typedef
            tetengo2::detail::stub::message_loop message_loop_details_type;
        typedef
            tetengo2::gui::message::dialog_message_loop<
                abstract_window_type, message_loop_details_type
            >
            dialog_message_loop_type;
        typedef
            tetengo2::gui::message::message_loop_break<
                message_loop_details_type
            >
            message_loop_break_type;
        typedef
            tetengo2::gui::widget::traits::dialog_traits<
                abstract_window_traits_type,
                dialog_message_loop_type,
                message_loop_break_type
            >
            dialog_traits_type;
        typedef
            tetengo2::gui::widget::traits::control_traits<
                widget_traits_type,
                boost::mpl::at<drawing_type_list, type::drawing::color>::type
            >
            control_traits_type;
        typedef
            tetengo2::gui::widget::traits::button_traits<control_traits_type>
            button_traits_type;
        typedef
            tetengo2::gui::widget::traits::image_traits<
                control_traits_type,
                boost::mpl::at<
                    drawing_type_list, type::drawing::picture
                >::type
            >
            image_traits_type;
        typedef
            tetengo2::gui::widget::traits::label_traits<control_traits_type>
            label_traits_type;
        typedef
            tetengo2::gui::widget::traits::link_label_traits<
                label_traits_type,
                boost::mpl::at<
                    drawing_type_list, type::drawing::solid_background
                >::type,
                boost::mpl::at<
                    drawing_type_list, type::drawing::system_color_set
                >::type
            >
            link_label_traits_type;
        typedef
            tetengo2::gui::widget::traits::text_box_traits<
                control_traits_type
            >
            text_box_traits_type;
    }}
#endif

    //! The widget type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::widget,
                tetengo2::gui::widget::widget<
                    detail::widget::widget_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::message_handler_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::abstract_window,
                detail::widget::abstract_window_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::window,
                tetengo2::gui::widget::window<
                    detail::widget::window_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::message_handler_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::dialog,
                tetengo2::gui::widget::dialog<
                    detail::widget::dialog_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::message_handler_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::control,
                tetengo2::gui::widget::control<
                    detail::widget::control_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::message_handler_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::button,
                tetengo2::gui::widget::button<
                    detail::widget::button_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::message_handler_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::image,
                tetengo2::gui::widget::image<
                    detail::widget::image_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::message_handler_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::label,
                tetengo2::gui::widget::label<
                    detail::widget::label_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::message_handler_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::link_label,
                tetengo2::gui::widget::link_label<
                    detail::widget::link_label_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::message_handler_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::widget::text_box,
                tetengo2::gui::widget::text_box<
                    detail::widget::text_box_traits_type,
                    detail::widget::widget_details_type,
                    detail::widget::message_handler_details_type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>
        widget_type_list;


    /**** Common Dialog *****************************************************/

    namespace type { namespace common_dialog
    {
        struct file_open;      //!< The file open dialog type.
        struct file_save;      //!< The file save dialog type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace common_dialog
    {
        typedef
            tetengo2::detail::stub::common_dialog common_dialog_details_type;
    }}
#endif

    //! The common dialog type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::file_open,
                tetengo2::gui::common_dialog::file_open<
                    boost::mpl::at<
                        widget_type_list, type::widget::abstract_window
                    >::type,
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
                    boost::mpl::at<
                        widget_type_list, type::widget::abstract_window
                    >::type,
                    boost::mpl::at<type_list, type::string>::type,
                    boost::mpl::at<type_list, type::path>::type,
                    boost::mpl::at<type_list, type::ui_encoder>::type,
                    detail::common_dialog::common_dialog_details_type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>
        common_dialog_type_list;


}}


#endif
