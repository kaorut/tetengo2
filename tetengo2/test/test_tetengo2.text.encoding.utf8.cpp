/*! \file
    \brief Test of class tetengo2::text::encoding::utf8.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2/text/encoding/utf8.h>


namespace
{
    // types

    using encoding_type = tetengo2::text::encoding::utf8;

    using pivot_type = encoding_type::pivot_type;

    using string_type = encoding_type::string_type;


    // functions

    string_type::value_type tc(const unsigned char c)
    {
        return static_cast<string_type::value_type>(c);
    }


    // data

#if BOOST_OS_WINDOWS
#   pragma warning (push)
#   pragma warning (disable: 4592)
    const pivot_type pivot{
        0x68EE,         // MORI in kanji
        0x9DD7,         // OU in kanji
        0x5916,         // GAI in kanji
        0xD842, 0xDF9F, // SHIKARU in kanji
    }; // in UTF-16
#   pragma warning (pop)
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

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const encoding_type encoding{};
    }

    BOOST_AUTO_TEST_CASE(name)
    {
        BOOST_TEST_PASSPOINT();

        const encoding_type encoding{};

        BOOST_CHECK(encoding.name() == "UTF-8");
    } 

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
