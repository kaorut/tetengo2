/*! \file
    \brief Test of class bobura::main_window.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>

#include <boost/test/unit_test.hpp>

#include <stub_tetengo2.gui.gui_type_list.h>
#include <tetengo2.encoder.h>
#include <tetengo2.encoding.locale.h>

#include "bobura.about_dialog.h"
#include "bobura.main_window.h"
#include "bobura.command.command_type_list.h"
#include "bobura.message.message_type_lists.h"


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
        stub_tetengo2::gui::gui_type_list<
            std::ptrdiff_t,
            std::size_t,
            std::wstring,
            ui_encoder_type,
            exception_encoder_type
        >
        gui_type_list_type;

    typedef
        bobura::message::about_dialog_message_type_list<
            gui_type_list_type::dialog_type
        >
        about_dialog_message_type_list_type;

    typedef
        bobura::about_dialog<
            gui_type_list_type::dialog_type,
            gui_type_list_type::button_type,
            about_dialog_message_type_list_type
        >
        about_dialog_type;

    typedef
        bobura::command::command_type_list<
            gui_type_list_type::window_type,
            about_dialog_type
        >
        command_type_list_type;

    typedef
        bobura::message::main_window_message_type_list<
            command_type_list_type::command_type,
            gui_type_list_type::canvas_type,
            gui_type_list_type::quit_message_loop_type
        >
        main_window_message_type_list_type;

    typedef
        bobura::main_window<
            gui_type_list_type,
            command_type_list_type,
            main_window_message_type_list_type
        >
        main_window_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(main_window)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const main_window_type main_window;
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
