/*! \file
    \brief Test of class bobura::model::train.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <cstddef>
#include <string>

#include <boost/test/unit_test.hpp>

#include "bobura.model.train_info.stop.h"
#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"

#include "bobura.model.train.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(train)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

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
        
        {
            const train_type train("1", "x");

            BOOST_CHECK(train.stops().empty());

            const train_type copy_of_train(train);

            BOOST_CHECK(train == copy_of_train);
        }
        {
            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));

            const train_type train("1", "x", stops.begin(), stops.end());

            BOOST_CHECK(train.stops() == stops);

            const train_type copy_of_train(train);

            BOOST_CHECK(train == copy_of_train);
        }
        {
            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));

            const train_type train("1", "x", stops.begin(), stops.end());

            BOOST_CHECK(train.stops() == stops);

            const train_type copy_of_train(train);

            BOOST_CHECK(train == copy_of_train);
        }
    }

    BOOST_AUTO_TEST_CASE(swap)
    {
        BOOST_TEST_PASSPOINT();

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
        
        train_type::stops_type stops1;
        stops1.push_back(stop_type(time_type(0), time_type(0), ""));
        train_type train1("1", "x", stops1.begin(), stops1.end());

        train_type::stops_type stops2;
        stops2.push_back(stop_type(time_type(1), time_type(2), "a"));
        stops2.push_back(stop_type(time_type(3), time_type(4), "b"));
        train_type train2("2", "y", stops2.begin(), stops2.end());

        train1.swap(train2);

        BOOST_CHECK(train1.stops() == stops2);
        BOOST_CHECK(train2.stops() == stops1);
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

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
        
        {
            train_type::stops_type stops1;
            stops1.push_back(stop_type(time_type(0), time_type(0), ""));
            train_type train1("1", "x", stops1.begin(), stops1.end());

            train_type::stops_type stops2;
            stops2.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops2.push_back(stop_type(time_type(3), time_type(4), "b"));
            const train_type train2("2", "y", stops2.begin(), stops2.end());

            train1 = train2;

            BOOST_CHECK(train1 == train2);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

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
        
        {
            const train_type train1("1", "x");

            const train_type train2("1", "x");

            BOOST_CHECK(train1 == train2);
        }
        {
            train_type::stops_type stops1;
            stops1.push_back(stop_type(time_type(0), time_type(0), ""));
            const train_type train1("1", "x", stops1.begin(), stops1.end());

            train_type::stops_type stops2;
            stops2.push_back(stop_type(time_type(0), time_type(0), ""));
            const train_type train2("1", "x", stops2.begin(), stops2.end());

            BOOST_CHECK(train1 == train2);
        }
        {
            train_type::stops_type stops1;
            stops1.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops1.push_back(stop_type(time_type(3), time_type(4), "b"));
            const train_type train1("1", "x", stops1.begin(), stops1.end());

            train_type::stops_type stops2;
            stops2.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops2.push_back(stop_type(time_type(3), time_type(4), "b"));
            const train_type train2("1", "x", stops2.begin(), stops2.end());

            BOOST_CHECK(train1 == train2);
        }
        {
            const train_type train1("1", "x");

            train_type::stops_type stops2;
            stops2.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops2.push_back(stop_type(time_type(3), time_type(4), "b"));
            const train_type train2("2", "y", stops2.begin(), stops2.end());

            BOOST_CHECK(train1 != train2);
        }
        {
            train_type::stops_type stops1;
            stops1.push_back(stop_type(time_type(0), time_type(0), ""));
            const train_type train1("1", "x", stops1.begin(), stops1.end());

            const train_type train2("2", "y");

            BOOST_CHECK(train1 != train2);
        }
        {
            train_type::stops_type stops1;
            stops1.push_back(stop_type(time_type(0), time_type(0), ""));
            const train_type train1("1", "x", stops1.begin(), stops1.end());

            train_type::stops_type stops2;
            stops2.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops2.push_back(stop_type(time_type(3), time_type(4), "b"));
            const train_type train2("2", "y", stops2.begin(), stops2.end());

            BOOST_CHECK(train1 != train2);
        }
    }

    BOOST_AUTO_TEST_CASE(number)
    {
        BOOST_TEST_PASSPOINT();

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
        
        {
            const train_type train("1", "x");

            BOOST_CHECK_EQUAL(train.number(), "1");
        }
    }

    BOOST_AUTO_TEST_CASE(note)
    {
        BOOST_TEST_PASSPOINT();

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
        
        {
            const train_type train("1", "x");

            BOOST_CHECK_EQUAL(train.note(), "x");
        }
    }

    BOOST_AUTO_TEST_CASE(stops)
    {
        BOOST_TEST_PASSPOINT();

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
        
        {
            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));

            const train_type train("1", "x", stops.begin(), stops.end());

            BOOST_CHECK(train.stops() == stops);
        }
    }

    BOOST_AUTO_TEST_CASE(insert_stop)
    {
        BOOST_TEST_PASSPOINT();

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
        
        {
            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));

            train_type train("1", "x");
            train.insert_stop(train.stops().end(), stops[0]);

            BOOST_CHECK(train.stops() == stops);
        }
        {
            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));

            train_type train("1", "x");
            train.insert_stop(train.stops().end(), stops[0]);
            train.insert_stop(train.stops().end(), stops[1]);

            BOOST_CHECK(train.stops() == stops);
        }
        {
            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));

            train_type train(
                "1", "x", stops.begin(), stops.begin() + 1
            );
            train.insert_stop(train.stops().end(), stops[1]);

            BOOST_CHECK(train.stops() == stops);
        }
        {
            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));

            train_type train("1", "x", stops.begin() + 1, stops.end());
            train.insert_stop(train.stops().begin(), stops[0]);

            BOOST_CHECK(train.stops() == stops);
        }
    }

    BOOST_AUTO_TEST_CASE(erase_stops)
    {
        BOOST_TEST_PASSPOINT();

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
        
        {
            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));

            train_type train("1", "x", stops.begin(), stops.end());

            train.erase_stops(train.stops().begin(), train.stops().end());

            BOOST_CHECK(train.stops().empty());
        }
        {
            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));

            train_type train("1", "x");
            train.insert_stop(train.stops().end(), stops[0]);
            train.insert_stop(train.stops().end(), stops[1]);

            train.erase_stops(train.stops().begin(), train.stops().end());

            BOOST_CHECK(train.stops().empty());
        }
        {
            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));

            train_type train(
                "1", "x", stops.begin(), stops.begin() + 1
            );
            train.insert_stop(train.stops().end(), stops[1]);

            train.erase_stops(train.stops().begin(), train.stops().end());

            BOOST_CHECK(train.stops().empty());
        }
        {
            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));

            train_type train("1", "x", stops.begin(), stops.end());

            train.erase_stops(train.stops().begin(), train.stops().begin());

            BOOST_CHECK_EQUAL(train.stops().size(), 2U);
            BOOST_CHECK(train.stops()[0].arrival() == time_type(0));
            BOOST_CHECK(train.stops()[0].departure() == time_type(0));
            BOOST_CHECK_EQUAL(train.stops()[0].platform(), "");
            BOOST_CHECK(train.stops()[1].arrival() == time_type(1));
            BOOST_CHECK(train.stops()[1].departure() == time_type(2));
            BOOST_CHECK_EQUAL(train.stops()[1].platform(), "a");
        }
        {
            train_type::stops_type stops;
            stops.push_back(stop_type(time_type(0), time_type(0), ""));
            stops.push_back(stop_type(time_type(1), time_type(2), "a"));
            stops.push_back(stop_type(time_type(3), time_type(4), "b"));

            train_type train("1", "x", stops.begin(), stops.end());

            train.erase_stops(
                train.stops().begin() + 1, train.stops().begin() + 2
            );

            BOOST_CHECK_EQUAL(train.stops().size(), 2U);
            BOOST_CHECK(train.stops()[0].arrival() == time_type(0));
            BOOST_CHECK(train.stops()[0].departure() == time_type(0));
            BOOST_CHECK_EQUAL(train.stops()[0].platform(), "");
            BOOST_CHECK(train.stops()[1].arrival() == time_type(3));
            BOOST_CHECK(train.stops()[1].departure() == time_type(4));
            BOOST_CHECK_EQUAL(train.stops()[1].platform(), "b");
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
