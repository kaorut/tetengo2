/*! \file
    \brief Test of class bobura::configuration.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <cstddef>

#include <boost/program_options.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.configuration.h"

#include "test_bobura.configuration.h"


namespace test_bobura
{
    // functions

    boost::unit_test::test_suite* configuration::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::cofiguration");

        p_suite->add(BOOST_TEST_CASE(options));
        p_suite->add(BOOST_TEST_CASE(construction));

        return p_suite;
    }

    void configuration::options()
    {
        BOOST_CHECKPOINT("");

        const boost::program_options::options_description options =
            bobura::configuration::options();

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

    void configuration::construction()
    {
        BOOST_CHECKPOINT("");

        const boost::program_options::variables_map variables_map;
        const bobura::configuration configuration(variables_map);
    }


}
