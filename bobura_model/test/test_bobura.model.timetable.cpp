/*! \file
    \brief Test of class bobura::model::timetable.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

#include <cstddef>
#include <string>

//#include <boost/test/unit_test.hpp>

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
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;
        typedef
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            >
            station_and_meters_type;

        {
            bobura::model::timetable<station_and_meters_type> timetable;

            bobura::model::timetable<station_and_meters_type>
            copy_of_timetable(timetable);

            BOOST_CHECK(timetable == copy_of_timetable);
        }
    }

    void timetable::swap()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;
        typedef
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            >
            station_and_meters_type;

        {
            bobura::model::timetable<station_and_meters_type> timetable1;
            timetable1.insert_station_and_meters(
                timetable1.stations_and_meters().end(),
                station_and_meters_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );

            bobura::model::timetable<station_and_meters_type> timetable2;
            timetable2.insert_station_and_meters(
                timetable2.stations_and_meters().end(),
                station_and_meters_type(
                    station_type(L"B", grade_type::instance()),
                    2
                )
            );

            timetable1.swap(timetable2);

            //BOOST_CHECK(timetable == copy_of_timetable);
        }
        {
            bobura::model::timetable<station_and_meters_type> timetable1;

            bobura::model::timetable<station_and_meters_type> timetable2;

            std::swap(timetable1, timetable2);

            //BOOST_CHECK(timetable == copy_of_timetable);
        }
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
