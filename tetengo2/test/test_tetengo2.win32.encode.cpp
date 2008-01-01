/*! \file
    \brief Test of class tetengo2::win32::encode.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.win32.encode.h"

#include "test_tetengo2.win32.encode.h"


namespace test_tetengo2 { namespace win32
{
    // functions

    boost::unit_test::test_suite* encode::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::win32::encode");

        p_suite->add(BOOST_TEST_CASE(operator_paren));

        return p_suite;
    }

    void encode::operator_paren()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}
