/*! \file
    \brief The type list for test_bobura.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_TYPES_H)
#define TESTBOBURA_TYPES_H

//#include <cstddef>
#include <istream>
//#include <string>
//#include <utility>

//#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>

#include <stub_tetengo2.gui.button.h>
#include <stub_tetengo2.gui.dialog.h>
#include <stub_tetengo2.gui.gui_initializer_finalizer.h>
#include <stub_tetengo2.gui.image.h>
#include <stub_tetengo2.gui.label.h>
#include <stub_tetengo2.gui.main_menu.h>
#include <stub_tetengo2.gui.menu.h>
#include <stub_tetengo2.gui.menu_command.h>
#include <stub_tetengo2.gui.menu_separator.h>
#include <stub_tetengo2.gui.message_loop.h>
#include <stub_tetengo2.gui.popup_menu.h>
#include <stub_tetengo2.gui.quit_message_loop.h>
#include <stub_tetengo2.gui.window.h>
#include <tetengo2.detail.stub.alert.h>
#include <tetengo2.detail.stub.drawing.h>
#include <tetengo2.detail.stub.encoding.h>
#include <tetengo2.detail.stub.unit.h>
#include <tetengo2.encoding.utf8.h>
#include <tetengo2.gui.alert.h>
#include <tetengo2.gui.drawing.background.h>
#include <tetengo2.gui.drawing.color.h>
#include <tetengo2.gui.drawing.font.h>
#include <tetengo2.gui.drawing.picture.h>
#include <tetengo2.gui.drawing.picture_reader.h>
#include <tetengo2.gui.drawing.transparent_background.h>
#include <tetengo2.gui.drawing.widget_canvas.h>
#include <tetengo2.gui.menu_observer_set.h>
#include <tetengo2.gui.mouse_observer_set.h>
#include <tetengo2.gui.paint_observer_set.h>
#include <tetengo2.gui.traits.abstract_window_traits.h>
#include <tetengo2.gui.traits.button_traits.h>
#include <tetengo2.gui.traits.control_traits.h>
#include <tetengo2.gui.traits.dialog_traits.h>
#include <tetengo2.gui.traits.image_traits.h>
#include <tetengo2.gui.traits.label_traits.h>
#include <tetengo2.gui.traits.menu_traits.h>
#include <tetengo2.gui.traits.widget_traits.h>
#include <tetengo2.gui.traits.window_traits.h>
#include <tetengo2.gui.unit.em.h>
#include <tetengo2.gui.window_observer_set.h>
#include <tetengo2.encoder.h>
#include <tetengo2.encoding.locale.h>
#include <tetengo2.messages.h>
#include <tetengo2.message_catalog.h>
#include <tetengo2.message_catalog_parser.h>

#include "bobura.about_dialog.h"
#include "bobura.bobura.h"
#include "bobura.command.type_list_impl.h"
#include "bobura.main_window.h"
#include "bobura.message.type_list_impl.h"
#include "bobura.settings.h"


// types

typedef tetengo2::detail::stub::encoding encoding_details_type;

typedef
    tetengo2::encoding::locale<std::wstring, encoding_details_type>
    internal_encoding_type;

typedef
    tetengo2::encoding::locale<std::wstring, encoding_details_type>
    ui_encoding_type;

typedef
    tetengo2::encoder<internal_encoding_type, ui_encoding_type>
    ui_encoder_type;

typedef
    tetengo2::encoding::locale<std::string, encoding_details_type>
    exception_encoding_type;

typedef
    tetengo2::encoder<internal_encoding_type, exception_encoding_type>
    exception_encoder_type;

typedef bobura::settings<std::wstring, boost::filesystem::path> settings_type;

typedef
    tetengo2::detail::stub::alert<std::string, ui_encoder_type>
    alert_details_type;

typedef
    tetengo2::gui::alert<
        ui_encoder_type, exception_encoder_type, alert_details_type
    >
    alert_type;

typedef tetengo2::detail::stub::unit unit_details_type;

typedef
    tetengo2::gui::unit::em<std::ptrdiff_t, std::ptrdiff_t, unit_details_type>
    unit_difference_type;

typedef std::pair<unit_difference_type, unit_difference_type> position_type;

typedef
    tetengo2::gui::unit::em<std::size_t, std::size_t, unit_details_type>
    unit_size_type;

typedef std::pair<unit_size_type, unit_size_type> dimension_type;

typedef tetengo2::detail::stub::drawing drawing_details_type;

typedef
    tetengo2::gui::drawing::background<drawing_details_type> background_type;

typedef
    tetengo2::gui::drawing::transparent_background<drawing_details_type>
    transparent_background_type;

typedef
    tetengo2::gui::drawing::font<
        std::wstring, std::size_t, drawing_details_type
    >
    font_type;

typedef
    tetengo2::gui::drawing::picture<std::size_t, drawing_details_type>
    picture_type;

typedef
    tetengo2::gui::drawing::picture_reader<
        picture_type, boost::filesystem::path, drawing_details_type
    >
    picture_reader_type;

typedef
    tetengo2::gui::drawing::widget_canvas<
        std::size_t,
        std::wstring,
        dimension_type,
        ui_encoder_type,
        background_type,
        font_type,
        picture_type,
        drawing_details_type
    >
    canvas_type;

typedef
    tetengo2::gui::traits::widget_traits<
        const void*,
        canvas_type,
        alert_type,
        position_type,
        dimension_type,
        std::wstring,
        ui_encoder_type,
        background_type,
        font_type,
        tetengo2::gui::paint_observer_set<canvas_type>,
        tetengo2::gui::mouse_observer_set
    >
    widget_traits_type;

typedef
    tetengo2::gui::traits::menu_traits<
        unsigned int,
        const void*,
        std::wstring,
        ui_encoder_type,
        tetengo2::gui::menu_observer_set
    >
    menu_traits_type;

typedef stub_tetengo2::gui::menu<menu_traits_type> menu_type;

typedef stub_tetengo2::gui::main_menu<menu_traits_type> main_menu_type;

typedef
    tetengo2::gui::traits::abstract_window_traits<
        widget_traits_type,
        main_menu_type,
        tetengo2::gui::window_observer_set
    >
    abstract_window_traits_type;

typedef
    tetengo2::gui::traits::window_traits<abstract_window_traits_type>
    window_traits_type;

typedef stub_tetengo2::gui::window<window_traits_type> window_type;

typedef
    tetengo2::encoding::utf8<encoding_details_type>
    message_catalog_encoding_type;

typedef
    tetengo2::encoding::locale<std::string, encoding_details_type>
    locale_name_encoding_type;

typedef
    tetengo2::encoder<internal_encoding_type, message_catalog_encoding_type>
    message_catalog_encoder_type;

typedef
    tetengo2::message_catalog_parser<
        std::istream, std::wstring, message_catalog_encoder_type
    >
    message_catalog_parser_type;

typedef
    tetengo2::encoder<internal_encoding_type, locale_name_encoding_type>
    locale_name_encoder_type;

typedef
    tetengo2::messages<
        boost::filesystem::path,
        message_catalog_parser_type,
        locale_name_encoder_type
    >
    messages_type;

typedef tetengo2::message_catalog<messages_type> message_catalog_type;

typedef stub_tetengo2::gui::message_loop message_loop_type;

typedef stub_tetengo2::gui::quit_message_loop quit_message_loop_type;

typedef
    tetengo2::gui::traits::dialog_traits<
        abstract_window_traits_type,
        message_loop_type,
        quit_message_loop_type
    >
    dialog_traits_type;

typedef stub_tetengo2::gui::dialog<dialog_traits_type> dialog_type;

typedef
    bobura::message::about_dialog::type_list<dialog_type>::type
    about_dialog_message_type_list_type;

typedef tetengo2::gui::drawing::color<unsigned char> color_type;

typedef
    tetengo2::gui::traits::control_traits<widget_traits_type, color_type>
    control_traits_type;

typedef
    tetengo2::gui::traits::label_traits<control_traits_type>
    label_traits_type;

typedef stub_tetengo2::gui::label<label_traits_type> label_type;

typedef
    tetengo2::gui::traits::image_traits<control_traits_type, picture_type>
    image_traits_type;

typedef stub_tetengo2::gui::image<image_traits_type> image_type;

typedef
    tetengo2::gui::traits::button_traits<control_traits_type>
    button_traits_type;

typedef stub_tetengo2::gui::button<button_traits_type> button_type;

typedef
    bobura::about_dialog<
        dialog_type,
        message_catalog_type,
        settings_type,
        label_type,
        image_type,
        button_type,
        picture_reader_type,
        transparent_background_type,
        about_dialog_message_type_list_type
    >
    about_dialog_type;

typedef
    bobura::command::type_list<window_type, about_dialog_type>::type
    command_type_list_type;

typedef
    bobura::message::main_window::type_list<
        boost::mpl::at<
            command_type_list_type, bobura::command::type::command
        >::type,
        canvas_type,
        position_type,
        picture_reader_type
    >::type
    main_window_message_type_list_type;

typedef stub_tetengo2::gui::menu_command<menu_traits_type> menu_command_type;

typedef stub_tetengo2::gui::popup_menu<menu_traits_type> popup_menu_type;

typedef
    stub_tetengo2::gui::menu_separator<menu_traits_type> menu_separator_type;

typedef
    bobura::main_window<
        window_type,
        message_catalog_type,
        settings_type,
        quit_message_loop_type,
        menu_command_type,
        popup_menu_type,
        menu_separator_type,
        command_type_list_type,
        main_window_message_type_list_type
    >
    main_window_type;

typedef
    bobura::bobura<
        settings_type,
        message_catalog_type,
        main_window_type,
        message_loop_type,
        quit_message_loop_type,
        stub_tetengo2::gui::gui_initializer_finalizer
    >
    bobura_type;


#endif
