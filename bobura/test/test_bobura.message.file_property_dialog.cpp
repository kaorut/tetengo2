/*! \file
    \brief Test of class bobura::message::about_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "test_bobura.types.h"

#include "bobura.message.about_dialog.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(about_dialog)
BOOST_AUTO_TEST_SUITE(ok_button_mouse_observer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        dialog_type dialog(parent);
        const bobura::message::about_dialog::ok_button_mouse<dialog_type>
        observer(dialog);
    }

    BOOST_AUTO_TEST_CASE(clicked)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        dialog_type dialog(parent);
        const bobura::message::about_dialog::ok_button_mouse<dialog_type>
        observer(dialog);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
