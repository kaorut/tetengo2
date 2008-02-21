/*! \file
    \brief Test of class tetengo2::win32::encode.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

#include <string>

//#include <boost/test/unit_test.hpp>

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


}}
