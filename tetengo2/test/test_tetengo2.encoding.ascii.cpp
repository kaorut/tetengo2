/*! \file
    \brief Test of class tetengo2::encoding::ascii.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

//#include <stdexcept>
//#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.encoding.ascii.h"


namespace
{
    // variables

    // "\n 0Aa~[DEL]"
    const wchar_t utf16_ascii[] = {
        0x000A, 0x0020, 0x0030, 0x0041, 0x0061, 0x007E, 0x007F, 0x0000
    };

    // "\n 0Aa~[DEL]"
    const unsigned char ascii_ascii[] = {
        0x0A, 0x20, 0x30, 0x41, 0x61, 0x7E, 0x7F, 0x00
    };

    // Non-ASCII characters
    const wchar_t utf16_nonascii[] = {
        0x0080, 0x00FF, 0x0000
    };

    // Non-ASCII characters
    const unsigned char ascii_nonascii[] = {
        0x3F, 0x3F, 0x00
    };

    // Non-ASCII characters
    const unsigned char nonascii[] = {
        0x80, 0xFF, 0x00
    };

}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(encoding)
BOOST_AUTO_TEST_SUITE(ascii)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        tetengo2::encoding::ascii encoding;
    }

    BOOST_AUTO_TEST_CASE(swap)
    {
        BOOST_TEST_PASSPOINT();

        tetengo2::encoding::ascii encoding1;
        tetengo2::encoding::ascii encoding2;

        encoding1.swap(encoding2);
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        tetengo2::encoding::ascii encoding1;
        const tetengo2::encoding::ascii encoding2;

        encoding1 = encoding2;
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        const tetengo2::encoding::ascii encoding1;
        const tetengo2::encoding::ascii encoding2;

        BOOST_CHECK(encoding1 == encoding2);
    }

    BOOST_AUTO_TEST_CASE(from_pivot)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::wstring pivot(utf16_ascii);
            const std::string string(
                ascii_ascii, ascii_ascii + sizeof(ascii_ascii) - 1
            );

            const tetengo2::encoding::ascii encoding;
            const std::string result = encoding.from_pivot(pivot);

            BOOST_CHECK(result == string);
        }
        {
            const std::wstring pivot(utf16_nonascii);
            const std::string string(
                ascii_nonascii, ascii_nonascii + sizeof(ascii_nonascii) - 1
            );

            const tetengo2::encoding::ascii encoding;
            const std::string result = encoding.from_pivot(pivot);

            BOOST_CHECK(result == string);
        }
    }

    BOOST_AUTO_TEST_CASE(to_pivot)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::wstring pivot(utf16_ascii);
            const std::string string(
                ascii_ascii, ascii_ascii + sizeof(ascii_ascii) - 1
            );

            const tetengo2::encoding::ascii encoding;
            const std::wstring result = encoding.to_pivot(string);

            BOOST_CHECK(result == pivot);
        }
        {
            const std::string string(
                nonascii, nonascii + sizeof(nonascii) - 1
            );

            const tetengo2::encoding::ascii encoding;
            BOOST_CHECK_THROW(
                encoding.to_pivot(string), std::invalid_argument
            );
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()