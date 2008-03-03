/*! \file
    \brief Test of class bobura::model::train_info::time_span.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.test.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

//#include <boost/test/unit_test.hpp>
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
            BOOST_TEST_SUITE(
                "test_bobura::model::train_info::time_span"
            );

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));
        p_suite->add(BOOST_TEST_CASE(seconds));
        p_suite->add(BOOST_TEST_CASE(hours_minutes_seconds));

        return p_suite;
    }

    void time_span::construction()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::size_t> time_span_type;

        {
            time_span_type time_span(0, time_span_type::hour());

            BOOST_CHECK_EQUAL(time_span.seconds(), 0U);

            time_span_type copy_of_time_span(time_span);
            
            BOOST_CHECK(time_span == copy_of_time_span);
        }
        {
            time_span_type time_span(1, time_span_type::hour());

            BOOST_CHECK_EQUAL(time_span.seconds(), 3600U);

            time_span_type copy_of_time_span(time_span);
            
            BOOST_CHECK(time_span == copy_of_time_span);
        }
        {
            time_span_type time_span(2, time_span_type::hour());

            BOOST_CHECK_EQUAL(time_span.seconds(), 7200U);

            time_span_type copy_of_time_span(time_span);
            
            BOOST_CHECK(time_span == copy_of_time_span);
        }
        {
            time_span_type time_span(0, time_span_type::minute());

            BOOST_CHECK_EQUAL(time_span.seconds(), 0U);
        }
        {
            time_span_type time_span(1, time_span_type::minute());

            BOOST_CHECK_EQUAL(time_span.seconds(), 60U);
        }
        {
            time_span_type time_span(2, time_span_type::minute());

            BOOST_CHECK_EQUAL(time_span.seconds(), 120U);
        }
        {
            BOOST_CHECK_THROW(
                time_span_type(60, time_span_type::minute()),
                std::length_error
            );
        }
        {
            time_span_type time_span(0, time_span_type::second());

            BOOST_CHECK_EQUAL(time_span.seconds(), 0U);
        }
        {
            time_span_type time_span(1, time_span_type::second());

            BOOST_CHECK_EQUAL(time_span.seconds(), 1U);
        }
        {
            time_span_type time_span(2, time_span_type::second());

            BOOST_CHECK_EQUAL(time_span.seconds(), 2U);
        }
        {
            BOOST_CHECK_THROW(
                time_span_type(60, time_span_type::second()),
                std::length_error
            );
        }
        {
            time_span_type time_span(0, 0, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 0U);
        }
        {
            time_span_type time_span(1, 0, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 3600U);
        }
        {
            time_span_type time_span(0, 1, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 60U);
        }
        {
            time_span_type time_span(0, 59, 0);

            BOOST_CHECK_EQUAL(time_span.seconds(), 3540U);
        }
        {
            time_span_type time_span(0, 0, 1);

            BOOST_CHECK_EQUAL(time_span.seconds(), 1U);
        }
        {
            time_span_type time_span(0, 0, 59);

            BOOST_CHECK_EQUAL(time_span.seconds(), 59U);
        }
        {
            time_span_type time_span(1, 1, 1);

            BOOST_CHECK_EQUAL(time_span.seconds(), 3661U);
        }
        {
            time_span_type time_span(1, 59, 59);

            BOOST_CHECK_EQUAL(time_span.seconds(), 7199U);
        }
        {
            BOOST_CHECK_THROW(time_span_type(0, 60, 0), std::length_error);
        }
        {
            BOOST_CHECK_THROW(time_span_type(0, 0, 60), std::length_error);
        }
        {
            BOOST_CHECK_THROW(time_span_type(0, 60, 60), std::length_error);
        }
    }

    void time_span::swap()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::size_t> time_span_type;

        {
            time_span_type time_span1(1, time_span_type::second());
            time_span_type time_span2(2, time_span_type::second());

            time_span1.swap(time_span2);

            BOOST_CHECK_EQUAL(time_span1.seconds(), 2U);
            BOOST_CHECK_EQUAL(time_span2.seconds(), 1U);
        }
        {
            time_span_type time_span1(1, time_span_type::second());
            time_span_type time_span2(2, time_span_type::second());

            std::swap(time_span1, time_span2);

            BOOST_CHECK_EQUAL(time_span1.seconds(), 2U);
            BOOST_CHECK_EQUAL(time_span2.seconds(), 1U);
        }
    }

    void time_span::operator_assign()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::size_t> time_span_type;

        {
            time_span_type time_span1(1, time_span_type::second());
            time_span_type time_span2(2, time_span_type::second());

            time_span1 = time_span2;

            BOOST_CHECK_EQUAL(time_span1.seconds(), 2U);
            BOOST_CHECK_EQUAL(time_span2.seconds(), 2U);
        }
    }

    void time_span::operator_equal()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::size_t> time_span_type;

        {
            time_span_type time_span1(1, time_span_type::second());
            time_span_type time_span2(1, time_span_type::second());

            BOOST_CHECK(time_span1 == time_span2);
        }
        {
            time_span_type time_span1(1, time_span_type::second());
            time_span_type time_span2(2, time_span_type::second());

            BOOST_CHECK(time_span1 != time_span2);
        }
    }

    void time_span::seconds()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::size_t> time_span_type;

        {
            time_span_type time_span(0, time_span_type::second());

            BOOST_CHECK_EQUAL(time_span.seconds(), 0U);
        }
        {
            time_span_type time_span(1, time_span_type::second());

            BOOST_CHECK_EQUAL(time_span.seconds(), 1U);
        }
        {
            time_span_type time_span(2, time_span_type::second());

            BOOST_CHECK_EQUAL(time_span.seconds(), 2U);
        }
    }

    void time_span::hours_minutes_seconds()
    {
        BOOST_CHECKPOINT("");

        typedef
            bobura::model::train_info::time_span<std::size_t> time_span_type;

        {
            time_span_type time_span(0, 0, 0);

            BOOST_CHECK(
                time_span.hours_minutes_seconds() ==
                boost::make_tuple(0U, 0U, 0U)
            );
        }
        {
            time_span_type time_span(1, 1, 1);

            BOOST_CHECK(
                time_span.hours_minutes_seconds() ==
                boost::make_tuple(1U, 1U, 1U)
            );
        }
        {
            time_span_type time_span(1, 2, 3);

            BOOST_CHECK(
                time_span.hours_minutes_seconds() ==
                boost::make_tuple(1U, 2U, 3U)
            );
        }
    }


}}}
