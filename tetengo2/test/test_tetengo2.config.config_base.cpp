/*! \file
    \brief Test of class tetengo2::config::config_base.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "test_tetengo2.type_list.h"

#include "tetengo2.config.config_base.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::type_list, test_tetengo2::type::string>::type string_type;

    typedef tetengo2::config::config_base<string_type> config_base_type;

    struct concrete_config : public config_base_type
    {

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

    
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
