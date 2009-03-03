/*! \file
    \brief Test of class bobura::about_dialog.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>

#include <boost/test/unit_test.hpp>

#include <stub_tetengo2.gui.gui_type_list.h>

#include "bobura.about_dialog.h"
#include "bobura.command.command_type_list.h"
#include "bobura.message.message_type_list.h"


namespace
{
    // types

    typedef
        stub_tetengo2::gui::gui_type_list<
            std::ptrdiff_t, std::size_t, std::wstring
        >
        gui_type_list_type;

    typedef
        bobura::command::command_type_list<
            gui_type_list_type::window_type, gui_type_list_type::dialog_type
        >
        command_type_list_type;

    typedef
        bobura::message::message_type_list<
            command_type_list_type::command_type,
            gui_type_list_type::canvas_type,
            gui_type_list_type::quit_message_loop_type
        >
        message_type_list_type;

    typedef
        bobura::about_dialog<
            gui_type_list_type, command_type_list_type, message_type_list_type
        >
        about_dialog_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(about_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_CHECKPOINT("");

        const about_dialog_type about_dialog;
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
