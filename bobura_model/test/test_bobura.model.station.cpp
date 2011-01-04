/*! \file
    \brief Test of class bobura::model::station.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <string>

#include <boost/test/unit_test.hpp>

#include "bobura.model.station_info.grade.h"

#include "bobura.model.station.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(station)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station_info::local<std::wstring> local_type;
        typedef
            bobura::model::station_info::principal<std::wstring>
            principal_type;

        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"", local_type::instance()
            );
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"A", local_type::instance()
            );
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"AB", local_type::instance()
            );
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                std::wstring(1024 * 1024, L'X'), local_type::instance()
            );
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"", principal_type::instance()
            );
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"A", principal_type::instance()
            );
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"AB", principal_type::instance()
            );
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                std::wstring(1024 * 1024, L'X'), local_type::instance()
            );
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station_info::local<std::wstring> local_type;
        typedef
            bobura::model::station_info::principal<std::wstring>
            principal_type;

        {
            const bobura::model::station<std::wstring, grade_type> station1(
                L"A", local_type::instance()
            );
            const bobura::model::station<std::wstring, grade_type> station2(
                L"A", local_type::instance()
            );

            BOOST_CHECK(station1 == station2);
        }
        {
            const bobura::model::station<std::wstring, grade_type> station1(
                L"B", principal_type::instance()
            );
            const bobura::model::station<std::wstring, grade_type> station2(
                L"B", principal_type::instance()
            );

            BOOST_CHECK(station1 == station2);
        }
        {
            const bobura::model::station<std::wstring, grade_type> station1(
                L"A", local_type::instance()
            );
            const bobura::model::station<std::wstring, grade_type> station2(
                L"B", principal_type::instance()
            );

            BOOST_CHECK(station1 != station2);
        }
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station_info::local<std::wstring> local_type;

        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"", local_type::instance()
            );

            BOOST_CHECK(station.name() == std::wstring(L""));
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"A", local_type::instance()
            );

            BOOST_CHECK(station.name() == std::wstring(L"A"));
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"AB", local_type::instance()
            );

            BOOST_CHECK(station.name() == std::wstring(L"AB"));
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                std::wstring(1024 * 1024, L'X'), local_type::instance()
            );

            BOOST_CHECK(station.name() == std::wstring(1024 * 1024, L'X'));
        }
    }

    BOOST_AUTO_TEST_CASE(grade)
    {
        BOOST_TEST_PASSPOINT();

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station_info::local<std::wstring> local_type;
        typedef
            bobura::model::station_info::principal<std::wstring>
            principal_type;
        typedef
            bobura::model::station_info::local_terminal<std::wstring>
            local_terminal_type;
        typedef
            bobura::model::station_info::principal_terminal<std::wstring>
            principal_terminal_type;

        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"", local_type::instance()
            );

            BOOST_CHECK_EQUAL(&station.grade(), &local_type::instance());
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"", principal_type::instance()
            );

            BOOST_CHECK_EQUAL(&station.grade(), &principal_type::instance());
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"", local_terminal_type::instance()
            );

            BOOST_CHECK_EQUAL(
                &station.grade(), &local_terminal_type::instance()
            );
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"", principal_terminal_type::instance()
            );

            BOOST_CHECK_EQUAL(
                &station.grade(), &principal_terminal_type::instance()
            );
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
