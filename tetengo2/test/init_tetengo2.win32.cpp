/*! \file
    \brief Test of namespace tetengo2::win32.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

#include "init_tetengo2.win32.h"
#include "test_tetengo2.win32.encode.h"


namespace test_tetengo2 { namespace win32
{
    // functions

    boost::unit_test::test_suite* suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::win32");

        p_suite->add(encode::suite());

        return p_suite;
    }


}}
