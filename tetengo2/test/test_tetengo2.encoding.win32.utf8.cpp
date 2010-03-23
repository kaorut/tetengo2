/*! \file
    \brief Test of class tetengo2::encoding::win32::utf8.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.encoding.win32.utf8.h"


namespace
{
    // variables

    // four-character hiragana: "tetengo"
    const wchar_t utf16_tetengo[] = {
        0x3066,
        0x3066,
        0x3093,
        0x3054,
        0x0000
    };

    // four-character hiragana: "tetengo"
    const unsigned char utf8_tetengo[] = {
        0xE3, 0x81, 0xA6,
        0xE3, 0x81, 0xA6,
        0xE3, 0x82, 0x93,
        0xE3, 0x81, 0x94,
        0x00
    };

    // four-character kanji: "mori o-gai shikaru"
    // The codepoint of "shikaru" is U+20B9F.
    const wchar_t utf16_moriogaishikaru[] = {
        0x68EE,
        0x9DD7,
        0x5916,
        0xD842, 0xDF9F,
        0x0000
    };

    // four-character kanji: "mori o-gai shikaru"
    const unsigned char utf8_moriogaishikaru[] = {
        0xE6, 0xA3, 0xAE,
        0xE9, 0xB7, 0x97,
        0xE5, 0xA4, 0x96,
        0xF0, 0xA0, 0xAE, 0x9F,
        0x00
    };

}

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
        BOOST_TEST_PASSPOINT();

        {
            const std::wstring pivot(utf16_tetengo);
            const std::string string(
                utf8_tetengo, utf8_tetengo + sizeof(utf8_tetengo) - 1
            );

            const tetengo2::encoding::win32::utf8 encoding;
            const std::string result = encoding.from_pivot(pivot);

            BOOST_CHECK(result == string);
        }
        {
            const std::wstring pivot(utf16_moriogaishikaru);
            const std::string string(
                utf8_moriogaishikaru,
                utf8_moriogaishikaru + sizeof(utf8_moriogaishikaru) - 1
            );

            const tetengo2::encoding::win32::utf8 encoding;
            const std::string result = encoding.from_pivot(pivot);

            BOOST_CHECK(result == string);
        }
    }

    BOOST_AUTO_TEST_CASE(to_pivot)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::wstring pivot(utf16_tetengo);
            const std::string string(
                utf8_tetengo, utf8_tetengo + sizeof(utf8_tetengo) - 1
            );

            const tetengo2::encoding::win32::utf8 encoding;
            const std::wstring result = encoding.to_pivot(string);

            BOOST_CHECK(result == pivot);
        }
        {
            const std::wstring pivot(utf16_moriogaishikaru);
            const std::string string(
                utf8_moriogaishikaru,
                utf8_moriogaishikaru + sizeof(utf8_moriogaishikaru) - 1
            );

            const tetengo2::encoding::win32::utf8 encoding;
            const std::wstring result = encoding.to_pivot(string);

            BOOST_CHECK(result == pivot);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
