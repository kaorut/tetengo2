/*! \file
    \brief Test of class tetengo2::config::config_list.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <memory>
//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>
//#include <boost/variant.hpp>

#include "test_tetengo2.type_list.h"
#include "tetengo2.config.temporary_config.h"
#include "tetengo2.text.h"
#include "tetengo2.unique.h"

#include "tetengo2.config.config_list.h"


namespace
{
    // types

    typedef boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::string>::type string_type;

    typedef boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::size>::type uint_type;

    typedef tetengo2::config::config_list<string_type, uint_type> config_list_type;

    typedef config_list_type::base_type config_base_type;

    typedef config_list_type::value_type value_type;

    typedef tetengo2::config::temporary_config<string_type, uint_type> temporary_config_type;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(config)
BOOST_AUTO_TEST_SUITE(config_list)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<std::unique_ptr<config_base_type>> p_configs;
        {
            std::vector<std::pair<string_type, value_type>> values;
            values.emplace_back(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("hoge"))));
            values.emplace_back(string_type(TETENGO2_TEXT("bar")), value_type(42));
            p_configs.push_back(tetengo2::make_unique<temporary_config_type>(values.begin(), values.end()));
        }
        {
            std::vector<std::pair<string_type, value_type>> values;
            values.emplace_back(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("fuga"))));
            values.emplace_back(string_type(TETENGO2_TEXT("baz")), value_type(4242));
            p_configs.push_back(tetengo2::make_unique<temporary_config_type>(values.begin(), values.end()));
        }
        const config_list_type config(std::move(p_configs));
    }

    BOOST_AUTO_TEST_CASE(get)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<std::unique_ptr<config_base_type>> p_configs;
            {
                std::vector<std::pair<string_type, value_type>> values;
                values.emplace_back(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("hoge"))));
                values.emplace_back(string_type(TETENGO2_TEXT("bar")), value_type(42));
                p_configs.push_back(tetengo2::make_unique<temporary_config_type>(values.begin(), values.end()));
            }
            {
                std::vector<std::pair<string_type, value_type>> values;
                values.emplace_back(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("fuga"))));
                values.emplace_back(string_type(TETENGO2_TEXT("baz")), value_type(4242));
                p_configs.push_back(tetengo2::make_unique<temporary_config_type>(values.begin(), values.end()));
            }
            const config_list_type config(std::move(p_configs));

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
                BOOST_REQUIRE(value);
                BOOST_CHECK_EQUAL(boost::get<uint_type>(*value), 4242U);
            }
        }
        {
            std::vector<std::unique_ptr<config_base_type>> p_configs;
            {
                std::vector<std::pair<string_type, value_type>> values;
                values.emplace_back(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("fuga"))));
                values.emplace_back(string_type(TETENGO2_TEXT("baz")), value_type(4242));
                p_configs.push_back(tetengo2::make_unique<temporary_config_type>(values.begin(), values.end()));
            }
            {
                std::vector<std::pair<string_type, value_type>> values;
                values.emplace_back(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("hoge"))));
                values.emplace_back(string_type(TETENGO2_TEXT("bar")), value_type(42));
                p_configs.push_back(tetengo2::make_unique<temporary_config_type>(values.begin(), values.end()));
            }
            const config_list_type config(std::move(p_configs));

            {
                const boost::optional<value_type> value = config.get(string_type(TETENGO2_TEXT("foo")));
                BOOST_REQUIRE(value);
                BOOST_CHECK(boost::get<string_type>(*value) == string_type(TETENGO2_TEXT("fuga")));
            }
        }
    }

    BOOST_AUTO_TEST_CASE(set)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<std::unique_ptr<config_base_type>> p_configs;
            {
                std::vector<std::pair<string_type, value_type>> values;
                values.emplace_back(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("hoge"))));
                values.emplace_back(string_type(TETENGO2_TEXT("bar")), value_type(42));
                p_configs.push_back(tetengo2::make_unique<temporary_config_type>(values.begin(), values.end()));
            }
            {
                std::vector<std::pair<string_type, value_type>> values;
                values.emplace_back(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("fuga"))));
                values.emplace_back(string_type(TETENGO2_TEXT("baz")), value_type(4242));
                p_configs.push_back(tetengo2::make_unique<temporary_config_type>(values.begin(), values.end()));
            }
            config_list_type config(std::move(p_configs));

            config.set(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("piyo"))));

            const boost::optional<value_type> value = config.get(string_type(TETENGO2_TEXT("foo")));
            BOOST_REQUIRE(value);
            BOOST_CHECK(boost::get<string_type>(*value) == string_type(TETENGO2_TEXT("piyo")));
        }
        {
            std::vector<std::unique_ptr<config_base_type>> p_configs;
            {
                std::vector<std::pair<string_type, value_type>> values;
                values.emplace_back(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("hoge"))));
                values.emplace_back(string_type(TETENGO2_TEXT("bar")), value_type(42));
                p_configs.push_back(tetengo2::make_unique<temporary_config_type>(values.begin(), values.end()));
            }
            {
                std::vector<std::pair<string_type, value_type>> values;
                values.emplace_back(string_type(TETENGO2_TEXT("foo")), value_type(string_type(TETENGO2_TEXT("fuga"))));
                values.emplace_back(string_type(TETENGO2_TEXT("baz")), value_type(4242));
                p_configs.push_back(tetengo2::make_unique<temporary_config_type>(values.begin(), values.end()));
            }
            config_list_type config(std::move(p_configs));

            config.set(string_type(TETENGO2_TEXT("bazz")), value_type(string_type(TETENGO2_TEXT("piyo"))));

            const boost::optional<value_type> value = config.get(string_type(TETENGO2_TEXT("bazz")));
            BOOST_REQUIRE(value);
            BOOST_CHECK(boost::get<string_type>(*value) == string_type(TETENGO2_TEXT("piyo")));
        }
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
