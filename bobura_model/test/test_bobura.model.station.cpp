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

        return p_suite;
    }

    void station::construction()
    {
        //BOOST_CHECKPOINT("");

        //typedef bobura::model::station_info::grade<std::wstring> grade_type;

        //const bobura::model::station<std::wstring, grade_type> station0(L"");
        //const bobura::model::station<std::wstring, grade_type> station1(L"A");
        //const bobura::model::station<std::wstring, grade_type> station2(L"AB");
        //const bobura::model::station<std::wstring, grade_type> station1M(
        //    std::wstring(1024 * 1024, L'X')
        //);

        //const bobura::model::station<std::wstring, grade_type>
        //copy_of_station0(station0);
        //const bobura::model::station<std::wstring, grade_type>
        //copy_of_station1(station1);
        //const bobura::model::station<std::wstring, grade_type>
        //copy_of_station2(station2);
        //const bobura::model::station<std::wstring, grade_type>
        //copy_of_station1M(station1M);
    }

    void station::swap()
    {
        //BOOST_CHECKPOINT("");

        //typedef bobura::model::station_info::grade<std::wstring> grade_type;

        //bobura::model::station<std::wstring, grade_type> station1(L"A");
        //bobura::model::station<std::wstring, grade_type> station2(L"B");

        //station1.swap(station2);

        //BOOST_CHECK(station1.name() == std::wstring(L"B"));
        //BOOST_CHECK(station2.name() == std::wstring(L"A"));
    }

    void station::operator_assign()
    {
        //BOOST_CHECKPOINT("");

        //typedef bobura::model::station_info::grade<std::wstring> grade_type;

        //bobura::model::station<std::wstring, grade_type> station1(L"A");
        //const bobura::model::station<std::wstring, grade_type> station2(L"B");

        //station1 = station2;

        //BOOST_CHECK(station1.name() == std::wstring(L"B"));
    }

    void station::name()
    {
        //BOOST_CHECKPOINT("");

        //typedef bobura::model::station_info::grade<std::wstring> grade_type;

        //{
        //    const bobura::model::station<std::wstring, grade_type> station(
        //        L""
        //    );

        //    BOOST_CHECK(station.name() == std::wstring(L""));
        //}
        //{
        //    const bobura::model::station<std::wstring, grade_type> station(
        //        L"A"
        //    );

        //    BOOST_CHECK(station.name() == std::wstring(L"A"));
        //}
        //{
        //    const bobura::model::station<std::wstring, grade_type> station(
        //        L"AB"
        //    );

        //    BOOST_CHECK(station.name() == std::wstring(L"AB"));
        //}
        //{
        //    const bobura::model::station<std::wstring, grade_type> station(
        //        std::wstring(1024 * 1024, L'X')
        //    );

        //    BOOST_CHECK(station.name() == std::wstring(1024 * 1024, L'X'));
        //}
    }


}}
