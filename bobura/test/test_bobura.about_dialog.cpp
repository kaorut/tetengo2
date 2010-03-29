/*! \file
    \brief Test of class bobura::about_dialog.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

//#include <cstddef>
#include <locale>
#include <string>

#include <boost/test/unit_test.hpp>

#include <stub_tetengo2.gui.gui_type_list.h>
#include <tetengo2.encoder.h>
#include <tetengo2.encoding.locale.h>

#include "bobura.about_dialog.h"
#include "bobura.message.message_type_lists.h"


namespace
{
    // types

    typedef tetengo2::encoding::locale<std::wstring> encoding_type;

    typedef tetengo2::encoder<encoding_type, encoding_type> ui_encoder_type;

    typedef
        stub_tetengo2::gui::gui_type_list<
            std::ptrdiff_t, std::size_t, std::wstring, ui_encoder_type
        >
        gui_type_list_type;

    typedef gui_type_list_type::window_type window_type;

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


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(about_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const ui_encoder_type ui_encoder = ui_encoder_type(
            encoding_type(std::locale()), encoding_type(std::locale())
        );
        window_type window(ui_encoder);
        const about_dialog_type about_dialog(window);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
