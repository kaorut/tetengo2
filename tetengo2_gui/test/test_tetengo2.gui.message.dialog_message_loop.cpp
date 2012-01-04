/*! \file
    \brief Test of class tetengo2::gui::message::dialog_message_loop.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.message_loop.h"

#include "tetengo2.gui.message.dialog_message_loop.h"


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(dialog_message_loop)
    // test cases

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        typedef
            tetengo2::gui::message::dialog_message_loop<
                tetengo2::detail::stub::message_loop
            >
            dialog_message_loop_type;
        const dialog_message_loop_type dialog_message_loop =
            dialog_message_loop_type();

        dialog_message_loop();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
