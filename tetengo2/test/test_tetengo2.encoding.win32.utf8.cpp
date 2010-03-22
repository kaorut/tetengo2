/*! \file
    \brief Test of class tetengo2::encoding::win32::utf8.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.encoding.win32.utf8.h"


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(encoding)
BOOST_AUTO_TEST_SUITE(win32)
BOOST_AUTO_TEST_SUITE(utf8)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        tetengo2::encoding::win32::utf8 encoding;
    }

    BOOST_AUTO_TEST_CASE(swap)
    {
        BOOST_TEST_PASSPOINT();

        tetengo2::encoding::win32::utf8 encoding1;
        tetengo2::encoding::win32::utf8 encoding2;

        encoding1.swap(encoding2);
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        tetengo2::encoding::win32::utf8 encoding1;
        const tetengo2::encoding::win32::utf8 encoding2;

        encoding1 = encoding2;
    }

    BOOST_AUTO_TEST_CASE(from_pivot)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(to_pivot)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
