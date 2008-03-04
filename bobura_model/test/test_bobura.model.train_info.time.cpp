/*! \file
    \brief Test of class bobura::model::train_info::time.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.test.h"

//#include <boost/test/unit_test.hpp>

#include "bobura.model.train_info.time_span.h"

#include "bobura.model.train_info.time.h"

#include "test_bobura.model.train_info.time.h"


namespace test_bobura { namespace model { namespace train_info
{
    // functions

    boost::unit_test::test_suite* time::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE(
                "test_bobura::model::train_info::time"
            );

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));

        return p_suite;
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
            BOOST_CHECK_THROW(time_type(0, 0, 60), std::length_error);
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
            BOOST_CHECK_THROW(time_type(0, 60, 0), std::length_error);
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
            BOOST_CHECK_THROW(time_type(24, 0, 0), std::length_error);
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


}}}
