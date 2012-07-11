/*! \file
    \brief Test of class bobura::model::timetable.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <stdexcept>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::station>::type
        station_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::grade_type_set>::type
        grade_type_set_type;

    typedef grade_type_set_type::local_type local_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::station_location>::type
        station_location_type;

    typedef boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::time>::type time_type;

    typedef boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::stop>::type stop_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::train_kind>::type
        train_kind_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::train>::type train_type;

    typedef boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type string_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::timetable>::type
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
            const timetable_type timetable;

            BOOST_CHECK(timetable.station_locations().empty());
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );

            const timetable_type timetable(station_locations.begin(), station_locations.end());

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );

            const timetable_type timetable(station_locations.begin(), station_locations.end());

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable1;

            const timetable_type timetable2;

            BOOST_CHECK(timetable1 == timetable2);
        }
        {
            timetable_type timetable1;
            timetable1.set_title(string_type(TETENGO2_TEXT("hoge")));

            timetable_type timetable2;
            timetable2.set_title(string_type(TETENGO2_TEXT("hoge")));

            BOOST_CHECK(timetable1 == timetable2);
        }
        {
            timetable_type timetable1;
            timetable1.set_title(string_type(TETENGO2_TEXT("hoge")));

            timetable_type timetable2;
            timetable2.set_title(string_type(TETENGO2_TEXT("fuga")));

            BOOST_CHECK(timetable1 == timetable2);
        }
        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );

            const timetable_type timetable1(station_locations1.begin(), station_locations1.end());

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );

            const timetable_type timetable2(station_locations2.begin(), station_locations2.end());

            BOOST_CHECK(timetable1 == timetable2);
        }
        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );

            const timetable_type timetable1(station_locations1.begin(), station_locations1.end());

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );

            const timetable_type timetable2(station_locations2.begin(), station_locations2.end());

            BOOST_CHECK(timetable1 != timetable2);
        }
        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );

            const timetable_type timetable1(station_locations1.begin(), station_locations1.end());

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            station_locations2.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );

            const timetable_type timetable2(station_locations2.begin(), station_locations2.end());

            BOOST_CHECK(timetable1 != timetable2);
        }
        {
            timetable_type::station_locations_type station_locations1;
            station_locations1.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            station_locations1.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );

            const timetable_type timetable1(station_locations1.begin(), station_locations1.end());

            timetable_type::station_locations_type station_locations2;
            station_locations2.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            station_locations2.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );

            const timetable_type timetable2(station_locations2.begin(), station_locations2.end());

            BOOST_CHECK(timetable1 == timetable2);
        }
    }

    BOOST_AUTO_TEST_CASE(station_locations)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable;

            const timetable_type::station_locations_type& station_locations = timetable.station_locations();

            BOOST_CHECK(station_locations.empty());
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );

            const timetable_type timetable(station_locations.begin(), station_locations.end());

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );

            const timetable_type timetable(station_locations.begin(), station_locations.end());

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
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );

            timetable_type timetable(station_locations.begin(), station_locations.begin() + 1);

            timetable.insert_station_location(timetable.station_locations().end(), station_locations[1]);

            BOOST_CHECK(timetable.station_locations() == station_locations);
        }
        {
            timetable_type timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );

            const timetable_type::station_locations_type& station_locations = timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 1U);
            BOOST_CHECK(station_locations[0].station().name() == string_type(TETENGO2_TEXT("A")));
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 1U);
        }
        {
            timetable_type timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );

            const timetable_type::station_locations_type& station_locations = timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 2U);
            BOOST_CHECK(station_locations[0].station().name() == string_type(TETENGO2_TEXT("A")));
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 1U);
            BOOST_CHECK(station_locations[1].station().name() == string_type(TETENGO2_TEXT("B")));
            BOOST_CHECK_EQUAL(station_locations[1].meterage(), 2U);
        }
        {
            timetable_type timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );
            BOOST_CHECK_THROW(
                timetable.insert_station_location(
                    timetable.station_locations().end(),
                    station_location_type(
                        station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                    )
                ),
                std::invalid_argument
            );

            const timetable_type::station_locations_type& station_locations = timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 1U);
            BOOST_CHECK(station_locations[0].station().name() == string_type(TETENGO2_TEXT("B")));
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 2U);
        }
        {
            timetable_type timetable;
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("D")), local_type::instance(), false, false), 4
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().begin(),
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            timetable.insert_station_location(
                timetable.station_locations().begin() + 2,
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("C")), local_type::instance(), false, false), 3
                )
            );

            const timetable_type::station_locations_type& station_locations = timetable.station_locations();

            BOOST_CHECK_EQUAL(station_locations.size(), 4U);
            BOOST_CHECK(station_locations[0].station().name() == string_type(TETENGO2_TEXT("A")));
            BOOST_CHECK_EQUAL(station_locations[0].meterage(), 1U);
            BOOST_CHECK(station_locations[1].station().name() == string_type(TETENGO2_TEXT("B")));
            BOOST_CHECK_EQUAL(station_locations[1].meterage(), 2U);
            BOOST_CHECK(station_locations[2].station().name() == string_type(TETENGO2_TEXT("C")));
            BOOST_CHECK_EQUAL(station_locations[2].meterage(), 3U);
            BOOST_CHECK(station_locations[3].station().name() == string_type(TETENGO2_TEXT("D")));
            BOOST_CHECK_EQUAL(station_locations[3].meterage(), 4U);
        }
        {
            timetable_type timetable;

            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x")))
            );

            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );

            BOOST_CHECK_EQUAL(timetable.down_trains()[0].stops().size(), timetable.station_locations().size());
            BOOST_CHECK(timetable.down_trains()[0].stops()[0].arrival() == time_type::uninitialized());
            BOOST_CHECK(timetable.down_trains()[0].stops()[0].departure() == time_type::uninitialized());
            BOOST_CHECK(timetable.down_trains()[0].stops()[0].platform().empty());

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), string_type(TETENGO2_TEXT("a"))));
            stops.push_back(stop_type(time_type(3), time_type(4), string_type(TETENGO2_TEXT("b"))));

            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y")),
                    stops.begin(),
                    stops.begin() + 1
                )
            );

            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(station_type(
                    string_type(TETENGO2_TEXT("C")), local_type::instance(), false, false), 3
                )
            );

            BOOST_CHECK_EQUAL(timetable.down_trains()[1].stops().size(), timetable.station_locations().size());
            BOOST_CHECK(timetable.down_trains()[1].stops()[1].arrival() == time_type::uninitialized());
            BOOST_CHECK(timetable.down_trains()[1].stops()[1].departure() == time_type::uninitialized());
            BOOST_CHECK(timetable.down_trains()[1].stops()[1].platform().empty());

            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("3")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("z")),
                    stops.begin(),
                    stops.end()
                )
            );

            timetable.insert_station_location(
                timetable.station_locations().begin() + 1,
                station_location_type(station_type(
                    string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );

            BOOST_CHECK_EQUAL(timetable.down_trains()[2].stops().size(), timetable.station_locations().size());
            BOOST_CHECK(timetable.down_trains()[2].stops()[1].arrival() == time_type::uninitialized());
            BOOST_CHECK(timetable.down_trains()[2].stops()[1].departure() == time_type::uninitialized());
            BOOST_CHECK(timetable.down_trains()[2].stops()[1].platform().empty());
        }
        {
            timetable_type timetable;

            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x")))
            );

            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );

            BOOST_CHECK_EQUAL(timetable.up_trains()[0].stops().size(), timetable.station_locations().size());
            BOOST_CHECK(timetable.up_trains()[0].stops()[0].arrival() == time_type::uninitialized());
            BOOST_CHECK(timetable.up_trains()[0].stops()[0].departure() == time_type::uninitialized());
            BOOST_CHECK(timetable.up_trains()[0].stops()[0].platform().empty());

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), string_type(TETENGO2_TEXT("a"))));
            stops.push_back(stop_type(time_type(3), time_type(4), string_type(TETENGO2_TEXT("b"))));

            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y")),
                    stops.begin(),
                    stops.begin() + 1
                )
            );

            timetable.insert_station_location(
                timetable.station_locations().end(),
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("C")), local_type::instance(), false, false), 3
                )
            );

            BOOST_CHECK_EQUAL(timetable.up_trains()[1].stops().size(), timetable.station_locations().size());
            BOOST_CHECK(timetable.up_trains()[1].stops()[1].arrival() == time_type::uninitialized());
            BOOST_CHECK(timetable.up_trains()[1].stops()[1].departure() == time_type::uninitialized());
            BOOST_CHECK(timetable.up_trains()[1].stops()[1].platform().empty());

            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("3")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("z")),
                    stops.begin(),
                    stops.end()
                )
            );

            timetable.insert_station_location(
                timetable.station_locations().begin() + 1,
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("C")), local_type::instance(), false, false), 3
                )
            );

            BOOST_CHECK_EQUAL(timetable.up_trains()[2].stops().size(), timetable.station_locations().size());
            BOOST_CHECK(timetable.up_trains()[2].stops()[1].arrival() == time_type::uninitialized());
            BOOST_CHECK(timetable.up_trains()[2].stops()[1].departure() == time_type::uninitialized());
            BOOST_CHECK(timetable.up_trains()[2].stops()[1].platform().empty());
        }
    }

    BOOST_AUTO_TEST_CASE(erase_station_locations)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );

            timetable_type timetable(station_locations.begin(), station_locations.end());

            timetable.erase_station_locations(
                timetable.station_locations().begin(), timetable.station_locations().end()
            );

            BOOST_CHECK(timetable.station_locations().empty());
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );

            timetable_type timetable(station_locations.begin(), station_locations.end());

            timetable.erase_station_locations(
                timetable.station_locations().begin(), timetable.station_locations().begin() + 1
            );

            BOOST_CHECK_EQUAL(timetable.station_locations().size(), 1U);
            BOOST_CHECK(timetable.station_locations()[0].station().name() == string_type(TETENGO2_TEXT("B")));
            BOOST_CHECK_EQUAL(timetable.station_locations()[0].meterage(), 2U);
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );

            timetable_type timetable(station_locations.begin(), station_locations.end());

            timetable.erase_station_locations(
                timetable.station_locations().begin(), timetable.station_locations().begin()
            );

            BOOST_CHECK_EQUAL(timetable.station_locations().size(), 2U);
            BOOST_CHECK(timetable.station_locations()[0].station().name() == string_type(TETENGO2_TEXT("A")));
            BOOST_CHECK_EQUAL(timetable.station_locations()[0].meterage(), 1U);
            BOOST_CHECK(timetable.station_locations()[1].station().name() == string_type(TETENGO2_TEXT("B")));
            BOOST_CHECK_EQUAL(timetable.station_locations()[1].meterage(), 2U);
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("C")), local_type::instance(), false, false), 3
                )
            );

            timetable_type timetable(station_locations.begin(), station_locations.end());

            timetable.erase_station_locations(
                timetable.station_locations().begin() + 1, timetable.station_locations().begin() + 2
            );

            BOOST_CHECK_EQUAL(timetable.station_locations().size(), 2U);
            BOOST_CHECK(timetable.station_locations()[0].station().name() == string_type(TETENGO2_TEXT("A")));
            BOOST_CHECK_EQUAL(timetable.station_locations()[0].meterage(), 1U);
            BOOST_CHECK(timetable.station_locations()[1].station().name() == string_type(TETENGO2_TEXT("C")));
            BOOST_CHECK_EQUAL(timetable.station_locations()[1].meterage(), 3U);
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );

            timetable_type timetable(station_locations.begin(), station_locations.end());
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), string_type(TETENGO2_TEXT("a"))));
            stops.push_back(stop_type(time_type(3), time_type(4), string_type(TETENGO2_TEXT("b"))));

            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x")),
                    stops.begin(),
                    stops.end()
                )
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(), timetable.station_locations().end()
            );

            BOOST_CHECK_EQUAL(timetable.down_trains()[0].stops().size(), timetable.station_locations().size());
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );

            timetable_type timetable(station_locations.begin(), station_locations.end());
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), string_type(TETENGO2_TEXT("a"))));
            stops.push_back(stop_type(time_type(3), time_type(4), string_type(TETENGO2_TEXT("b"))));

            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x")),
                    stops.begin(),
                    stops.end()
                )
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(), timetable.station_locations().end()
            );

            BOOST_CHECK_EQUAL(timetable.up_trains()[0].stops().size(), timetable.station_locations().size());
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );

            timetable_type timetable(station_locations.begin(), station_locations.end());
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), string_type(TETENGO2_TEXT("a"))));
            stops.push_back(stop_type(time_type(3), time_type(4), string_type(TETENGO2_TEXT("b"))));

            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x")),
                    stops.begin(),
                    stops.end()
                )
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(), timetable.station_locations().begin() + 1
            );

            BOOST_CHECK_EQUAL(timetable.down_trains()[0].stops().size(), timetable.station_locations().size());
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("B")), local_type::instance(), false, false), 2
                )
            );

            timetable_type timetable(station_locations.begin(), station_locations.end());
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(1), time_type(2), string_type(TETENGO2_TEXT("a"))));
            stops.push_back(stop_type(time_type(3), time_type(4), string_type(TETENGO2_TEXT("b"))));

            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x")),
                    stops.begin(),
                    stops.end()
                )
            );

            timetable.erase_station_locations(
                timetable.station_locations().begin(), timetable.station_locations().begin() + 1
            );

            BOOST_CHECK_EQUAL(timetable.up_trains()[0].stops().size(), timetable.station_locations().size());
        }
    }

    BOOST_AUTO_TEST_CASE(station_intervals)
    {
        BOOST_TEST_PASSPOINT();

        const timetable_type timetable;
        timetable.station_intervals();
    }

    BOOST_AUTO_TEST_CASE(train_kinds)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(train_kind_index)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(train_kind_referred)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(insert_train_kind)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(erase_train_kind)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(down_trains)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable;

            const timetable_type::trains_type& trains = timetable.down_trains();

            BOOST_CHECK(trains.empty());
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );

            const timetable_type::trains_type& trains = timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("1")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("x")));
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y"))
                )
            );

            const timetable_type::trains_type& trains = timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("1")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("x")));
            BOOST_CHECK(trains[1].number() == string_type(TETENGO2_TEXT("2")));
            BOOST_CHECK(trains[1].note() == string_type(TETENGO2_TEXT("y")));
        }
    }

    BOOST_AUTO_TEST_CASE(up_trains)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable;

            const timetable_type::trains_type& trains = timetable.up_trains();

            BOOST_CHECK(trains.empty());
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );

            const timetable_type::trains_type& trains = timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("1")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("x")));
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y"))
                )
            );

            const timetable_type::trains_type& trains = timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("1")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("x")));
            BOOST_CHECK(trains[1].number() == string_type(TETENGO2_TEXT("2")));
            BOOST_CHECK(trains[1].note() == string_type(TETENGO2_TEXT("y")));
        }
    }

    BOOST_AUTO_TEST_CASE(insert_down_train)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );

            const timetable_type::trains_type& trains = timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("1")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("x")));
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y"))
                )
            );

            const timetable_type::trains_type& trains = timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("1")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("x")));
            BOOST_CHECK(trains[1].number() == string_type(TETENGO2_TEXT("2")));
            BOOST_CHECK(trains[1].note() == string_type(TETENGO2_TEXT("y")));
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y"))
                )
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("4")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("w"))
                )
            );
            timetable.insert_down_train(
                timetable.down_trains().begin(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );
            timetable.insert_down_train(
                timetable.down_trains().begin() + 2,
                train_type(
                    string_type(TETENGO2_TEXT("3")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("z"))
                )
            );

            const timetable_type::trains_type& trains = timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 4U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("1")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("x")));
            BOOST_CHECK(trains[1].number() == string_type(TETENGO2_TEXT("2")));
            BOOST_CHECK(trains[1].note() == string_type(TETENGO2_TEXT("y")));
            BOOST_CHECK(trains[2].number() == string_type(TETENGO2_TEXT("3")));
            BOOST_CHECK(trains[2].note() == string_type(TETENGO2_TEXT("z")));
            BOOST_CHECK(trains[3].number() == string_type(TETENGO2_TEXT("4")));
            BOOST_CHECK(trains[3].note() == string_type(TETENGO2_TEXT("w")));
        }
        {
            timetable_type::station_locations_type station_locations;
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );

            timetable_type timetable(station_locations.begin(), station_locations.end());

            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            BOOST_CHECK_THROW(
                timetable.insert_down_train(
                    timetable.down_trains().end(),
                    train_type(
                        string_type(TETENGO2_TEXT("1")),
                        kind,
                        string_type(TETENGO2_TEXT("a")),
                        string_type(TETENGO2_TEXT("42")),
                        string_type(TETENGO2_TEXT("x"))
                    )
                ),
                std::invalid_argument
            );
        }
        {
            timetable_type timetable;

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), string_type()));

            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            BOOST_CHECK_THROW(
                timetable.insert_down_train(
                    timetable.down_trains().end(),
                    train_type(
                        string_type(TETENGO2_TEXT("1")),
                        kind,
                        string_type(TETENGO2_TEXT("a")),
                        string_type(TETENGO2_TEXT("42")),
                        string_type(TETENGO2_TEXT("x")),
                        stops.begin(),
                        stops.end()
                    )
                ),
                std::invalid_argument
            );
        }
    }

    BOOST_AUTO_TEST_CASE(insert_up_train)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );

            const timetable_type::trains_type& trains = timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("1")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("x")));
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y"))
                )
            );

            const timetable_type::trains_type& trains = timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("1")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("x")));
            BOOST_CHECK(trains[1].number() == string_type(TETENGO2_TEXT("2")));
            BOOST_CHECK(trains[1].note() == string_type(TETENGO2_TEXT("y")));
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y"))
                )
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("4")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("w"))
                )
            );
            timetable.insert_up_train(
                timetable.up_trains().begin(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );
            timetable.insert_up_train(
                timetable.up_trains().begin() + 2,
                train_type(
                    string_type(TETENGO2_TEXT("3")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("z"))
                )
            );

            const timetable_type::trains_type& trains = timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 4U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("1")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("x")));
            BOOST_CHECK(trains[1].number() == string_type(TETENGO2_TEXT("2")));
            BOOST_CHECK(trains[1].note() == string_type(TETENGO2_TEXT("y")));
            BOOST_CHECK(trains[2].number() == string_type(TETENGO2_TEXT("3")));
            BOOST_CHECK(trains[2].note() == string_type(TETENGO2_TEXT("z")));
            BOOST_CHECK(trains[3].number() == string_type(TETENGO2_TEXT("4")));
            BOOST_CHECK(trains[3].note() == string_type(TETENGO2_TEXT("w")));
        }
        {
            timetable_type::station_locations_type station_locations;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            station_locations.push_back(
                station_location_type(
                    station_type(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false), 1
                )
            );

            timetable_type timetable(station_locations.begin(), station_locations.end());

            BOOST_CHECK_THROW(
                timetable.insert_up_train(
                    timetable.up_trains().end(),
                    train_type(
                        string_type(TETENGO2_TEXT("1")),
                        kind,
                        string_type(TETENGO2_TEXT("a")),
                        string_type(TETENGO2_TEXT("42")),
                        string_type(TETENGO2_TEXT("x"))
                    )
                ),
                std::invalid_argument
            );
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));

            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), string_type()));

            BOOST_CHECK_THROW(
                timetable.insert_up_train(
                    timetable.up_trains().end(),
                    train_type(
                        string_type(TETENGO2_TEXT("1")),
                        kind,
                        string_type(TETENGO2_TEXT("a")),
                        string_type(TETENGO2_TEXT("42")),
                        string_type(TETENGO2_TEXT("x")),
                        stops.begin(),
                        stops.end()
                    )
                ),
                std::invalid_argument
            );
        }
    }

    BOOST_AUTO_TEST_CASE(erase_down_trains)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y"))
                )
            );

            timetable.erase_down_trains(timetable.down_trains().begin(), timetable.down_trains().end());

            const timetable_type::trains_type& trains = timetable.down_trains();

            BOOST_CHECK(trains.empty());
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y"))
                )
            );

            timetable.erase_down_trains(timetable.down_trains().begin(), timetable.down_trains().begin() + 1);

            const timetable_type::trains_type& trains = timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("2")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("y")));
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y"))
                )
            );

            timetable.erase_down_trains(timetable.down_trains().begin(), timetable.down_trains().begin());

            const timetable_type::trains_type& trains = timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("1")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("x")));
            BOOST_CHECK(trains[1].number() == string_type(TETENGO2_TEXT("2")));
            BOOST_CHECK(trains[1].note() == string_type(TETENGO2_TEXT("y")));
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y"))
                )
            );
            timetable.insert_down_train(
                timetable.down_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("3")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("z"))
                )
            );

            timetable.erase_down_trains(timetable.down_trains().begin() + 1, timetable.down_trains().begin() + 2);

            const timetable_type::trains_type& trains = timetable.down_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("1")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("x")));
            BOOST_CHECK(trains[1].number() == string_type(TETENGO2_TEXT("3")));
            BOOST_CHECK(trains[1].note() == string_type(TETENGO2_TEXT("z")));
        }
    }

    BOOST_AUTO_TEST_CASE(erase_up_trains)
    {
        BOOST_TEST_PASSPOINT();

        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y"))
                )
            );

            timetable.erase_up_trains(timetable.up_trains().begin(), timetable.up_trains().end());

            const timetable_type::trains_type& trains = timetable.up_trains();

            BOOST_CHECK(trains.empty());
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y"))
                )
            );

            timetable.erase_up_trains(timetable.up_trains().begin(), timetable.up_trains().begin() + 1);

            const timetable_type::trains_type& trains = timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 1U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("2")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("y")));
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y"))
                )
            );

            timetable.erase_up_trains(timetable.up_trains().begin(), timetable.up_trains().begin());

            const timetable_type::trains_type& trains = timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("1")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("x")));
            BOOST_CHECK(trains[1].number() == string_type(TETENGO2_TEXT("2")));
            BOOST_CHECK(trains[1].note() == string_type(TETENGO2_TEXT("y")));
        }
        {
            timetable_type timetable;
            const train_kind_type kind(string_type(TETENGO2_TEXT("Express")), string_type(TETENGO2_TEXT("Exp.")));
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("1")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("x"))
                )
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("2")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("y"))
                )
            );
            timetable.insert_up_train(
                timetable.up_trains().end(),
                train_type(
                    string_type(TETENGO2_TEXT("3")),
                    kind,
                    string_type(TETENGO2_TEXT("a")),
                    string_type(TETENGO2_TEXT("42")),
                    string_type(TETENGO2_TEXT("z"))
                )
            );

            timetable.erase_up_trains(timetable.up_trains().begin() + 1, timetable.up_trains().begin() + 2);

            const timetable_type::trains_type& trains = timetable.up_trains();

            BOOST_CHECK_EQUAL(trains.size(), 2U);
            BOOST_CHECK(trains[0].number() == string_type(TETENGO2_TEXT("1")));
            BOOST_CHECK(trains[0].note() == string_type(TETENGO2_TEXT("x")));
            BOOST_CHECK(trains[1].number() == string_type(TETENGO2_TEXT("3")));
            BOOST_CHECK(trains[1].note() == string_type(TETENGO2_TEXT("z")));
        }
    }

    BOOST_AUTO_TEST_CASE(observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_type timetable;

            timetable.observer_set();
        }
        {
            timetable_type timetable;

            timetable.observer_set();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
