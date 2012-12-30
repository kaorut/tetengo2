/*! \file
    \brief Test of class tetengo2::gui::drawing::color.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::color>::type
        color_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(color)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const color_type color(0x02, 0x46, 0x8A, 0xCE);
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const color_type color1(0x02, 0x46, 0x8A, 0xCE);
            const color_type color2(0x02, 0x46, 0x8A, 0xCE);

            BOOST_CHECK(color1 == color2);
        }
        {
            const color_type color1(0x02, 0x46, 0x8A, 0xCE);
            const color_type color2(0x13, 0x57, 0x9B, 0xDF);

            BOOST_CHECK(color1 != color2);
        }
    }

    BOOST_AUTO_TEST_CASE(red)
    {
        BOOST_TEST_PASSPOINT();

        const color_type color(0x02, 0x46, 0x8A, 0xCE);

        BOOST_CHECK_EQUAL(color.red(), 0x02);
    }

    BOOST_AUTO_TEST_CASE(green)
    {
        BOOST_TEST_PASSPOINT();

        const color_type color(0x02, 0x46, 0x8A, 0xCE);

        BOOST_CHECK_EQUAL(color.green(), 0x46);
    }

    BOOST_AUTO_TEST_CASE(blue)
    {
        BOOST_TEST_PASSPOINT();

        const color_type color(0x02, 0x46, 0x8A, 0xCE);

        BOOST_CHECK_EQUAL(color.blue(), 0x8A);
    }

    BOOST_AUTO_TEST_CASE(alpha)
    {
        BOOST_TEST_PASSPOINT();

        const color_type color(0x02, 0x46, 0x8A, 0xCE);

        BOOST_CHECK_EQUAL(color.alpha(), 0xCE);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
