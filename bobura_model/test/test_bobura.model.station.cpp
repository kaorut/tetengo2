/*! \file
    \brief Test of class bobura::model::station.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

#include "bobura.model.station.h"
#include "bobura.model.station_info.grade.h"

#include "test_bobura.model.station.h"


namespace test_bobura { namespace model
{
    // functions

    boost::unit_test::test_suite* station::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model::station");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(swap));
        p_suite->add(BOOST_TEST_CASE(operator_assign));
        p_suite->add(BOOST_TEST_CASE(name));
        p_suite->add(BOOST_TEST_CASE(grade));

        return p_suite;
    }

    void station::construction()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station_info::major<std::wstring> major_type;

        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"", grade_type::instance()
            );
            const bobura::model::station<std::wstring, grade_type>
            copy_of_station(station);

            BOOST_CHECK(station == copy_of_station);
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"A", grade_type::instance()
            );

            const bobura::model::station<std::wstring, grade_type>
            copy_of_station(station);

            BOOST_CHECK(station == copy_of_station);
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"AB", grade_type::instance()
            );

            const bobura::model::station<std::wstring, grade_type>
            copy_of_station(station);

            BOOST_CHECK(station == copy_of_station);
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                std::wstring(1024 * 1024, L'X'), grade_type::instance()
            );

            const bobura::model::station<std::wstring, grade_type>
            copy_of_station(station);

            BOOST_CHECK(station == copy_of_station);
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"", major_type::instance()
            );

            const bobura::model::station<std::wstring, grade_type>
            copy_of_station(station);

            BOOST_CHECK(station == copy_of_station);
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"A", major_type::instance()
            );

            const bobura::model::station<std::wstring, grade_type>
            copy_of_station(station);

            BOOST_CHECK(station == copy_of_station);
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"AB", major_type::instance()
            );

            const bobura::model::station<std::wstring, grade_type>
            copy_of_station(station);

            BOOST_CHECK(station == copy_of_station);
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                std::wstring(1024 * 1024, L'X'), grade_type::instance()
            );

            const bobura::model::station<std::wstring, grade_type>
            copy_of_station(station);

            BOOST_CHECK(station == copy_of_station);
        }
    }

    void station::swap()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station_info::major<std::wstring> major_type;

        bobura::model::station<std::wstring, grade_type> station1(
            L"A", grade_type::instance()
        );
        bobura::model::station<std::wstring, grade_type> station2(
            L"B", major_type::instance()
        );

        station1.swap(station2);

        BOOST_CHECK(station1.name() == std::wstring(L"B"));
        BOOST_CHECK_EQUAL(&station1.grade(), &major_type::instance());
        BOOST_CHECK(station2.name() == std::wstring(L"A"));
        BOOST_CHECK_EQUAL(&station2.grade(), &grade_type::instance());

        std::swap(station1, station2);

        BOOST_CHECK(station1.name() == std::wstring(L"A"));
        BOOST_CHECK_EQUAL(&station1.grade(), &grade_type::instance());
        BOOST_CHECK(station2.name() == std::wstring(L"B"));
        BOOST_CHECK_EQUAL(&station2.grade(), &major_type::instance());
    }

    void station::operator_assign()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station_info::major<std::wstring> major_type;

        bobura::model::station<std::wstring, grade_type> station1(
            L"A", grade_type::instance()
        );
        const bobura::model::station<std::wstring, grade_type> station2(
            L"B", major_type::instance()
        );

        station1 = station2;

        BOOST_CHECK(station1 == station2);
    }

    void station::operator_equal()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station_info::major<std::wstring> major_type;

        {
            const bobura::model::station<std::wstring, grade_type> station1(
                L"A", grade_type::instance()
            );
            const bobura::model::station<std::wstring, grade_type> station2(
                L"A", grade_type::instance()
            );

            BOOST_CHECK(station1 == station2);
            BOOST_CHECK(!(station1 != station2));
        }
        {
            const bobura::model::station<std::wstring, grade_type> station1(
                L"B", major_type::instance()
            );
            const bobura::model::station<std::wstring, grade_type> station2(
                L"B", major_type::instance()
            );

            BOOST_CHECK(station1 == station2);
            BOOST_CHECK(!(station1 != station2));
        }
        {
            const bobura::model::station<std::wstring, grade_type> station1(
                L"A", grade_type::instance()
            );
            const bobura::model::station<std::wstring, grade_type> station2(
                L"B", major_type::instance()
            );

            BOOST_CHECK(station1 != station2);
            BOOST_CHECK(!(station1 == station2));
        }
    }

    void station::name()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;

        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"", grade_type::instance()
            );

            BOOST_CHECK(station.name() == std::wstring(L""));
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"A", grade_type::instance()
            );

            BOOST_CHECK(station.name() == std::wstring(L"A"));
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"AB", grade_type::instance()
            );

            BOOST_CHECK(station.name() == std::wstring(L"AB"));
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                std::wstring(1024 * 1024, L'X'), grade_type::instance()
            );

            BOOST_CHECK(station.name() == std::wstring(1024 * 1024, L'X'));
        }
    }

    void station::grade()
    {
        BOOST_CHECKPOINT("");

        typedef bobura::model::station_info::grade<std::wstring> grade_type;
        typedef bobura::model::station_info::local<std::wstring> local_type;
        typedef bobura::model::station_info::major<std::wstring> major_type;
        typedef
            bobura::model::station_info::local_terminal<std::wstring>
            local_terminal_type;
        typedef
            bobura::model::station_info::major_terminal<std::wstring>
            major_terminal_type;

        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"", grade_type::instance()
            );

            BOOST_CHECK_EQUAL(&station.grade(), &grade_type::instance());
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"", local_type::instance()
            );

            BOOST_CHECK_EQUAL(&station.grade(), &local_type::instance());
        }
        {
            const bobura::model::station<std::wstring, grade_type> station(
                L"", major_type::instance()
            );

            BOOST_CHECK_EQUAL(&station.grade(), &major_type::instance());
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
                L"", major_terminal_type::instance()
            );

            BOOST_CHECK_EQUAL(
                &station.grade(), &major_terminal_type::instance()
            );
        }
    }


}}
