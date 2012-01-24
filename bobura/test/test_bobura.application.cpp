/*! \file
    \brief Test of class bobura::application.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <string>
//#include <utility>
//#include <vector>

//#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.types.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(application)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        const application_type application(settings);
    }

    BOOST_AUTO_TEST_CASE(run)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        application_type application(settings);

        BOOST_CHECK_EQUAL(application.run(), 0);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
