/*! \file
    \brief Test of class tetengo2::gui::unit::em.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <cstddef>

#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/unit/em.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using unit_details_type = detail_type_list_type::unit_type;

    using unit_type = tetengo2::gui::unit::em<boost::rational<std::ptrdiff_t>, unit_details_type>;

    using another_unit_type = tetengo2::gui::unit::em<boost::rational<std::size_t>, unit_details_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(unit)
BOOST_AUTO_TEST_SUITE(em)
    // test cases

    BOOST_AUTO_TEST_CASE(from)
    {
        BOOST_TEST_PASSPOINT();

        const auto unit = unit_type::from(another_unit_type{ 123 });

        BOOST_TEST(unit.value() == 123);
    }

    BOOST_AUTO_TEST_CASE(from_pixels)
    {
        BOOST_TEST_PASSPOINT();

        const auto unit = unit_type::from_pixels(123 * 12);

        BOOST_TEST(unit.value() == 123);
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const int value = 123;
            const unit_type unit{ value };
        }
        {
            const unit_type unit{ 123 };
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1{ 123 };

            BOOST_CHECK(unit1 == 123);
        }
        {
            const unit_type unit1{ 456 };

            BOOST_CHECK(unit1 != 123);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_less_than)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit1{ 123 };

        BOOST_CHECK(unit1 < 456);
    }

    BOOST_AUTO_TEST_CASE(operator_greater_than)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit1{ 456 };

        BOOST_CHECK(unit1 > 123);
    }

    BOOST_AUTO_TEST_CASE(add)
    {
        BOOST_TEST_PASSPOINT();

        unit_type unit1{ 456 };

        unit1.add(123);

        BOOST_TEST(unit1.value() == 579);
    }

    BOOST_AUTO_TEST_CASE(subtract)
    {
        BOOST_TEST_PASSPOINT();

        unit_type unit1{ 456 };

        unit1.subtract(123);

        BOOST_TEST(unit1.value() == 333);
    }

    BOOST_AUTO_TEST_CASE(multiply)
    {
        BOOST_TEST_PASSPOINT();

        unit_type unit1{ 456 };

        unit1.multiply(123);

        BOOST_TEST(unit1.value() == 56088);
    }

    BOOST_AUTO_TEST_CASE(divide_by)
    {
        BOOST_TEST_PASSPOINT();

        {
            unit_type unit1{ 456 };

            unit1.divide_by(123);

            BOOST_TEST(unit1.value() == 3);
        }
        {
            const unit_type unit1{ 456 };
            const unit_type unit2{ 123 };

            BOOST_TEST(unit1.divide_by(unit2) == 3);
        }
    }

    BOOST_AUTO_TEST_CASE(value)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit{ 123 };

        BOOST_TEST(unit.value() == 123);
    }

    BOOST_AUTO_TEST_CASE(to_pixels)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit{ 123 };

        BOOST_TEST(unit.to_pixels<std::ptrdiff_t>() == 123 * 12);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
