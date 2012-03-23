/*! \file
    \brief Test of class tetengo2::text.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.text.h"


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    // test cases

    BOOST_AUTO_TEST_CASE(text_)
    {
        {
            const std::string string(TETENGO2_TEXT("hoge"));
            BOOST_CHECK(string == "hoge");
        }
        {
            const std::wstring string(TETENGO2_TEXT("hoge"));
            BOOST_CHECK(string == L"hoge");
        }
    }


BOOST_AUTO_TEST_SUITE_END()
