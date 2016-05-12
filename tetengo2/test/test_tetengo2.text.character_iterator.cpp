/*! \file
    \brief Test of class tetengo2::text::character_iterator.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_tetengo2.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::type_list::detail_for_test;

    using encoding_details_type = detail_type_list_type::encoding_type;

    using string_type = encoding_details_type::utf8_string_type;

    using utf8_encoder_type =
        tetengo2::text::encoder<
            tetengo2::text::encoding::utf8<encoding_details_type>,
            tetengo2::text::encoding::utf8<encoding_details_type>
        >;

    using character_iterator_type = tetengo2::text::character_iterator<string_type, utf8_encoder_type>;


    // functions

    string_type::value_type tc(const unsigned char c)
    {
        return static_cast<string_type::value_type>(c);
    }


    // data

    const string_type test_string{
        tc(0xE6), tc(0xA3), tc(0xAE),           // MORI in kanji
        tc(0x41),                               // A
        tc(0xF0), tc(0xA0), tc(0xAE), tc(0x9F), // SHIKARU in kanji
        tc(0x34),                               // 4
    };

    const string_type string_mori{
        tc(0xE6), tc(0xA3), tc(0xAE),           // MORI in kanji
    };

    const string_type string_a{
        tc(0x41),                               // A
    };

    const string_type string_shikaru{
        tc(0xF0), tc(0xA0), tc(0xAE), tc(0x9F), // SHIKARU in kanji
    };

    const string_type string_4{
        tc(0x34),                               // 4
    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(text)
BOOST_AUTO_TEST_SUITE(character_iterator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const character_iterator_type iterator{ test_string, utf8_encoder_type{} };
    }

    BOOST_AUTO_TEST_CASE(dereference)
    {
        BOOST_TEST_PASSPOINT();

        character_iterator_type iterator{ test_string, utf8_encoder_type{} };

        const auto value = *iterator;
        BOOST_TEST(value == string_mori);
    }

    BOOST_AUTO_TEST_CASE(equal)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Implement it.");
    }

    BOOST_AUTO_TEST_CASE(increment)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Implement it.");
    }


BOOST_AUTO_TEST_SUITE_END()
    // test cases

    BOOST_AUTO_TEST_CASE(make_character_iterator)
    {
        BOOST_TEST_PASSPOINT();

        const string_type string;
        tetengo2::text::make_character_iterator(string, utf8_encoder_type{});
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
