/*! \file
    \brief Test of class tetengo2::config::persistent_config.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_tetengo2.type_list.h"


namespace
{
    // types

    using string_type = boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::string>::type;

    using uint_type = boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::size>::type;

    using encoder_type = boost::mpl::at<test_tetengo2::config_type_list, test_tetengo2::type::config::encoder>::type;

    using persistent_config_type =
        tetengo2::config::persistent_config<string_type, uint_type, encoder_type, tetengo2::detail::stub::config>;

    using config_base_type = persistent_config_type::base_type;

    using value_type = persistent_config_type::value_type;


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(config)
BOOST_AUTO_TEST_SUITE(persistent_config)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const persistent_config_type config{ string_type{ TETENGO2_TEXT("group") } };
    }

    BOOST_AUTO_TEST_CASE(get)
    {
        BOOST_TEST_PASSPOINT();

        const persistent_config_type config{ string_type{ TETENGO2_TEXT("group") } };

        config.get(string_type(TETENGO2_TEXT("foo")));
    }

    BOOST_AUTO_TEST_CASE(set)
    {
        BOOST_TEST_PASSPOINT();

        persistent_config_type config{ string_type(TETENGO2_TEXT("group")) };

        config.set(string_type(TETENGO2_TEXT("foo")), value_type(4242));
    }

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
