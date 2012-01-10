/*! \file
    \brief Test of class tetengo2::gui::virtual_key.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.virtual_key.h"

#include "tetengo2.gui.virtual_key.h"


namespace
{
    // types

    typedef
        tetengo2::detail::stub::virtual_key<std::string>
        virtual_key_details_type;

    typedef
        tetengo2::gui::virtual_key<virtual_key_details_type>
        virtual_key_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(virtual_key)
    // test cases

    BOOST_AUTO_TEST_CASE(static_member_functions)
    {
        BOOST_TEST_PASSPOINT();

        virtual_key_type::backspace();
    }

    BOOST_AUTO_TEST_CASE(code)
    {
        BOOST_TEST_PASSPOINT();

        //BOOST_CHECK_EQUAL(
        //    virtual_key_type::char_a().code(),
        //    virtual_key_details_type::char_a().first
        //);
    }

    BOOST_AUTO_TEST_CASE(string)
    {
        BOOST_TEST_PASSPOINT();

        //BOOST_CHECK(
        //    virtual_key_type::char_a().to_string() ==
        //    virtual_key_details_type::char_a().second
        //);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
