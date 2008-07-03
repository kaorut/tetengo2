/*! \file
    \brief Test of class bobura::model::train_info::time.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <algorithm>
#include <cstddef>
#include <stdexcept>

//#include <boost/test/unit_test.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include "bobura.model.train_info.time_span.h"

#include "bobura.model.train_info.time.h"

#include "test_bobura.model.train_info.time.h"


namespace test_bobura { namespace model { namespace train_info
{
    // functions

    boost::unit_test::test_suite* time::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model::train_info::time");

        p_suite->add(BOOST_TEST_CASE(uninitialized));
        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_plus_assign));
        p_suite->add(BOOST_TEST_CASE(operator_minus_assign));
        p_suite->add(BOOST_TEST_CASE(operator_minus));
        p_suite->add(BOOST_TEST_CASE(operator_equal));
        p_suite->add(BOOST_TEST_CASE(operator_less_than));
        p_suite->add(BOOST_TEST_CASE(seconds_from_midnight));
        p_suite->add(BOOST_TEST_CASE(hours_minutes_seconds));

        return p_suite;
    }

    void time::uninitialized()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;

            const time_type time = time_type::uninitialized();

            const time_type copy_of_time(time);

            BOOST_CHECK(time == copy_of_time);
    }

    void time::construction()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;

        {
            const time_type time(0);

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);

            const time_type copy_of_time(time);

            BOOST_CHECK(time == copy_of_time);
        }
        {
            const time_type time(1);

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 1U);

            const time_type copy_of_time(time);

            BOOST_CHECK(time == copy_of_time);
        }
        {
            const time_type time(2);

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 2U);

            const time_type copy_of_time(time);

            BOOST_CHECK(time == copy_of_time);
        }
        {
            const time_type time(24 * 60 * 60 - 1);

            BOOST_CHECK_EQUAL(
                time.seconds_from_midnight(), 24U * 60U * 60U - 1U
            );
        }
        {
            const time_type time(24 * 60 * 60);

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            const time_type time(0, 0, 0);

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            const time_type time(0, 0, 1);

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 1U);
        }
        {
            const time_type time(0, 0, 59);

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 59U);
        }
        {
            BOOST_CHECK_THROW(time_type(0, 0, 60), std::out_of_range);
        }
        {
            const time_type time(0, 1, 0);

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 60U);
        }
        {
            const time_type time(0, 59, 0);

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 3540U);
        }
        {
            BOOST_CHECK_THROW(time_type(0, 60, 0), std::out_of_range);
        }
        {
            const time_type time(1, 0, 0);

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 3600U);
        }
        {
            const time_type time(23, 0, 0);

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 82800U);
        }
        {
            BOOST_CHECK_THROW(time_type(24, 0, 0), std::out_of_range);
        }
    }

    void time::swap()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;

        {
            time_type time1(1);
            time_type time2(2);

            time1.swap(time2);

            BOOST_CHECK_EQUAL(time1.seconds_from_midnight(), 2U);
            BOOST_CHECK_EQUAL(time2.seconds_from_midnight(), 1U);
        }
        {
            time_type time1(1);
            time_type time2(2);

            std::swap(time1, time2);

            BOOST_CHECK_EQUAL(time1.seconds_from_midnight(), 2U);
            BOOST_CHECK_EQUAL(time2.seconds_from_midnight(), 1U);
        }
    }

    void time::operator_assign()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;

        {
            time_type time1(1);
            const time_type time2(2);

            time1 = time2;

            BOOST_CHECK(time1 == time2);
        }
        {
            time_type time1 = time_type::uninitialized();
            const time_type time2(2);

            time1 = time2;

            BOOST_CHECK(time1 == time2);
        }
        {
            time_type time1(1);
            const time_type time2 = time_type::uninitialized();

            time1 = time2;

            BOOST_CHECK(time1 == time2);
        }
    }

    void time::operator_plus_assign()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::ptrdiff_t>
            time_span_type;
        typedef
            bobura::model::train_info::time<std::size_t, time_span_type>
            time_type;

        {
            time_type time(0);
            const time_span_type time_span(0);

            time += time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            time_type time(0);
            const time_span_type time_span(1);

            time += time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 1U);
        }
        {
            time_type time(0);
            const time_span_type time_span(-1);

            time += time_span;

            BOOST_CHECK_EQUAL(
                time.seconds_from_midnight(), 24U * 60U * 60U - 1U
            );
        }
        {
            time_type time(24 * 60 * 60 - 1);
            const time_span_type time_span(1);

            time += time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            time_type time(0);
            const time_span_type time_span(24, 0, 0);

            time += time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            time_type time(0);
            const time_span_type time_span(-24, 0, 0);

            time += time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            time_type time = time_type::uninitialized();
            const time_span_type time_span(1);

            time += time_span;

            BOOST_CHECK(time == time_type::uninitialized());
        }
    }

    void time::operator_minus_assign()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::ptrdiff_t>
            time_span_type;
        typedef
            bobura::model::train_info::time<std::size_t, time_span_type>
            time_type;

        {
            time_type time(0);
            const time_span_type time_span(0);

            time -= time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            time_type time(0);
            const time_span_type time_span(-1);

            time -= time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 1U);
        }
        {
            time_type time(0);
            const time_span_type time_span(1);

            time -= time_span;

            BOOST_CHECK_EQUAL(
                time.seconds_from_midnight(), 24U * 60U * 60U - 1U
            );
        }
        {
            time_type time(24 * 60 * 60 - 1);
            const time_span_type time_span(-1);

            time -= time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            time_type time(0);
            const time_span_type time_span(24, 0, 0);

            time -= time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            time_type time(0);
            const time_span_type time_span(-24, 0, 0);

            time -= time_span;

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            time_type time = time_type::uninitialized();
            const time_span_type time_span(1);

            time -= time_span;

            BOOST_CHECK(time == time_type::uninitialized());
        }
    }

    void time::operator_minus()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::ptrdiff_t>
            time_span_type;
        typedef
            bobura::model::train_info::time<std::size_t, time_span_type>
            time_type;

        {
            const time_type time1(0);
            const time_type time2(0);

            const time_span_type time_span = time1 - time2;

            BOOST_CHECK_EQUAL(time_span.seconds(), 0);
        }
        {
            const time_type time1(1);
            const time_type time2(0);

            const time_span_type time_span = time1 - time2;

            BOOST_CHECK_EQUAL(time_span.seconds(), 1);
        }
        {
            const time_type time1(0);
            const time_type time2(1);

            const time_span_type time_span = time1 - time2;

            BOOST_CHECK_EQUAL(time_span.seconds(), 24 * 60 * 60 - 1);
        }
        {
            const time_type time1(1);
            const time_type time2(24 * 60 * 60 - 1);

            const time_span_type time_span = time1 - time2;

            BOOST_CHECK_EQUAL(time_span.seconds(), 2);
        }
        {
            const time_type time2(1);

            BOOST_CHECK_THROW(
                time_type::uninitialized() - time2, std::logic_error
            );
        }
        {
            const time_type time1(1);

            BOOST_CHECK_THROW(
                time1 - time_type::uninitialized(), std::logic_error
            );
        }
        {
            BOOST_CHECK_THROW(
                time_type::uninitialized() - time_type::uninitialized(),
                std::logic_error
            );
        }
    }

    void time::operator_equal()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;

        {
            const time_type time1(1);
            const time_type time2(1);

            BOOST_CHECK(time1 == time2);
        }
        {
            const time_type time1(1);
            const time_type time2(2);

            BOOST_CHECK(time1 != time2);
        }
    }

    void time::operator_less_than()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;

        {
            const time_type time1(1);
            const time_type time2(1);

            BOOST_CHECK(!(time1 < time2));
            BOOST_CHECK(time1 <= time2);
            BOOST_CHECK(!(time1 > time2));
            BOOST_CHECK(time1 >= time2);
        }
        {
            const time_type time1(1);
            const time_type time2(2);

            BOOST_CHECK(time1 < time2);
            BOOST_CHECK(time1 <= time2);
            BOOST_CHECK(!(time1 > time2));
            BOOST_CHECK(!(time1 >= time2));
        }
        {
            const time_type time1(2);
            const time_type time2(1);

            BOOST_CHECK(!(time1 < time2));
            BOOST_CHECK(!(time1 <= time2));
            BOOST_CHECK(time1 > time2);
            BOOST_CHECK(time1 >= time2);
        }
    }

    void time::seconds_from_midnight()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;

        {
            const time_type time(0);

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 0U);
        }
        {
            const time_type time(1);

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 1U);
        }
        {
            const time_type time(2);

            BOOST_CHECK_EQUAL(time.seconds_from_midnight(), 2U);
        }
        {
            BOOST_CHECK_THROW(
                time_type::uninitialized().seconds_from_midnight(),
                std::logic_error
            );
        }
    }

    void time::hours_minutes_seconds()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time<
                std::size_t,
                bobura::model::train_info::time_span<std::ptrdiff_t>
            >
            time_type;

        {
            const time_type time(0, 0, 0);

            BOOST_CHECK(
                time.hours_minutes_seconds() == boost::make_tuple(0U, 0U, 0U)
            );
        }
        {
            const time_type time(0, 0, 1);

            BOOST_CHECK(
                time.hours_minutes_seconds() == boost::make_tuple(0U, 0U, 1U)
            );
        }
        {
            const time_type time(0, 1, 0);

            BOOST_CHECK(
                time.hours_minutes_seconds() == boost::make_tuple(0U, 1U, 0U)
            );
        }
        {
            const time_type time(1, 0, 0);

            BOOST_CHECK(
                time.hours_minutes_seconds() == boost::make_tuple(1U, 0U, 0U)
            );
        }
        {
            const time_type time(1, 2, 3);

            BOOST_CHECK(
                time.hours_minutes_seconds() == boost::make_tuple(1U, 2U, 3U)
            );
        }
        {
            BOOST_CHECK_THROW(
                time_type::uninitialized().hours_minutes_seconds(),
                std::logic_error
            );
        }
    }


}}}
