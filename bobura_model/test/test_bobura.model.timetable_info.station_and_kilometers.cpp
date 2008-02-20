/*! \file
    \brief Test of class bobura::model::timetable_info::station_and_kilometers.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

#include "bobura.model.timetable_info.station_and_kilometers.h"

#include "test_bobura.model.timetable_info.station_and_kilometers.h"


namespace test_bobura { namespace model { namespace timetable_info
{
    // functions

    boost::unit_test::test_suite* station_and_kilometers::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE(
                "test_bobura::model::timetable_info::station_and_kilometers"
            );

        p_suite->add(BOOST_TEST_CASE(construction));

        return p_suite;
    }

    void station_and_kilometers::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}
