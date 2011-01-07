/*! \file
    \brief Test of class bobura::settings.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <string>
//#include <utility>
//#include <vector>

//#define BOOST_FILESYSTEM_VERSION 3
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


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
