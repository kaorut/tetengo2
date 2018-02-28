/*! \file
    \brief Test of class tetengo2::gui::message::window_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/message/window_observer_set.h>


namespace {
// types

using window_observer_set_type = tetengo2::gui::message::window_observer_set;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(message)
            BOOST_AUTO_TEST_SUITE(window_observer_set)
                // test cases

                BOOST_AUTO_TEST_CASE(closing)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const window_observer_set_type observer_set{};

                        observer_set.closing();
                    }
                    {
                        window_observer_set_type observer_set{};

                        observer_set.closing();
                    }
                }

                BOOST_AUTO_TEST_CASE(destroyed)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const window_observer_set_type observer_set{};

                        observer_set.destroyed();
                    }
                    {
                        window_observer_set_type observer_set{};

                        observer_set.destroyed();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
