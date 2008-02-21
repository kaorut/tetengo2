/*! \file
    \brief The initialization of test of tetengo2.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

//#include <boost/test/unit_test.hpp>

#include "init_tetengo2.h"


boost::unit_test::test_suite* init_unit_test_suite(
    const int    /* argc */,
    char** const /* argv */
)
{
    boost::unit_test::test_suite* const p_suite = BOOST_TEST_SUITE("init");

    p_suite->add(test_tetengo2::suite());

    return p_suite;
}
