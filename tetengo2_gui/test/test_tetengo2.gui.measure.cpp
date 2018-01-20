/*! \file
    \brief Test of class tetengo2::gui::measure.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/rational.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/measure.h>
#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/type_list.h>


namespace
{
    // types

    using difference_rational_type = boost::rational<tetengo2::type_list::difference_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
    // test cases

    BOOST_AUTO_TEST_CASE(to_pixels)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::gui::unit::pixel value{ 123 };

            const auto pixels = tetengo2::gui::to_pixels<int>(value);

            BOOST_TEST(pixels == 123);
        }
        {
            const int value = 456;

            const auto pixels = tetengo2::gui::to_pixels<int>(value);

            BOOST_TEST(pixels == 456);
        }
    }

    BOOST_AUTO_TEST_CASE(to_unit)
    {
        BOOST_TEST_PASSPOINT();

        {
            using unit_type = tetengo2::gui::unit::pixel;
            const int value = 123;

            const auto unit = tetengo2::gui::to_unit<unit_type>(value);

            BOOST_TEST(unit.value() == 123);
        }
        {
            using unit_type = int;
            const int value = 456;

            const auto unit = tetengo2::gui::to_unit<unit_type>(value);

            BOOST_TEST(unit == 456);
        }
    }

    BOOST_AUTO_TEST_CASE(ceil)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::gui::unit::pixel value{ difference_rational_type{ 3, 2 } };

            const auto ceiling = tetengo2::gui::ceil<difference_rational_type::int_type>(value);

            BOOST_TEST(ceiling == 2);
        }
        {
            const difference_rational_type::int_type value = 42;

            const auto ceiling = tetengo2::gui::ceil<difference_rational_type::int_type>(value);

            BOOST_TEST(ceiling == 42);
        }
    }

    BOOST_AUTO_TEST_CASE(floor)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::gui::unit::pixel value{ difference_rational_type{ 3, 2 } };

            const auto floor = tetengo2::gui::floor<difference_rational_type::int_type>(value);

            BOOST_TEST(floor == 1);
        }
        {
            const difference_rational_type::int_type value = 42;

            const auto floor = tetengo2::gui::floor<difference_rational_type::int_type>(value);

            BOOST_TEST(floor == 42);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
