/*! \file
    \brief Test of class bobura::settings.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <string>
//#include <utility>
//#include <vector>

#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.settings.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(settings)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const bobura::settings<std::wstring, boost::filesystem::path>
        settings(std::move(arguments), std::move(path));
    }

    BOOST_AUTO_TEST_CASE(base_path)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::wstring> arguments;
        boost::filesystem::path path(L"path/to");
        const bobura::settings<std::wstring, boost::filesystem::path>
        settings(std::move(arguments), std::move(path));

        BOOST_CHECK(
            settings.base_path() == boost::filesystem::path(L"path/to")
        );
    }

    BOOST_AUTO_TEST_CASE(message_directory_path)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::wstring> arguments;
        boost::filesystem::path path(L"path/to");
        const bobura::settings<std::wstring, boost::filesystem::path>
        settings(std::move(arguments), std::move(path));

        BOOST_CHECK(
            settings.message_directory_path() ==
            boost::filesystem::path(L"path/to/messages")
        );
    }

    BOOST_AUTO_TEST_CASE(image_directory_path)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::wstring> arguments;
        boost::filesystem::path path(L"path/to");
        const bobura::settings<std::wstring, boost::filesystem::path>
        settings(std::move(arguments), std::move(path));

        BOOST_CHECK(
            settings.image_directory_path() ==
            boost::filesystem::path(L"path/to/images")
        );
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
