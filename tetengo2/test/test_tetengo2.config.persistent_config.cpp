/*! \file
    \brief Test of class tetengo2::config::persistent_config.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>
#include <boost/variant.hpp>

#include <tetengo2.h>

#include "test_tetengo2.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::type_list::common;

    using string_type = common_type_list_type::string_type;

    using uint_type = common_type_list_type::size_type;

    using encoding_details_type = detail_type_list_type::encoding_type;

    using internal_encoding_type = tetengo2::text::encoding::locale<string_type, encoding_details_type>;

    using config_details_type = detail_type_list_type::config_type;

    using config_encoding_type =
        tetengo2::text::encoding::locale<config_details_type::string_type, encoding_details_type>;

    using encoder_type = tetengo2::text::encoder<internal_encoding_type, config_encoding_type>;

    using persistent_config_type =
        tetengo2::config::persistent_config<string_type, uint_type, encoder_type, config_details_type>;

    using config_base_type = persistent_config_type::base_type;

    using value_type = persistent_config_type::value_type;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(config)
BOOST_AUTO_TEST_SUITE(persistent_config)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        persistent_config_type config{ string_type{ TETENGO2_TEXT("test_tetengo2") } };

        config.clear();
    }

    BOOST_AUTO_TEST_CASE(get)
    {
        BOOST_TEST_PASSPOINT();

        persistent_config_type config{ string_type{ TETENGO2_TEXT("test_tetengo2") } };

        {
            const auto value = config.get(string_type{ TETENGO2_TEXT("foo") });
            BOOST_CHECK(!value);
        }

        config.clear();
    }

    BOOST_AUTO_TEST_CASE(set)
    {
        BOOST_TEST_PASSPOINT();

        {
            persistent_config_type config{ string_type{ TETENGO2_TEXT("test_tetengo2") } };

            config.set(string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } });
            config.set(string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 });
            config.set(string_type{ TETENGO2_TEXT("foo") }, value_type{ 4242 });

            const auto value = config.get(string_type{ TETENGO2_TEXT("foo") });
            BOOST_REQUIRE(value);
            BOOST_CHECK_EQUAL(boost::get<uint_type>(*value), 4242U);

            config.clear();
        }
        {
            persistent_config_type config{ string_type{ TETENGO2_TEXT("test_tetengo2") } };

            config.set(string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } });
            config.set(string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 });
            config.set(string_type{ TETENGO2_TEXT("baz") }, value_type{ string_type{ TETENGO2_TEXT("fuga") } });

            const auto value = config.get(string_type{ TETENGO2_TEXT("baz") });
            BOOST_REQUIRE(value);
            BOOST_CHECK(boost::get<string_type>(*value) == string_type{ TETENGO2_TEXT("fuga") });

            config.clear();
        }
    }

    BOOST_AUTO_TEST_CASE(clear)
    {
        BOOST_TEST_PASSPOINT();

        {
            persistent_config_type config{ string_type{ TETENGO2_TEXT("test_tetengo2") } };

            config.set(string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } });
            config.set(string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 });

            config.clear();

            BOOST_CHECK(!config.get(string_type{ TETENGO2_TEXT("foo") }));
            BOOST_CHECK(!config.get(string_type{ TETENGO2_TEXT("bar") }));

            config.clear();
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
