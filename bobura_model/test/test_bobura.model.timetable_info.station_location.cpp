/*! \file
    \brief Test of class bobura::model::timetable_info::station_location.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>

#include <boost/test/unit_test.hpp>

#include "bobura.model.station.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.timetable_info.station_location.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(timetable_info)
BOOST_AUTO_TEST_SUITE(station_location)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        typedef bobura::model::station_info::local<std::wstring> local_type;
        typedef bobura::model::station<std::wstring, local_type> station_type;

        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location(
                station_type(L"", local_type::instance()), 0
            );

            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > copy_of_station_location(station_location);

            BOOST_CHECK(station_location == copy_of_station_location);
        }
    }

    BOOST_AUTO_TEST_CASE(swap)
    {
        BOOST_TEST_PASSPOINT();

        typedef bobura::model::station_info::local<std::wstring> local_type;
        typedef bobura::model::station<std::wstring, local_type> station_type;

        bobura::model::timetable_info::station_location<
            station_type, std::size_t
        > station_location1(
            station_type(L"A", local_type::instance()), 1
        );
        bobura::model::timetable_info::station_location<
            station_type, std::size_t
        > station_location2(
            station_type(L"B", local_type::instance()), 2
        );

        station_location1.swap(station_location2);

        BOOST_CHECK(station_location1.station().name() == L"B");
        BOOST_CHECK_EQUAL(station_location1.meterage(), 2U);
        BOOST_CHECK(station_location2.station().name() == L"A");
        BOOST_CHECK_EQUAL(station_location2.meterage(), 1U);
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        typedef bobura::model::station_info::local<std::wstring> local_type;
        typedef bobura::model::station<std::wstring, local_type> station_type;

        {
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location1(
                station_type(L"A", local_type::instance()), 1
            );
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location2(
                station_type(L"B", local_type::instance()), 2
            );

            station_location1 = station_location2;

            BOOST_CHECK(station_location1 == station_location2);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        typedef bobura::model::station_info::local<std::wstring> local_type;
        typedef bobura::model::station<std::wstring, local_type> station_type;

        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location1(
                station_type(L"A", local_type::instance()), 1
            );
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location2(
                station_type(L"A", local_type::instance()), 1
            );

            BOOST_CHECK(station_location1 == station_location2);
        }
        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location1(
                station_type(L"A", local_type::instance()), 1
            );
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location2(
                station_type(L"B", local_type::instance()), 2
            );

            BOOST_CHECK(station_location1 != station_location2);
        }
    }

    BOOST_AUTO_TEST_CASE(station)
    {
        BOOST_TEST_PASSPOINT();

        typedef bobura::model::station_info::local<std::wstring> local_type;
        typedef bobura::model::station<std::wstring, local_type> station_type;

        const station_type station(L"", local_type::instance());
        const bobura::model::timetable_info::station_location<
            station_type, std::size_t
        > station_location(station, 0);

        BOOST_CHECK(station_location.station() == station);
    }

    BOOST_AUTO_TEST_CASE(meterage)
    {
        BOOST_TEST_PASSPOINT();

        typedef bobura::model::station_info::local<std::wstring> local_type;
        typedef bobura::model::station<std::wstring, local_type> station_type;

        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location(
                station_type(L"", local_type::instance()), 0
            );

            BOOST_CHECK_EQUAL(station_location.meterage(), 0U);
        }
        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location(
                station_type(L"", local_type::instance()), 1
            );

            BOOST_CHECK_EQUAL(station_location.meterage(), 1U);
        }
        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location(
                station_type(L"", local_type::instance()), 2
            );

            BOOST_CHECK_EQUAL(station_location.meterage(), 2U);
        }
    }

    BOOST_AUTO_TEST_CASE(before)
    {
        BOOST_TEST_PASSPOINT();

        typedef bobura::model::station_info::local<std::wstring> local_type;
        typedef bobura::model::station<std::wstring, local_type> station_type;

        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location1(
                station_type(L"", local_type::instance()), 1
            );
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location2(
                station_type(L"", local_type::instance()), 1
            );

            BOOST_CHECK(station_location1.before(station_location2));
        }
        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location1(
                station_type(L"", local_type::instance()), 1
            );
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location2(
                station_type(L"", local_type::instance()), 2
            );

            BOOST_CHECK(station_location1.before(station_location2));
        }
        {
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location1(
                station_type(L"", local_type::instance()), 2
            );
            const bobura::model::timetable_info::station_location<
                station_type, std::size_t
            > station_location2(
                station_type(L"", local_type::instance()), 1
            );

            BOOST_CHECK(!station_location1.before(station_location2));
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
