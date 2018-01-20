/*! \file
    \brief Test of class tetengo2::gui::message::message_loop_break.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/message/message_loop_break.h>

#include "test_tetengo2.gui.detail_type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(message_loop_break)
    // test cases

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        using message_loop_break_type =
            tetengo2::gui::message::message_loop_break<detail_type_list_type::message_loop_type>;
        const message_loop_break_type message_loop_break{};

        message_loop_break(0);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
