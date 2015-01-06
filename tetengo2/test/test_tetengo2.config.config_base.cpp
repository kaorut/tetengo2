/*! \file
    \brief Test of class tetengo2::config::config_base.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/optional.hpp>
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

    using config_base_type = tetengo2::config::config_base<string_type, uint_type>;

    using value_type = config_base_type::value_type;

    class concrete_config : public config_base_type
    {
    private:
        virtual boost::optional<value_type> get_impl(const string_type& key)
        const override
        {
            return
                key == string_type{ TETENGO2_TEXT("foo") } ?
                boost::make_optional(value_type{ string_type{ TETENGO2_TEXT("hoge") } }) :
                boost::make_optional(value_type{ 42 });
        }

        virtual void set_impl(const string_type& key, value_type value)
        override
        {
            boost::ignore_unused(key, value);
        }

        virtual void clear_impl()
        override
        {}

    };


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(config)
BOOST_AUTO_TEST_SUITE(config_base)
    // test cases

    BOOST_AUTO_TEST_CASE(get)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_config config;

            const auto value = config.get(string_type{ TETENGO2_TEXT("foo") });
            BOOST_REQUIRE(value);
            BOOST_CHECK(boost::get<string_type>(*value) == string_type{ TETENGO2_TEXT("hoge") });
        }
        {
            const concrete_config config;

            const auto value = config.get(string_type{ TETENGO2_TEXT("bar") });
            BOOST_REQUIRE(value);
            BOOST_CHECK_EQUAL(boost::get<uint_type>(*value), 42U);
        }
    }

    BOOST_AUTO_TEST_CASE(set)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_config config;

            config.set(string_type{ TETENGO2_TEXT("foo") }, string_type{ TETENGO2_TEXT("hoge") });
        }
        {
            concrete_config config;

            config.set(string_type{ TETENGO2_TEXT("bar") }, 42);
        }
    }

    BOOST_AUTO_TEST_CASE(clear)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_config config;

            config.clear();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
