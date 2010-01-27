/*! \file
    \brief Test of class tetengo2::gui::window_observer.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.window_observer.h"


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(window_observer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        tetengo2::gui::window_observer();
    }

    BOOST_AUTO_TEST_CASE(destroyed)
    {
        BOOST_TEST_PASSPOINT();

        tetengo2::gui::window_observer window_observer;

        window_observer.destroyed();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
