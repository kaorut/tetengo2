/*! \file
    \brief Test of class bobura::type_list.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <cstddef>

#include <boost/program_options.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"

#include "test_bobura.type_list.h"


namespace test_bobura
{
    // functions

    boost::unit_test::test_suite* type_list::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::cofiguration");

        p_suite->add(BOOST_TEST_CASE(options));
        p_suite->add(BOOST_TEST_CASE(construction));

        return p_suite;
    }

    void type_list::options()
    {
        BOOST_CHECKPOINT("");

        const boost::program_options::options_description options =
            bobura::type_list::options();

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

    void type_list::construction()
    {
        BOOST_CHECKPOINT("");

        const boost::program_options::variables_map variables_map;
        const bobura::type_list type_list(variables_map);
    }


}
