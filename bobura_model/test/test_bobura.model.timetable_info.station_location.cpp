/*! \file
    \brief Test of class bobura::model::timetable_info::station_location.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.test.h"

#include <algorithm>
#include <cstddef>
#include <string>

//#include <boost/test/unit_test.hpp>

#include "bobura.model.station.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.timetable_info.station_location.h"

#include "test_bobura.model.timetable_info.station_location.h"


namespace test_bobura { namespace model { namespace timetable_info
{
    // functions

    boost::unit_test::test_suite* station_location::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE(
                "test_bobura::model::timetable_info::station_location"
            );

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));
        p_suite->add(BOOST_TEST_CASE(station));
        p_suite->add(BOOST_TEST_CASE(meters));
        p_suite->add(BOOST_TEST_CASE(before));

        return p_suite;
    }

    void station_location::construction()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location(
                station_type(L"", grade_type::instance()), 0
            );

            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > copy_of_station_location(station_location);

            BOOST_CHECK(station_location == copy_of_station_location);
        }
    }

    void station_location::swap()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location1(
                station_type(L"A", grade_type::instance()), 1
            );
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location2(
                station_type(L"B", grade_type::instance()), 2
            );

            station_location1.swap(station_location2);

            BOOST_CHECK(station_location1.station().name() == L"B");
            BOOST_CHECK_EQUAL(station_location1.meters(), 2U);
            BOOST_CHECK(station_location2.station().name() == L"A");
            BOOST_CHECK_EQUAL(station_location2.meters(), 1U);
        }
        {
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location1(
                station_type(L"A", grade_type::instance()), 1
            );
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location2(
                station_type(L"B", grade_type::instance()), 2
            );

            std::swap(station_location1, station_location2);

            BOOST_CHECK(station_location1.station().name() == L"B");
            BOOST_CHECK_EQUAL(station_location1.meters(), 2U);
            BOOST_CHECK(station_location2.station().name() == L"A");
            BOOST_CHECK_EQUAL(station_location2.meters(), 1U);
        }
    }

    void station_location::operator_assign()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location1(
                station_type(L"A", grade_type::instance()), 1
            );
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location2(
                station_type(L"B", grade_type::instance()), 2
            );

            station_location1 = station_location2;

            BOOST_CHECK(station_location1 == station_location2);
        }
    }

    void station_location::operator_equal()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location1(
                station_type(L"A", grade_type::instance()), 1
            );
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location2(
                station_type(L"A", grade_type::instance()), 1
            );

            BOOST_CHECK(station_location1 == station_location2);
        }
        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location1(
                station_type(L"A", grade_type::instance()), 1
            );
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location2(
                station_type(L"B", grade_type::instance()), 2
            );

            BOOST_CHECK(station_location1 != station_location2);
        }
    }

    void station_location::station()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        const station_type station(L"", grade_type::instance());
        const bobura::model::timetable_info::station_location<
            station_type, std::size_t
        > station_location(station, 0);

        BOOST_CHECK(station_location.station() == station);
    }

    void station_location::meters()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location(
                station_type(L"", grade_type::instance()), 0
            );

            BOOST_CHECK_EQUAL(station_location.meters(), 0U);
        }
        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location(
                station_type(L"", grade_type::instance()), 1
            );

            BOOST_CHECK_EQUAL(station_location.meters(), 1U);
        }
        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location(
                station_type(L"", grade_type::instance()), 2
            );

            BOOST_CHECK_EQUAL(station_location.meters(), 2U);
        }
    }

    void station_location::before()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location1(
                station_type(L"", grade_type::instance()), 1
            );
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location2(
                station_type(L"", grade_type::instance()), 1
            );

            BOOST_CHECK(station_location1.before(station_location2));
        }
        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location1(
                station_type(L"", grade_type::instance()), 1
            );
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location2(
                station_type(L"", grade_type::instance()), 2
            );

            BOOST_CHECK(station_location1.before(station_location2));
        }
        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location1(
                station_type(L"", grade_type::instance()), 2
            );
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location2(
                station_type(L"", grade_type::instance()), 1
            );

            BOOST_CHECK(!station_location1.before(station_location2));
        }
    }


}}}
