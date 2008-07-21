/*! \file
    \brief Test of class bobura::model::train_info::stop.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <algorithm>
#include <cstddef>
#include <string>

//#include <boost/test/unit_test.hpp>

#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"

#include "bobura.model.train_info.stop.h"

#include "test_bobura.model.train_info.stop.h"


namespace test_bobura { namespace model { namespace train_info
{
    // functions

    boost::unit_test::test_suite* stop::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model::train_info::stop");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));
        p_suite->add(BOOST_TEST_CASE(arrival));
        p_suite->add(BOOST_TEST_CASE(departure));
        p_suite->add(BOOST_TEST_CASE(platform));

        return p_suite;
    }

    void stop::construction()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        
        {
            const stop_type stop(time_type(0), time_type(0), "");

            BOOST_CHECK(stop.arrival() == time_type(0));
            BOOST_CHECK(stop.departure() == time_type(0));
            BOOST_CHECK(stop.platform() == std::string(""));

            const stop_type copy_of_stop(stop);

            BOOST_CHECK(stop == copy_of_stop);
        }
        {
            const stop_type stop(time_type(0), time_type(1), "1");

            BOOST_CHECK(stop.arrival() == time_type(0));
            BOOST_CHECK(stop.departure() == time_type(1));
            BOOST_CHECK(stop.platform() == std::string("1"));

            const stop_type copy_of_stop(stop);

            BOOST_CHECK(stop == copy_of_stop);
        }
        {
            const stop_type stop(time_type(1), time_type(2), "ZZZ");

            BOOST_CHECK(stop.arrival() == time_type(1));
            BOOST_CHECK(stop.departure() == time_type(2));
            BOOST_CHECK(stop.platform() == std::string("ZZZ"));

            const stop_type copy_of_stop(stop);

            BOOST_CHECK(stop == copy_of_stop);
        }
    }

    void stop::swap()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        
        {
            stop_type stop1(time_type(1), time_type(2), "1");
            stop_type stop2(time_type(3), time_type(4), "2");

            stop1.swap(stop2);

            BOOST_CHECK(stop1.arrival() == time_type(3));
            BOOST_CHECK(stop1.departure() == time_type(4));
            BOOST_CHECK(stop1.platform() == std::string("2"));
            BOOST_CHECK(stop2.arrival() == time_type(1));
            BOOST_CHECK(stop2.departure() == time_type(2));
            BOOST_CHECK(stop2.platform() == std::string("1"));
        }
        {
            stop_type stop1(time_type(1), time_type(2), "1");
            stop_type stop2(time_type(3), time_type(4), "2");

            std::swap(stop1, stop2);

            BOOST_CHECK(stop1.arrival() == time_type(3));
            BOOST_CHECK(stop1.departure() == time_type(4));
            BOOST_CHECK(stop1.platform() == std::string("2"));
            BOOST_CHECK(stop2.arrival() == time_type(1));
            BOOST_CHECK(stop2.departure() == time_type(2));
            BOOST_CHECK(stop2.platform() == std::string("1"));
        }
    }

    void stop::operator_assign()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        
        {
            stop_type stop1(time_type(1), time_type(2), "1");
            const stop_type stop2(time_type(3), time_type(4), "2");

            stop1 = stop2;

            BOOST_CHECK(stop1 == stop2);
        }
    }

    void stop::operator_equal()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        
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

    void stop::arrival()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        
        {
            const stop_type stop(time_type(1), time_type(2), "1");

            BOOST_CHECK(stop.arrival() == time_type(1));
        }
        {
            const stop_type stop(time_type(3), time_type(4), "2");

            BOOST_CHECK(stop.arrival() == time_type(3));
        }
    }

    void stop::departure()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        
        {
            const stop_type stop(time_type(1), time_type(2), "1");

            BOOST_CHECK(stop.departure() == time_type(2));
        }
        {
            const stop_type stop(time_type(3), time_type(4), "2");

            BOOST_CHECK(stop.departure() == time_type(4));
        }
    }

    void stop::platform()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<time_type, std::string>
            stop_type;
        
        {
            const stop_type stop(time_type(1), time_type(2), "1");

            BOOST_CHECK_EQUAL(stop.platform(), "1");
        }
        {
            const stop_type stop(time_type(3), time_type(4), "2");

            BOOST_CHECK_EQUAL(stop.platform(), "2");
        }
    }


}}}
