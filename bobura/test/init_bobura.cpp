/*! \file
    \brief Test of namespace bobura.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.test.h"

//#include <boost/test/unit_test.hpp>

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

        p_suite->add(bobura::suite());
        p_suite->add(configuration::suite());

        return p_suite;
    }


}
