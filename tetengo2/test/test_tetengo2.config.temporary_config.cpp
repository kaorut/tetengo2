/*! \file
    \brief Test of class tetengo2::config::temporary_config.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <string>
#include <utility>
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/config/temporary_config.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/type_list.h>


namespace {
    // types

    using string_type = tetengo2::type_list::string_type;

    using uint_type = tetengo2::type_list::size_type;

    using temporary_config_type = tetengo2::config::temporary_config;

    using value_type = temporary_config_type::value_type;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(config)
        BOOST_AUTO_TEST_SUITE(temporary_config)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                const temporary_config_type config{};
            }

            BOOST_AUTO_TEST_CASE(get)
            {
                BOOST_TEST_PASSPOINT();

                const std::vector<std::pair<string_type, value_type>> values{
                    { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
                    { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
                };
                temporary_config_type config{};
                for (const auto& value : values)
                {
                    config.set(value.first, value.second);
                }

                {
                    const auto value = config.get(string_type{ TETENGO2_TEXT("foo") });
                    BOOST_TEST_REQUIRE(tetengo2::stdalt::has_value(value));
                    BOOST_CHECK(tetengo2::stdalt::get<string_type>(*value) == string_type{ TETENGO2_TEXT("hoge") });
                }
                {
                    const auto value = config.get(string_type{ TETENGO2_TEXT("bar") });
                    BOOST_TEST_REQUIRE(tetengo2::stdalt::has_value(value));
                    BOOST_TEST(tetengo2::stdalt::get<uint_type>(*value) == 42U);
                }
                {
                    const auto value = config.get(string_type{ TETENGO2_TEXT("baz") });
                    BOOST_TEST_REQUIRE(!value);
                }
            }

            BOOST_AUTO_TEST_CASE(set)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const std::vector<std::pair<string_type, value_type>> values{
                        { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
                        { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
                    };
                    temporary_config_type config{};
                    for (const auto& value : values)
                    {
                        config.set(value.first, value.second);
                    }

                    config.set(string_type{ TETENGO2_TEXT("foo") }, value_type{ 4242 });

                    const auto value = config.get(string_type{ TETENGO2_TEXT("foo") });
                    BOOST_TEST_REQUIRE(tetengo2::stdalt::has_value(value));
                    BOOST_TEST(tetengo2::stdalt::get<uint_type>(*value) == 4242U);
                }
                {
                    const std::vector<std::pair<string_type, value_type>> values{
                        { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
                        { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
                    };
                    temporary_config_type config{};
                    for (const auto& value : values)
                    {
                        config.set(value.first, value.second);
                    }

                    config.set(string_type{ TETENGO2_TEXT("baz") }, string_type{ TETENGO2_TEXT("fuga") });

                    const auto value = config.get(string_type{ TETENGO2_TEXT("baz") });
                    BOOST_TEST_REQUIRE(tetengo2::stdalt::has_value(value));
                    BOOST_CHECK(tetengo2::stdalt::get<string_type>(*value) == string_type{ TETENGO2_TEXT("fuga") });
                }
            }

            BOOST_AUTO_TEST_CASE(clear)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const std::vector<std::pair<string_type, value_type>> values{
                        { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
                        { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
                    };
                    temporary_config_type config{};
                    for (const auto& value : values)
                    {
                        config.set(value.first, value.second);
                    }

                    config.clear();

                    BOOST_TEST(!config.get(string_type{ TETENGO2_TEXT("foo") }));
                    BOOST_TEST(!config.get(string_type{ TETENGO2_TEXT("bar") }));
                }
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
