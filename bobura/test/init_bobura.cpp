/*! \file
    \brief Test of namespace bobura.

    Copyright (C) 2007 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "init_bobura.h"
#include "test_bobura.bobura.h"
#include "test_bobura.configuration.h"


namespace test_bobura
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura");

        p_suite->add(test_bobura::bobura::suite());
        p_suite->add(test_bobura::configuration::suite());

        return p_suite;
    }

}
