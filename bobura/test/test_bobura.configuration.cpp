/*! \file
    \brief Test of class bobura::configuration.

    Copyright (C) 2007 kaoru

    $Id$
*/

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

        p_suite->add(BOOST_TEST_CASE(test_bobura::configuration::construction));

        return p_suite;
    }

    void configuration::options()
    {

    }

    void configuration::construction()
    {

    }

}
