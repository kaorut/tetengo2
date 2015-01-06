/*! \file
    \brief Test of class tetengo2::config::cached_config.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <utility>
#include <vector>

#include <boost/test/unit_test.hpp>
#include <boost/variant.hpp>

#include <tetengo2.h>

#include "test_tetengo2.type_list.h"


namespace
{
    // types

    using common_type_list_type = test_tetengo2::type_list::common;

    using string_type = common_type_list_type::string_type;

    using uint_type = common_type_list_type::size_type;

    using cached_config_type = tetengo2::config::cached_config<string_type, uint_type>;

    using config_base_type = cached_config_type::base_type;

    using value_type = cached_config_type::value_type;

    using temporary_config_type = tetengo2::config::temporary_config<string_type, uint_type>;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(config)
BOOST_AUTO_TEST_SUITE(cached_config)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<std::pair<string_type, value_type>> values{
            { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
            { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
        };
        auto p_temporary_config = tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end());
        const cached_config_type config{ std::move(p_temporary_config) };
    }

    BOOST_AUTO_TEST_CASE(get)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<std::pair<string_type, value_type>> values{
            { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
            { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
        };
        auto p_temporary_config = tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end());
        const cached_config_type config{ std::move(p_temporary_config) };

        {
            const auto value = config.get(string_type{ TETENGO2_TEXT("foo") });
            BOOST_REQUIRE(value);
            BOOST_CHECK(boost::get<string_type>(*value) == string_type{ TETENGO2_TEXT("hoge") });
        }
        {
            const auto value = config.get(string_type{ TETENGO2_TEXT("foo") });
            BOOST_REQUIRE(value);
            BOOST_CHECK(boost::get<string_type>(*value) == string_type{ TETENGO2_TEXT("hoge") });
        }
        {
            const auto value = config.get(string_type{ TETENGO2_TEXT("baz") });
            BOOST_REQUIRE(!value);
        }
    }

    BOOST_AUTO_TEST_CASE(set)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<std::pair<string_type, value_type>> values{
            { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
            { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
        };
        auto p_temporary_config = tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end());
        cached_config_type config{ std::move(p_temporary_config) };

        config.set(string_type{ TETENGO2_TEXT("foo") }, value_type{ 4242 });

        const auto value = config.get(string_type{ TETENGO2_TEXT("foo") });
        BOOST_REQUIRE(value);
        BOOST_CHECK_EQUAL(boost::get<uint_type>(*value), 4242U);
    }

    BOOST_AUTO_TEST_CASE(clear)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<std::pair<string_type, value_type>> values{
            { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
            { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
        };
        auto p_temporary_config = tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end());
        cached_config_type config{ std::move(p_temporary_config) };

        config.clear();

        BOOST_CHECK(!config.get(string_type{ TETENGO2_TEXT("foo") }));
        BOOST_CHECK(!config.get(string_type{ TETENGO2_TEXT("bar") }));
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
