/*! \file
    \brief Test of class tetengo2::gui::message::keyboard_observer_set.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using virtual_key_type = tetengo2::gui::virtual_key<string_type, detail_type_list_type::virtual_key_type>;

    using keyboard_observer_set_type = tetengo2::gui::message::keyboard_observer_set<virtual_key_type, string_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(keyboard_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(key_up)
    {
        BOOST_TEST_PASSPOINT();

        {
            const keyboard_observer_set_type observer_set{};

            observer_set.key_up();
        }
        {
            keyboard_observer_set_type observer_set{};

            observer_set.key_up();
        }
    }

    BOOST_AUTO_TEST_CASE(key_down)
    {
        BOOST_TEST_PASSPOINT();

        {
            const keyboard_observer_set_type observer_set{};

            observer_set.key_down();
        }
        {
            keyboard_observer_set_type observer_set{};

            observer_set.key_down();
        }
    }

    BOOST_AUTO_TEST_CASE(character_input)
    {
        BOOST_TEST_PASSPOINT();

        {
            const keyboard_observer_set_type observer_set{};

            observer_set.character_input();
        }
        {
            keyboard_observer_set_type observer_set{};

            observer_set.character_input();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
