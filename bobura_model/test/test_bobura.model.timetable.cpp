/*! \file
    \brief Test of class bobura::model::timetable.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

#include "bobura.model.station.h"
#include "bobura.model.timetable.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.timetable_info.station_and_meters.h"

#include "test_bobura.model.timetable.h"


namespace test_bobura { namespace model
{
    // functions

    boost::unit_test::test_suite* timetable::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model::timetable");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));

        return p_suite;
    }

    void timetable::construction()
    {
        typedef
            bobura::model::station<
                std::wstring, bobura::model::station_info::grade<std::wstring>
            >
            station_type;
        typedef
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            >
            station_and_meters_type;

        bobura::model::timetable<station_and_meters_type> timetable;
    }

    void timetable::swap()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void timetable::operator_assign()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void timetable::operator_equal()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}
