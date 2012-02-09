/*! \file
    \brief Test of class bobura::model::timetable.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <cstddef>
//#include <stdexcept>
#include <string>
//#include <utility>

#include <boost/test/unit_test.hpp>

#include "bobura.model.message.timetable_observer_set.h"
#include "bobura.model.station.h"
#include "bobura.model.train.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.timetable_info.station_location.h"
#include "bobura.model.train_info.stop.h"
#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"

#include "bobura.model.timetable.h"


namespace
{
    // types

    typedef
        bobura::model::station_info::grade_type_set<std::wstring>
        station_grade_type_set_type;

    typedef station_grade_type_set_type::grade_type grade_type;

    typedef station_grade_type_set_type::local_type local_type;

    typedef bobura::model::station<std::wstring, grade_type> station_type;

    typedef
        bobura::model::timetable_info::station_location<
            station_type, std::size_t
        >
        station_location_type;

    typedef
        bobura::model::train_info::time<
            std::size_t, bobura::model::train_info::time_span<std::ptrdiff_t>
        >
        time_type;

    typedef bobura::model::train_info::stop<time_type, std::string> stop_type;

    typedef
        bobura::model::train<std::string, std::string, stop_type> train_type;

    typedef
        bobura::model::timetable<
            std::string,
            station_location_type,
            train_type,
            bobura::model::message::timetable_observer_set
        >
        timetable_type;

}

BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(timetable)
    // test cases

   BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();


        {
            const timetable_type timetable("hoge");

            BOOST_CHECK(timetable.station_locations().empty());
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );
            timetable_type::station_locations_type station_locations2(
                station_locations
            );

            const timetable_type timetable(
                "hoge", std::move(station_locations2)
            );

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );

            const timetable_type timetable("hoge", station_locations);

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );

            const timetable_type timetable(
                "hoge", station_locations.begin(), station_locations.end()
            );

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );

            const timetable_type timetable(
                "hoge", station_locations.begin(), station_locations.end()
            );

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable1("hoge");

            const timetable_type timetable2("hoge");

            BOOST_CHECK(timetable1 == timetable2);
        }
        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );

            const timetable_type timetable1(
                "hoge", station_locations1.begin(), station_locations1.end()
            );

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );

            const timetable_type timetable2(
                "hoge", station_locations2.begin(), station_locations2.end()
            );

            BOOST_CHECK(timetable1 == timetable2);
        }
        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );

            const timetable_type timetable1(
                "hoge", station_locations1.begin(), station_locations1.end()
            );

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );

            const timetable_type timetable2(
                "hoge", station_locations2.begin(), station_locations2.end()
            );

            BOOST_CHECK(timetable1 != timetable2);
        }
        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );

            const timetable_type timetable1(
                "hoge", station_locations1.begin(), station_locations1.end()
            );

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations2.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );

            const timetable_type timetable2(
                "hoge", station_locations2.begin(), station_locations2.end()
            );

            BOOST_CHECK(timetable1 != timetable2);
        }
        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations1.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );

            const timetable_type timetable1(
                "hoge", station_locations1.begin(), station_locations1.end()
            );

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations2.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );

            const timetable_type timetable2(
                "hoge", station_locations2.begin(), station_locations2.end()
            );

            BOOST_CHECK(timetable1 == timetable2);
        }
    }

    BOOST_AUTO_TEST_CASE(station_locations)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable("hoge");

            const timetable_type::station_locations_type&
            station_locations = timetable.station_locations();

            BOOST_CHECK(station_locations.empty());
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );

            const timetable_type timetable(
                "hoge", station_locations.begin(), station_locations.end()
            );

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );

            const timetable_type timetable(
                "hoge", station_locations.begin(), station_locations.end()
            );

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
    }

    BOOST_AUTO_TEST_CASE(insert_station_location)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );

            timetable_type timetable(
                "hoge",
                station_locations.begin(),
                station_locations.begin() + 1
            );

            timetable.insert_station_location(
                timetable.station_locations().end(), station_locations[1]
            );

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
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
            timetable_type timetable("hoge");
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
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
            timetable_type timetable("hoge");
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );
            BOOST_CHECK_THROW(
                timetable.insert_station_location(
                    timetable.station_locations().end(),
                    station_location_type(
                        station_type(L"A", local_type::instance()), 1
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
            timetable_type timetable("hoge");
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"D", local_type::instance()), 4
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().begin(),
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().begin() + 2,
                station_location_type(
                    station_type(L"C", local_type::instance()), 3
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
            timetable_type timetable("hoge");

            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("1", "x")
            );

            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );

            BOOST_CHECK_EQUAL(
                timetable.down_trains()[0].stops().size(),
                timetable.station_locations().size()
            );
            BOOST_CHECK(
                timetable.down_trains()[0].stops()[0].arrival() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.down_trains()[0].stops()[0].departure() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.down_trains()[0].stops()[0].platform().empty()
            );

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops.push_back(stop_type(time_type(3), time_type(4), "b"));

            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type("2", "y", stops.begin(), stops.begin() + 1)
            );

            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"C", local_type::instance()), 3
                )
            );

            BOOST_CHECK_EQUAL(
                timetable.down_trains()[1].stops().size(),
                timetable.station_locations().size()
            );
            BOOST_CHECK(
                timetable.down_trains()[1].stops()[1].arrival() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.down_trains()[1].stops()[1].departure() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.down_trains()[1].stops()[1].platform().empty()
            );

            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type("3", "z", stops.begin(), stops.end())
            );

            timetable.insert_station_location(
                timetable.station_locations().begin() + 1,
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );

            BOOST_CHECK_EQUAL(
                timetable.down_trains()[2].stops().size(),
                timetable.station_locations().size()
            );
            BOOST_CHECK(
                timetable.down_trains()[2].stops()[1].arrival() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.down_trains()[2].stops()[1].departure() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.down_trains()[2].stops()[1].platform().empty()
            );
        }
        {
            timetable_type timetable("hoge");

            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("1", "x")
            );

            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );

            BOOST_CHECK_EQUAL(
                timetable.up_trains()[0].stops().size(),
                timetable.station_locations().size()
            );
            BOOST_CHECK(
                timetable.up_trains()[0].stops()[0].arrival() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.up_trains()[0].stops()[0].departure() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.up_trains()[0].stops()[0].platform().empty()
            );

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops.push_back(stop_type(time_type(3), time_type(4), "b"));

            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type("2", "y", stops.begin(), stops.begin() + 1)
            );

            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(L"C", local_type::instance()), 3
                )
            );

            BOOST_CHECK_EQUAL(
                timetable.up_trains()[1].stops().size(),
                timetable.station_locations().size()
            );
            BOOST_CHECK(
                timetable.up_trains()[1].stops()[1].arrival() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.up_trains()[1].stops()[1].departure() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.up_trains()[1].stops()[1].platform().empty()
            );

            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type("3", "z", stops.begin(), stops.end())
            );

            timetable.insert_station_location(
                timetable.station_locations().begin() + 1,
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );

            BOOST_CHECK_EQUAL(
                timetable.up_trains()[2].stops().size(),
                timetable.station_locations().size()
            );
            BOOST_CHECK(
                timetable.up_trains()[2].stops()[1].arrival() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.up_trains()[2].stops()[1].departure() ==
                time_type::uninitialized()
            );
            BOOST_CHECK(
                timetable.up_trains()[2].stops()[1].platform().empty()
            );
        }
    }

    BOOST_AUTO_TEST_CASE(erase_station_locations)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );

            timetable_type timetable(
                "hoge", station_locations.begin(), station_locations.end()
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
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );

            timetable_type timetable(
                "hoge", station_locations.begin(), station_locations.end()
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
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );

            timetable_type timetable(
                "hoge", station_locations.begin(), station_locations.end()
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
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"C", local_type::instance()), 3
                )
            );

            timetable_type timetable(
                "hoge", station_locations.begin(), station_locations.end()
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
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );

            timetable_type timetable(
                "hoge", station_locations.begin(), station_locations.end()
            );

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops.push_back(stop_type(time_type(3), time_type(4), "b"));

            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type("1", "x", stops.begin(), stops.end())
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(),
                timetable.station_locations().end()
            );

            BOOST_CHECK_EQUAL(
                timetable.down_trains()[0].stops().size(),
                timetable.station_locations().size()
            );
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );

            timetable_type timetable(
                "hoge", station_locations.begin(), station_locations.end()
            );

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops.push_back(stop_type(time_type(3), time_type(4), "b"));

            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type("1", "x", stops.begin(), stops.end())
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(),
                timetable.station_locations().end()
            );

            BOOST_CHECK_EQUAL(
                timetable.up_trains()[0].stops().size(),
                timetable.station_locations().size()
            );
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );

            timetable_type timetable(
                "hoge", station_locations.begin(), station_locations.end()
            );

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops.push_back(stop_type(time_type(3), time_type(4), "b"));

            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type("1", "x", stops.begin(), stops.end())
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(),
                timetable.station_locations().begin() + 1
            );

            BOOST_CHECK_EQUAL(
                timetable.down_trains()[0].stops().size(),
                timetable.station_locations().size()
            );
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(L"A", local_type::instance()), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(L"B", local_type::instance()), 2
                )
            );

            timetable_type timetable(
                "hoge", station_locations.begin(), station_locations.end()
            );

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops.push_back(stop_type(time_type(3), time_type(4), "b"));

            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type("1", "x", stops.begin(), stops.end())
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(),
                timetable.station_locations().begin() + 1
            );

            BOOST_CHECK_EQUAL(
                timetable.up_trains()[0].stops().size(),
                timetable.station_locations().size()
            );
        }
    }

    BOOST_AUTO_TEST_CASE(down_trains)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable("hoge");

            const timetable_type::trains_type& trains =
                timetable.down_trains();

            BOOST_CHECK(trains.empty());
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("1", "x")
            );

            const timetable_type::trains_type& trains =
                timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("1", "x")
            );
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("2", "y")
            );

            const timetable_type::trains_type& trains =
                timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
            BOOST_CHECK_EQUAL(trains[1].number(), "2");
            BOOST_CHECK_EQUAL(trains[1].note(),  "y");
        }
    }

    BOOST_AUTO_TEST_CASE(up_trains)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable("hoge");

            const timetable_type::trains_type& trains =
                timetable.up_trains();

            BOOST_CHECK(trains.empty());
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("1", "x")
            );

            const timetable_type::trains_type& trains =
                timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("1", "x")
            );
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("2", "y")
            );

            const timetable_type::trains_type& trains =
                timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
            BOOST_CHECK_EQUAL(trains[1].number(), "2");
            BOOST_CHECK_EQUAL(trains[1].note(),  "y");
        }
    }

    BOOST_AUTO_TEST_CASE(insert_down_train)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable("hoge");
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("1", "x")
            );

            const timetable_type::trains_type& trains =
                timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("1", "x")
            );
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("2", "y")
            );

            const timetable_type::trains_type& trains =
                timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
            BOOST_CHECK_EQUAL(trains[1].number(), "2");
            BOOST_CHECK_EQUAL(trains[1].note(),  "y");
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("2", "y")
            );
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("4", "w")
            );
            timetable.insert_down_train(
                timetable.down_trains().begin(), train_type("1", "x")
            );
            timetable.insert_down_train(
                timetable.down_trains().begin() + 2, train_type("3", "z")
            );

            const timetable_type::trains_type& trains =
                timetable.down_trains();

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
                    station_type(L"A", local_type::instance()), 1
                )
            );

            timetable_type timetable(
                "hoge", station_locations.begin(), station_locations.end()
            );

            BOOST_CHECK_THROW(
                timetable.insert_down_train(
                    timetable.down_trains().end(), train_type("1", "x")
                ),
                std::invalid_argument
            );
        }
        {
            timetable_type timetable("hoge");

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));

            BOOST_CHECK_THROW(
                timetable.insert_down_train(
                    timetable.down_trains().end(),
                    train_type("1", "x", stops.begin(), stops.end())
                ),
                std::invalid_argument
            );
        }
    }

    BOOST_AUTO_TEST_CASE(insert_up_train)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable("hoge");
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("1", "x")
            );

            const timetable_type::trains_type& trains =
                timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("1", "x")
            );
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("2", "y")
            );

            const timetable_type::trains_type& trains =
                timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
            BOOST_CHECK_EQUAL(trains[1].number(), "2");
            BOOST_CHECK_EQUAL(trains[1].note(),  "y");
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("2", "y")
            );
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("4", "w")
            );
            timetable.insert_up_train(
                timetable.up_trains().begin(), train_type("1", "x")
            );
            timetable.insert_up_train(
                timetable.up_trains().begin() + 2, train_type("3", "z")
            );

            const timetable_type::trains_type& trains =
                timetable.up_trains();

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
                    station_type(L"A", local_type::instance()), 1
                )
            );

            timetable_type timetable(
                "hoge", station_locations.begin(), station_locations.end()
            );

            BOOST_CHECK_THROW(
                timetable.insert_up_train(
                    timetable.up_trains().end(), train_type("1", "x")
                ),
                std::invalid_argument
            );
        }
        {
            timetable_type timetable("hoge");

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));

            BOOST_CHECK_THROW(
                timetable.insert_up_train(
                    timetable.up_trains().end(),
                    train_type("1", "x", stops.begin(), stops.end())
                ),
                std::invalid_argument
            );
        }
    }

    BOOST_AUTO_TEST_CASE(erase_down_trains)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable("hoge");
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("1", "x")
            );
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("2", "y")
            );

            timetable.erase_down_trains(
                timetable.down_trains().begin(), timetable.down_trains().end()
            );

            const timetable_type::trains_type& trains =
                timetable.down_trains();

            BOOST_CHECK(trains.empty());
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("1", "x")
            );
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("2", "y")
            );

            timetable.erase_down_trains(
                timetable.down_trains().begin(),
                timetable.down_trains().begin() + 1
            );

            const timetable_type::trains_type& trains =
                timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK_EQUAL(trains[0].number(), "2");
            BOOST_CHECK_EQUAL(trains[0].note(),  "y");
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("1", "x")
            );
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("2", "y")
            );

            timetable.erase_down_trains(
                timetable.down_trains().begin(),
                timetable.down_trains().begin()
            );

            const timetable_type::trains_type& trains =
                timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
            BOOST_CHECK_EQUAL(trains[1].number(), "2");
            BOOST_CHECK_EQUAL(trains[1].note(),  "y");
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("1", "x")
            );
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("2", "y")
            );
            timetable.insert_down_train(
                timetable.down_trains().end(), train_type("3", "z")
            );

            timetable.erase_down_trains(
                timetable.down_trains().begin() + 1,
                timetable.down_trains().begin() + 2
            );

            const timetable_type::trains_type& trains =
                timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
            BOOST_CHECK_EQUAL(trains[1].number(), "3");
            BOOST_CHECK_EQUAL(trains[1].note(),  "z");
        }
    }

    BOOST_AUTO_TEST_CASE(erase_up_trains)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable("hoge");
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("1", "x")
            );
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("2", "y")
            );

            timetable.erase_up_trains(
                timetable.up_trains().begin(), timetable.up_trains().end()
            );

            const timetable_type::trains_type& trains =
                timetable.up_trains();

            BOOST_CHECK(trains.empty());
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("1", "x")
            );
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("2", "y")
            );

            timetable.erase_up_trains(
                timetable.up_trains().begin(),
                timetable.up_trains().begin() + 1
            );

            const timetable_type::trains_type& trains =
                timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK_EQUAL(trains[0].number(), "2");
            BOOST_CHECK_EQUAL(trains[0].note(),  "y");
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("1", "x")
            );
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("2", "y")
            );

            timetable.erase_up_trains(
                timetable.up_trains().begin(), timetable.up_trains().begin()
            );

            const timetable_type::trains_type& trains =
                timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
            BOOST_CHECK_EQUAL(trains[1].number(), "2");
            BOOST_CHECK_EQUAL(trains[1].note(),  "y");
        }
        {
            timetable_type timetable("hoge");
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("1", "x")
            );
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("2", "y")
            );
            timetable.insert_up_train(
                timetable.up_trains().end(), train_type("3", "z")
            );

            timetable.erase_up_trains(
                timetable.up_trains().begin() + 1,
                timetable.up_trains().begin() + 2
            );

            const timetable_type::trains_type& trains =
                timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK_EQUAL(trains[0].number(), "1");
            BOOST_CHECK_EQUAL(trains[0].note(),  "x");
            BOOST_CHECK_EQUAL(trains[1].number(), "3");
            BOOST_CHECK_EQUAL(trains[1].note(),  "z");
        }
    }

    BOOST_AUTO_TEST_CASE(observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable("hoge");

            timetable.observer_set();
        }
        {
            timetable_type timetable("hoge");

            timetable.observer_set();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
