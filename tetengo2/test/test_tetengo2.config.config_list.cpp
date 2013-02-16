/*! \file
    \brief Test of class tetengo2::config::config_list.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <utility>
#include <vector>

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.type_list.h"
#include "tetengo2.text.h"

#include "tetengo2.config.config_list.h"


namespace
{
    // types

    typedef boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::string>::type string_type;

    typedef boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::size>::type uint_type;

    typedef tetengo2::config::config_list<string_type, uint_type> config_list_type;

    typedef config_list_type::value_type value_type;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(config)
BOOST_AUTO_TEST_SUITE(config_list)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const config_list_type config;
        }
        {
            std::vector<std::pair<string_type, value_type>> values;
            values.emplace_back(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("hoge"))));
            values.emplace_back(string_type(TETENGO2_TEXT("bar")), value_type(42));
            const config_list_type config(values.begin(), values.end());
        }
    }

    BOOST_AUTO_TEST_CASE(get)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::pair<string_type, value_type>> values;
        values.emplace_back(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("hoge"))));
        values.emplace_back(string_type(TETENGO2_TEXT("bar")), value_type(42));
        const config_list_type config(values.begin(), values.end());

        {
            const boost::optional<value_type> value = config.get(string_type(TETENGO2_TEXT("foo")));
            BOOST_REQUIRE(value);
            BOOST_CHECK(boost::get<string_type>(*value) == string_type(TETENGO2_TEXT("hoge")));
        }
        {
            const boost::optional<value_type> value = config.get(string_type(TETENGO2_TEXT("bar")));
            BOOST_REQUIRE(value);
            BOOST_CHECK_EQUAL(boost::get<uint_type>(*value), 42U);
        }
        {
            const boost::optional<value_type> value = config.get(string_type(TETENGO2_TEXT("baz")));
            BOOST_REQUIRE(!value);
        }
    }

    BOOST_AUTO_TEST_CASE(set)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<std::pair<string_type, value_type>> values;
            values.emplace_back(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("hoge"))));
            values.emplace_back(string_type(TETENGO2_TEXT("bar")), value_type(42));
            config_list_type config(values.begin(), values.end());

            config.set(string_type(TETENGO2_TEXT("foo")), value_type(4242));

            const boost::optional<value_type> value = config.get(string_type(TETENGO2_TEXT("foo")));
            BOOST_REQUIRE(value);
            BOOST_CHECK_EQUAL(boost::get<uint_type>(*value), 4242U);
        }
        {
            std::vector<std::pair<string_type, value_type>> values;
            values.emplace_back(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("hoge"))));
            values.emplace_back(string_type(TETENGO2_TEXT("bar")), value_type(42));
            config_list_type config(values.begin(), values.end());

            config.set(string_type(TETENGO2_TEXT("baz")), string_type(TETENGO2_TEXT("fuga")));

            const boost::optional<value_type> value = config.get(string_type(TETENGO2_TEXT("baz")));
            BOOST_REQUIRE(value);
            BOOST_CHECK(boost::get<string_type>(*value) == string_type(TETENGO2_TEXT("fuga")));
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
