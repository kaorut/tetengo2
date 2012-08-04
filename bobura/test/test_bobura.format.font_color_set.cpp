/*! \file
    \brief Test of class bobura::format::font_color_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::font_color>::type font_color_type;

    typedef font_color_type::font_type font_type;

    typedef font_type::string_type string_type;

    typedef font_color_type::color_type color_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(format)
BOOST_AUTO_TEST_SUITE(font_color)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_type font_color(
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true), color_type(12, 34, 56)
        );
    }

    BOOST_AUTO_TEST_CASE(font)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_type font_color(
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true), color_type(12, 34, 56)
        );

        BOOST_CHECK(font_color.font() == font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true));
    }

    BOOST_AUTO_TEST_CASE(color)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_type font_color(
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true), color_type(12, 34, 56)
        );

        BOOST_CHECK(font_color.color() == color_type(12, 34, 56));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(font_color_set)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(company_line_name)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
