/*! \file
    \brief Test of class tetengo2::gui::unit::pixel.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <boost/rational.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/type_list.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types
    
    using difference_rational_type = boost::rational<tetengo2::type_list::difference_type>;

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using unit_details_type = detail_type_list_type::unit_type;

    using unit_type = tetengo2::gui::unit::pixel;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(unit)
BOOST_AUTO_TEST_SUITE(pixel)
    // test cases

    BOOST_AUTO_TEST_CASE(from_pixels)
    {
        BOOST_TEST_PASSPOINT();

        const auto unit = unit_type::from_pixels(123, unit_details_type::instance());

        BOOST_TEST(unit.value() == 123);
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const difference_rational_type value{ 123 };
            const unit_type unit{ std::move(value), unit_details_type::instance() };
        }
        {
            const unit_type unit{ 123, unit_details_type::instance() };
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1{ 123, unit_details_type::instance() };

            BOOST_CHECK(unit1 == difference_rational_type{ 123 } );
        }
        {
            const unit_type unit1{ 123, unit_details_type::instance() };

            BOOST_CHECK(unit1 == static_cast<difference_rational_type::int_type>(123) );
        }
        {
            const unit_type unit1{ 456, unit_details_type::instance() };

            BOOST_CHECK(unit1 != difference_rational_type{ 123 });
        }
    }

    BOOST_AUTO_TEST_CASE(operator_less_than)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1{ 123, unit_details_type::instance() };

            BOOST_CHECK(unit1 < difference_rational_type{ 456 });
        }
        {
            const unit_type unit1{ 123, unit_details_type::instance() };

            BOOST_CHECK(unit1 < static_cast<difference_rational_type::int_type>(456));
        }
    }

    BOOST_AUTO_TEST_CASE(operator_greater_than)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1{ 456, unit_details_type::instance() };

            BOOST_CHECK(unit1 > difference_rational_type{ 123 });
        }
        {
            const unit_type unit1{ 456, unit_details_type::instance() };

            BOOST_CHECK(unit1 > static_cast<difference_rational_type::int_type>(123));
        }
    }

    BOOST_AUTO_TEST_CASE(add)
    {
        BOOST_TEST_PASSPOINT();

        unit_type unit1{ 456, unit_details_type::instance() };

        unit1 += 123;

        BOOST_TEST(unit1.value() == 579);
    }

    BOOST_AUTO_TEST_CASE(subtract)
    {
        BOOST_TEST_PASSPOINT();

        unit_type unit1{ 456, unit_details_type::instance() };

        unit1 -= 123;

        BOOST_TEST(unit1.value() == 333);
    }

    BOOST_AUTO_TEST_CASE(multiply)
    {
        BOOST_TEST_PASSPOINT();

        unit_type unit1{ 456, unit_details_type::instance() };

        unit1.multiply(123);

        BOOST_TEST(unit1.value() == 56088);
    }

    BOOST_AUTO_TEST_CASE(divide_by)
    {
        BOOST_TEST_PASSPOINT();

        {
            unit_type unit1{ 456, unit_details_type::instance() };

            unit1.divide_by(152);

            BOOST_TEST(unit1.value() == 3);
        }
        {
            const unit_type unit1{ 456, unit_details_type::instance() };
            const unit_type unit2{ 152, unit_details_type::instance() };

            BOOST_TEST(unit1.divide_by(unit2) == 3);
        }
    }

    BOOST_AUTO_TEST_CASE(value)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit{ 123, unit_details_type::instance() };

        BOOST_TEST(unit.value() == 123);
    }

    BOOST_AUTO_TEST_CASE(to_pixels)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit{ 123, unit_details_type::instance() };

        BOOST_TEST(unit.to_pixels<int>() == 123);
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit{ 42, unit_details_type::instance() };

        BOOST_TEST(&unit.details() == &unit_details_type::instance());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
