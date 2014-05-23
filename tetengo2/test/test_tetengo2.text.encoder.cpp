/*! \file
    \brief Test of class tetengo2::text::encoder.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2/detail/stub/encoding.h>


namespace
{
    // types

    using encoding_details_type = tetengo2::detail::stub::encoding;

    using encoding_type = tetengo2::text::encoding::ascii<encoding_details_type>;

    using encoder_type = tetengo2::text::encoder<encoding_type, encoding_type>;

}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(text)
BOOST_AUTO_TEST_SUITE(encoder)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const encoder_type encoder{};
        }
        {
            const encoding_type encoding1{};
            const encoding_type encoding2{};
            const encoder_type encoder{ encoding1, encoding2 };
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        const encoding_type encoding1{};
        const encoding_type encoding2{};
        encoder_type encoder1{ encoding1, encoding2 };
        encoder_type encoder2{ encoding1, encoding2 };

        BOOST_CHECK(encoder1 == encoder2);
    }

    BOOST_AUTO_TEST_CASE(internal_encoding)
    {
        BOOST_TEST_PASSPOINT();

        const encoding_type encoding1{};
        const encoding_type encoding2{};
        const encoder_type encoder{ encoding1, encoding2 };
    }

    BOOST_AUTO_TEST_CASE(external_encoding)
    {
        BOOST_TEST_PASSPOINT();

        const encoding_type encoding1{};
        const encoding_type encoding2{};
        const encoder_type encoder{ encoding1, encoding2 };
    }

    BOOST_AUTO_TEST_CASE(encode)
    {
        BOOST_TEST_PASSPOINT();

        const encoder_type::internal_string_type internal_string{ TETENGO2_TEXT("Tetengo2") };
        const encoder_type::external_string_type external_string{ TETENGO2_TEXT("Tetengo2") };

        const encoding_type encoding1{};
        const encoding_type encoding2{};
        const encoder_type encoder{ encoding1, encoding2 };

        BOOST_CHECK(encoder.encode(internal_string) == external_string);
    }

    BOOST_AUTO_TEST_CASE(decode)
    {
        BOOST_TEST_PASSPOINT();

        const encoder_type::internal_string_type internal_string{ TETENGO2_TEXT("Tetengo2") };
        const encoder_type::external_string_type external_string{ TETENGO2_TEXT("Tetengo2") };

        const encoding_type encoding1{};
        const encoding_type encoding2{};
        const encoder_type encoder{ encoding1, encoding2 };

        BOOST_CHECK(encoder.decode(external_string) == internal_string);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
