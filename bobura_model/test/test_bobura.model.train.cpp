/*! \file
    \brief Test of class bobura::model::train.

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
#include "bobura.model.train.h"

#include "test_bobura.model.train.h"


namespace test_bobura { namespace model
{
    // functions

    boost::unit_test::test_suite* train::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE(
                "test_bobura::model::train"
            );

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(operator_equal));
        p_suite->add(BOOST_TEST_CASE(station));
        p_suite->add(BOOST_TEST_CASE(meters));
        p_suite->add(BOOST_TEST_CASE(before));

        return p_suite;
    }

    void train::construction()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            const bobura::model::train<
                station_type, std::size_t
            > train(
                station_type(L"", grade_type::instance()), 0
            );

            const bobura::model::train<
                station_type, std::size_t
            > copy_of_train(train);

            BOOST_CHECK(train == copy_of_train);
        }
    }

    void train::swap()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            bobura::model::train<
                station_type, std::size_t
            > train1(
                station_type(L"A", grade_type::instance()), 1
            );
            bobura::model::train<
                station_type, std::size_t
            > train2(
                station_type(L"B", grade_type::instance()), 2
            );

            train1.swap(train2);

            BOOST_CHECK(train1.station().name() == L"B");
            BOOST_CHECK_EQUAL(train1.meters(), 2U);
            BOOST_CHECK(train2.station().name() == L"A");
            BOOST_CHECK_EQUAL(train2.meters(), 1U);
        }
        {
            bobura::model::train<
                station_type, std::size_t
            > train1(
                station_type(L"A", grade_type::instance()), 1
            );
            bobura::model::train<
                station_type, std::size_t
            > train2(
                station_type(L"B", grade_type::instance()), 2
            );

            std::swap(train1, train2);

            BOOST_CHECK(train1.station().name() == L"B");
            BOOST_CHECK_EQUAL(train1.meters(), 2U);
            BOOST_CHECK(train2.station().name() == L"A");
            BOOST_CHECK_EQUAL(train2.meters(), 1U);
        }
    }

    void train::operator_assign()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            bobura::model::train<
                station_type, std::size_t
            > train1(
                station_type(L"A", grade_type::instance()), 1
            );
            const bobura::model::train<
                station_type, std::size_t
            > train2(
                station_type(L"B", grade_type::instance()), 2
            );

            train1 = train2;

            BOOST_CHECK(train1 == train2);
        }
    }

    void train::operator_equal()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            const bobura::model::train<
                station_type, std::size_t
            > train1(
                station_type(L"A", grade_type::instance()), 1
            );
            const bobura::model::train<
                station_type, std::size_t
            > train2(
                station_type(L"A", grade_type::instance()), 1
            );

            BOOST_CHECK(train1 == train2);
        }
        {
            const bobura::model::train<
                station_type, std::size_t
            > train1(
                station_type(L"A", grade_type::instance()), 1
            );
            const bobura::model::train<
                station_type, std::size_t
            > train2(
                station_type(L"B", grade_type::instance()), 2
            );

            BOOST_CHECK(train1 != train2);
        }
    }

    void train::station()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        const station_type station(L"", grade_type::instance());
        const bobura::model::train<
            station_type, std::size_t
        > train(station, 0);

        BOOST_CHECK(train.station() == station);
    }

    void train::meters()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            const bobura::model::train<
                station_type, std::size_t
            > train(
                station_type(L"", grade_type::instance()), 0
            );

            BOOST_CHECK_EQUAL(train.meters(), 0U);
        }
        {
            const bobura::model::train<
                station_type, std::size_t
            > train(
                station_type(L"", grade_type::instance()), 1
            );

            BOOST_CHECK_EQUAL(train.meters(), 1U);
        }
        {
            const bobura::model::train<
                station_type, std::size_t
            > train(
                station_type(L"", grade_type::instance()), 2
            );

            BOOST_CHECK_EQUAL(train.meters(), 2U);
        }
    }

    void train::before()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station<std::wstring, grade_type> station_type;

        {
            const bobura::model::train<
                station_type, std::size_t
            > train1(
                station_type(L"", grade_type::instance()), 1
            );
            const bobura::model::train<
                station_type, std::size_t
            > train2(
                station_type(L"", grade_type::instance()), 1
            );

            BOOST_CHECK(train1.before(train2));
        }
        {
            const bobura::model::train<
                station_type, std::size_t
            > train1(
                station_type(L"", grade_type::instance()), 1
            );
            const bobura::model::train<
                station_type, std::size_t
            > train2(
                station_type(L"", grade_type::instance()), 2
            );

            BOOST_CHECK(train1.before(train2));
        }
        {
            const bobura::model::train<
                station_type, std::size_t
            > train1(
                station_type(L"", grade_type::instance()), 2
            );
            const bobura::model::train<
                station_type, std::size_t
            > train2(
                station_type(L"", grade_type::instance()), 1
            );

            BOOST_CHECK(!train1.before(train2));
        }
    }


}}
