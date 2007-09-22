/*! \file
    \brief The initialization of test of tetengo2.

    Copyright (C) 2007 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>


boost::unit_test::test_suite* init_unit_test_suite(
    const int    /* argc */,
    char** const /* argv */
)
{
    boost::unit_test::test_suite* const p_suite = BOOST_TEST_SUITE("init");

    return p_suite;
}
