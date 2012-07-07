/*! \file
    \brief Test of class bobura::model::station.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::grade_type_set>::type
        grade_type_set_type;

    typedef grade_type_set_type::local_type local_type;

    typedef grade_type_set_type::principal_type principal_type;

    typedef grade_type_set_type::local_terminal_type local_terminal_type;

    typedef grade_type_set_type::principal_terminal_type principal_terminal_type;

    typedef boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type string_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::station>::type
        station_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(station)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station(string_type(), local_type::instance(), false, false);
        }
        {
            const station_type station(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false);
        }
        {
            const station_type station(string_type(TETENGO2_TEXT("AB")), local_type::instance(), false, false);
        }
        {
            const station_type station(string_type(1024 * 1024, TETENGO2_TEXT('X')), local_type::instance(), false, false);
        }
        {
            const station_type station(string_type(TETENGO2_TEXT("A")), principal_type::instance(), false, false);
        }
        {
            const station_type station(string_type(TETENGO2_TEXT("A")), local_type::instance(), true, false);
        }
        {
            const station_type station(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, true);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station1(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false);
            const station_type station2(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false);

            BOOST_CHECK(station1 == station2);
        }
        {
            const station_type station1(string_type(TETENGO2_TEXT("B")), principal_type::instance(), false, false);
            const station_type station2(string_type(TETENGO2_TEXT("B")), principal_type::instance(), false, false);

            BOOST_CHECK(station1 == station2);
        }
        {
            const station_type station1(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false);
            const station_type station2(string_type(TETENGO2_TEXT("B")), principal_type::instance(), false, false);

            BOOST_CHECK(station1 != station2);
        }
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station(string_type(), local_type::instance(), false, false);

            BOOST_CHECK(station.name() == string_type());
        }
        {
            const station_type station(string_type(TETENGO2_TEXT("A")), local_type::instance(), false, false);

            BOOST_CHECK(station.name() == string_type(TETENGO2_TEXT("A")));
        }
        {
            const station_type station(string_type(TETENGO2_TEXT("AB")), local_type::instance(), false, false);

            BOOST_CHECK(station.name() == string_type(TETENGO2_TEXT("AB")));
        }
        {
            const station_type station(
                string_type(1024 * 1024, TETENGO2_TEXT('X')), local_type::instance(), false, false
            );

            BOOST_CHECK(station.name() == string_type(1024 * 1024, TETENGO2_TEXT('X')));
        }
    }

    BOOST_AUTO_TEST_CASE(grade)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station(string_type(), local_type::instance(), false, false);

            BOOST_CHECK_EQUAL(&station.grade(), &local_type::instance());
        }
        {
            const station_type station(string_type(), principal_type::instance(), false, false);

            BOOST_CHECK_EQUAL(&station.grade(), &principal_type::instance());
        }
        {
            const station_type station(string_type(), local_terminal_type::instance(), false, false);

            BOOST_CHECK_EQUAL(&station.grade(), &local_terminal_type::instance());
        }
        {
            const station_type station(string_type(), principal_terminal_type::instance(), false, false);

            BOOST_CHECK_EQUAL(&station.grade(), &principal_terminal_type::instance());
        }
    }

    BOOST_AUTO_TEST_CASE(shows_down_arrival_times)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station(string_type(), local_type::instance(), false, false);

            BOOST_CHECK(!station.shows_down_arrival_times());
        }
        {
            const station_type station(string_type(), local_type::instance(), true, false);

            BOOST_CHECK(station.shows_down_arrival_times());
        }
    }

    BOOST_AUTO_TEST_CASE(shows_up_arrival_times)
    {
        BOOST_TEST_PASSPOINT();

        {
            const station_type station(string_type(), local_type::instance(), false, false);

            BOOST_CHECK(!station.shows_up_arrival_times());
        }
        {
            const station_type station(string_type(), local_type::instance(), false, true);

            BOOST_CHECK(station.shows_up_arrival_times());
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
