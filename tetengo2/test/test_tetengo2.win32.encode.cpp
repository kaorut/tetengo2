/*! \file
    \brief Test of class tetengo2::win32::encode.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.win32.encode.h"


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(win32)
BOOST_AUTO_TEST_SUITE(encode)
    // test cases

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_CHECKPOINT("");

        {
            const std::string converted =
                tetengo2::win32::encode<std::string, std::string>()("");

            BOOST_CHECK(converted.empty());
        }
        {
            const std::string converted =
                tetengo2::win32::encode<std::string, std::wstring>()(L"");

            BOOST_CHECK(converted.empty());
        }
        {
            const std::wstring converted =
                tetengo2::win32::encode<std::wstring, std::string>()("");

            BOOST_CHECK(converted.empty());
        }
        {
            const std::wstring converted =
                tetengo2::win32::encode<std::wstring, std::wstring>()(L"");

            BOOST_CHECK(converted.empty());
        }

        {
            const std::string converted =
                tetengo2::win32::encode<std::string, std::string>()("A");

            BOOST_CHECK_EQUAL(converted.length(), 1U);
            BOOST_CHECK(converted == std::string("A"));
        }
        {
            const std::string converted =
                tetengo2::win32::encode<std::string, std::wstring>()(L"A");

            BOOST_CHECK_EQUAL(converted.length(), 1U);
            BOOST_CHECK(converted == std::string("A"));
        }
        {
            const std::wstring converted =
                tetengo2::win32::encode<std::wstring, std::string>()("A");

            BOOST_CHECK_EQUAL(converted.length(), 1U);
            BOOST_CHECK(converted == std::wstring(L"A"));
        }
        {
            const std::wstring converted =
                tetengo2::win32::encode<std::wstring, std::wstring>()(L"A");

            BOOST_CHECK_EQUAL(converted.length(), 1U);
            BOOST_CHECK(converted == std::wstring(L"A"));
        }

        // \x93 \xEC (Code Page 932), \x5357 (UTF-16) = 'minami' in Kanji
        // \x89 \x5A (Code Page 932), \x74DC (UTF-16) = 'uri' in Kanji
        {
            const std::string converted =
                tetengo2::win32::encode<std::string, std::string>()(
                    "\x93\xEC\x89\x5A"
                );

            BOOST_CHECK_EQUAL(converted.length(), 4U);
            BOOST_CHECK(converted == std::string("\x93\xEC\x89\x5A"));
        }
        {
            const std::string converted =
                tetengo2::win32::encode<std::string, std::wstring>()(
                    L"\x5357\x74DC"
                );

            BOOST_CHECK_EQUAL(converted.length(), 4U);
            BOOST_CHECK(converted == std::string("\x93\xEC\x89\x5A"));
        }
        {
            const std::wstring converted =
                tetengo2::win32::encode<std::wstring, std::string>()(
                    "\x93\xEC\x89\x5A"
                );

            BOOST_CHECK_EQUAL(converted.length(), 2U);
            BOOST_CHECK(converted == std::wstring(L"\x5357\x74DC"));
        }
        {
            const std::wstring converted =
                tetengo2::win32::encode<std::wstring, std::wstring>()(
                    L"\x5357\x74DC"
                );

            BOOST_CHECK_EQUAL(converted.length(), 2U);
            BOOST_CHECK(converted == std::wstring(L"\x5357\x74DC"));
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
