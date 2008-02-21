/*! \file
    \brief Test of class tetengo2::generator.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

//#include <boost/test/unit_test.hpp>

#include "tetengo2.generator.h"

#include "test_tetengo2.generator.h"


namespace test_tetengo2
{
    // functions

    boost::unit_test::test_suite* generator::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::tetengo2");

        return p_suite;
    }


}
