/*! \file
    \brief Test of class tetengo2::config::config_base.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.type_list.h"
#include "tetengo2.text.h"

#include "tetengo2.config.config_base.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::string>::type string_type;

    typedef
        boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::size>::type uint_type;

    typedef tetengo2::config::config_base<string_type, uint_type> config_base_type;

    class concrete_config : public config_base_type
    {
    public:
        concrete_config()
        :
        config_base_type()
        {}

    private:
        virtual boost::optional<string_type> get_string_impl(const string_type& key)
        const
        {
            return boost::make_optional(string_type(TETENGO2_TEXT("hoge")));
        }

        virtual boost::optional<uint_type> get_uint_impl(const string_type& key)
        const
        {
            return boost::make_optional<uint_type>(42);
        }

        virtual void set_impl(const string_type& key, string_type value)
        {}

        virtual void set_impl(const string_type& key, const uint_type value)
        {}

    };


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(config)
BOOST_AUTO_TEST_SUITE(config_base)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_config config;
    }

    BOOST_AUTO_TEST_CASE(get_string)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_config config;

        const boost::optional<string_type> value = config.get_string(string_type(TETENGO2_TEXT("foo")));
        BOOST_REQUIRE(value);
        BOOST_CHECK(*value == string_type(TETENGO2_TEXT("hoge")));
    }

    BOOST_AUTO_TEST_CASE(get_uint)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_config config;

        const boost::optional<uint_type> value = config.get_uint(string_type(TETENGO2_TEXT("bar")));
        BOOST_REQUIRE(value);
        BOOST_CHECK_EQUAL(*value, 42U);
    }

    BOOST_AUTO_TEST_CASE(set_string)
    {
        BOOST_TEST_PASSPOINT();

        concrete_config config;

        config.set(string_type(TETENGO2_TEXT("foo")), string_type(TETENGO2_TEXT("hoge")));
    }

    BOOST_AUTO_TEST_CASE(set_uint)
    {
        BOOST_TEST_PASSPOINT();

        concrete_config config;

        config.set(string_type(TETENGO2_TEXT("bar")), 42);
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
