/*! \file
    \brief Test of class bobura::settings.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <string>
//#include <utility>
//#include <vector>

#include <boost/test/unit_test.hpp>

#include "bobura.settings.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(settings)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::wstring> arguments;
        const bobura::settings<std::wstring> settings(std::move(arguments));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
