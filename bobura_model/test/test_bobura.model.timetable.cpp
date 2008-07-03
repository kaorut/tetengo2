/*! \file
    \brief Test of class bobura::model::timetable.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>

//#include <boost/test/unit_test.hpp>

#include "bobura.model.station.h"
#include "bobura.model.timetable.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.timetable_info.station_location.h"

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
        p_suite->add(BOOST_TEST_CASE(station_locations));
        p_suite->add(BOOST_TEST_CASE(insert_station_location));
        p_suite->add(BOOST_TEST_CASE(erase_station_locations));

        return p_suite;
    }

    void timetable::construction()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;
        typedef
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            >
            station_location_type;

        {
            bobura::model::timetable<station_location_type> timetable;

            bobura::model::timetable<station_location_type>
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
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            >
            station_location_type;

        {
            bobura::model::timetable<station_location_type> timetable1;
            timetable1.insert_station_location(
                timetable1.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );

            bobura::model::timetable<station_location_type> timetable2;
            timetable2.insert_station_location(
                timetable2.station_locations().end(),
                station_location_type(
                    station_type(L"B", grade_type::instance()),
                    2
                )
            );

            timetable1.swap(timetable2);

            BOOST_CHECK(
                timetable1.station_locations()[0].station().name() ==
                std::wstring(L"B")
            );
            BOOST_CHECK_EQUAL(
                timetable1.station_locations()[0].meterage(), 2U
            );
            BOOST_CHECK(
                timetable2.station_locations()[0].station().name() ==
                std::wstring(L"A")
            );
            BOOST_CHECK_EQUAL(
                timetable2.station_locations()[0].meterage(), 1U
            );
        }
        {
            bobura::model::timetable<station_location_type> timetable1;
            timetable1.insert_station_location(
                timetable1.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );

            bobura::model::timetable<station_location_type> timetable2;
            timetable2.insert_station_location(
                timetable2.station_locations().end(),
                station_location_type(
                    station_type(L"B", grade_type::instance()),
                    2
                )
            );

            std::swap(timetable1, timetable2);

            BOOST_CHECK(
                timetable1.station_locations()[0].station().name() ==
                std::wstring(L"B")
            );
            BOOST_CHECK_EQUAL(
                timetable1.station_locations()[0].meterage(), 2U
            );
            BOOST_CHECK(
                timetable2.station_locations()[0].station().name() ==
                std::wstring(L"A")
            );
            BOOST_CHECK_EQUAL(
                timetable2.station_locations()[0].meterage(), 1U
            );
        }
    }

    void timetable::operator_assign()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;
        typedef
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            >
            station_location_type;

        bobura::model::timetable<station_location_type> timetable1;
        timetable1.insert_station_location(
            timetable1.station_locations().end(),
            station_location_type(
                station_type(L"A", grade_type::instance()),
                1
            )
        );

        bobura::model::timetable<station_location_type> timetable2;
        timetable2.insert_station_location(
            timetable2.station_locations().end(),
            station_location_type(
                station_type(L"B", grade_type::instance()),
                2
            )
        );

        timetable1 = timetable2;

        BOOST_CHECK(timetable1 == timetable2);
    }

    void timetable::operator_equal()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;
        typedef
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            >
            station_location_type;

        {
            bobura::model::timetable<station_location_type> timetable1;

            bobura::model::timetable<station_location_type> timetable2;

            BOOST_CHECK(timetable1 == timetable2);
        }
        {
            bobura::model::timetable<station_location_type> timetable1;
            timetable1.insert_station_location(
                timetable1.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );

            bobura::model::timetable<station_location_type> timetable2;
            timetable2.insert_station_location(
                timetable2.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );

            BOOST_CHECK(timetable1 == timetable2);
        }
        {
            bobura::model::timetable<station_location_type> timetable1;
            timetable1.insert_station_location(
                timetable1.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );

            bobura::model::timetable<station_location_type> timetable2;
            timetable2.insert_station_location(
                timetable2.station_locations().end(),
                station_location_type(
                    station_type(L"B", grade_type::instance()),
                    2
                )
            );

            BOOST_CHECK(timetable1 != timetable2);
        }
        {
            bobura::model::timetable<station_location_type> timetable1;
            timetable1.insert_station_location(
                timetable1.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );

            bobura::model::timetable<station_location_type> timetable2;
            timetable2.insert_station_location(
                timetable2.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );
            timetable2.insert_station_location(
                timetable2.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );

            BOOST_CHECK(timetable1 != timetable2);
        }
        {
            bobura::model::timetable<station_location_type> timetable1;
            timetable1.insert_station_location(
                timetable1.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );
            timetable1.insert_station_location(
                timetable1.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );

            bobura::model::timetable<station_location_type> timetable2;
            timetable2.insert_station_location(
                timetable2.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );
            timetable2.insert_station_location(
                timetable2.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );

            BOOST_CHECK(timetable1 == timetable2);
        }
    }

    void timetable::station_locations()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;
        typedef
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            >
            station_location_type;

        {
            bobura::model::timetable<station_location_type> timetable;

            const bobura::model::timetable<
                station_location_type
            >::station_locations_type& station_locations =
                timetable.station_locations();

            BOOST_CHECK(station_locations.empty());
        }
        {
            bobura::model::timetable<station_location_type> timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );

            const bobura::model::timetable<
                station_location_type
            >::station_locations_type& station_locations =
                timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 1U);
            BOOST_CHECK(
                station_locations[0].station().name() == std::wstring(L"A")
            );
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 1U);
        }
        {
            bobura::model::timetable<station_location_type> timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"B", grade_type::instance()),
                    2
                )
            );

            const bobura::model::timetable<
                station_location_type
            >::station_locations_type& station_locations =
                timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 2U);
            BOOST_CHECK(
                station_locations[0].station().name() == std::wstring(L"A")
            );
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 1U);
            BOOST_CHECK(
                station_locations[1].station().name() == std::wstring(L"B")
            );
            BOOST_CHECK_EQUAL(station_locations[1].meterage(), 2U);
        }
    }

    void timetable::insert_station_location()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;
        typedef
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            >
            station_location_type;

        {
            bobura::model::timetable<station_location_type> timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );

            const bobura::model::timetable<
                station_location_type
            >::station_locations_type& station_locations =
                timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 1U);
            BOOST_CHECK(
                station_locations[0].station().name() == std::wstring(L"A")
            );
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 1U);
        }
        {
            bobura::model::timetable<station_location_type> timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"B", grade_type::instance()),
                    2
                )
            );

            const bobura::model::timetable<
                station_location_type
            >::station_locations_type& station_locations =
                timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 2U);
            BOOST_CHECK(
                station_locations[0].station().name() == std::wstring(L"A")
            );
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 1U);
            BOOST_CHECK(
                station_locations[1].station().name() == std::wstring(L"B")
            );
            BOOST_CHECK_EQUAL(station_locations[1].meterage(), 2U);
        }
        {
            bobura::model::timetable<station_location_type> timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"B", grade_type::instance()),
                    2
                )
            );
            BOOST_CHECK_THROW(
                timetable.insert_station_location(
                    timetable.station_locations().end(),
                    station_location_type(
                        station_type(L"A", grade_type::instance()),
                        1
                    )
                ),
                std::invalid_argument
            );

            const bobura::model::timetable<
                station_location_type
            >::station_locations_type& station_locations =
                timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 1U);
            BOOST_CHECK(
                station_locations[0].station().name() == std::wstring(L"B")
            );
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 2U);
        }
        {
            bobura::model::timetable<station_location_type> timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"B", grade_type::instance()),
                    2
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"D", grade_type::instance()),
                    4
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().begin(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().begin() + 2,
                station_location_type(
                    station_type(L"C", grade_type::instance()),
                    3
                )
            );

            const bobura::model::timetable<
                station_location_type
            >::station_locations_type& station_locations =
                timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 4U);
            BOOST_CHECK(
                station_locations[0].station().name() == std::wstring(L"A")
            );
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 1U);
            BOOST_CHECK(
                station_locations[1].station().name() == std::wstring(L"B")
            );
            BOOST_CHECK_EQUAL(station_locations[1].meterage(), 2U);
            BOOST_CHECK(
                station_locations[2].station().name() == std::wstring(L"C")
            );
            BOOST_CHECK_EQUAL(station_locations[2].meterage(), 3U);
            BOOST_CHECK(
                station_locations[3].station().name() == std::wstring(L"D")
            );
            BOOST_CHECK_EQUAL(station_locations[3].meterage(), 4U);
        }
    }

    void timetable::erase_station_locations()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;
        typedef
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            >
            station_location_type;

        {
            bobura::model::timetable<station_location_type> timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"B", grade_type::instance()),
                    2
                )
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(),
                timetable.station_locations().end()
            );

            const bobura::model::timetable<
                station_location_type
            >::station_locations_type& station_locations =
                timetable.station_locations();

            BOOST_CHECK(station_locations.empty());
        }
        {
            bobura::model::timetable<station_location_type> timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"B", grade_type::instance()),
                    2
                )
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(),
                timetable.station_locations().begin() + 1
            );

            const bobura::model::timetable<
                station_location_type
            >::station_locations_type& station_locations =
                timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 1U);
            BOOST_CHECK(
                station_locations[0].station().name() == std::wstring(L"B")
            );
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 2U);
        }
        {
            bobura::model::timetable<station_location_type> timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"B", grade_type::instance()),
                    2
                )
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(),
                timetable.station_locations().begin()
            );

            const bobura::model::timetable<
                station_location_type
            >::station_locations_type& station_locations =
                timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 2U);
            BOOST_CHECK(
                station_locations[0].station().name() == std::wstring(L"A")
            );
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 1U);
            BOOST_CHECK(
                station_locations[1].station().name() == std::wstring(L"B")
            );
            BOOST_CHECK_EQUAL(station_locations[1].meterage(), 2U);
        }
        {
            bobura::model::timetable<station_location_type> timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()),
                    1
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"B", grade_type::instance()),
                    2
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"C", grade_type::instance()),
                    3
                )
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin() + 1,
                timetable.station_locations().begin() + 2
            );

            const bobura::model::timetable<
                station_location_type
            >::station_locations_type& station_locations =
                timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 2U);
            BOOST_CHECK(
                station_locations[0].station().name() == std::wstring(L"A")
            );
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 1U);
            BOOST_CHECK(
                station_locations[1].station().name() == std::wstring(L"C")
            );
            BOOST_CHECK_EQUAL(station_locations[1].meterage(), 3U);
        }
    }


}}
