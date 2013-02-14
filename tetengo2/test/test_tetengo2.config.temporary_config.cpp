/*! \file
    \brief Test of class tetengo2::config::temporary_config.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.type_list.h"
#include "tetengo2.text.h"

#include "tetengo2.config.temporary_config.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::string>::type string_type;

    typedef
        boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::size>::type uint_type;

    typedef tetengo2::config::temporary_config<string_type, uint_type> temporary_config_type;

    typedef temporary_config_type::value_type value_type;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(config)
BOOST_AUTO_TEST_SUITE(temporary_config)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const temporary_config_type config;
    }

    BOOST_AUTO_TEST_CASE(get)
    {
        BOOST_TEST_PASSPOINT();

        //const concrete_config config;

        //const boost::optional<value_type> value = config.get(string_type(TETENGO2_TEXT("foo")));
        //BOOST_REQUIRE(value);
        //BOOST_CHECK(boost::get<string_type>(*value) == string_type(TETENGO2_TEXT("hoge")));
    }

    BOOST_AUTO_TEST_CASE(set)
    {
        BOOST_TEST_PASSPOINT();

        //concrete_config config;

        //config.set(string_type(TETENGO2_TEXT("foo")), string_type(TETENGO2_TEXT("hoge")));
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
