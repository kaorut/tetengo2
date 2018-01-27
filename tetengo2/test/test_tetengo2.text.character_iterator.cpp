/*! \file
    \brief Test of class tetengo2::text::character_iterator.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/text/character_iterator.h>
#include <tetengo2/text/encoding/polymorphic.h>
#include <tetengo2/text/encoding/utf8.h>


namespace
{
    // types

    using string_type = std::string;

    using character_iterator_type = tetengo2::text::character_iterator<string_type>;


    // functions

    tetengo2::text::encoding::polymorphic<string_type> make_encoding()
    {
        return tetengo2::text::encoding::make_polymorphic<tetengo2::text::encoding::utf8>();
    }

    string_type::value_type tc(const unsigned char c)
    {
        return static_cast<string_type::value_type>(c);
    }


    // data

    const string_type test_string{
        tc(0xE6), tc(0xA3), tc(0xAE),           // MORI in kanji
        tc(0x41),                               // A
        tc(0x42),                               // B
        tc(0xF0), tc(0xA0), tc(0xAE), tc(0x9F), // SHIKARU in kanji
        tc(0x34),                               // 4
    };

    const string_type string_mori{
        tc(0xE6), tc(0xA3), tc(0xAE),           // MORI in kanji
    };

    const string_type string_a{
        tc(0x41),                               // A
    };

    const string_type string_b{
        tc(0x42),                               // B
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

        {
            const character_iterator_type iterator{};
        }
        {
            const character_iterator_type iterator{ test_string, make_encoding() };
        }
        {
            const character_iterator_type iterator1{ test_string, make_encoding() };
            const character_iterator_type iterator2{ iterator1 };

            const auto value = *iterator2;
            BOOST_TEST(value == string_mori);
        }
        {
            character_iterator_type iterator1{ test_string, make_encoding() };
            const character_iterator_type iterator2{ std::move(iterator1) };

            const auto value = *iterator2;
            BOOST_TEST(value == string_mori);
        }
    }

    BOOST_AUTO_TEST_CASE(dereference)
    {
        BOOST_TEST_PASSPOINT();

        character_iterator_type iterator{ test_string, make_encoding() };

        const auto value = *iterator;
        BOOST_TEST(value == string_mori);
    }

    BOOST_AUTO_TEST_CASE(equal)
    {
        BOOST_TEST_PASSPOINT();

        character_iterator_type iterator1{ test_string, make_encoding() };

        BOOST_CHECK(iterator1 == iterator1);

        character_iterator_type iterator2{ test_string, make_encoding() };

        BOOST_CHECK(iterator1 == iterator2);

        ++iterator2;

        BOOST_CHECK(iterator1 != iterator2);

        character_iterator_type iterator3{ string_mori, make_encoding() };

        BOOST_CHECK(iterator1 != iterator3);

        ++iterator1;

        BOOST_CHECK(iterator1 == iterator2);

        const character_iterator_type iterator4{};
        const character_iterator_type iterator5{};

        BOOST_CHECK(iterator4 == iterator5);
    }

    BOOST_AUTO_TEST_CASE(increment)
    {
        BOOST_TEST_PASSPOINT();

        character_iterator_type iterator{ test_string, make_encoding() };

        {
            const auto value = *iterator;
            BOOST_TEST(value == string_mori);
        }

        ++iterator;

        {
            const auto value = *iterator;
            BOOST_TEST(value == string_a);
        }

        ++iterator;

        {
            const auto value = *iterator;
            BOOST_TEST(value == string_b);
        }

        ++iterator;

        {
            const auto value = *iterator;
            BOOST_TEST(value == string_shikaru);
        }

        ++iterator;

        {
            const auto value = *iterator;
            BOOST_TEST(value == string_4);
        }

        ++iterator;

        BOOST_CHECK(iterator == character_iterator_type{});

        BOOST_CHECK_THROW(++iterator, std::logic_error);
    }


BOOST_AUTO_TEST_SUITE_END()
    // test cases

    BOOST_AUTO_TEST_CASE(make_character_iterator)
    {
        BOOST_TEST_PASSPOINT();

        {
            tetengo2::text::make_character_iterator<string_type>();
        }
        {
            const string_type string;
            tetengo2::text::make_character_iterator(string, make_encoding());
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
