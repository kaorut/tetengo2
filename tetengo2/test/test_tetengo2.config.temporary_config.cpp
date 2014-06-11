/*! \file
    \brief Test of class tetengo2::config::temporary_config.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <utility>
#include <vector>

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/variant.hpp>

#include <tetengo2.h>

#include "test_tetengo2.type_list.h"


namespace
{
    // types

    using string_type = boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::string>::type;

    using uint_type = boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::size>::type;

    using temporary_config_type = tetengo2::config::temporary_config<string_type, uint_type>;

    using value_type = temporary_config_type::value_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(config)
BOOST_AUTO_TEST_SUITE(temporary_config)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const temporary_config_type config{};
        }
        {
            const std::vector<std::pair<string_type, value_type>> values{
                { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
                { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
            };
            const temporary_config_type config{ values.begin(), values.end() };
        }
    }

    BOOST_AUTO_TEST_CASE(get)
    {
        BOOST_TEST_PASSPOINT();

        const std::vector<std::pair<string_type, value_type>> values{
            { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
            { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
        };
        const temporary_config_type config{ values.begin(), values.end() };

        {
            const auto value = config.get(string_type{ TETENGO2_TEXT("foo") });
            BOOST_REQUIRE(value);
            BOOST_CHECK(boost::get<string_type>(*value) == string_type{ TETENGO2_TEXT("hoge") });
        }
        {
            const auto value = config.get(string_type{ TETENGO2_TEXT("bar") });
            BOOST_REQUIRE(value);
            BOOST_CHECK_EQUAL(boost::get<uint_type>(*value), 42U);
        }
        {
            const auto value = config.get(string_type{ TETENGO2_TEXT("baz") });
            BOOST_REQUIRE(!value);
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
            temporary_config_type config{ values.begin(), values.end() };

            config.set(string_type{ TETENGO2_TEXT("foo") }, value_type{ 4242 });

            const auto value = config.get(string_type{ TETENGO2_TEXT("foo") });
            BOOST_REQUIRE(value);
            BOOST_CHECK_EQUAL(boost::get<uint_type>(*value), 4242U);
        }
        {
            const std::vector<std::pair<string_type, value_type>> values{
                { string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } } },
                { string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 } }
            };
            temporary_config_type config{ values.begin(), values.end() };

            config.set(string_type{ TETENGO2_TEXT("baz") }, string_type{ TETENGO2_TEXT("fuga") });

            const auto value = config.get(string_type{ TETENGO2_TEXT("baz") });
            BOOST_REQUIRE(value);
            BOOST_CHECK(boost::get<string_type>(*value) == string_type{ TETENGO2_TEXT("fuga") });
        }
    }

    BOOST_AUTO_TEST_CASE(clear)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
