/*! \file
    \brief Test of class tetengo2::config::config_list.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <memory>
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

    using config_list_type = tetengo2::config::config_list<string_type, uint_type>;

    using config_base_type = config_list_type::base_type;

    using value_type = config_list_type::value_type;

    using temporary_config_type = tetengo2::config::temporary_config<string_type, uint_type>;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(config)
BOOST_AUTO_TEST_SUITE(config_list)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::unique_ptr<config_base_type>> p_configs{};
        {
            const std::vector<std::pair<string_type, value_type>> values{
                { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
                { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
            };
            p_configs.push_back(tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end()));
        }
        {
            const std::vector<std::pair<string_type, value_type>> values{
                { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("fuga") } } },
                { string_type{ TETENGO2_TEXT("baz") }, value_type{ 4242 } }
            };
            p_configs.push_back(tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end()));
        }
        const config_list_type config{ std::move(p_configs) };
    }

    BOOST_AUTO_TEST_CASE(get)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<std::unique_ptr<config_base_type>> p_configs{};
            {
                const std::vector<std::pair<string_type, value_type>> values{
                    { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
                    { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
                };
                p_configs.push_back(
                    tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end())
                );
            }
            {
                const std::vector<std::pair<string_type, value_type>> values{
                    { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("fuga") } } },
                    { string_type{ TETENGO2_TEXT("baz") }, value_type{ 4242 } }
                };
                p_configs.push_back(
                    tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end())
                );
            }
            const config_list_type config{ std::move(p_configs) };

            {
                const auto value = config.get(string_type{ TETENGO2_TEXT("foo") });
                BOOST_TEST_REQUIRE(value.is_initialized());
                BOOST_CHECK(boost::get<string_type>(*value) == string_type{ TETENGO2_TEXT("hoge") });
            }
            {
                const auto value = config.get(string_type{ TETENGO2_TEXT("bar") });
                BOOST_TEST_REQUIRE(value.is_initialized());
                BOOST_TEST(boost::get<uint_type>(*value) == 42U);
            }
            {
                const auto value = config.get(string_type{ TETENGO2_TEXT("baz") });
                BOOST_TEST_REQUIRE(value.is_initialized());
                BOOST_TEST(boost::get<uint_type>(*value) == 4242U);
            }
        }
        {
            std::vector<std::unique_ptr<config_base_type>> p_configs{};
            {
                const std::vector<std::pair<string_type, value_type>> values{
                    { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("fuga") } } },
                    { string_type{ TETENGO2_TEXT("baz") }, value_type{ 4242 } }
                };
                p_configs.push_back(
                    tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end())
                );
            }
            {
                const std::vector<std::pair<string_type, value_type>> values{
                    { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
                    { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
                };
                p_configs.push_back(
                    tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end())
                );
            }
            const config_list_type config{ std::move(p_configs) };

            {
                const auto value = config.get(string_type{ TETENGO2_TEXT("foo") });
                BOOST_TEST_REQUIRE(value.is_initialized());
                BOOST_CHECK(boost::get<string_type>(*value) == string_type{ TETENGO2_TEXT("fuga") });
            }
        }
    }

    BOOST_AUTO_TEST_CASE(set)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<std::unique_ptr<config_base_type>> p_configs{};
            {
                const std::vector<std::pair<string_type, value_type>> values{
                    { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
                    { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
                };
                p_configs.push_back(
                    tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end())
                );
            }
            {
                const std::vector<std::pair<string_type, value_type>> values{
                    { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("fuga") } } },
                    { string_type{ TETENGO2_TEXT("baz") }, value_type{ 4242 } }
                };
                p_configs.push_back(
                    tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end())
                );
            }
            config_list_type config{ std::move(p_configs) };

            config.set(string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("piyo") } });

            const auto value = config.get(string_type{ TETENGO2_TEXT("foo") });
            BOOST_TEST_REQUIRE(value.is_initialized());
            BOOST_CHECK(boost::get<string_type>(*value) == string_type{ TETENGO2_TEXT("piyo") });
        }
        {
            std::vector<std::unique_ptr<config_base_type>> p_configs{};
            {
                const std::vector<std::pair<string_type, value_type>> values{
                    { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
                    { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
                };
                p_configs.push_back(
                    tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end())
                );
            }
            {
                const std::vector<std::pair<string_type, value_type>> values{
                    { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("fuga") } } },
                    { string_type{ TETENGO2_TEXT("baz") }, value_type{ 4242 } }
                };
                p_configs.push_back(
                    tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end())
                );
            }
            config_list_type config{ std::move(p_configs) };

            config.set(string_type{ TETENGO2_TEXT("bazz") }, value_type{ string_type{ TETENGO2_TEXT("piyo") } });

            const auto value = config.get(string_type{ TETENGO2_TEXT("bazz") });
            BOOST_TEST_REQUIRE(value.is_initialized());
            BOOST_CHECK(boost::get<string_type>(*value) == string_type{ TETENGO2_TEXT("piyo") });
        }
    }

    BOOST_AUTO_TEST_CASE(clear)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<std::unique_ptr<config_base_type>> p_configs{};
            {
                const std::vector<std::pair<string_type, value_type>> values{
                    { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
                    { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
                };
                p_configs.push_back(
                    tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end())
                );
            }
            {
                const std::vector<std::pair<string_type, value_type>> values{
                    { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("fuga") } } },
                    { string_type{ TETENGO2_TEXT("baz") }, value_type{ 4242 } }
                };
                p_configs.push_back(
                    tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end())
                );
            }
            config_list_type config{ std::move(p_configs) };

            config.clear();

            BOOST_TEST(!config.get(string_type{ TETENGO2_TEXT("foo") }));
            BOOST_TEST(!config.get(string_type{ TETENGO2_TEXT("bar") }));
            BOOST_TEST(!config.get(string_type{ TETENGO2_TEXT("baz") }));
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
