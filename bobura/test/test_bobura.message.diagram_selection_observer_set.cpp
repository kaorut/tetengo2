/*! \file
    \brief Test of class bobura::message::diagram_selection_observer_set.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "bobura.message.diagram_selection_observer_set.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(diagram_selection_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(station_selected)
    {
        BOOST_TEST_PASSPOINT();

        {
            const bobura::message::diagram_selection_observer_set observer_set;

            observer_set.station_selected();
        }
        {
            bobura::message::diagram_selection_observer_set observer_set;

            observer_set.station_selected();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
