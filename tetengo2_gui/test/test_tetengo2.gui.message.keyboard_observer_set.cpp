/*! \file
    \brief Test of class tetengo2::gui::message::keyboard_observer_set.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using string_type = boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type;

    using virtual_key_type =
        tetengo2::gui::virtual_key<
            string_type,
            boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::virtual_key>::type
        >;

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
