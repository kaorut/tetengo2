/*! \file
    \brief Test of class bobura::model::timetable_info::station_location.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

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

    typedef boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type string_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::station_location>::type
        station_location_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(timetable_info)
BOOST_AUTO_TEST_SUITE(station_location)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();
        
        const station_location_type station_location(
            station_type(string_type(), local_type::instance(), false, false, string_type()), 0
        );
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_location_type station_location1(
                station_type(
                    string_type(TETENGO2_TEXT("A")),
                    local_type::instance(),
                    false,
                    false,
                    string_type(TETENGO2_TEXT("N"))
                ),
                1
            );
            const station_location_type station_location2(
                station_type(
                    string_type(TETENGO2_TEXT("A")),
                    local_type::instance(),
                    false,
                    false,
                    string_type(TETENGO2_TEXT("N"))
                ),
                1
            );

            BOOST_CHECK(station_location1 == station_location2);
        }
        {
            const station_location_type station_location1(
                station_type(
                    string_type(TETENGO2_TEXT("A")),
                    local_type::instance(),
                    false,
                    false,
                    string_type(TETENGO2_TEXT("N"))
                ),
                1
            );
            const station_location_type station_location2(
                station_type(
                    string_type(TETENGO2_TEXT("B")),
                    local_type::instance(),
                    false,
                    false,
                    string_type(TETENGO2_TEXT("N"))
                ),
                2
            );

            BOOST_CHECK(station_location1 != station_location2);
        }
    }

    BOOST_AUTO_TEST_CASE(station)
    {
        BOOST_TEST_PASSPOINT();

        const station_location_type station_location(
            station_type(string_type(), local_type::instance(), false, false, string_type()), 0
        );

        BOOST_CHECK(station_location.station() == station_type(string_type(), local_type::instance(), false, false, string_type()));
    }

    BOOST_AUTO_TEST_CASE(meterage)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_location_type station_location(
                station_type(string_type(), local_type::instance(), false, false, string_type()), 0
            );

            BOOST_CHECK_EQUAL(station_location.meterage(), 0U);
        }
        {
            const station_location_type station_location(
                station_type(string_type(), local_type::instance(), false, false, string_type()), 1
            );

            BOOST_CHECK_EQUAL(station_location.meterage(), 1U);
        }
        {
            const station_location_type station_location(
                station_type(string_type(), local_type::instance(), false, false, string_type()), 2
            );

            BOOST_CHECK_EQUAL(station_location.meterage(), 2U);
        }
    }

    BOOST_AUTO_TEST_CASE(before)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_location_type station_location1(
                station_type(string_type(), local_type::instance(), false, false, string_type()), 1
            );
            const station_location_type station_location2(
                station_type(string_type(), local_type::instance(), false, false, string_type()), 1
            );

            BOOST_CHECK(station_location1.before(station_location2));
        }
        {
            const station_location_type station_location1(
                station_type(string_type(), local_type::instance(), false, false, string_type()), 1
            );
            const station_location_type station_location2(
                station_type(string_type(), local_type::instance(), false, false, string_type()), 2
            );

            BOOST_CHECK(station_location1.before(station_location2));
        }
        {
            const station_location_type station_location1(
                station_type(string_type(), local_type::instance(), false, false, string_type()), 2
            );
            const station_location_type station_location2(
                station_type(string_type(), local_type::instance(), false, false, string_type()), 1
            );

            BOOST_CHECK(!station_location1.before(station_location2));
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
