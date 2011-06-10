/*! \file
    \brief Test of class tetengo2::gui::unit::unit.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.unit.h"

#include "tetengo2.gui.unit.unit.h"


/*
namespace
{
    // types

    typedef
        tetengo2::gui::unit::unit<int, int, tetengo2::detail::stub::unit>
        unit_type;

    typedef
        tetengo2::gui::unit::unit<
            unsigned short, unsigned short, tetengo2::detail::stub::unit
        >
        another_unit_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(unit)
BOOST_AUTO_TEST_SUITE(unit)
    // test cases

    BOOST_AUTO_TEST_CASE(from_pixels)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit = unit_type::from_pixels(123 * 12);

        BOOST_CHECK_EQUAL(unit.value(), 123);
    }

    BOOST_AUTO_TEST_CASE(from)
    {
        BOOST_TEST_PASSPOINT();

        const another_unit_type another_unit(123);
        const unit_type unit = unit_type::from(another_unit);

        BOOST_CHECK_EQUAL(unit.value(), 123);
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit(123);
    }

    BOOST_AUTO_TEST_CASE(operator_plus_assign)
    {
        BOOST_TEST_PASSPOINT();

        {
            unit_type unit1(456);
            const unit_type unit2(123);

            unit1 += unit2;

            BOOST_CHECK_EQUAL(unit1.value(), 579);
        }
        {
            BOOST_TEST_PASSPOINT();

            unit_type unit1(456);

            unit1 += 123;

            BOOST_CHECK_EQUAL(unit1.value(), 579);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_minus_assign)
    {
        BOOST_TEST_PASSPOINT();

        {
            unit_type unit1(456);
            const unit_type unit2(123);

            unit1 -= unit2;

            BOOST_CHECK_EQUAL(unit1.value(), 333);
        }
        {
            unit_type unit1(456);

            unit1 -= 123;

            BOOST_CHECK_EQUAL(unit1.value(), 333);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1(123);
            const unit_type unit2(123);

            BOOST_CHECK(unit1 == unit2);
        }
        {
            const unit_type unit1(456);
            const unit_type unit2(123);

            BOOST_CHECK(unit1 != unit2);
        }
        {
            const unit_type unit1(123);

            BOOST_CHECK(unit1 == 123);
        }
        {
            const unit_type unit1(456);

            BOOST_CHECK(unit1 != 123);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_less)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1(123);
            const unit_type unit2(456);

            BOOST_CHECK(unit1 < unit2);
        }
        {
            const unit_type unit1(456);
            const unit_type unit2(123);

            BOOST_CHECK(unit1 > unit2);
        }
        {
            const unit_type unit1(123);

            BOOST_CHECK(unit1 < 456);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_greater)
    {
        BOOST_TEST_PASSPOINT();

        {
            const unit_type unit1(456);

            BOOST_CHECK(unit1 > 123);
        }
    }

    BOOST_AUTO_TEST_CASE(value)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit(123);

        BOOST_CHECK_EQUAL(unit.value(), 123);
    }

    BOOST_AUTO_TEST_CASE(to_pixels)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit(123);

        BOOST_CHECK_EQUAL(unit.to_pixels(), 123 * 12);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
*/