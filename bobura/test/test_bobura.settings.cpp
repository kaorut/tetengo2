/*! \file
    \brief Test of class bobura::settings.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>

#include "bobura.settings.h"

#include "test_bobura.settings.h"


namespace test_bobura
{
    // functions

    boost::unit_test::test_suite* settings::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::settings");

        p_suite->add(BOOST_TEST_CASE(construction));

        return p_suite;
    }

    void settings::construction()
    {
        BOOST_CHECKPOINT("");

        const std::vector<std::wstring> arguments;
        const bobura::settings<std::wstring> settings(
            arguments.begin(), arguments.end()
        );
    }


}
