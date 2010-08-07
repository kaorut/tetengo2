/*! \file
    \brief Test of class bobura::about_dialog.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>

#include <boost/test/unit_test.hpp>

#include <stub_tetengo2.gui.abstract_popup_menu.h>
#include <stub_tetengo2.gui.abstract_window.h>
#include <stub_tetengo2.gui.alert.h>
#include <stub_tetengo2.gui.button.h>
#include <stub_tetengo2.gui.canvas.h>
#include <stub_tetengo2.gui.dialog.h>
#include <stub_tetengo2.gui.font.h>
#include <stub_tetengo2.gui.main_menu.h>
#include <stub_tetengo2.gui.menu.h>
#include <stub_tetengo2.gui.message_loop.h>
#include <stub_tetengo2.gui.quit_message_loop.h>
#include <stub_tetengo2.gui.widget.h>
#include <stub_tetengo2.gui.window.h>
#include <tetengo2.gui.menu_observer_set.h>
#include <tetengo2.gui.mouse_observer_set.h>
#include <tetengo2.gui.paint_observer_set.h>
#include <tetengo2.gui.widget_traits.h>
#include <tetengo2.gui.window_observer_set.h>
#include <tetengo2.encoder.h>
#include <tetengo2.encoding.locale.h>

#include "bobura.about_dialog.h"
#include "bobura.message.type_list_impl.h"


namespace
{
    // types

    typedef tetengo2::encoding::locale<std::wstring> internal_encoding_type;

    typedef tetengo2::encoding::locale<std::wstring> ui_encoding_type;

    typedef
        tetengo2::encoder<internal_encoding_type, ui_encoding_type>
        ui_encoder_type;

    typedef tetengo2::encoding::locale<std::string> exception_encoding_type;

    typedef
        tetengo2::encoder<internal_encoding_type, exception_encoding_type>
        exception_encoder_type;

    typedef
        stub_tetengo2::gui::alert<
            const void*, ui_encoder_type, exception_encoder_type
        >
        alert_type;

    typedef stub_tetengo2::gui::font<std::wstring, std::size_t> font_type;

    typedef
        stub_tetengo2::gui::canvas<
            const void*,
            std::size_t,
            std::wstring,
            ui_encoder_type,
            const void*,
            font_type
        >
        canvas_type;

    typedef
        tetengo2::gui::widget_traits<
            const void*,
            canvas_type,
            alert_type,
            std::ptrdiff_t,
            std::size_t,
            std::wstring,
            ui_encoder_type,
            font_type,
            tetengo2::gui::paint_observer_set<canvas_type>,
            tetengo2::gui::mouse_observer_set
        >
        widget_traits_type;

    typedef stub_tetengo2::gui::widget<widget_traits_type> widget_type;

    typedef
        stub_tetengo2::gui::menu<
            unsigned int,
            const void*,
            std::wstring,
            ui_encoder_type,
            tetengo2::gui::menu_observer_set
        >
        menu_type;

    typedef
        stub_tetengo2::gui::abstract_popup_menu<menu_type>
        abstract_popup_menu_type;

    typedef
        stub_tetengo2::gui::main_menu<abstract_popup_menu_type>
        main_menu_type;

    typedef
        stub_tetengo2::gui::abstract_window<
            widget_type, main_menu_type, tetengo2::gui::window_observer_set
        >
        abstract_window_type;

    typedef stub_tetengo2::gui::window<abstract_window_type> window_type;

    typedef stub_tetengo2::gui::message_loop message_loop_type;

    typedef stub_tetengo2::gui::quit_message_loop quit_message_loop_type;

    typedef
        stub_tetengo2::gui::dialog<
            abstract_window_type,
            message_loop_type,
            quit_message_loop_type
        >
        dialog_type;

    typedef stub_tetengo2::gui::button<widget_type> button_type;

    typedef
        bobura::message::about_dialog::type_list<dialog_type>::type
        about_dialog_message_type_list_type;

    typedef
        bobura::about_dialog<
            dialog_type, button_type, about_dialog_message_type_list_type
        >
        about_dialog_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(about_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const about_dialog_type about_dialog(window);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
