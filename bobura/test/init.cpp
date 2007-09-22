/*! \file
    \brief The initialization of test of bobura.

    Copyright (C) 2007 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "test_bobura.bobura.h"


boost::unit_test::test_suite* init_unit_test_suite(
    const int    /* argc */,
    char** const /* argv */
)
{
    boost::unit_test::test_suite* const p_suite =
        BOOST_TEST_SUITE("Test of bobura");

    p_suite->add(test_bobura::bobura::suite());

    return p_suite;
}
