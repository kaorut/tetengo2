/*! \file
    \brief Test of namespace bobura::model::timetable_info.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

#include "init_bobura.model.timetable_info.h"
#include "test_bobura.model.timetable_info.station_and_meters.h"


namespace test_bobura { namespace model { namespace timetable_info
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model::timetable_info");

        p_suite->add(station_and_meters::suite());

        return p_suite;
    }


}}}
