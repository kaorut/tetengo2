/*! \file
    \brief Test of class bobura::model::train_info::time.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.test.h"

#include <algorithm>
#include <cstddef>
#include <string>

//#include <boost/test/unit_test.hpp>

#include "bobura.model.station.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.train_info.time.h"

#include "test_bobura.model.train_info.time.h"


/*
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
        p_suite->add(BOOST_TEST_CASE(station));
        p_suite->add(BOOST_TEST_CASE(meterage));
        p_suite->add(BOOST_TEST_CASE(before));

        return p_suite;
    }

    void time::construction()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time(
                station_type(L"", grade_type::instance()), 0
            );

            const bobura::model::train_info::time<
                station_type, std::size_t
            > copy_of_time(time);

            BOOST_CHECK(time == copy_of_time);
        }
    }

    void time::swap()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            bobura::model::train_info::time<
                station_type, std::size_t
            > time1(
                station_type(L"A", grade_type::instance()), 1
            );
            bobura::model::train_info::time<
                station_type, std::size_t
            > time2(
                station_type(L"B", grade_type::instance()), 2
            );

            time1.swap(time2);

            BOOST_CHECK(time1.station().name() == L"B");
            BOOST_CHECK_EQUAL(time1.meterage(), 2U);
            BOOST_CHECK(time2.station().name() == L"A");
            BOOST_CHECK_EQUAL(time2.meterage(), 1U);
        }
        {
            bobura::model::train_info::time<
                station_type, std::size_t
            > time1(
                station_type(L"A", grade_type::instance()), 1
            );
            bobura::model::train_info::time<
                station_type, std::size_t
            > time2(
                station_type(L"B", grade_type::instance()), 2
            );

            std::swap(time1, time2);

            BOOST_CHECK(time1.station().name() == L"B");
            BOOST_CHECK_EQUAL(time1.meterage(), 2U);
            BOOST_CHECK(time2.station().name() == L"A");
            BOOST_CHECK_EQUAL(time2.meterage(), 1U);
        }
    }

    void time::operator_assign()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            bobura::model::train_info::time<
                station_type, std::size_t
            > time1(
                station_type(L"A", grade_type::instance()), 1
            );
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time2(
                station_type(L"B", grade_type::instance()), 2
            );

            time1 = time2;

            BOOST_CHECK(time1 == time2);
        }
    }

    void time::operator_equal()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time1(
                station_type(L"A", grade_type::instance()), 1
            );
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time2(
                station_type(L"A", grade_type::instance()), 1
            );

            BOOST_CHECK(time1 == time2);
        }
        {
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time1(
                station_type(L"A", grade_type::instance()), 1
            );
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time2(
                station_type(L"B", grade_type::instance()), 2
            );

            BOOST_CHECK(time1 != time2);
        }
    }

    void time::station()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        const station_type station(L"", grade_type::instance());
        const bobura::model::train_info::time<
            station_type, std::size_t
        > time(station, 0);

        BOOST_CHECK(time.station() == station);
    }

    void time::meterage()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time(
                station_type(L"", grade_type::instance()), 0
            );

            BOOST_CHECK_EQUAL(time.meterage(), 0U);
        }
        {
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time(
                station_type(L"", grade_type::instance()), 1
            );

            BOOST_CHECK_EQUAL(time.meterage(), 1U);
        }
        {
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time(
                station_type(L"", grade_type::instance()), 2
            );

            BOOST_CHECK_EQUAL(time.meterage(), 2U);
        }
    }

    void time::before()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time1(
                station_type(L"", grade_type::instance()), 1
            );
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time2(
                station_type(L"", grade_type::instance()), 1
            );

            BOOST_CHECK(time1.before(time2));
        }
        {
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time1(
                station_type(L"", grade_type::instance()), 1
            );
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time2(
                station_type(L"", grade_type::instance()), 2
            );

            BOOST_CHECK(time1.before(time2));
        }
        {
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time1(
                station_type(L"", grade_type::instance()), 2
            );
            const bobura::model::train_info::time<
                station_type, std::size_t
            > time2(
                station_type(L"", grade_type::instance()), 1
            );

            BOOST_CHECK(!time1.before(time2));
        }
    }


}}}
*/
