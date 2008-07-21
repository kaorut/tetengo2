/*! \file
    \brief Test of class bobura::model::train.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

//#include <boost/test/unit_test.hpp>

#include "bobura.model.train_info.stop.h"
#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"

#include "bobura.model.train.h"

#include "test_bobura.model.train.h"


namespace test_bobura { namespace model
{
    // functions

    boost::unit_test::test_suite* train::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model::train");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));

        return p_suite;
    }

    void train::construction()
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
        typedef bobura::model::train<stop_type> train_type;
        
        {
            const train_type train;

            BOOST_CHECK(train.stops().empty());

            const train_type copy_of_train(train);

            BOOST_CHECK(train == copy_of_train);
        }
        {
            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));

            const train_type train(stops.begin(), stops.end());

            BOOST_CHECK(train.stops() == stops);

            const train_type copy_of_train(train);

            BOOST_CHECK(train == copy_of_train);
        }
        {
            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));

            const train_type train(stops.begin(), stops.end());

            BOOST_CHECK(train.stops() == stops);

            const train_type copy_of_train(train);

            BOOST_CHECK(train == copy_of_train);
        }
    }

    void train::swap()
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
        typedef bobura::model::train<stop_type> train_type;
        
        {
            train_type::stops_type stops1;
            stops1.push_back(stop_type(time_type(0), time_type(0), ""));
            train_type train1(stops1.begin(), stops1.end());

            train_type::stops_type stops2;
            stops2.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops2.push_back(stop_type(time_type(3), time_type(4), "b"));
            train_type train2(stops2.begin(), stops2.end());

            train1.swap(train2);

            BOOST_CHECK(train1.stops() == stops2);
            BOOST_CHECK(train2.stops() == stops1);
        }
        {
            train_type::stops_type stops1;
            stops1.push_back(stop_type(time_type(0), time_type(0), ""));
            train_type train1(stops1.begin(), stops1.end());

            train_type::stops_type stops2;
            stops2.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops2.push_back(stop_type(time_type(3), time_type(4), "b"));
            train_type train2(stops2.begin(), stops2.end());

            std::swap(train1, train2);

            BOOST_CHECK(train1.stops() == stops2);
            BOOST_CHECK(train2.stops() == stops1);
        }
    }

    void train::operator_assign()
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
        typedef bobura::model::train<stop_type> train_type;
        
        {
            train_type::stops_type stops1;
            stops1.push_back(stop_type(time_type(0), time_type(0), ""));
            train_type train1(stops1.begin(), stops1.end());

            train_type::stops_type stops2;
            stops2.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops2.push_back(stop_type(time_type(3), time_type(4), "b"));
            const train_type train2(stops2.begin(), stops2.end());

            train1 = train2;

            BOOST_CHECK(train1 == train2);
        }
    }

    void train::operator_equal()
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
        typedef bobura::model::train<stop_type> train_type;
        
        {
            const train_type train1;

            const train_type train2;

            BOOST_CHECK(train1 == train2);
        }
        {
            train_type::stops_type stops1;
            stops1.push_back(stop_type(time_type(0), time_type(0), ""));
            const train_type train1(stops1.begin(), stops1.end());

            train_type::stops_type stops2;
            stops2.push_back(stop_type(time_type(0), time_type(0), ""));
            const train_type train2(stops2.begin(), stops2.end());

            BOOST_CHECK(train1 == train2);
        }
        {
            train_type::stops_type stops1;
            stops1.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops1.push_back(stop_type(time_type(3), time_type(4), "b"));
            const train_type train1(stops1.begin(), stops1.end());

            train_type::stops_type stops2;
            stops2.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops2.push_back(stop_type(time_type(3), time_type(4), "b"));
            const train_type train2(stops2.begin(), stops2.end());

            BOOST_CHECK(train1 == train2);
        }
        {
            const train_type train1;

            train_type::stops_type stops2;
            stops2.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops2.push_back(stop_type(time_type(3), time_type(4), "b"));
            const train_type train2(stops2.begin(), stops2.end());

            BOOST_CHECK(train1 != train2);
        }
        {
            train_type::stops_type stops1;
            stops1.push_back(stop_type(time_type(0), time_type(0), ""));
            const train_type train1(stops1.begin(), stops1.end());

            const train_type train2;

            BOOST_CHECK(train1 != train2);
        }
        {
            train_type::stops_type stops1;
            stops1.push_back(stop_type(time_type(0), time_type(0), ""));
            const train_type train1(stops1.begin(), stops1.end());

            train_type::stops_type stops2;
            stops2.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops2.push_back(stop_type(time_type(3), time_type(4), "b"));
            const train_type train2(stops2.begin(), stops2.end());

            BOOST_CHECK(train1 != train2);
        }
    }


}}
