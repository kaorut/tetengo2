/*! \file
    \brief Test of class tetengo2::gui::unit::point.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <cstddef>
#include <utility>

#include <boost/rational.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/unit/point.h>
#include <tetengo2/type_list.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using difference_rational_type = boost::rational<tetengo2::type_list::difference_type>;

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using unit_details_type = detail_type_list_type::unit_type;

    using unit_type = tetengo2::gui::unit::point<boost::rational<std::ptrdiff_t>>;

    using another_unit_type = tetengo2::gui::unit::point<boost::rational<std::size_t>>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(unit)
BOOST_AUTO_TEST_SUITE(point)
    // test cases

    BOOST_AUTO_TEST_CASE(from)
    {
        BOOST_TEST_PASSPOINT();

        const auto unit = unit_type::from(another_unit_type{ 12, unit_details_type::instance() });

        BOOST_TEST(unit.value() == 12);
    }

    BOOST_AUTO_TEST_CASE(from_pixels)
    {
        BOOST_TEST_PASSPOINT();

        const auto unit = unit_type::from_pixels(16, unit_details_type::instance());

        BOOST_TEST(unit.value() == 12);
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const difference_rational_type value{ 12 };
            const unit_type unit{ std::move(value), unit_details_type::instance() };
        }
        {
            const unit_type unit{ 12, unit_details_type::instance() };
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1{ 12, unit_details_type::instance() };

            BOOST_CHECK(unit1 == difference_rational_type{ 12 });
        }
        {
            const unit_type unit1{ 12, unit_details_type::instance() };

            BOOST_CHECK(unit1 == static_cast<difference_rational_type::int_type>(12));
        }
        {
            const unit_type unit1{ 34, unit_details_type::instance() };

            BOOST_CHECK(unit1 != difference_rational_type{ 12 });
        }
    }

    BOOST_AUTO_TEST_CASE(operator_less_than)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1{ 12, unit_details_type::instance() };

            BOOST_CHECK(unit1 < difference_rational_type{ 34 });
        }
        {
            const unit_type unit1{ 12, unit_details_type::instance() };

            BOOST_CHECK(unit1 < static_cast<difference_rational_type::int_type>(34));
        }
    }

    BOOST_AUTO_TEST_CASE(operator_greater_than)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1{ 34, unit_details_type::instance() };

            BOOST_CHECK(unit1 > difference_rational_type{ 12 });
        }
        {
            const unit_type unit1{ 34, unit_details_type::instance() };

            BOOST_CHECK(unit1 > static_cast<difference_rational_type::int_type>(12));
        }
    }

    BOOST_AUTO_TEST_CASE(add)
    {
        BOOST_TEST_PASSPOINT();

        unit_type unit1{ 34, unit_details_type::instance() };

        unit1.add(12);

        BOOST_TEST(unit1.value() == 46);
    }

    BOOST_AUTO_TEST_CASE(subtract)
    {
        BOOST_TEST_PASSPOINT();

        unit_type unit1{ 34, unit_details_type::instance() };

        unit1.subtract(12);

        BOOST_TEST(unit1.value() == 22);
    }

    BOOST_AUTO_TEST_CASE(multiply)
    {
        BOOST_TEST_PASSPOINT();

        unit_type unit1{ 34, unit_details_type::instance() };

        unit1.multiply(12);

        BOOST_TEST(unit1.value() == 408);
    }

    BOOST_AUTO_TEST_CASE(divide_by)
    {
        BOOST_TEST_PASSPOINT();

        {
            unit_type unit1{ 36, unit_details_type::instance() };

            unit1.divide_by(12);

            BOOST_TEST(unit1.value() == 3);
        }
        {
            const unit_type unit1{ 36, unit_details_type::instance() };
            const unit_type unit2{ 12, unit_details_type::instance() };

            BOOST_TEST(unit1.divide_by(unit2) == 3);
        }
    }

    BOOST_AUTO_TEST_CASE(value)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit{ 12, unit_details_type::instance() };

        BOOST_TEST(unit.value() == 12);
    }

    BOOST_AUTO_TEST_CASE(to_pixels)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit{ 12, unit_details_type::instance() };

        BOOST_TEST(unit.to_pixels<std::ptrdiff_t>() == 16);
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
