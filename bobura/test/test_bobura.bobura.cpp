/*! \file
    \brief Test of bobura.bobura.

    Copyright (C) 2007 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "bobura.bobura.h"

#include "test_bobura.bobura.h"


namespace test_bobura
{
    boost::unit_test::test_suite* bobura::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("bobura::bobura");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(run));

        return p_suite;
    }

    void bobura::construction()
    {
    
    }

    void bobura::run()
    {
    
    }

}
