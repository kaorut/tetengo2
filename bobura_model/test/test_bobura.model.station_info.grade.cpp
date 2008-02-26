/*! \file
    \brief Test of class bobura::model::station_info::grade.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.test.h"

#include <string>

//#include <boost/test/unit_test.hpp>

#include "bobura.model.station_info.grade.h"

#include "test_bobura.model.station_info.grade.h"


namespace test_bobura { namespace model { namespace station_info
{
    // functions

    boost::unit_test::test_suite* grade::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::model::station_info::grade");

        p_suite->add(BOOST_TEST_CASE(instance));
        p_suite->add(BOOST_TEST_CASE(name));

        return p_suite;
    }

    void grade::instance()
    {
        BOOST_CHECKPOINT("");

        bobura::model::station_info::grade<std::string>::instance();
        bobura::model::station_info::local<std::string>::instance();
        bobura::model::station_info::major<std::string>::instance();
        bobura::model::station_info::local_terminal<std::string>::instance();
        bobura::model::station_info::major_terminal<std::string>::instance();

        bobura::model::station_info::grade<std::wstring>::instance();
        bobura::model::station_info::local<std::wstring>::instance();
        bobura::model::station_info::major<std::wstring>::instance();
        bobura::model::station_info::local_terminal<std::wstring>::instance();
        bobura::model::station_info::major_terminal<std::wstring>::instance();
    }

    void grade::name()
    {
        BOOST_CHECKPOINT("");

        BOOST_CHECK(
            bobura::model::station_info::grade<
                std::string
            >::instance().name() == std::string("local")
        );
        BOOST_CHECK(
            bobura::model::station_info::local<
                std::string
            >::instance().name() == std::string("local")
        );
        BOOST_CHECK(
            bobura::model::station_info::major<
                std::string
            >::instance().name() == std::string("major")
        );
        BOOST_CHECK(
            bobura::model::station_info::local_terminal<
                std::string
            >::instance().name() == std::string("local terminal")
        );
        BOOST_CHECK(
            bobura::model::station_info::major_terminal<
                std::string
            >::instance().name() == std::string("major terminal")
        );

        BOOST_CHECK(
            bobura::model::station_info::grade<
                std::wstring
            >::instance().name() == std::wstring(L"local")
        );
        BOOST_CHECK(
            bobura::model::station_info::local<
                std::wstring
            >::instance().name() == std::wstring(L"local")
        );
        BOOST_CHECK(
            bobura::model::station_info::major<
                std::wstring
            >::instance().name() == std::wstring(L"major")
        );
        BOOST_CHECK(
            bobura::model::station_info::local_terminal<
                std::wstring
            >::instance().name() == std::wstring(L"local terminal")
        );
        BOOST_CHECK(
            bobura::model::station_info::major_terminal<
                std::wstring
            >::instance().name() == std::wstring(L"major terminal")
        );
    }


}}}
