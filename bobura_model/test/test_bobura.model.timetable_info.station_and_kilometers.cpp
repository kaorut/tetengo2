/*! \file
    \brief Test of class bobura::model::timetable_info::station_and_kilometers.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

#include "bobura.model.station.h"
#include "bobura.model.station_info.grade.h"
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
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));
        p_suite->add(BOOST_TEST_CASE(operator_less));

        return p_suite;
    }

    void station_and_kilometers::construction()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            bobura::model::timetable_info::station_and_kilometers<
                station_type, std::size_t
            > station_and_kilometers(
                station_type(L"", grade_type::instance()), 0
            );

            bobura::model::timetable_info::station_and_kilometers<
                station_type, std::size_t
            > copy_of_station_and_kilometers(station_and_kilometers);

            BOOST_CHECK(
                station_and_kilometers == copy_of_station_and_kilometers
            );
        }
    }

    void station_and_kilometers::swap()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void station_and_kilometers::operator_assign()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void station_and_kilometers::operator_equal()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void station_and_kilometers::operator_less()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}
