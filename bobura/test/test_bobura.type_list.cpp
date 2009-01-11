/*! \file
    \brief Test of class bobura::type_list.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"

#include "test_bobura.type_list.h"


namespace test_bobura
{
    // functions

    boost::unit_test::test_suite* type_list::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_bobura::type_list");

        return p_suite;
    }


}
