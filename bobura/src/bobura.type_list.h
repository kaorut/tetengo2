/*! \file
    \brief The definition of bobura::type_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_TYPELIST_H)
#define BOBURA_TYPELIST_H

//#include <cstddef>
//#include <iterator>
//#include <string>
//#include <tuple>
//#include <utility>

//#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
//#include <boost/mpl/insert_range.hpp>
//#include <boost/mpl/pair.hpp>
//#include <boost/rational.hpp>
//#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2.detail.windows.alert.h>
#include <tetengo2.detail.windows.common_dialog.h>
#include <tetengo2.detail.windows.cursor.h>
#include <tetengo2.detail.windows.encoding.h>
#include <tetengo2.detail.windows.gdiplus.drawing.h>
#include <tetengo2.detail.windows.gdiplus.gui_fixture.h>
#include <tetengo2.detail.windows.gui_fixture.h>
#include <tetengo2.detail.windows.menu.h>
#include <tetengo2.detail.windows.message_handler.h>
#include <tetengo2.detail.windows.message_loop.h>
#include <tetengo2.detail.windows.unit.h>
#include <tetengo2.detail.windows.virtual_key.h>
#include <tetengo2.detail.windows.widget.h>
#include <tetengo2.gui.alert.h>
#include <tetengo2.gui.common_dialog.file_open.h>
#include <tetengo2.gui.cursor.system.h>
#include <tetengo2.gui.drawing.background.h>
#include <tetengo2.gui.drawing.color.h>
#include <tetengo2.gui.drawing.font.h>
#include <tetengo2.gui.drawing.picture.h>
#include <tetengo2.gui.drawing.picture_reader.h>
#include <tetengo2.gui.drawing.transparent_background.h>
#include <tetengo2.gui.drawing.widget_canvas.h>
#include <tetengo2.gui.fixture.h>
#include <tetengo2.gui.menu.abstract_popup.h>
#include <tetengo2.gui.menu.command.h>
#include <tetengo2.gui.menu.menu_bar.h>
#include <tetengo2.gui.menu.menu_base.h>
#include <tetengo2.gui.menu.popup.h>
#include <tetengo2.gui.menu.separator.h>
#include <tetengo2.gui.menu.shortcut_key.h>
#include <tetengo2.gui.menu.shortcut_key_table.h>
#include <tetengo2.gui.menu.traits.h>
#include <tetengo2.gui.message.dialog_message_loop.h>
#include <tetengo2.gui.message.menu_observer_set.h>
#include <tetengo2.gui.message.message_loop.h>
#include <tetengo2.gui.message.message_loop_break.h>
#include <tetengo2.gui.message.mouse_observer_set.h>
#include <tetengo2.gui.message.paint_observer_set.h>
#include <tetengo2.gui.message.window_observer_set.h>
#include <tetengo2.gui.unit.em.h>
#include <tetengo2.gui.virtual_key.h>
#include <tetengo2.gui.widget.button.h>
#include <tetengo2.gui.widget.dialog.h>
#include <tetengo2.gui.widget.image.h>
#include <tetengo2.gui.widget.label.h>
#include <tetengo2.gui.widget.link_label.h>
#include <tetengo2.gui.widget.abstract_window.h>
#include <tetengo2.gui.widget.traits.abstract_window_traits.h>
#include <tetengo2.gui.widget.traits.button_traits.h>
#include <tetengo2.gui.widget.traits.control_traits.h>
#include <tetengo2.gui.widget.traits.dialog_traits.h>
#include <tetengo2.gui.widget.traits.image_traits.h>
#include <tetengo2.gui.widget.traits.label_traits.h>
#include <tetengo2.gui.widget.traits.link_label_traits.h>
#include <tetengo2.gui.widget.traits.widget_traits.h>
#include <tetengo2.gui.widget.traits.window_traits.h>
#include <tetengo2.gui.widget.window.h>
#include <tetengo2.message.messages.h>
#include <tetengo2.message.message_catalog.h>
#include <tetengo2.message.message_catalog_parser.h>
#include <tetengo2.meta.assoc_list.h>
#include <tetengo2.text.encoder.h>
#include <tetengo2.text.encoding.locale.h>
#include <tetengo2.text.encoding.utf8.h>
#include <tetengo2.text.grammar.json.h>
#include <tetengo2.text.pull_parser.h>
#include <tetengo2.text.push_parser.h>

#include "bobura.about_dialog.h"
#include "bobura.bobura.h"
#include "bobura.command.set.h"
#include "bobura.command.type_list_impl.h"
#include "bobura.main_window.h"
#include "bobura.message.type_list_impl.h"
#include "bobura.model.station.h"
#include "bobura.model.train.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.timetable.h"
#include "bobura.model.timetable_info.station_location.h"
#include "bobura.model.train_info.stop.h"
#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"
#include "bobura.settings.h"
#include "bobura.timetable_model.h"


namespace bobura
{
    /**** Common ************************************************************/

    namespace type
    {
        struct difference;     //!< The difference type.
        struct size;           //!< The size type.
        struct string;         //!< The string type.
        struct io_string;      //!< The I/O string.
        struct path;           //!< The path type.
        struct json_grammar;   //!< The JSON grammar type.
        struct push_parser;    //!< The push parser type.
        struct pull_parser;    //!< The pull parser_type.
        struct settings;       //!< The settings type.
    }

#if !defined(DOCUMENTATION)
    namespace detail { namespace common
    {
        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;
        typedef std::wstring string_type;
        typedef std::string io_string_type;
        typedef boost::filesystem::path path_type;
        typedef
            boost::spirit::multi_pass<std::istreambuf_iterator<
                io_string_type::value_type>
            >
            input_stream_iterator_type;
        typedef
            tetengo2::text::grammar::json<input_stream_iterator_type>
            json_grammar_type;
        typedef
            tetengo2::text::push_parser<
                input_stream_iterator_type, json_grammar_type, int, double
            >
            push_parser_type;
        typedef
            tetengo2::text::pull_parser<push_parser_type, size_type>
            pull_parser_type;
        typedef settings<string_type, path_type> settings_type;
    }}
#endif

    //! The common type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::difference, detail::common::difference_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::size, detail::common::size_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::string, detail::common::string_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::path, detail::common::path_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::json_grammar, detail::common::json_grammar_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::push_parser, detail::common::push_parser_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::pull_parser, detail::common::pull_parser_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::settings, detail::common::settings_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>
        common_type_list;


    /**** Model *************************************************************/

    namespace type
    {
        struct model;          //!< The model type.
    }

#if !defined(DOCUMENTATION)
    namespace detail { namespace model
    {
        typedef
            ::bobura::model::station_info::local<
                boost::mpl::at<common_type_list, type::string>::type
            >
            local_type;
        typedef
            ::bobura::model::station<
                boost::mpl::at<common_type_list, type::string>::type,
                local_type
            >
            station_type;
        typedef
            ::bobura::model::timetable_info::station_location<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::size>::type
            >
            station_location_type;
        typedef
            ::bobura::model::train_info::time<
                boost::mpl::at<common_type_list, type::size>::type,
                ::bobura::model::train_info::time_span<
                    boost::mpl::at<common_type_list, type::difference>::type
                >
            >
            time_type;
        typedef
            ::bobura::model::train_info::stop<
                time_type,
                boost::mpl::at<common_type_list, type::string>::type
            >
            stop_type;
        typedef
            ::bobura::model::train<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                stop_type
            >
            train_type;
        typedef
            ::bobura::model::timetable<station_location_type, train_type>
            timetable_type;
    }}
#endif

    //! The common type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model,
                ::bobura::timetable_model<detail::model::timetable_type>
            >,
        tetengo2::meta::assoc_list_end
        >
        model_type_list;


    /**** Locale ************************************************************/

    namespace type
    {
        struct ui_encoder;     //!< The encoder type for the user interface.
        struct exception_encoder; //!< The encoder type for exceptions.
        struct message_catalog_encoder; //!< The encoder type for the
                                        //!< message catalog.
        struct locale_name_encoder; //!< The encoder type for locale names.

        struct message_catalog_parser; //!< The message catalog parser type.
        struct messages_facet; //!< The messages facet type.
        struct message_catalog; //!< The message catalog type.
    }

#if !defined(DOCUMENTATION)
    namespace detail { namespace locale
    {
        typedef tetengo2::detail::windows::encoding encoding_details_type;
        typedef
            tetengo2::text::encoding::locale<
                boost::mpl::at<common_type_list, type::string>::type,
                encoding_details_type
            >
            internal_encoding_type;
        typedef
            tetengo2::text::encoding::locale<
                std::wstring, encoding_details_type
            >
            ui_encoding_type;
        typedef
            tetengo2::text::encoding::utf8<encoding_details_type>
            exception_encoding_type;
        typedef
            tetengo2::text::encoding::utf8<encoding_details_type>
            message_catalog_encoding_type;
        typedef
            tetengo2::text::encoding::locale<
                std::string, encoding_details_type
            >
            locale_name_encoding_type;
        typedef
            tetengo2::text::encoder<
                internal_encoding_type, message_catalog_encoding_type
            >
            message_catalog_encoder_type;
        typedef
            tetengo2::message::message_catalog_parser<
                boost::mpl::at<common_type_list, type::pull_parser>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                message_catalog_encoder_type
            >
            message_catalog_parser_type;
        typedef
            tetengo2::text::encoder<
                internal_encoding_type, locale_name_encoding_type
            >
            locale_name_encoder_type;
        typedef
            tetengo2::message::messages<
                boost::mpl::at<common_type_list, type::path>::type,
                message_catalog_parser_type,
                locale_name_encoder_type
            >
            messages_type;
    }}
#endif

    //! The type list for the locale.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::ui_encoder,
                tetengo2::text::encoder<
                    detail::locale::internal_encoding_type,
                    detail::locale::ui_encoding_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::exception_encoder,
                tetengo2::text::encoder<
                    detail::locale::internal_encoding_type,
                    detail::locale::exception_encoding_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::message_catalog_encoder,
                detail::locale::message_catalog_encoder_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::locale_name_encoder,
                detail::locale::locale_name_encoder_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::message_catalog_parser,
                detail::locale::message_catalog_parser_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::messages_facet, detail::locale::messages_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::message_catalog,
                tetengo2::message::message_catalog<
                    detail::locale::messages_type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>
        locale_type_list;


    /**** User Interface ****************************************************/

    namespace type
    {
        struct gui_fixture;    //!< The GUI fixture type.
        struct position;       //!< The position type.
        struct dimension;      //!< The dimension type.
        struct picture;        //!< The picture type.
        struct picture_reader; //!< The picture reader type.
        struct canvas;         //!< The canvas type.
        struct alert;          //!< The alert type.
        struct window;         //!< The window type.
        struct menu_bar;       //!< The menu bar type.
        struct popup_menu;     //!< The popup menu type.
        struct menu_command;   //!< The menu command type.
        struct menu_separator; //!< The menu separator type;
        struct dialog;         //!< The dialog type.
        struct label;          //!< The label type.
        struct link_label;     //!< The link label type.
        struct image;          //!< The image type.
        struct button;         //!< The button type.
        struct message_loop;   //!< The message loop type.
        struct message_loop_break; //!< The message loop break type.
        struct transparent_background; //!< The transparent background type.
    }

#if !defined(DOCUMENTATION)
    namespace detail { namespace ui
    {
        typedef
            std::tuple<
                tetengo2::detail::windows::gui_fixture,
                tetengo2::detail::windows::gdiplus::gui_fixture
            >
            gui_fixture_details_tuple_type;
        typedef
            tetengo2::gui::fixture<
               gui_fixture_details_tuple_type
            >
            gui_fixture_type;
        typedef tetengo2::detail::windows::unit unit_details_type;
        typedef
            tetengo2::gui::unit::em<
                boost::rational<
                    boost::mpl::at<common_type_list, type::difference>::type
                >,
                boost::mpl::at<common_type_list, type::difference>::type,
                unit_details_type
            >
            unit_difference_type;
        typedef
            std::pair<unit_difference_type, unit_difference_type>
            position_type;
        typedef
            tetengo2::gui::unit::em<
                boost::rational<
                    boost::mpl::at<common_type_list, type::size>::type
                >,
                boost::mpl::at<common_type_list, type::size>::type,
                unit_details_type
            >
            unit_size_type;
        typedef std::pair<unit_size_type, unit_size_type> dimension_type;
        typedef
            tetengo2::detail::windows::gdiplus::drawing drawing_details_type;
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
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::size>::type,
                drawing_details_type
            >
            font_type;
        typedef
            tetengo2::gui::drawing::picture<
                unit_size_type, drawing_details_type
            >
            picture_type;
        typedef
            tetengo2::gui::drawing::picture_reader<
                picture_type,
                boost::mpl::at<common_type_list, type::path>::type,
                drawing_details_type
            >
            picture_reader_type;
        typedef
            tetengo2::gui::drawing::widget_canvas<
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                dimension_type,
                boost::mpl::at<locale_type_list, type::ui_encoder>::type,
                background_type,
                font_type,
                picture_type,
                drawing_details_type
            >
            canvas_type;
        typedef
            tetengo2::detail::windows::alert<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<locale_type_list, type::ui_encoder>::type
            >
            alert_details_type;
        typedef
            tetengo2::gui::alert<
                boost::mpl::at<locale_type_list, type::ui_encoder>::type,
                boost::mpl::at<
                    locale_type_list, type::exception_encoder
                >::type,
                alert_details_type
            >
            alert_type;
        typedef
            tetengo2::gui::cursor::system<tetengo2::detail::windows::cursor>
            system_cursor_type;
        typedef
            tetengo2::gui::widget::traits::widget_traits<
                canvas_type,
                alert_type,
                position_type,
                dimension_type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<locale_type_list, type::ui_encoder>::type,
                background_type,
                font_type,
                system_cursor_type,
                tetengo2::gui::message::paint_observer_set<canvas_type>,
                tetengo2::gui::message::mouse_observer_set
            >
            widget_traits_type;
        typedef tetengo2::detail::windows::widget widget_details_type;
        typedef
            tetengo2::detail::windows::message_handler<widget_details_type>
            message_handler_details_type;
        typedef
            tetengo2::gui::menu::shortcut_key<
                tetengo2::gui::virtual_key<
                    tetengo2::detail::windows::virtual_key<
                        boost::mpl::at<common_type_list, type::string>::type
                    >
                >
            >
            shortcut_key_type;
        typedef
            tetengo2::gui::menu::traits<
                boost::mpl::at<common_type_list, type::string>::type,
                shortcut_key_type,
                boost::mpl::at<locale_type_list, type::ui_encoder>::type,
                tetengo2::gui::message::menu_observer_set
            >
            menu_traits_type;
        typedef tetengo2::detail::windows::menu menu_details_type;
        typedef
            tetengo2::gui::menu::abstract_popup<
                menu_traits_type, menu_details_type
            >
            abstract_popup_menu_type;
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
        typedef
            tetengo2::gui::menu::menu_bar<
                menu_traits_type, shortcut_key_table_type, menu_details_type
            >
            menu_bar_type;
        typedef
            tetengo2::gui::widget::traits::abstract_window_traits<
                widget_traits_type,
                menu_bar_type,
                tetengo2::gui::message::window_observer_set
            >
            abstract_window_traits_type;
        typedef
            tetengo2::gui::widget::abstract_window<
                abstract_window_traits_type,
                widget_details_type,
                message_handler_details_type
            >
            abstract_window_type;
        typedef
            tetengo2::gui::widget::traits::window_traits<
                abstract_window_traits_type
            >
            window_traits_type;
        typedef
            tetengo2::gui::widget::window<
                window_traits_type,
                widget_details_type,
                message_handler_details_type
            >
            window_type;
        typedef
            tetengo2::detail::windows::message_loop message_loop_details_type;
        typedef
            tetengo2::gui::message::message_loop<
                abstract_window_type, message_loop_details_type
            >
            message_loop_type;
        typedef
            tetengo2::gui::message::message_loop_break<
                message_loop_details_type
            >
            message_loop_break_type;
        typedef
            tetengo2::gui::message::dialog_message_loop<
                abstract_window_type, message_loop_details_type
            >
            dialog_message_loop_type;
        typedef
            tetengo2::gui::widget::traits::dialog_traits<
                abstract_window_traits_type,
                dialog_message_loop_type,
                message_loop_break_type
            >
            dialog_traits_type;
        typedef
            tetengo2::gui::widget::dialog<
                dialog_traits_type,
                widget_details_type,
                message_handler_details_type
            >
            dialog_type;
        typedef tetengo2::gui::drawing::color<unsigned char> color_type;
        typedef
            tetengo2::gui::widget::traits::control_traits<
                widget_traits_type, color_type
            >
            control_traits_type;
        typedef
            tetengo2::gui::widget::traits::label_traits<control_traits_type>
            label_traits_type;
        typedef
            tetengo2::gui::widget::label<
                label_traits_type,
                widget_details_type,
                message_handler_details_type
            >
            label_type;
        typedef
            tetengo2::gui::widget::traits::link_label_traits<label_traits_type>
            link_label_traits_type;
        typedef
            tetengo2::gui::widget::link_label<
                link_label_traits_type,
                widget_details_type,
                message_handler_details_type
            >
            link_label_type;
        typedef
            tetengo2::gui::widget::traits::image_traits<
                control_traits_type, picture_type
            >
            image_traits_type;
        typedef
            tetengo2::gui::widget::image<
                image_traits_type,
                widget_details_type,
                message_handler_details_type
            >
            image_type;
        typedef
            tetengo2::gui::widget::traits::button_traits<control_traits_type>
            button_traits_type;
        typedef
            tetengo2::gui::widget::button<
                button_traits_type,
                widget_details_type,
                message_handler_details_type
            >
            button_type;
    }}
#endif

    //! The type list for the user interface.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::gui_fixture, detail::ui::gui_fixture_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::position, detail::ui::position_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::dimension, detail::ui::dimension_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::picture, detail::ui::picture_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::picture_reader, detail::ui::picture_reader_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::canvas, detail::ui::canvas_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::alert, detail::ui::alert_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::window, detail::ui::window_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu_bar, detail::ui::menu_bar_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::popup_menu,
                tetengo2::gui::menu::popup<
                    detail::ui::menu_traits_type,
                    detail::ui::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu_command,
                tetengo2::gui::menu::command<
                    detail::ui::menu_traits_type,
                    detail::ui::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::menu_separator,
                tetengo2::gui::menu::separator<
                    detail::ui::menu_traits_type,
                    detail::ui::menu_details_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::dialog, detail::ui::dialog_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::label, detail::ui::label_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::link_label, detail::ui::link_label_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::image, detail::ui::image_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::button, detail::ui::button_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::message_loop, detail::ui::message_loop_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::message_loop_break, detail::ui::message_loop_break_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::transparent_background,
                detail::ui::transparent_background_type
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>>>>>>>>>>
        ui_type_list;


    /**** Common Dialog *****************************************************/

    namespace type
    {
        struct file_open_dialog; //!< The file open dialog type.
    }

    //! The type list for the commong dialogs.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::file_open_dialog,
                tetengo2::gui::common_dialog::file_open<
                    boost::mpl::at<ui_type_list, type::window>::type,
                    boost::mpl::at<common_type_list, type::string>::type,
                    boost::mpl::at<common_type_list, type::path>::type,
                    boost::mpl::at<locale_type_list, type::ui_encoder>::type,
                    tetengo2::detail::windows::common_dialog
                >
            >,
        tetengo2::meta::assoc_list_end
        >
        common_dialog_type_list;


    /**** About Dialog ******************************************************/

    namespace type
    {
        struct about_dialog;   //!< The about dialog type.
    }

    //! The type list for the about dialog.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::about_dialog,
                about_dialog<
                    boost::mpl::at<ui_type_list, type::dialog>::type,
                    boost::mpl::at<
                        locale_type_list, type::message_catalog
                    >::type,
                    boost::mpl::at<common_type_list, type::settings>::type,
                    boost::mpl::at<ui_type_list, type::label>::type,
                    boost::mpl::at<ui_type_list, type::link_label>::type,
                    boost::mpl::at<ui_type_list, type::image>::type,
                    boost::mpl::at<ui_type_list, type::button>::type,
                    boost::mpl::at<ui_type_list, type::picture_reader>::type,
                    boost::mpl::at<
                        ui_type_list, type::transparent_background
                    >::type,
                    message::about_dialog::type_list<
                        boost::mpl::at<ui_type_list, type::dialog>::type
                    >::type
                >
            >,
        tetengo2::meta::assoc_list_end
        >
        about_dialog_type_list;


    /**** Command ***********************************************************/

    namespace type
    {
        struct command_set;    //!< The command set type.
    }

#if !defined(DOCUMENTATION)
    namespace detail { namespace command
    {
        typedef
            ::bobura::command::type_list<
                boost::mpl::at<ui_type_list, type::window>::type,
                boost::mpl::at<
                    common_dialog_type_list, type::file_open_dialog
                >::type,
                boost::mpl::at<
                    about_dialog_type_list, type::about_dialog
                >::type,
                boost::mpl::at<model_type_list, type::model>::type,
                boost::mpl::at<
                    locale_type_list, type::message_catalog
                >::type
            >::type
            type_list;
    }}
#endif

    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::command_set,
                command::set<detail::command::type_list>
            >,
        tetengo2::meta::assoc_list_end
        >
        command_type_list;


    /**** Main Window *******************************************************/

    namespace type
    {
        struct main_window;    //!< The main window type.
        struct main_window_message_type_list; //!< The main window message
                                              //!< type list.
    }

#if !defined(DOCUMENTATION)
    namespace detail { namespace main_window
    {
        typedef
            message::main_window::type_list<
                boost::mpl::at<
                    detail::command::type_list,
                    ::bobura::command::type::command
                >::type,
                boost::mpl::at<ui_type_list, type::canvas>::type,
                boost::mpl::at<ui_type_list, type::position>::type,
                boost::mpl::at<ui_type_list, type::picture_reader>::type
            >::type
            message_type_list;
    }}
#endif

    //! The type list for the main window.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::main_window,
                main_window<
                    boost::mpl::at<ui_type_list, type::window>::type,
                    boost::mpl::at<
                        locale_type_list, type::message_catalog
                    >::type,
                    boost::mpl::at<common_type_list, type::settings>::type,
                    boost::mpl::at<
                        ui_type_list, type::message_loop_break
                    >::type,
                    detail::main_window::message_type_list
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::main_window_message_type_list,
                detail::main_window::message_type_list
            >,
        tetengo2::meta::assoc_list_end
        >>
        main_window_type_list;


    /**** The Application ***************************************************/

    namespace type
    {
        struct application;    //!< The application type.
    }

    //! The type list for the application.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::application,
                bobura<
                    boost::mpl::at<common_type_list, type::settings>::type,
                    boost::mpl::at<model_type_list, type::model>::type,
                    boost::mpl::at<
                        locale_type_list, type::message_catalog
                    >::type,
                    boost::mpl::at<
                        command_type_list, type::command_set
                    >::type,
                    boost::mpl::at<
                        main_window_type_list, type::main_window
                    >::type,
                    boost::mpl::at<
                        main_window_type_list,
                        type::main_window_message_type_list
                    >::type,
                    boost::mpl::at<ui_type_list, type::menu_bar>::type,
                    boost::mpl::at<ui_type_list, type::menu_command>::type,
                    boost::mpl::at<ui_type_list, type::popup_menu>::type,
                    boost::mpl::at<ui_type_list, type::menu_separator>::type,
                    boost::mpl::at<ui_type_list, type::message_loop>::type,
                    boost::mpl::at<
                        ui_type_list, type::message_loop_break
                    >::type,
                    boost::mpl::at<ui_type_list, type::gui_fixture>::type
                >
            >,
        tetengo2::meta::assoc_list_end
        >
        bobura_type_list;


    /**** All ***************************************************************/

    //! The type list for Bobura.
    typedef
        boost::mpl::insert_range<
            common_type_list, tetengo2::meta::assoc_list_end,
        boost::mpl::insert_range<
            locale_type_list, tetengo2::meta::assoc_list_end,
        boost::mpl::insert_range<
            ui_type_list, tetengo2::meta::assoc_list_end,
        boost::mpl::insert_range<
            about_dialog_type_list, tetengo2::meta::assoc_list_end,
        boost::mpl::insert_range<
            main_window_type_list, tetengo2::meta::assoc_list_end,
        boost::mpl::insert_range<
            bobura_type_list, tetengo2::meta::assoc_list_end,
        tetengo2::meta::assoc_list_end
        >::type>::type>::type>::type>::type>::type
        type_list;


}


#endif
