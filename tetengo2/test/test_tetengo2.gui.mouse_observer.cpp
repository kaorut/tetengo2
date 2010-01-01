/*! \file
    \brief Test of class tetengo2::gui::mouse_observer.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.mouse_observer.h"


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(mouse_observer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_CHECKPOINT("");

        tetengo2::gui::mouse_observer();
    }

    BOOST_AUTO_TEST_CASE(clicked)
    {
        BOOST_CHECKPOINT("");

        tetengo2::gui::mouse_observer mouse_observer;

        mouse_observer.clicked();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
