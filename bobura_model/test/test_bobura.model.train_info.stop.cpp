/*! \file
    \brief Test of class bobura::model::train_info::stop.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::time
        >::type
        time_type;

    typedef
        boost::mpl::at<
            test_bobura::model::type_list, test_bobura::model::type::string
        >::type
        string_type;

    typedef
        boost::mpl::at<
            test_bobura::model::model_type_list,
            test_bobura::model::type::model::stop
        >::type
        stop_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(train_info)
BOOST_AUTO_TEST_SUITE(stop)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop(time_type(0), time_type(0), "");

            BOOST_CHECK(stop.arrival() == time_type(0));
            BOOST_CHECK(stop.departure() == time_type(0));
            BOOST_CHECK(stop.platform() == string_type());
        }
        {
            const stop_type stop(time_type(0), time_type(1), "1");

            BOOST_CHECK(stop.arrival() == time_type(0));
            BOOST_CHECK(stop.departure() == time_type(1));
            BOOST_CHECK(stop.platform() == string_type("1"));
        }
        {
            const stop_type stop(time_type(1), time_type(2), "ZZZ");

            BOOST_CHECK(stop.arrival() == time_type(1));
            BOOST_CHECK(stop.departure() == time_type(2));
            BOOST_CHECK(stop.platform() == string_type("ZZZ"));
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop1(time_type(1), time_type(2), "1");
            const stop_type stop2(time_type(1), time_type(2), "1");

            BOOST_CHECK(stop1 == stop2);
        }
        {
            const stop_type stop1(time_type(1), time_type(2), "1");
            const stop_type stop2(time_type(3), time_type(2), "1");

            BOOST_CHECK(stop1 != stop2);
        }
        {
            const stop_type stop1(time_type(1), time_type(2), "1");
            const stop_type stop2(time_type(1), time_type(4), "1");

            BOOST_CHECK(stop1 != stop2);
        }
        {
            const stop_type stop1(time_type(1), time_type(2), "1");
            const stop_type stop2(time_type(1), time_type(2), "2");

            BOOST_CHECK(stop1 != stop2);
        }
        {
            const stop_type stop1(time_type(1), time_type(2), "1");
            const stop_type stop2(time_type(3), time_type(4), "2");

            BOOST_CHECK(stop1 != stop2);
        }
    }

    BOOST_AUTO_TEST_CASE(arrival)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop(time_type(1), time_type(2), "1");

            BOOST_CHECK(stop.arrival() == time_type(1));
        }
        {
            const stop_type stop(time_type(3), time_type(4), "2");

            BOOST_CHECK(stop.arrival() == time_type(3));
        }
    }

    BOOST_AUTO_TEST_CASE(departure)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop(time_type(1), time_type(2), "1");

            BOOST_CHECK(stop.departure() == time_type(2));
        }
        {
            const stop_type stop(time_type(3), time_type(4), "2");

            BOOST_CHECK(stop.departure() == time_type(4));
        }
    }

    BOOST_AUTO_TEST_CASE(platform)
    {
        BOOST_TEST_PASSPOINT();

        {
            const stop_type stop(time_type(1), time_type(2), "1");

            BOOST_CHECK_EQUAL(stop.platform(), "1");
        }
        {
            const stop_type stop(time_type(3), time_type(4), "2");

            BOOST_CHECK_EQUAL(stop.platform(), "2");
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
