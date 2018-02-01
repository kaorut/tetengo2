/*! \file
    \brief Test of class tetengo2::config::persistent_config.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <string>

#include <boost/optional.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/variant.hpp>

#include <tetengo2/config/persistent_config.h>
#include <tetengo2/text.h>
#include <tetengo2/type_list.h>


namespace
{
    // types

    using string_type = tetengo2::type_list::string_type;

    using uint_type = tetengo2::type_list::size_type;

    using persistent_config_type = tetengo2::config::persistent_config;

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
            BOOST_TEST(!value);
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
            BOOST_TEST_REQUIRE(value.is_initialized());
            BOOST_TEST(boost::get<uint_type>(*value) == 4242U);

            config.clear();
        }
        {
            persistent_config_type config{ string_type{ TETENGO2_TEXT("test_tetengo2") } };

            config.set(string_type{ TETENGO2_TEXT("foo") }, value_type{ string_type{ TETENGO2_TEXT("hoge") } });
            config.set(string_type{ TETENGO2_TEXT("bar") }, value_type{ 42 });
            config.set(string_type{ TETENGO2_TEXT("baz") }, value_type{ string_type{ TETENGO2_TEXT("fuga") } });

            const auto value = config.get(string_type{ TETENGO2_TEXT("baz") });
            BOOST_TEST_REQUIRE(value.is_initialized());
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

            BOOST_TEST(!config.get(string_type{ TETENGO2_TEXT("foo") }).is_initialized());
            BOOST_TEST(!config.get(string_type{ TETENGO2_TEXT("bar") }).is_initialized());

            config.clear();
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
