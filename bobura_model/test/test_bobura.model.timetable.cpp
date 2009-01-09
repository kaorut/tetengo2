/*! \file
    \brief Test of class bobura::model::timetable.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>

#include <boost/test/unit_test.hpp>

#include "bobura.model.station.h"
#include "bobura.model.train.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.timetable_info.station_location.h"
#include "bobura.model.train_info.stop.h"
#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"

#include "bobura.model.timetable.h"

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
        p_suite->add(BOOST_TEST_CASE(trains));
        p_suite->add(BOOST_TEST_CASE(insert_train));
        p_suite->add(BOOST_TEST_CASE(erase_trains));

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
        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        typedef
            bobura::model::train<std::string, std::string, stop_type>
            train_type;
        typedef
            bobura::model::timetable<station_location_type, train_type>
            timetable_type;

        {
            const timetable_type timetable;

            BOOST_CHECK(timetable.station_locations().empty());

            timetable_type copy_of_timetable(timetable);

            BOOST_CHECK(timetable == copy_of_timetable);
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            const timetable_type timetable(
                station_locations.begin(), station_locations.end()
            );

            BOOST_CHECK(timetable.station_locations() == station_locations);

            timetable_type copy_of_timetable(timetable);

            BOOST_CHECK(timetable == copy_of_timetable);
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );

            const timetable_type timetable(
                station_locations.begin(), station_locations.end()
            );

            BOOST_CHECK(timetable.station_locations() == station_locations);

            timetable_type copy_of_timetable(timetable);

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
        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        typedef
            bobura::model::train<std::string, std::string, stop_type>
            train_type;
        typedef
            bobura::model::timetable<station_location_type, train_type>
            timetable_type;

        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            timetable_type timetable1(
                station_locations1.begin(), station_locations1.end()
            );

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );

            timetable_type timetable2(
                station_locations2.begin(), station_locations2.end()
            );

            timetable1.swap(timetable2);

            BOOST_CHECK(timetable1.station_locations() == station_locations2);
            BOOST_CHECK(timetable2.station_locations() == station_locations1);
        }
        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            timetable_type timetable1(
                station_locations1.begin(), station_locations1.end()
            );

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );

            timetable_type timetable2(
                station_locations2.begin(), station_locations2.end()
            );

            std::swap(timetable1, timetable2);

            BOOST_CHECK(timetable1.station_locations() == station_locations2);
            BOOST_CHECK(timetable2.station_locations() == station_locations1);
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
        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        typedef
            bobura::model::train<std::string, std::string, stop_type>
            train_type;
        typedef
            bobura::model::timetable<station_location_type, train_type>
            timetable_type;

        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            timetable_type timetable1(
                station_locations1.begin(), station_locations1.end()
            );

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );

            const timetable_type timetable2(
                station_locations2.begin(), station_locations2.end()
            );

            timetable1 = timetable2;

            BOOST_CHECK(timetable1 == timetable2);
        }
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
        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        typedef
            bobura::model::train<std::string, std::string, stop_type>
            train_type;
        typedef
            bobura::model::timetable<station_location_type, train_type>
            timetable_type;

        {
            const timetable_type timetable1;

            const timetable_type timetable2;

            BOOST_CHECK(timetable1 == timetable2);
        }
        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            const timetable_type timetable1(
                station_locations1.begin(), station_locations1.end()
            );

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            const timetable_type timetable2(
                station_locations2.begin(), station_locations2.end()
            );

            BOOST_CHECK(timetable1 == timetable2);
        }
        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            const timetable_type timetable1(
                station_locations1.begin(), station_locations1.end()
            );

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );

            const timetable_type timetable2(
                station_locations2.begin(), station_locations2.end()
            );

            BOOST_CHECK(timetable1 != timetable2);
        }
        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            const timetable_type timetable1(
                station_locations1.begin(), station_locations1.end()
            );

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );
            station_locations2.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            const timetable_type timetable2(
                station_locations2.begin(), station_locations2.end()
            );

            BOOST_CHECK(timetable1 != timetable2);
        }
        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );
            station_locations1.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            const timetable_type timetable1(
                station_locations1.begin(), station_locations1.end()
            );

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );
            station_locations2.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            const timetable_type timetable2(
                station_locations2.begin(), station_locations2.end()
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
        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        typedef
            bobura::model::train<std::string, std::string, stop_type>
            train_type;
        typedef
            bobura::model::timetable<station_location_type, train_type>
            timetable_type;

        {
            const timetable_type timetable;

            const timetable_type::station_locations_type&
            station_locations = timetable.station_locations();

            BOOST_CHECK(station_locations.empty());
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            const timetable_type timetable(
                station_locations.begin(), station_locations.end()
            );

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );

            const timetable_type timetable(
                station_locations.begin(), station_locations.end()
            );

            BOOST_CHECK(timetable.station_locations() == station_locations);
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
        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        typedef
            bobura::model::train<std::string, std::string, stop_type>
            train_type;
        typedef
            bobura::model::timetable<station_location_type, train_type>
            timetable_type;

        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );

            timetable_type timetable(
                station_locations.begin(), station_locations.begin() + 1
            );

            timetable.insert_station_location(
                timetable.station_locations().end(), station_locations[1]
            );

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
        {
            timetable_type timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            const timetable_type::station_locations_type&
            station_locations =
                timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 1U);
            BOOST_CHECK(
                station_locations[0].station().name() == std::wstring(L"A")
            );
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 1U);
        }
        {
            timetable_type timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );

            const timetable_type::station_locations_type&
            station_locations = timetable.station_locations();

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
            timetable_type timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );
            BOOST_CHECK_THROW(
                timetable.insert_station_location(
                    timetable.station_locations().end(),
                    station_location_type(
                        station_type(L"A", grade_type::instance()), 1
                    )
                ),
                std::invalid_argument
            );

            const timetable_type::station_locations_type&
            station_locations = timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 1U);
            BOOST_CHECK(
                station_locations[0].station().name() == std::wstring(L"B")
            );
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 2U);
        }
        {
            timetable_type timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"D", grade_type::instance()), 4
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().begin(),
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().begin() + 2,
                station_location_type(
                    station_type(L"C", grade_type::instance()), 3
                )
            );

            const timetable_type::station_locations_type&
            station_locations = timetable.station_locations();

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
        {
            timetable_type timetable;

            timetable.insert_train(
                timetable.trains().end(), train_type("1", "x")
            );

            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            BOOST_CHECK_EQUAL(
                timetable.trains()[0].stops().size(),
                timetable.station_locations().size()
            );
            BOOST_CHECK(
                timetable.trains()[0].stops()[0].arrival() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.trains()[0].stops()[0].departure() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(timetable.trains()[0].stops()[0].platform().empty());

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops.push_back(stop_type(time_type(3), time_type(4), "b"));

            timetable.insert_train(
                timetable.trains().end(),
                train_type("2", "y", stops.begin(), stops.begin() + 1)
            );

            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"C", grade_type::instance()), 3
                )
            );

            BOOST_CHECK_EQUAL(
                timetable.trains()[1].stops().size(),
                timetable.station_locations().size()
            );
            BOOST_CHECK(
                timetable.trains()[1].stops()[1].arrival() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.trains()[1].stops()[1].departure() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(timetable.trains()[1].stops()[1].platform().empty());

            timetable.insert_train(
                timetable.trains().end(),
                train_type("3", "z", stops.begin(), stops.end())
            );

            timetable.insert_station_location(
                timetable.station_locations().begin() + 1,
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );

            BOOST_CHECK_EQUAL(
                timetable.trains()[2].stops().size(),
                timetable.station_locations().size()
            );
            BOOST_CHECK(
                timetable.trains()[2].stops()[1].arrival() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.trains()[2].stops()[1].departure() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(timetable.trains()[2].stops()[1].platform().empty());
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
        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        typedef
            bobura::model::train<std::string, std::string, stop_type>
            train_type;
        typedef
            bobura::model::timetable<station_location_type, train_type>
            timetable_type;

        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );

            timetable_type timetable(
                station_locations.begin(), station_locations.end()
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(),
                timetable.station_locations().end()
            );

            BOOST_CHECK(timetable.station_locations().empty());
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );

            timetable_type timetable(
                station_locations.begin(), station_locations.end()
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(),
                timetable.station_locations().begin() + 1
            );

            BOOST_CHECK_EQUAL(timetable.station_locations().size(), 1U);
            BOOST_CHECK(
                timetable.station_locations()[0].station().name() ==
                std::wstring(L"B")
            );
            BOOST_CHECK_EQUAL(
                timetable.station_locations()[0].meterage(), 2U
            );
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );

            timetable_type timetable(
                station_locations.begin(), station_locations.end()
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(),
                timetable.station_locations().begin()
            );

            BOOST_CHECK_EQUAL(timetable.station_locations().size(), 2U);
            BOOST_CHECK(
                timetable.station_locations()[0].station().name() ==
                std::wstring(L"A")
            );
            BOOST_CHECK_EQUAL(
                timetable.station_locations()[0].meterage(), 1U
            );
            BOOST_CHECK(
                timetable.station_locations()[1].station().name() ==
                std::wstring(L"B")
            );
            BOOST_CHECK_EQUAL(
                timetable.station_locations()[1].meterage(), 2U
            );
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"C", grade_type::instance()), 3
                )
            );

            timetable_type timetable(
                station_locations.begin(), station_locations.end()
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin() + 1,
                timetable.station_locations().begin() + 2
            );

            BOOST_CHECK_EQUAL(timetable.station_locations().size(), 2U);
            BOOST_CHECK(
                timetable.station_locations()[0].station().name() ==
                std::wstring(L"A")
            );
            BOOST_CHECK_EQUAL(
                timetable.station_locations()[0].meterage(), 1U
            );
            BOOST_CHECK(
                timetable.station_locations()[1].station().name() ==
                std::wstring(L"C")
            );
            BOOST_CHECK_EQUAL(
                timetable.station_locations()[1].meterage(), 3U
            );
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );

            timetable_type timetable(
                station_locations.begin(), station_locations.end()
            );

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops.push_back(stop_type(time_type(3), time_type(4), "b"));

            timetable.insert_train(
                timetable.trains().end(),
                train_type("1", "x", stops.begin(), stops.end())
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(),
                timetable.station_locations().end()
            );

            BOOST_CHECK_EQUAL(
                timetable.trains()[0].stops().size(),
                timetable.station_locations().size()
            );
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", grade_type::instance()), 2
                )
            );

            timetable_type timetable(
                station_locations.begin(), station_locations.end()
            );

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops.push_back(stop_type(time_type(3), time_type(4), "b"));

            timetable.insert_train(
                timetable.trains().end(),
                train_type("1", "x", stops.begin(), stops.end())
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(),
                timetable.station_locations().begin() + 1
            );

            BOOST_CHECK_EQUAL(
                timetable.trains()[0].stops().size(),
                timetable.station_locations().size()
            );
        }
    }

    void timetable::trains()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;
        typedef
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            >
            station_location_type;
        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        typedef
            bobura::model::train<std::string, std::string, stop_type>
            train_type;
        typedef
            bobura::model::timetable<station_location_type, train_type>
            timetable_type;

        {
            const timetable_type timetable;

            const timetable_type::trains_type& trains =
                timetable.trains();

            BOOST_CHECK(trains.empty());
        }
        {
            timetable_type timetable;
            timetable.insert_train(
                timetable.trains().end(), train_type("1", "x")
            );

            const timetable_type::trains_type& trains =
                timetable.trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
        }
        {
            timetable_type timetable;
            timetable.insert_train(
                timetable.trains().end(), train_type("1", "x")
            );
            timetable.insert_train(
                timetable.trains().end(), train_type("2", "y")
            );

            const timetable_type::trains_type& trains =
                timetable.trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
            BOOST_CHECK_EQUAL(trains[1].number(), "2");
            BOOST_CHECK_EQUAL(trains[1].note(),  "y");
        }
    }

    void timetable::insert_train()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;
        typedef
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            >
            station_location_type;
        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        typedef
            bobura::model::train<std::string, std::string, stop_type>
            train_type;
        typedef
            bobura::model::timetable<station_location_type, train_type>
            timetable_type;

        {
            timetable_type timetable;
            timetable.insert_train(
                timetable.trains().end(), train_type("1", "x")
            );

            const timetable_type::trains_type& trains =
                timetable.trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
        }
        {
            timetable_type timetable;
            timetable.insert_train(
                timetable.trains().end(), train_type("1", "x")
            );
            timetable.insert_train(
                timetable.trains().end(), train_type("2", "y")
            );

            const timetable_type::trains_type& trains =
                timetable.trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
            BOOST_CHECK_EQUAL(trains[1].number(), "2");
            BOOST_CHECK_EQUAL(trains[1].note(),  "y");
        }
        {
            timetable_type timetable;
            timetable.insert_train(
                timetable.trains().end(), train_type("2", "y")
            );
            timetable.insert_train(
                timetable.trains().end(), train_type("4", "w")
            );
            timetable.insert_train(
                timetable.trains().begin(), train_type("1", "x")
            );
            timetable.insert_train(
                timetable.trains().begin() + 2, train_type("3", "z")
            );

            const timetable_type::trains_type& trains =
                timetable.trains();

            BOOST_CHECK_EQUAL(trains.size(), 4U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
            BOOST_CHECK_EQUAL(trains[1].number(), "2");
            BOOST_CHECK_EQUAL(trains[1].note(),  "y");
            BOOST_CHECK_EQUAL(trains[2].number(), "3");
            BOOST_CHECK_EQUAL(trains[2].note(),  "z");
            BOOST_CHECK_EQUAL(trains[3].number(), "4");
            BOOST_CHECK_EQUAL(trains[3].note(),  "w");
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", grade_type::instance()), 1
                )
            );

            timetable_type timetable(
                station_locations.begin(), station_locations.end()
            );

            BOOST_CHECK_THROW(
                timetable.insert_train(
                    timetable.trains().end(), train_type("1", "x")
                ),
                std::invalid_argument
            );
        }
        {
            timetable_type timetable;

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));

            BOOST_CHECK_THROW(
                timetable.insert_train(
                    timetable.trains().end(),
                    train_type("1", "x", stops.begin(), stops.end())
                ),
                std::invalid_argument
            );
        }
    }

    void timetable::erase_trains()
    {
        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;
        typedef
            bobura::model::timetable_info::station_location<
                station_type, std::size_t
            >
            station_location_type;
        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        typedef
            bobura::model::train<std::string, std::string, stop_type>
            train_type;
        typedef
            bobura::model::timetable<station_location_type, train_type>
            timetable_type;

        {
            timetable_type timetable;
            timetable.insert_train(
                timetable.trains().end(), train_type("1", "x")
            );
            timetable.insert_train(
                timetable.trains().end(), train_type("2", "y")
            );

            timetable.erase_trains(
                timetable.trains().begin(), timetable.trains().end()
            );

            const timetable_type::trains_type& trains =
                timetable.trains();

            BOOST_CHECK(trains.empty());
        }
        {
            timetable_type timetable;
            timetable.insert_train(
                timetable.trains().end(), train_type("1", "x")
            );
            timetable.insert_train(
                timetable.trains().end(), train_type("2", "y")
            );

            timetable.erase_trains(
                timetable.trains().begin(), timetable.trains().begin() + 1
            );

            const timetable_type::trains_type& trains =
                timetable.trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK_EQUAL(trains[0].number(), "2");
            BOOST_CHECK_EQUAL(trains[0].note(),  "y");
        }
        {
            timetable_type timetable;
            timetable.insert_train(
                timetable.trains().end(), train_type("1", "x")
            );
            timetable.insert_train(
                timetable.trains().end(), train_type("2", "y")
            );

            timetable.erase_trains(
                timetable.trains().begin(), timetable.trains().begin()
            );

            const timetable_type::trains_type& trains =
                timetable.trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
            BOOST_CHECK_EQUAL(trains[1].number(), "2");
            BOOST_CHECK_EQUAL(trains[1].note(),  "y");
        }
        {
            timetable_type timetable;
            timetable.insert_train(
                timetable.trains().end(), train_type("1", "x")
            );
            timetable.insert_train(
                timetable.trains().end(), train_type("2", "y")
            );
            timetable.insert_train(
                timetable.trains().end(), train_type("3", "z")
            );

            timetable.erase_trains(
                timetable.trains().begin() + 1, timetable.trains().begin() + 2
            );

            const timetable_type::trains_type& trains =
                timetable.trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
            BOOST_CHECK_EQUAL(trains[1].number(), "3");
            BOOST_CHECK_EQUAL(trains[1].note(),  "z");
        }
    }


}}
