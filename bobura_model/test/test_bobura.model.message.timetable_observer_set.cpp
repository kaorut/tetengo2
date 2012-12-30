/*! \file
    \brief Test of class bobura::model::message::timetable_observer_set.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "bobura.model.message.timetable_observer_set.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(timetable_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(changed)
    {
        BOOST_TEST_PASSPOINT();

        {
            const bobura::model::message::timetable_observer_set observer_set;

            observer_set.changed();
        }
        {
            bobura::model::message::timetable_observer_set observer_set;

            observer_set.changed();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
