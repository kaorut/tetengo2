/*! \file
    \brief Test of class tetengo2::gui::message::keyboard_observer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.virtual_key.h"
#include "tetengo2.gui.virtual_key.h"

#include "tetengo2.gui.message.keyboard_observer_set.h"


namespace
{
    // types

    typedef
        tetengo2::detail::stub::virtual_key<std::string>
        virtual_key_details_type;

    typedef
        tetengo2::gui::virtual_key<virtual_key_details_type>
        virtual_key_type;

    typedef
        tetengo2::gui::message::keyboard_observer_set<virtual_key_type, char>
        keyboard_observer_set_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(keyboard_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(character_input)
    {
        BOOST_TEST_PASSPOINT();

        {
            const keyboard_observer_set_type observer_set;

            observer_set.character_input();
        }
        {
            keyboard_observer_set_type observer_set;

            observer_set.character_input();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
