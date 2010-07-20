/*! \file
    \brief Test of class bobura::model::station_info::grade.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <string>

#include <boost/test/unit_test.hpp>

#include "bobura.model.station_info.grade.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(station_info)
BOOST_AUTO_TEST_SUITE(grade)
    // test cases

    BOOST_AUTO_TEST_CASE(instance)
    {
        BOOST_TEST_PASSPOINT();

        bobura::model::station_info::local<std::string>::instance();
        bobura::model::station_info::principal<std::string>::instance();
        bobura::model::station_info::local_terminal<std::string>::instance();
        bobura::model::station_info::principal_terminal<
            std::string
        >::instance();

        bobura::model::station_info::local<std::wstring>::instance();
        bobura::model::station_info::principal<std::wstring>::instance();
        bobura::model::station_info::local_terminal<std::wstring>::instance();
        bobura::model::station_info::principal_terminal<
            std::wstring
        >::instance();
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_CHECK(
            bobura::model::station_info::local<
                std::string
            >::instance().name() == std::string("local")
        );
        BOOST_CHECK(
            bobura::model::station_info::principal<
                std::string
            >::instance().name() == std::string("principal")
        );
        BOOST_CHECK(
            bobura::model::station_info::local_terminal<
                std::string
            >::instance().name() == std::string("local terminal")
        );
        BOOST_CHECK(
            bobura::model::station_info::principal_terminal<
                std::string
            >::instance().name() == std::string("principal terminal")
        );

        BOOST_CHECK(
            bobura::model::station_info::local<
                std::wstring
            >::instance().name() == std::wstring(L"local")
        );
        BOOST_CHECK(
            bobura::model::station_info::principal<
                std::wstring
            >::instance().name() == std::wstring(L"principal")
        );
        BOOST_CHECK(
            bobura::model::station_info::local_terminal<
                std::wstring
            >::instance().name() == std::wstring(L"local terminal")
        );
        BOOST_CHECK(
            bobura::model::station_info::principal_terminal<
                std::wstring
            >::instance().name() == std::wstring(L"principal terminal")
        );
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
