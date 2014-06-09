/*! \file
    \brief Test of class tetengo2::text::encoding::cp932.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/predef.h>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_tetengo2.detail_type_list.h"


namespace
{
    // types

    using encoding_details_type =
        boost::mpl::at<test_tetengo2::detail_type_list, test_tetengo2::type::detail::encoding>::type;

    using pivot_type = encoding_details_type::pivot_type;

    using string_type = encoding_details_type::cp932_string_type;

    using encoding_type = tetengo2::text::encoding::cp932<encoding_details_type>;


    // function

    string_type::value_type tc(const unsigned char c)
    {
        return static_cast<string_type::value_type>(c);
    }


    // data

#if BOOST_OS_WINDOWS
    const pivot_type pivot{
        0x304F, // KU in fullwidth hiragana
        0x307E, // MA in fullwidth hiragana
        0xFF93, // MO in halfwidth katakana
        0xFF9D, // N  in halfwidth katakana
    }; // in UTF-16
#else
    const pivot_type pivot{
        tc(0xE3), tc(0x81), tc(0x8F), // KU in fullwidth hiragana
        tc(0xE3), tc(0x81), tc(0xBE), // MA in fullwidth hiragana
        tc(0xEF), tc(0xBE), tc(0x93), // MO in halfwidth katakana
        tc(0xEF), tc(0xBE), tc(0x9D), // N  in halfwidth katakana
    }; // in UTF-8
#endif

    const string_type cp932_{
        tc(0x82), tc(0xAD), // KU in fullwidth hiragana
        tc(0x82), tc(0xDC), // MA in fullwidth hiragana
        tc(0xD3),           // MO in halfwidth katakana
        tc(0xDD),           // N  in halfwidth katakana
    }; // in CP932

}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(text)
BOOST_AUTO_TEST_SUITE(encoding)
BOOST_AUTO_TEST_SUITE(cp932)
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

            BOOST_CHECK(result == cp932_);
        }
    }

    BOOST_AUTO_TEST_CASE(to_pivot)
    {
        BOOST_TEST_PASSPOINT();

        {
            const encoding_type encoding{};
            const auto result = encoding.to_pivot(cp932_);

            BOOST_CHECK(result == pivot);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
