/*! \file
    \brief Test of class bobura::settings.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <cstddef>

#include <boost/program_options.hpp>
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

        p_suite->add(BOOST_TEST_CASE(options));
        p_suite->add(BOOST_TEST_CASE(construction));

        return p_suite;
    }

    void settings::options()
    {
        BOOST_CHECKPOINT("");

        const boost::program_options::options_description options =
            bobura::settings::options();

        {
            const boost::program_options::option_description* const p_option =
                options.find_nothrow("help", false);
            BOOST_CHECK(p_option != NULL);
        }
        {
            const boost::program_options::option_description* const p_option =
                options.find_nothrow("h", true);
            BOOST_CHECK(p_option != NULL);
        }
    }

    void settings::construction()
    {
        BOOST_CHECKPOINT("");

        const boost::program_options::variables_map variables_map;
        const bobura::settings settings(variables_map);
    }


}
