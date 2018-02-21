/*! \file
    \brief Test of class tetengo2::gui::drawing::color.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>
#include <stdexcept>

#include <boost/operators.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/color.h>


namespace
{
    // types

    using color_type = tetengo2::gui::drawing::color;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(basic_color)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const color_type color{ 0x02, 0x46, 0x8A, 0xCE };
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const color_type color1{ 0x02, 0x46, 0x8A, 0xCE };
            const color_type color2{ 0x02, 0x46, 0x8A, 0xCE };

            BOOST_CHECK(color1 == color2);
        }
        {
            const color_type color1{ 0x02, 0x46, 0x8A, 0xCE };
            const color_type color2{ 0x13, 0x57, 0x9B, 0xDF };

            BOOST_CHECK(color1 != color2);
        }
    }

    BOOST_AUTO_TEST_CASE(red)
    {
        BOOST_TEST_PASSPOINT();

        const color_type color{ 0x02, 0x46, 0x8A, 0xCE };

        BOOST_TEST(color.red() == 0x02);
    }

    BOOST_AUTO_TEST_CASE(green)
    {
        BOOST_TEST_PASSPOINT();

        const color_type color{ 0x02, 0x46, 0x8A, 0xCE };

        BOOST_TEST(color.green() == 0x46);
    }

    BOOST_AUTO_TEST_CASE(blue)
    {
        BOOST_TEST_PASSPOINT();

        const color_type color{ 0x02, 0x46, 0x8A, 0xCE };

        BOOST_TEST(color.blue() == 0x8A);
    }

    BOOST_AUTO_TEST_CASE(alpha)
    {
        BOOST_TEST_PASSPOINT();

        const color_type color{ 0x02, 0x46, 0x8A, 0xCE };

        BOOST_TEST(color.alpha() == 0xCE);
    }

    BOOST_AUTO_TEST_CASE(mix)
    {
        BOOST_TEST_PASSPOINT();

        {
            const color_type color1{ 0x00, 0x40, 0x80, 0xC0 };
            const color_type color2{ 0x20, 0x80, 0xC0, 0x00 };

            const color_type expected{ 0x00, 0x40, 0x80, 0xC0 };
            BOOST_CHECK(color1.mix(color2, 0.0) == expected);
        }
        {
            const color_type color1{ 0x00, 0x40, 0x80, 0xC0 };
            const color_type color2{ 0x20, 0x80, 0xC0, 0x00 };

            const color_type expected{ 0x08, 0x50, 0x90, 0x90 };
            BOOST_CHECK(color1.mix(color2, 0.25) == expected);
        }
        {
            const color_type color1{ 0x00, 0x40, 0x80, 0xC0 };
            const color_type color2{ 0x20, 0x80, 0xC0, 0x00 };

            const color_type expected{ 0x20, 0x80, 0xC0, 0x00 };
            BOOST_CHECK(color1.mix(color2, 1.0) == expected);
        }
        {
            const color_type color1{ 0x00, 0x40, 0x80, 0xC0 };
            const color_type color2{ 0x20, 0x80, 0xC0, 0x00 };

            BOOST_CHECK_THROW(color1.mix(color2, -0.01), std::invalid_argument);
        }
        {
            const color_type color1{ 0x00, 0x40, 0x80, 0xC0 };
            const color_type color2{ 0x20, 0x80, 0xC0, 0x00 };

            BOOST_CHECK_THROW(color1.mix(color2, 1.01), std::invalid_argument);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
