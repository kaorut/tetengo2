/*! \file
    \brief Test of class bobura::model::timetable_info::station_and_meters.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

#include "bobura.model.station.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.timetable_info.station_and_meters.h"

#include "test_bobura.model.timetable_info.station_and_meters.h"


namespace test_bobura { namespace model { namespace timetable_info
{
    // functions

    boost::unit_test::test_suite* station_and_meters::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE(
                "test_bobura::model::timetable_info::station_and_meters"
            );

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));
        p_suite->add(BOOST_TEST_CASE(operator_less));

        return p_suite;
    }

    void station_and_meters::construction()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            > station_and_meters(
                station_type(L"", grade_type::instance()), 0
            );

            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            > copy_of_station_and_meters(station_and_meters);

            BOOST_CHECK(station_and_meters == copy_of_station_and_meters);
        }
    }

    void station_and_meters::swap()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            > station_and_meters1(
                station_type(L"A", grade_type::instance()), 1
            );
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            > station_and_meters2(
                station_type(L"B", grade_type::instance()), 2
            );

            station_and_meters1.swap(station_and_meters2);

            BOOST_CHECK(station_and_meters1.station().name() == L"B");
            BOOST_CHECK_EQUAL(station_and_meters1.meters(), 2U);
            BOOST_CHECK(station_and_meters2.station().name() == L"A");
            BOOST_CHECK_EQUAL(station_and_meters2.meters(), 1U);
        }
        {
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            > station_and_meters1(
                station_type(L"A", grade_type::instance()), 1
            );
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            > station_and_meters2(
                station_type(L"B", grade_type::instance()), 2
            );

            std::swap(station_and_meters1, station_and_meters2);

            BOOST_CHECK(station_and_meters1.station().name() == L"B");
            BOOST_CHECK_EQUAL(station_and_meters1.meters(), 2U);
            BOOST_CHECK(station_and_meters2.station().name() == L"A");
            BOOST_CHECK_EQUAL(station_and_meters2.meters(), 1U);
        }
    }

    void station_and_meters::operator_assign()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            > station_and_meters1(
                station_type(L"A", grade_type::instance()), 1
            );
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            > station_and_meters2(
                station_type(L"B", grade_type::instance()), 2
            );

            station_and_meters1 = station_and_meters2;

            BOOST_CHECK(station_and_meters1 == station_and_meters2);
        }
    }

    void station_and_meters::operator_equal()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            > station_and_meters1(
                station_type(L"A", grade_type::instance()), 1
            );
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            > station_and_meters2(
                station_type(L"A", grade_type::instance()), 1
            );

            BOOST_CHECK(station_and_meters1 == station_and_meters2);
        }
        {
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            > station_and_meters1(
                station_type(L"A", grade_type::instance()), 1
            );
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            > station_and_meters2(
                station_type(L"B", grade_type::instance()), 2
            );

            BOOST_CHECK(station_and_meters1 != station_and_meters2);
        }
    }

    void station_and_meters::operator_less()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            > station_and_meters1(
                station_type(L"A", grade_type::instance()), 1
            );
            bobura::model::timetable_info::station_and_meters<
                station_type, std::size_t
            > station_and_meters2(
                station_type(L"A", grade_type::instance()), 1
            );

            BOOST_CHECK(station_and_meters1 == station_and_meters2);
        }
    }


}}}
