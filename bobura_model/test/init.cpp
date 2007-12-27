/*! \file
    \brief The initialization of test of bobura_model.

    Copyright (C) 2007 kaoru

    $Id: init.cpp 107 2007-09-22 06:24:49Z kaoru $
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
