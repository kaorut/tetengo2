/*! \file
    \brief Test of class tetengo2::gui::message::keyboard_observer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.message.keyboard_observer_set.h"


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(keyboard_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(character_input)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::gui::message::keyboard_observer_set<char>
            observer_set;

            observer_set.character_input();
        }
        {
            tetengo2::gui::message::keyboard_observer_set<char>
            observer_set;

            observer_set.character_input();
        }
        {
            const tetengo2::gui::message::keyboard_observer_set<wchar_t>
            observer_set;

            observer_set.character_input();
        }
        {
            tetengo2::gui::message::keyboard_observer_set<wchar_t>
            observer_set;

            observer_set.character_input();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
