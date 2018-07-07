/*! \file
    \brief Test of class tetengo2::gui::message::keyboard_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/message/keyboard_observer_set.h>


namespace {
    // types

    using keyboard_observer_set_type = tetengo2::gui::message::keyboard_observer_set;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(message)
            BOOST_AUTO_TEST_SUITE(keyboard_observer_set)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const keyboard_observer_set_type observer_set{};
                }

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
