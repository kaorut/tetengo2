/*! \file
    \brief Test of class bobura::model::train_info::time_span.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <algorithm>
#include <cstddef>
#include <stdexcept>

#include <boost/test/unit_test.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include "bobura.model.train_info.time_span.h"

#include "test_bobura.model.train_info.time_span.h"


namespace test_bobura { namespace model { namespace train_info
{
    // functions

    boost::unit_test::test_suite* time_span::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model::train_info::time_span");

        p_suite->add(BOOST_TEST_CASE(seconds_of_whole_day));
        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_plus_assign));
        p_suite->add(BOOST_TEST_CASE(operator_minus_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));
        p_suite->add(BOOST_TEST_CASE(operator_less_than));
        p_suite->add(BOOST_TEST_CASE(seconds));
        p_suite->add(BOOST_TEST_CASE(hours_minutes_seconds));

        return p_suite;
    }

    void time_span::seconds_of_whole_day()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::ptrdiff_t>
            time_span_type;

        BOOST_CHECK_EQUAL(
            time_span_type::seconds_of_whole_day(), 24 * 60 * 60
        );
    }

    void time_span::construction()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::ptrdiff_t>
            time_span_type;

        {
            const time_span_type time_span(0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 0);

            const time_span_type copy_of_time_span(time_span);
            
            BOOST_CHECK(time_span == copy_of_time_span);
        }
        {
            const time_span_type time_span(1);

            BOOST_CHECK_EQUAL(time_span.seconds(), 1);

            const time_span_type copy_of_time_span(time_span);
            
            BOOST_CHECK(time_span == copy_of_time_span);
        }
        {
            const time_span_type time_span(2);

            BOOST_CHECK_EQUAL(time_span.seconds(), 2);

            const time_span_type copy_of_time_span(time_span);
            
            BOOST_CHECK(time_span == copy_of_time_span);
        }
        {
            const time_span_type time_span(-1);

            BOOST_CHECK_EQUAL(time_span.seconds(), -1);

            const time_span_type copy_of_time_span(time_span);
            
            BOOST_CHECK(time_span == copy_of_time_span);
        }
        {
            const time_span_type time_span(-2);

            BOOST_CHECK_EQUAL(time_span.seconds(), -2);

            const time_span_type copy_of_time_span(time_span);
            
            BOOST_CHECK(time_span == copy_of_time_span);
        }
        {
            const time_span_type time_span(0, 0, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 0);
        }
        {
            const time_span_type time_span(1, 0, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 3600);
        }
        {
            const time_span_type time_span(-1, 0, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), -3600);
        }
        {
            const time_span_type time_span(0, 1, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 60);
        }
        {
            const time_span_type time_span(0, 59, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 3540);
        }
        {
            const time_span_type time_span(0, -1, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), -60);
        }
        {
            const time_span_type time_span(0, -59, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), -3540);
        }
        {
            const time_span_type time_span(0, 0, 1);

            BOOST_CHECK_EQUAL(time_span.seconds(), 1);
        }
        {
            const time_span_type time_span(0, 0, 59);

            BOOST_CHECK_EQUAL(time_span.seconds(), 59);
        }
        {
            const time_span_type time_span(0, 0, -1);

            BOOST_CHECK_EQUAL(time_span.seconds(), -1);
        }
        {
            const time_span_type time_span(0, 0, -59);

            BOOST_CHECK_EQUAL(time_span.seconds(), -59);
        }
        {
            const time_span_type time_span(1, 1, 1);

            BOOST_CHECK_EQUAL(time_span.seconds(), 3661);
        }
        {
            const time_span_type time_span(1, 59, 59);

            BOOST_CHECK_EQUAL(time_span.seconds(), 7199);
        }
        {
            const time_span_type time_span(-1, -1, -1);

            BOOST_CHECK_EQUAL(time_span.seconds(), -3661);
        }
        {
            const time_span_type time_span(-1, -59, -59);

            BOOST_CHECK_EQUAL(time_span.seconds(), -7199);
        }
        {
            BOOST_CHECK_THROW(time_span_type(0, 60, 0), std::out_of_range);
        }
        {
            BOOST_CHECK_THROW(time_span_type(0, 0, 60), std::out_of_range);
        }
        {
            BOOST_CHECK_THROW(time_span_type(0, 60, 60), std::out_of_range);
        }
        {
            BOOST_CHECK_THROW(
                time_span_type(-1, 1, 1), std::invalid_argument
            );
        }
        {
            BOOST_CHECK_THROW(
                time_span_type(-1, -1, 1), std::invalid_argument
            );
        }
        {
            BOOST_CHECK_THROW(
                time_span_type(1, -1, 1), std::invalid_argument
            );
        }
        {
            BOOST_CHECK_THROW(
                time_span_type(1, -1, -1), std::invalid_argument
            );
        }
        {
            BOOST_CHECK_THROW(
                time_span_type(1, 1, -1), std::invalid_argument
            );
        }
        {
            BOOST_CHECK_THROW(
                time_span_type(-1, 1, -1), std::invalid_argument
            );
        }
    }

    void time_span::swap()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::ptrdiff_t>
            time_span_type;

        {
            time_span_type time_span1(1);
            time_span_type time_span2(2);

            time_span1.swap(time_span2);

            BOOST_CHECK_EQUAL(time_span1.seconds(), 2);
            BOOST_CHECK_EQUAL(time_span2.seconds(), 1);
        }
        {
            time_span_type time_span1(1);
            time_span_type time_span2(2);

            std::swap(time_span1, time_span2);

            BOOST_CHECK_EQUAL(time_span1.seconds(), 2);
            BOOST_CHECK_EQUAL(time_span2.seconds(), 1);
        }
    }

    void time_span::operator_assign()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::ptrdiff_t>
            time_span_type;

        {
            time_span_type time_span1(1);
            const time_span_type time_span2(2);

            time_span1 = time_span2;

            BOOST_CHECK_EQUAL(time_span1.seconds(), 2);
            BOOST_CHECK_EQUAL(time_span2.seconds(), 2);
        }
    }

    void time_span::operator_plus_assign()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::ptrdiff_t>
            time_span_type;

        {
            time_span_type time_span1(1);
            const time_span_type time_span2(2);

            time_span1 += time_span2;

            BOOST_CHECK_EQUAL(time_span1.seconds(), 3);
        }
        {
            time_span_type time_span1(0, 0, 59);
            const time_span_type time_span2(0, 0, 1);

            time_span1 += time_span2;

            BOOST_CHECK(
                time_span1.hours_minutes_seconds() ==
                boost::make_tuple(0, 1, 0)
            );
        }
        {
            time_span_type time_span1(0, 1, 0);
            const time_span_type time_span2(0, 0, -1);

            time_span1 += time_span2;

            BOOST_CHECK(
                time_span1.hours_minutes_seconds() ==
                boost::make_tuple(0, 0, 59)
            );
        }
        {
            const time_span_type time_span1(1);
            const time_span_type time_span2(2);

            const time_span_type time_span3 = time_span1 + time_span2;

            BOOST_CHECK_EQUAL(time_span3.seconds(), 3);
        }
        {
            const time_span_type time_span1(0, 59, 59);
            const time_span_type time_span2(0, 0, 1);

            const time_span_type time_span3 = time_span1 + time_span2;

            BOOST_CHECK(
                time_span3.hours_minutes_seconds() ==
                boost::make_tuple(1, 0, 0)
            );
        }
        {
            const time_span_type time_span1(1, 0, 0);
            const time_span_type time_span2(0, 0, -1);

            const time_span_type time_span3 = time_span1 + time_span2;

            BOOST_CHECK(
                time_span3.hours_minutes_seconds() ==
                boost::make_tuple(0, 59, 59)
            );
        }
    }

    void time_span::operator_minus_assign()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::ptrdiff_t>
            time_span_type;

        {
            time_span_type time_span1(1);
            const time_span_type time_span2(2);

            time_span1 -= time_span2;

            BOOST_CHECK_EQUAL(time_span1.seconds(), -1);
        }
        {
            time_span_type time_span1(0, 0, 59);
            const time_span_type time_span2(0, 0, -1);

            time_span1 -= time_span2;

            BOOST_CHECK(
                time_span1.hours_minutes_seconds() ==
                boost::make_tuple(0, 1, 0)
            );
        }
        {
            time_span_type time_span1(0, 1, 0);
            const time_span_type time_span2(0, 0, 1);

            time_span1 -= time_span2;

            BOOST_CHECK(
                time_span1.hours_minutes_seconds() ==
                boost::make_tuple(0, 0, 59)
            );
        }
        {
            const time_span_type time_span1(1);
            const time_span_type time_span2(2);

            const time_span_type time_span3 = time_span1 - time_span2;

            BOOST_CHECK_EQUAL(time_span3.seconds(), -1);
        }
        {
            const time_span_type time_span1(0, 59, 59);
            const time_span_type time_span2(0, 0, -1);

            const time_span_type time_span3 = time_span1 - time_span2;

            BOOST_CHECK(
                time_span3.hours_minutes_seconds() ==
                boost::make_tuple(1, 0, 0)
            );
        }
        {
            const time_span_type time_span1(1, 0, 0);
            const time_span_type time_span2(0, 0, 1);

            const time_span_type time_span3 = time_span1 - time_span2;

            BOOST_CHECK(
                time_span3.hours_minutes_seconds() ==
                boost::make_tuple(0, 59, 59)
            );
        }
    }

    void time_span::operator_equal()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::ptrdiff_t>
            time_span_type;

        {
            const time_span_type time_span1(1);
            const time_span_type time_span2(1);

            BOOST_CHECK(time_span1 == time_span2);
        }
        {
            const time_span_type time_span1(1);
            const time_span_type time_span2(2);

            BOOST_CHECK(time_span1 != time_span2);
        }
    }

    void time_span::operator_less_than()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::ptrdiff_t>
            time_span_type;

        {
            const time_span_type time_span1(0);
            const time_span_type time_span2(0);

            BOOST_CHECK(!(time_span1 < time_span2));
            BOOST_CHECK(time_span1 <= time_span2);
            BOOST_CHECK(!(time_span1 > time_span2));
            BOOST_CHECK(time_span1 >= time_span2);
        }
        {
            const time_span_type time_span1(0);
            const time_span_type time_span2(1);

            BOOST_CHECK(time_span1 < time_span2);
            BOOST_CHECK(time_span1 <= time_span2);
            BOOST_CHECK(!(time_span1 > time_span2));
            BOOST_CHECK(!(time_span1 >= time_span2));
        }
        {
            const time_span_type time_span1(1);
            const time_span_type time_span2(0);

            BOOST_CHECK(!(time_span1 < time_span2));
            BOOST_CHECK(!(time_span1 <= time_span2));
            BOOST_CHECK(time_span1 > time_span2);
            BOOST_CHECK(time_span1 >= time_span2);
        }
        {
            const time_span_type time_span1(0, 0, 1);
            const time_span_type time_span2(0, 1, 0);

            BOOST_CHECK(time_span1 < time_span2);
            BOOST_CHECK(time_span1 <= time_span2);
            BOOST_CHECK(!(time_span1 > time_span2));
            BOOST_CHECK(!(time_span1 >= time_span2));
        }
        {
            const time_span_type time_span1(0, 0, 1);
            const time_span_type time_span2(1, 0, 0);

            BOOST_CHECK(time_span1 < time_span2);
            BOOST_CHECK(time_span1 <= time_span2);
            BOOST_CHECK(!(time_span1 > time_span2));
            BOOST_CHECK(!(time_span1 >= time_span2));
        }
        {
            const time_span_type time_span1(0, 1, 0);
            const time_span_type time_span2(1, 0, 0);

            BOOST_CHECK(time_span1 < time_span2);
            BOOST_CHECK(time_span1 <= time_span2);
            BOOST_CHECK(!(time_span1 > time_span2));
            BOOST_CHECK(!(time_span1 >= time_span2));
        }
        {
            const time_span_type time_span1(0, 1, 0);
            const time_span_type time_span2(0, 0, 1);

            BOOST_CHECK(!(time_span1 < time_span2));
            BOOST_CHECK(!(time_span1 <= time_span2));
            BOOST_CHECK(time_span1 > time_span2);
            BOOST_CHECK(time_span1 >= time_span2);
        }
        {
            const time_span_type time_span1(1, 0, 0);
            const time_span_type time_span2(0, 0, 1);

            BOOST_CHECK(!(time_span1 < time_span2));
            BOOST_CHECK(!(time_span1 <= time_span2));
            BOOST_CHECK(time_span1 > time_span2);
            BOOST_CHECK(time_span1 >= time_span2);
        }
        {
            const time_span_type time_span1(1, 0, 0);
            const time_span_type time_span2(0, 1, 0);

            BOOST_CHECK(!(time_span1 < time_span2));
            BOOST_CHECK(!(time_span1 <= time_span2));
            BOOST_CHECK(time_span1 > time_span2);
            BOOST_CHECK(time_span1 >= time_span2);
        }
    }

    void time_span::seconds()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::ptrdiff_t>
            time_span_type;

        {
            const time_span_type time_span(0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 0);
        }
        {
            const time_span_type time_span(1);

            BOOST_CHECK_EQUAL(time_span.seconds(), 1);
        }
        {
            const time_span_type time_span(2);

            BOOST_CHECK_EQUAL(time_span.seconds(), 2);
        }
        {
            const time_span_type time_span(-1);

            BOOST_CHECK_EQUAL(time_span.seconds(), -1);
        }
        {
            const time_span_type time_span(-2);

            BOOST_CHECK_EQUAL(time_span.seconds(), -2);
        }
    }

    void time_span::hours_minutes_seconds()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::ptrdiff_t>
            time_span_type;

        {
            const time_span_type time_span(0, 0, 0);

            BOOST_CHECK(
                time_span.hours_minutes_seconds() ==
                boost::make_tuple(0, 0, 0)
            );
        }
        {
            const time_span_type time_span(1, 1, 1);

            BOOST_CHECK(
                time_span.hours_minutes_seconds() ==
                boost::make_tuple(1, 1, 1)
            );
        }
        {
            const time_span_type time_span(1, 2, 3);

            BOOST_CHECK(
                time_span.hours_minutes_seconds() ==
                boost::make_tuple(1, 2, 3)
            );
        }
        {
            const time_span_type time_span(-1, -1, -1);

            BOOST_CHECK(
                time_span.hours_minutes_seconds() ==
                boost::make_tuple(-1, -1, -1)
            );
        }
        {
            const time_span_type time_span(-1, -2, -3);

            BOOST_CHECK(
                time_span.hours_minutes_seconds() ==
                boost::make_tuple(-1, -2, -3)
            );
        }
    }


}}}
