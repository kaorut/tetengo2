/*! \file
    \brief Test of class tetengo2::gui::unit::point.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/unit/point.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using unit_details_type = detail_type_list_type::unit_type;

    using unit_type = tetengo2::gui::unit::point<int, unit_details_type>;

    using another_unit_type = tetengo2::gui::unit::point<unsigned short, unit_details_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(unit)
BOOST_AUTO_TEST_SUITE(point)
    // test cases

    BOOST_AUTO_TEST_CASE(from)
    {
        BOOST_TEST_PASSPOINT();

        const auto unit = unit_type::from(another_unit_type{ 12 });

        BOOST_TEST(unit.value() == 12);
    }

    BOOST_AUTO_TEST_CASE(from_pixels)
    {
        BOOST_TEST_PASSPOINT();

        const auto unit = unit_type::from_pixels(16);

        BOOST_TEST(unit.value() == 12);
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const int value = 12;
            const unit_type unit{ value };
        }
        {
            const unit_type unit{ 12 };
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1{ 12 };

            BOOST_CHECK(unit1 == 12);
        }
        {
            const unit_type unit1{ 34 };

            BOOST_CHECK(unit1 != 12);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_less_than)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit1{ 12 };

        BOOST_CHECK(unit1 < 34);
    }

    BOOST_AUTO_TEST_CASE(operator_greater_than)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit1{ 34 };

        BOOST_CHECK(unit1 > 12);
    }

    BOOST_AUTO_TEST_CASE(add)
    {
        BOOST_TEST_PASSPOINT();

        unit_type unit1{ 34 };

        unit1.add(12);

        BOOST_TEST(unit1.value() == 46);
    }

    BOOST_AUTO_TEST_CASE(subtract)
    {
        BOOST_TEST_PASSPOINT();

        unit_type unit1{ 34 };

        unit1.subtract(12);

        BOOST_TEST(unit1.value() == 22);
    }

    BOOST_AUTO_TEST_CASE(multiply)
    {
        BOOST_TEST_PASSPOINT();

        unit_type unit1{ 34 };

        unit1.multiply(12);

        BOOST_TEST(unit1.value() == 408);
    }

    BOOST_AUTO_TEST_CASE(divide_by)
    {
        BOOST_TEST_PASSPOINT();

        {
            unit_type unit1{ 36 };

            unit1.divide_by(12);

            BOOST_TEST(unit1.value() == 3);
        }
        {
            const unit_type unit1{ 36 };
            const unit_type unit2{ 12 };

            BOOST_TEST(unit1.divide_by(unit2) == 3);
        }
    }

    BOOST_AUTO_TEST_CASE(value)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit{ 12 };

        BOOST_TEST(unit.value() == 12);
    }

    BOOST_AUTO_TEST_CASE(to_pixels)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit{ 12 };

        BOOST_TEST(unit.to_pixels<int>() == 16);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
