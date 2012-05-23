/*! \file
    \brief The definition of bobura::type_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_TYPELIST_H)
#define BOBURA_TYPELIST_H

//#include <cstddef>
//#include <functional>
//#include <iterator>
#include <ostream>
//#include <string>
//#include <utility>

//#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
//#include <boost/mpl/pair.hpp>
//#include <boost/rational.hpp>
//#include <boost/spirit/include/support_multi_pass.hpp>

#include <tetengo2.gui.alert.h>
#include <tetengo2.gui.common_dialog.file_open.h>
#include <tetengo2.gui.common_dialog.file_save.h>
#include <tetengo2.gui.common_dialog.message_box.h>
#include <tetengo2.gui.cursor.system.h>
#include <tetengo2.gui.drawing.background.h>
#include <tetengo2.gui.drawing.color.h>
#include <tetengo2.gui.drawing.font.h>
#include <tetengo2.gui.drawing.picture.h>
#include <tetengo2.gui.drawing.picture_reader.h>
#include <tetengo2.gui.drawing.solid_background.h>
#include <tetengo2.gui.drawing.system_color_set.h>
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
#include <tetengo2.gui.message.focus_observer_set.h>
#include <tetengo2.gui.message.keyboard_observer_set.h>
#include <tetengo2.gui.message.menu_observer_set.h>
#include <tetengo2.gui.message.message_loop.h>
#include <tetengo2.gui.message.message_loop_break.h>
#include <tetengo2.gui.message.mouse_observer_set.h>
#include <tetengo2.gui.message.paint_observer_set.h>
#include <tetengo2.gui.message.scroll_bar_observer_set.h>
#include <tetengo2.gui.message.window_observer_set.h>
#include <tetengo2.gui.scroll_bar.h>
#include <tetengo2.gui.unit.em.h>
#include <tetengo2.gui.virtual_key.h>
#include <tetengo2.gui.widget.abstract_window.h>
#include <tetengo2.gui.widget.button.h>
#include <tetengo2.gui.widget.control.h>
#include <tetengo2.gui.widget.dialog.h>
#include <tetengo2.gui.widget.image.h>
#include <tetengo2.gui.widget.label.h>
#include <tetengo2.gui.widget.link_label.h>
#include <tetengo2.gui.widget.picture_box.h>
#include <tetengo2.gui.widget.text_box.h>
#include <tetengo2.gui.widget.traits.abstract_window_traits.h>
#include <tetengo2.gui.widget.traits.button_traits.h>
#include <tetengo2.gui.widget.traits.control_traits.h>
#include <tetengo2.gui.widget.traits.dialog_traits.h>
#include <tetengo2.gui.widget.traits.image_traits.h>
#include <tetengo2.gui.widget.traits.label_traits.h>
#include <tetengo2.gui.widget.traits.link_label_traits.h>
#include <tetengo2.gui.widget.traits.picture_box_traits.h>
#include <tetengo2.gui.widget.traits.text_box_traits.h>
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
#include "bobura.command.set.h"
#include "bobura.command.type_list_impl.h"
#include "bobura.detail_type_list.h"
#include "bobura.diagram_view.h"
#include "bobura.file_property_dialog.h"
#include "bobura.load_save.confirm_file_save.h"
#include "bobura.load_save.load_from_file.h"
#include "bobura.load_save.new_file.h"
#include "bobura.load_save.save_to_file.h"
#include "bobura.main_window.h"
#include "bobura.message.timetable_model_observer_set.h"
#include "bobura.message.type_list_impl.h"
#include "bobura.model.message.timetable_observer_set.h"
#include "bobura.model.serializer.reader_selector.h"
#include "bobura.model.serializer.reader_set.h"
#include "bobura.model.serializer.writer_selector.h"
#include "bobura.model.serializer.writer_set.h"
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
        struct path;           //!< The path type.
        struct input_stream_iterator; //!< The input stream iterator type.
        struct pull_parser;    //!< The pull parser_type.
        struct output_stream;  //!< The output stream type.
        struct settings;       //!< The settings type.
    }

#if !defined(DOCUMENTATION)
    namespace detail
    {
        typedef std::size_t size_type;
        typedef std::wstring string_type;
        typedef std::string io_string_type;
        typedef
            boost::spirit::multi_pass<std::istreambuf_iterator<io_string_type::value_type>> input_stream_iterator_type;
        typedef tetengo2::text::grammar::json<input_stream_iterator_type> json_grammar_type;
        typedef
            tetengo2::text::push_parser<input_stream_iterator_type, json_grammar_type, int, double> push_parser_type;
        typedef tetengo2::text::pull_parser<push_parser_type, size_type> pull_parser_type;
        typedef boost::filesystem::path path_type;
        typedef settings<string_type, path_type> settings_type;
    }
#endif

    //! The common type list.
    typedef
        tetengo2::meta::assoc_list<boost::mpl::pair<type::difference, std::ptrdiff_t>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::size, detail::size_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::string, detail::string_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::path, detail::path_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::input_stream_iterator, detail::input_stream_iterator_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::pull_parser, detail::pull_parser_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::output_stream, std::basic_ostream<detail::io_string_type::value_type>>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::settings, detail::settings_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>
        common_type_list;


    /**** Locale ************************************************************/

    namespace type { namespace locale
    {
        struct ui_encoder;     //!< The encoder type for the user interface.
        struct exception_encoder; //!< The encoder type for exceptions.
        struct messages_facet; //!< The messages facet type.
        struct message_catalog; //!< The message catalog type.
        struct timetable_file_encoder; //!< The encoder type for the timetable file.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace locale
    {
        typedef
            tetengo2::text::encoding::locale<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<detail_type_list, type::detail::encoding>::type
            >
            internal_encoding_type;
        typedef
            tetengo2::text::encoding::locale<
                boost::mpl::at<detail_type_list, type::detail::widget>::type::string_type,
                boost::mpl::at<detail_type_list, type::detail::encoding>::type
            >
            ui_encoding_type;
        typedef
            tetengo2::text::encoding::utf8<boost::mpl::at<detail_type_list, type::detail::encoding>::type>
            utf8_encoding_type;
        typedef utf8_encoding_type exception_encoding_type;
        typedef utf8_encoding_type message_catalog_encoding_type;
        typedef
            tetengo2::text::encoding::locale<
                std::string, boost::mpl::at<detail_type_list, type::detail::encoding>::type
            >
            locale_name_encoding_type;
        typedef
            tetengo2::text::encoder<internal_encoding_type, message_catalog_encoding_type>
            message_catalog_encoder_type;
        typedef
            tetengo2::message::message_catalog_parser<
                boost::mpl::at<common_type_list, type::pull_parser>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                message_catalog_encoder_type
            >
            message_catalog_parser_type;
        typedef tetengo2::text::encoder<internal_encoding_type, locale_name_encoding_type> locale_name_encoder_type;
        typedef
            tetengo2::message::messages<
                boost::mpl::at<common_type_list, type::path>::type,
                message_catalog_parser_type,
                locale_name_encoder_type
            >
            messages_type;
        typedef utf8_encoding_type timetable_file_encoding_type;
        typedef
            tetengo2::text::encoder<internal_encoding_type, timetable_file_encoding_type> timetable_file_encoder_type;
    }}
#endif

    //! The type list for the locale.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::locale::ui_encoder,
                tetengo2::text::encoder<detail::locale::internal_encoding_type, detail::locale::ui_encoding_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::locale::exception_encoder,
                tetengo2::text::encoder<
                    detail::locale::internal_encoding_type, detail::locale::exception_encoding_type
                >
            >,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::locale::messages_facet, detail::locale::messages_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::locale::message_catalog, tetengo2::message::message_catalog<detail::locale::messages_type>
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::locale::timetable_file_encoder, detail::locale::timetable_file_encoder_type>,
        tetengo2::meta::assoc_list_end
        >>>>>
        locale_type_list;


    /**** Model *************************************************************/

    namespace type { namespace model
    {
        struct model;          //!< The model type.
        struct reader_selector; //!< The reader selector type.
        struct reader_set;     //!< The reader set type.
        struct writer_selector; //!< The writer selector type.
        struct writer_set;     //!< The writer set type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace model
    {
        typedef
            bobura::model::station_info::grade_type_set<boost::mpl::at<common_type_list, type::string>::type>
            station_grade_type_set_type;
        typedef station_grade_type_set_type::grade_type grade_type;
        typedef bobura::model::station<boost::mpl::at<common_type_list, type::string>::type, grade_type> station_type;
        typedef
            bobura::model::timetable_info::station_location<
                station_type, boost::mpl::at<common_type_list, type::size>::type
            >
            station_location_type;
        typedef
            bobura::model::train_info::time<
                boost::mpl::at<common_type_list, type::size>::type,
                bobura::model::train_info::time_span<boost::mpl::at<common_type_list, type::difference>::type>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, boost::mpl::at<common_type_list, type::string>::type>
            stop_type;
        typedef
            bobura::model::train<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::string>::type,
                stop_type
            >
            train_type;
        typedef
            bobura::model::timetable<
                boost::mpl::at<common_type_list, type::string>::type,
                station_location_type,
                train_type,
                bobura::model::message::timetable_observer_set
            >
            timetable_type;
    }}
#endif

    //! The model type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::model,
                timetable_model<
                    detail::model::timetable_type,
                    boost::mpl::at<common_type_list, type::path>::type,
                    message::timetable_model_observer_set
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::reader_selector,
                model::serializer::reader_selector<
                    boost::mpl::at<common_type_list, type::input_stream_iterator>::type, detail::model::timetable_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::reader_set,
                model::serializer::reader_set<
                    boost::mpl::at<common_type_list, type::input_stream_iterator>::type,
                    detail::model::timetable_type,
                    boost::mpl::at<common_type_list, type::pull_parser>::type,
                    detail::model::station_grade_type_set_type,
                    boost::mpl::at<locale_type_list, type::locale::timetable_file_encoder>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::writer_selector,
                model::serializer::writer_selector<
                    boost::mpl::at<common_type_list, type::output_stream>::type,
                    detail::model::timetable_type,
                    boost::mpl::at<common_type_list, type::path>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::writer_set,
                model::serializer::writer_set<
                    boost::mpl::at<common_type_list, type::output_stream>::type,
                    detail::model::timetable_type,
                    boost::mpl::at<common_type_list, type::path>::type,
                    detail::model::station_grade_type_set_type,
                    boost::mpl::at<locale_type_list, type::locale::timetable_file_encoder>::type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>
        model_type_list;


    /**** User Interface ****************************************************/

    namespace type { namespace ui
    {
        struct gui_fixture;    //!< The GUI fixture type.
        struct position;       //!< The position type.
        struct picture_reader; //!< The picture reader type.
        struct fast_picture_reader; //!< The fast picture reader type.
        struct canvas;         //!< The canvas type.
        struct fast_canvas;    //!< The fast canvas type.
        struct alert;          //!< The alert type.
        struct abstract_window; //!< The abstract window type.
        struct window;         //!< The window type.
        struct menu_bar;       //!< The menu bar type.
        struct popup_menu;     //!< The popup menu type.
        struct menu_command;   //!< The menu command type.
        struct menu_separator; //!< The menu separator type;
        struct dialog;         //!< The dialog type.
        struct control;        //!< The control type.
        struct label;          //!< The label type.
        struct link_label;     //!< The link label type.
        struct picture_box;    //!< The picture box type.
        struct text_box;       //!< The text box type.
        struct image;          //!< The image type.
        struct button;         //!< The button type.
        struct message_loop;   //!< The message loop type.
        struct message_loop_break; //!< The message loop break type.
        struct solid_background; //!< The solid background type.
        struct fast_solid_background; //!< The fast solid background type.
        struct transparent_background; //!< The transparent background type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace ui
    {
        typedef
            tetengo2::gui::fixture<boost::mpl::at<detail_type_list, type::detail::gui_fixture>::type> gui_fixture_type;
        typedef
            tetengo2::gui::unit::em<
                boost::rational<boost::mpl::at<common_type_list, type::difference>::type>,
                boost::mpl::at<common_type_list, type::difference>::type,
                boost::mpl::at<detail_type_list, type::detail::unit>::type
            >
            unit_difference_type;
        typedef std::pair<unit_difference_type, unit_difference_type> position_type;
        typedef
            tetengo2::gui::unit::em<
                boost::rational<boost::mpl::at<common_type_list, type::size>::type>,
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<detail_type_list, type::detail::unit>::type
            >
            unit_size_type;
        typedef std::pair<unit_size_type, unit_size_type> dimension_type;
        typedef tetengo2::gui::drawing::color<unsigned char> color_type;
        typedef
            tetengo2::gui::drawing::background<boost::mpl::at<detail_type_list, type::detail::drawing>::type>
            background_type;
        typedef
            tetengo2::gui::drawing::background<boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type>
            fast_background_type;
        typedef
            tetengo2::gui::drawing::solid_background<
                color_type, boost::mpl::at<detail_type_list, type::detail::drawing>::type
            >
            solid_background_type;
        typedef
            tetengo2::gui::drawing::solid_background<
                color_type, boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type
            >
            fast_solid_background_type;
        typedef
            tetengo2::gui::drawing::transparent_background<
                boost::mpl::at<detail_type_list, type::detail::drawing>::type
            >
            transparent_background_type;
        typedef
            tetengo2::gui::drawing::font<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<detail_type_list, type::detail::drawing>::type
            >
            font_type;
        typedef
            tetengo2::gui::drawing::font<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type
            >
            fast_font_type;
        typedef
            tetengo2::gui::drawing::picture<
                unit_size_type, boost::mpl::at<detail_type_list, type::detail::drawing>::type
            >
            picture_type;
        typedef
            tetengo2::gui::drawing::picture<
                unit_size_type, boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type
            >
            fast_picture_type;
        typedef
            tetengo2::gui::drawing::picture_reader<
                picture_type,
                boost::mpl::at<common_type_list, type::path>::type,
                boost::mpl::at<detail_type_list, type::detail::drawing>::type
            >
            picture_reader_type;
        typedef
            tetengo2::gui::drawing::picture_reader<
                fast_picture_type,
                boost::mpl::at<common_type_list, type::path>::type,
                boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type
            >
            fast_picture_reader_type;
        typedef
            tetengo2::gui::drawing::widget_canvas<
                unit_size_type,
                boost::mpl::at<common_type_list, type::string>::type,
                position_type,
                dimension_type,
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                color_type,
                background_type,
                solid_background_type,
                font_type,
                picture_type,
                boost::mpl::at<detail_type_list, type::detail::drawing>::type
            >
            widget_canvas_type;
        typedef widget_canvas_type::base_type canvas_type;
        typedef
            tetengo2::gui::drawing::widget_canvas<
                unit_size_type,
                boost::mpl::at<common_type_list, type::string>::type,
                position_type,
                dimension_type,
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                color_type,
                fast_background_type,
                fast_solid_background_type,
                fast_font_type,
                fast_picture_type,
                boost::mpl::at<detail_type_list, type::detail::fast_drawing>::type
            >
            fast_widget_canvas_type;
        typedef fast_widget_canvas_type::base_type fast_canvas_type;
        typedef
            tetengo2::gui::alert<
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                boost::mpl::at<locale_type_list, type::locale::exception_encoder>::type,
                boost::mpl::at<detail_type_list, type::detail::alert>::type
            >
            alert_type;
        typedef
            tetengo2::gui::cursor::system<boost::mpl::at<detail_type_list, type::detail::cursor>::type>
            system_cursor_type;
        typedef
            tetengo2::gui::scroll_bar<
                boost::mpl::at<common_type_list, type::size>::type,
                tetengo2::gui::message::scroll_bar_observer_set<boost::mpl::at<common_type_list, type::size>::type>,
                boost::mpl::at<detail_type_list, type::detail::scroll>::type
            >
            scroll_bar_type;
        typedef
            tetengo2::gui::virtual_key<
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<detail_type_list, type::detail::virtual_key>::type
            >
            virtual_key_type;
        typedef
            tetengo2::gui::widget::traits::widget_traits<
                widget_canvas_type,
                alert_type,
                position_type,
                dimension_type,
                boost::mpl::at<common_type_list, type::string>::type,
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                background_type,
                font_type,
                system_cursor_type,
                scroll_bar_type,
                tetengo2::gui::message::focus_observer_set,
                tetengo2::gui::message::paint_observer_set<canvas_type>,
                tetengo2::gui::message::keyboard_observer_set<
                    virtual_key_type, boost::mpl::at<common_type_list, type::string>::type::value_type
                >,
                tetengo2::gui::message::mouse_observer_set
            >
            widget_traits_type;
        typedef tetengo2::gui::menu::shortcut_key<virtual_key_type> shortcut_key_type;
        typedef
            tetengo2::gui::menu::traits<
                boost::mpl::at<common_type_list, type::string>::type,
                shortcut_key_type,
                boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                tetengo2::gui::message::menu_observer_set
            >
            menu_traits_type;
        typedef
            tetengo2::gui::menu::abstract_popup<
                menu_traits_type, boost::mpl::at<detail_type_list, type::detail::menu>::type
            >
            abstract_popup_menu_type;
        typedef
            tetengo2::gui::menu::menu_base<
                menu_traits_type, boost::mpl::at<detail_type_list, type::detail::menu>::type
            >
            menu_base_type;
        typedef
            tetengo2::gui::menu::shortcut_key_table<
                shortcut_key_type, menu_base_type, boost::mpl::at<detail_type_list, type::detail::menu>::type
            >
            shortcut_key_table_type;
        typedef
            tetengo2::gui::menu::menu_bar<
                menu_traits_type, shortcut_key_table_type, boost::mpl::at<detail_type_list, type::detail::menu>::type
            >
            menu_bar_type;
        typedef
            tetengo2::gui::widget::traits::abstract_window_traits<
                widget_traits_type, menu_bar_type, tetengo2::gui::message::window_observer_set
            >
            abstract_window_traits_type;
        typedef
            tetengo2::gui::widget::abstract_window<
                abstract_window_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >
            abstract_window_type;
        typedef tetengo2::gui::widget::traits::window_traits<abstract_window_traits_type> window_traits_type;
        typedef
            tetengo2::gui::widget::window<
                window_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >
            window_type;
        typedef
            tetengo2::gui::message::message_loop<
                abstract_window_type, boost::mpl::at<detail_type_list, type::detail::message_loop>::type
            >
            message_loop_type;
        typedef
            tetengo2::gui::message::message_loop_break<
                boost::mpl::at<detail_type_list, type::detail::message_loop>::type
            >
            message_loop_break_type;
        typedef
            tetengo2::gui::message::dialog_message_loop<
                abstract_window_type, boost::mpl::at<detail_type_list, type::detail::message_loop>::type
            >
            dialog_message_loop_type;
        typedef
            tetengo2::gui::widget::traits::dialog_traits<
                abstract_window_traits_type, dialog_message_loop_type, message_loop_break_type
            >
            dialog_traits_type;
        typedef
            tetengo2::gui::widget::dialog<
                dialog_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >
            dialog_type;
        typedef
            tetengo2::gui::widget::traits::control_traits<widget_traits_type, color_type>
            control_traits_type;
        typedef
            tetengo2::gui::widget::control<
                control_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >
            control_type;
        typedef tetengo2::gui::widget::traits::label_traits<control_traits_type> label_traits_type;
        typedef
            tetengo2::gui::widget::label<
                label_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >
            label_type;
        typedef
            tetengo2::gui::drawing::system_color_set<
                color_type, boost::mpl::at<detail_type_list, type::detail::system_color>::type
            >
            system_color_set_type;
        typedef
            tetengo2::gui::widget::traits::link_label_traits<
                label_traits_type, solid_background_type, system_color_set_type
            >
            link_label_traits_type;
        typedef
            tetengo2::gui::widget::link_label<
                link_label_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >
            link_label_type;
        typedef
            tetengo2::gui::widget::traits::image_traits<control_traits_type, picture_type> image_traits_type;
        typedef
            tetengo2::gui::widget::image<
                image_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >
            image_type;
        typedef tetengo2::gui::widget::traits::button_traits<control_traits_type> button_traits_type;
        typedef
            tetengo2::gui::widget::button<
                button_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >
            button_type;
        typedef
            tetengo2::gui::widget::traits::picture_box_traits<
                control_traits_type,
                fast_widget_canvas_type,
                tetengo2::gui::message::paint_observer_set<fast_canvas_type>
            >
            picture_box_traits_type;
        typedef
            tetengo2::gui::widget::picture_box<
                picture_box_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >
            picture_box_type;
        typedef tetengo2::gui::widget::traits::text_box_traits<control_traits_type> text_box_traits_type;
        typedef
            tetengo2::gui::widget::text_box<
                text_box_traits_type,
                boost::mpl::at<detail_type_list, type::detail::widget>::type,
                boost::mpl::at<detail_type_list, type::detail::message_handler>::type
            >
            text_box_type;
    }}
#endif

    //! The type list for the user interface.
    typedef
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::gui_fixture, detail::ui::gui_fixture_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::position, detail::ui::position_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::picture_reader, detail::ui::picture_reader_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::fast_picture_reader, detail::ui::fast_picture_reader_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::canvas, detail::ui::canvas_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::fast_canvas, detail::ui::fast_canvas_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::alert, detail::ui::alert_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::abstract_window, detail::ui::abstract_window_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::window, detail::ui::window_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::menu_bar, detail::ui::menu_bar_type >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::ui::popup_menu,
                tetengo2::gui::menu::popup<
                    detail::ui::menu_traits_type, boost::mpl::at<detail_type_list, type::detail::menu>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::ui::menu_command,
                tetengo2::gui::menu::command<
                    detail::ui::menu_traits_type, boost::mpl::at<detail_type_list, type::detail::menu>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::ui::menu_separator,
                tetengo2::gui::menu::separator<
                    detail::ui::menu_traits_type, boost::mpl::at<detail_type_list, type::detail::menu>::type
                >
            >,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::dialog, detail::ui::dialog_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::control, detail::ui::control_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::label, detail::ui::label_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::link_label, detail::ui::link_label_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::image, detail::ui::image_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::button, detail::ui::button_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::picture_box, detail::ui::picture_box_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::text_box, detail::ui::text_box_type>,
        tetengo2::meta::assoc_list<boost::mpl::pair<type::ui::message_loop, detail::ui::message_loop_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::message_loop_break, detail::ui::message_loop_break_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::solid_background, detail::ui::solid_background_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::fast_solid_background, detail::ui::fast_solid_background_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::ui::transparent_background, detail::ui::transparent_background_type>,
        tetengo2::meta::assoc_list_end
        >>>>>>>>>>>>>>>>>>>>>>>>>>
        ui_type_list;


    /**** Common Dialog *****************************************************/

    namespace type { namespace common_dialog
    {
        struct message_box;    //!< The message box type.
        struct file_open_dialog; //!< The file open dialog type.
        struct file_save_dialog; //!< The file save dialog type.
    }}

    //! The type list for the commong dialogs.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::message_box,
                tetengo2::gui::common_dialog::message_box<
                    boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                    boost::mpl::at<common_type_list, type::string>::type,
                    boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                    boost::mpl::at<detail_type_list, type::detail::common_dialog>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::file_open_dialog,
                tetengo2::gui::common_dialog::file_open<
                    boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                    boost::mpl::at<common_type_list, type::string>::type,
                    boost::mpl::at<common_type_list, type::path>::type,
                    boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                    boost::mpl::at<detail_type_list, type::detail::common_dialog>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::common_dialog::file_save_dialog,
                tetengo2::gui::common_dialog::file_save<
                    boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                    boost::mpl::at<common_type_list, type::string>::type,
                    boost::mpl::at<common_type_list, type::path>::type,
                    boost::mpl::at<locale_type_list, type::locale::ui_encoder>::type,
                    boost::mpl::at<detail_type_list, type::detail::common_dialog>::type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>
        common_dialog_type_list;


    /**** View **************************************************************/

    namespace type { namespace view
    {
        struct view;           //!< The view type.
    }}

    //! The view type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::view::view,
                bobura::diagram_view<
                    boost::mpl::at<model_type_list, type::model::model>::type,
                    boost::mpl::at<ui_type_list, type::ui::fast_canvas>::type,
                    boost::mpl::at<ui_type_list, type::ui::fast_solid_background>::type
                >
            >,
        tetengo2::meta::assoc_list_end
        >
        view_type_list;


    /**** Dialog ************************************************************/

    namespace type { namespace dialog
    {
        struct about_dialog;   //!< The about dialog type.
        struct file_property_dialog; //!< The file property dialog type.
    }}

    //! The type list for the dialogs.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::dialog::about_dialog,
                about_dialog<
                    boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                    boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
                    boost::mpl::at<common_type_list, type::settings>::type,
                    boost::mpl::at<ui_type_list, type::ui::label>::type,
                    boost::mpl::at<ui_type_list, type::ui::link_label>::type,
                    boost::mpl::at<ui_type_list, type::ui::image>::type,
                    boost::mpl::at<ui_type_list, type::ui::button>::type,
                    boost::mpl::at<ui_type_list, type::ui::picture_reader>::type,
                    boost::mpl::at<ui_type_list, type::ui::transparent_background>::type,
                    message::about_dialog::type_list<boost::mpl::at<ui_type_list, type::ui::dialog>::type>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::dialog::file_property_dialog,
                file_property_dialog<
                    boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                    boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
                    boost::mpl::at<ui_type_list, type::ui::label>::type,
                    boost::mpl::at<ui_type_list, type::ui::text_box>::type,
                    boost::mpl::at<ui_type_list, type::ui::button>::type,
                    boost::mpl::at<ui_type_list, type::ui::transparent_background>::type,
                    message::file_property_dialog::type_list<
                        boost::mpl::at<ui_type_list, type::ui::dialog>::type
                    >::type
                >
            >,
        tetengo2::meta::assoc_list_end
        >>
        dialog_type_list;


    /**** Loading and Saving ************************************************/

    namespace type { namespace load_save
    {
        struct new_file;       //!< The file initialization.
        struct load_from_file; //!< The file loading.
        struct save_to_file;   //!< The file saving.
        struct confirm_file_save; //!< The file save confirmation.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace load_save
    {
        typedef
            bobura::load_save::save_to_file<
                boost::mpl::at<model_type_list, type::model::model>::type,
                boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::message_box>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::file_save_dialog>::type,
                boost::mpl::at<model_type_list, type::model::writer_selector>::type,
                boost::mpl::at<model_type_list, type::model::writer_set>::type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
            >
            save_to_file_type;
        typedef
            bobura::load_save::confirm_file_save<
                boost::mpl::at<model_type_list, type::model::model>::type,
                boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                boost::mpl::at<common_dialog_type_list, type::common_dialog::message_box>::type,
                save_to_file_type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
            >
            confirm_file_save_type;

    }}
#endif

    //! The type list for the miscellaneous processings.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::load_save::new_file,
                load_save::new_file<
                    boost::mpl::at<model_type_list, type::model::model>::type,
                    boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                    detail::load_save::confirm_file_save_type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::load_save::load_from_file,
                load_save::load_from_file<
                    boost::mpl::at<model_type_list, type::model::model>::type,
                    boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                    boost::mpl::at<common_dialog_type_list, type::common_dialog::message_box>::type,
                    boost::mpl::at<common_dialog_type_list, type::common_dialog::file_open_dialog>::type,
                    detail::load_save::confirm_file_save_type,
                    boost::mpl::at<model_type_list, type::model::reader_selector>::type,
                    boost::mpl::at<model_type_list, type::model::reader_set>::type,
                    boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::load_save::save_to_file, detail::load_save::save_to_file_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::load_save::confirm_file_save, detail::load_save::confirm_file_save_type>,
        tetengo2::meta::assoc_list_end
        >>>>
        load_save_type_list;


    /**** Command Type List *************************************************/

    namespace type { namespace command_type_list
    {
        struct command;        //!< The command.
        struct command_type_list; //!< The command type list.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace command_type_list
    {
        typedef boost::mpl::at<model_type_list, type::model::model>::type model_type;
        typedef boost::mpl::at<ui_type_list, type::ui::abstract_window>::type abstract_window_type;
        typedef std::function<void (model_type& model, abstract_window_type& parent)> command_type;
    }}
#endif

    //! The type list for the command type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::command_type_list::command, detail::command_type_list::command_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::command_type_list::command_type_list,
                command::type_list<
                    detail::command_type_list::command_type,
                    boost::mpl::at<model_type_list, type::model::model>::type,
                    boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                    boost::mpl::at<dialog_type_list, type::dialog::file_property_dialog>::type,
                    boost::mpl::at<dialog_type_list, type::dialog::about_dialog>::type,
                    boost::mpl::at<load_save_type_list, type::load_save::new_file>::type,
                    boost::mpl::at<load_save_type_list, type::load_save::load_from_file>::type,
                    boost::mpl::at<load_save_type_list, type::load_save::save_to_file>::type
                >::type
            >,
        tetengo2::meta::assoc_list_end
        >>
        command_type_list_type_list;


    /**** Main Window *******************************************************/

    namespace type { namespace main_window
    {
        struct main_window;    //!< The main window type.
        struct message_type_list; //!< The main window message type list type.
        struct diagram_picture_box_message_type_list; //!< The diagram picture box message type list type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail { namespace main_window
    {
        typedef
            message::main_window::type_list<
                boost::mpl::at<command_type_list_type_list, type::command_type_list::command>::type,
                boost::mpl::at<model_type_list, type::model::model>::type,
                boost::mpl::at<view_type_list, type::view::view>::type,
                boost::mpl::at<ui_type_list, type::ui::abstract_window>::type,
                boost::mpl::at<ui_type_list, type::ui::control>::type,
                boost::mpl::at<load_save_type_list, type::load_save::confirm_file_save>::type
            >::type
            main_window_message_type_list;
        typedef
            message::diagram_picture_box::type_list<
                boost::mpl::at<ui_type_list, type::ui::fast_canvas>::type,
                boost::mpl::at<ui_type_list, type::ui::picture_box>::type,
                boost::mpl::at<view_type_list, type::view::view>::type
            >::type
            diagram_picture_box_message_type_list;
    }}
#endif

    //! The type list for the main window.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::main_window::main_window,
                main_window<
                    boost::mpl::at<ui_type_list, type::ui::window>::type,
                    boost::mpl::at<locale_type_list, type::locale::message_catalog>::type,
                    boost::mpl::at<ui_type_list, type::ui::picture_box>::type,
                    boost::mpl::at<common_type_list, type::settings>::type,
                    boost::mpl::at<load_save_type_list, type::load_save::confirm_file_save>::type,
                    boost::mpl::at<ui_type_list, type::ui::message_loop_break>::type,
                    detail::main_window::main_window_message_type_list
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::main_window::message_type_list, detail::main_window::main_window_message_type_list>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::main_window::diagram_picture_box_message_type_list,
                detail::main_window::diagram_picture_box_message_type_list
            >,
        tetengo2::meta::assoc_list_end
        >>>
        main_window_type_list;


    /**** The Application ***************************************************/

    namespace type { namespace application
    {
        struct command_set;    //!< The command set type.
        struct model_message_type_list; //!< The model message type list type.
    }}

    //! The type list for the application.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::application::command_set,
                command::set<
                    boost::mpl::at<command_type_list_type_list, type::command_type_list::command_type_list>::type,
                    boost::mpl::at<load_save_type_list, type::load_save::new_file>::type,
                    boost::mpl::at<load_save_type_list, type::load_save::load_from_file>::type,
                    boost::mpl::at<load_save_type_list, type::load_save::save_to_file>::type,
                    boost::mpl::at<common_type_list, type::settings>::type,
                    boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
                >
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::application::model_message_type_list,
                message::timetable_model::type_list<
                    boost::mpl::at<model_type_list, type::model::model>::type,
                    boost::mpl::at<main_window_type_list, type::main_window::main_window>::type
                >::type
            >,
        tetengo2::meta::assoc_list_end
        >>
        application_type_list;


}


#endif
