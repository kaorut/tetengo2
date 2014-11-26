/*! \file
    \brief Test of class tetengo2::text::encoding::utf8.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_tetengo2.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::type_list::detail_for_test;

    using encoding_details_type = detail_type_list_type::encoding_type;

    using pivot_type = encoding_details_type::pivot_type;

    using string_type = encoding_details_type::utf8_string_type;

    using encoding_type = tetengo2::text::encoding::utf8<encoding_details_type>;


    // functions

    string_type::value_type tc(const unsigned char c)
    {
        return static_cast<string_type::value_type>(c);
    }


    // data

#if BOOST_OS_WINDOWS
    const pivot_type pivot{
        0x68EE,         // MORI in kanji
        0x9DD7,         // OU in kanji
        0x5916,         // GAI in kanji
        0xD842, 0xDF9F, // SHIKARU in kanji
    }; // in UTF-16
#else
    const pivot_type pivot{
        tc(0xE6), tc(0xA3), tc(0xAE),           // MORI in kanji
        tc(0xE9), tc(0xB7), tc(0x97),           // OU in kanji
        tc(0xE5), tc(0xA4), tc(0x96),           // GAI in kanji
        tc(0xF0), tc(0xA0), tc(0xAE), tc(0x9F), // SHIKARU in kanji
    }; // in UTF-8
#endif

    const pivot_type empty_pivot{};

    const string_type utf8_{
        tc(0xE6), tc(0xA3), tc(0xAE),           // MORI in kanji
        tc(0xE9), tc(0xB7), tc(0x97),           // OU in kanji
        tc(0xE5), tc(0xA4), tc(0x96),           // GAI in kanji
        tc(0xF0), tc(0xA0), tc(0xAE), tc(0x9F), // SHIKARU in kanji
    }; // in CP932

    const string_type empty_utf8_{};


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(text)
BOOST_AUTO_TEST_SUITE(encoding)
BOOST_AUTO_TEST_SUITE(utf8)
    // test cases

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        const encoding_type encoding1{};
        const encoding_type encoding2{};

        BOOST_CHECK(encoding1 == encoding2);
    }

    BOOST_AUTO_TEST_CASE(from_pivot)
    {
        BOOST_TEST_PASSPOINT();

        {
            const encoding_type encoding{};
            const auto result = encoding.from_pivot(pivot);

            BOOST_CHECK(result == utf8_);
        }
        {
            const encoding_type encoding{};
            const auto result = encoding.from_pivot(empty_pivot);

            BOOST_CHECK(result == empty_utf8_);
        }
    }

    BOOST_AUTO_TEST_CASE(to_pivot)
    {
        BOOST_TEST_PASSPOINT();

        {
            const encoding_type encoding{};
            const auto result = encoding.to_pivot(utf8_);

            BOOST_CHECK(result == pivot);
        }
        {
            const encoding_type encoding{};
            const auto result = encoding.to_pivot(empty_utf8_);

            BOOST_CHECK(result == empty_pivot);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
