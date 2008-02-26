/*! \file
    \brief The initialization of test of bobura_model.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.test.h"

//#include <boost/test/unit_test.hpp>

#include "init_bobura.model.h"


boost::unit_test::test_suite* init_unit_test_suite(
    const int    /* argc */,
    char** const /* argv */
)
{
    boost::unit_test::test_suite* const p_suite = BOOST_TEST_SUITE("init");

    p_suite->add(test_bobura::model::suite());

    return p_suite;
}
