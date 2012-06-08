/*! \file
    \brief Test of class bobura::model::timetable_info::station_interval_calculator.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::station_location>::type
        station_location_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::train>::type train_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list, test_bobura::model::type::model::station_interval_calculator
        >::type
        station_interval_calculator_type;

    typedef station_interval_calculator_type::station_intervals_type station_intervals_type;

    typedef boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type string_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::station>::type
        station_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::grade_type_set>::type
        grade_type_set_type;


    // functions

    std::vector<station_location_type> make_station_locations()
    {
        std::vector<station_location_type> locations;

        locations.push_back(
            station_location_type(
                station_type(string_type(TETENGO2_TEXT("AAA")), grade_type_set_type::local_type::instance()), 0
            )
        );
        locations.push_back(
            station_location_type(
                station_type(string_type(TETENGO2_TEXT("BBB")), grade_type_set_type::local_type::instance()), 10
            )
        );
        locations.push_back(
            station_location_type(
                station_type(string_type(TETENGO2_TEXT("CCC")), grade_type_set_type::local_type::instance()), 20
            )
        );
        locations.push_back(
            station_location_type(
                station_type(string_type(TETENGO2_TEXT("DDD")), grade_type_set_type::local_type::instance()), 30
            )
        );

        return locations;
    }


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(timetable_info)
BOOST_AUTO_TEST_SUITE(station_interval_calculator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<station_location_type> station_locations;
        const std::vector<train_type> down_trains;
        const std::vector<train_type> up_trains;
        const station_interval_calculator_type calculator(station_locations, down_trains, up_trains);
    }

    BOOST_AUTO_TEST_CASE(calculate)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::vector<station_location_type> station_locations;
            const std::vector<train_type> down_trains;
            const std::vector<train_type> up_trains;
            const station_interval_calculator_type calculator(station_locations, down_trains, up_trains);

            const station_intervals_type intervals = calculator.calculate();

            BOOST_CHECK(intervals.empty());
        }
        {
            const std::vector<station_location_type> station_locations = make_station_locations();
            const std::vector<train_type> down_trains;
            const std::vector<train_type> up_trains;
            const station_interval_calculator_type calculator(station_locations, down_trains, up_trains);

            const station_intervals_type intervals = calculator.calculate();

            BOOST_CHECK(intervals.size() == station_locations.size());
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
