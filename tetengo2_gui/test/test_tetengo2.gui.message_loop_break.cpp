/*! \file
    \brief Test of class tetengo2::gui::message_loop_break.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.message_loop.h"

#include "tetengo2.gui.message_loop_break.h"


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message_loop_break)
    // test cases

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        typedef
            tetengo2::gui::message_loop_break<
                tetengo2::detail::stub::message_loop
            >
            message_loop_break_type;
        const message_loop_break_type message_loop_break =
            message_loop_break_type();

        message_loop_break(0);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
