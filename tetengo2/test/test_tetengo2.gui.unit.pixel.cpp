/*! \file
    \brief Test of class tetengo2::gui::unit::pixel.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.unit.pixel.h"


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(unit)
BOOST_AUTO_TEST_SUITE(pixel)
    // test cases

    BOOST_AUTO_TEST_CASE(from_pixels)
    {
        BOOST_TEST_PASSPOINT();

        const tetengo2::gui::unit::pixel<int, int> unit =
            tetengo2::gui::unit::pixel<int, int>::from_pixels(123);

        BOOST_CHECK_EQUAL(unit.value(), 123);
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const tetengo2::gui::unit::pixel<int, int> unit(123);
    }

    BOOST_AUTO_TEST_CASE(operator_plus_assign)
    {
        BOOST_TEST_PASSPOINT();

        {
            tetengo2::gui::unit::pixel<int, int> unit1(456);
            const tetengo2::gui::unit::pixel<int, int> unit2(123);

            unit1 += unit2;

            BOOST_CHECK_EQUAL(unit1.value(), 579);
        }
        {
            BOOST_TEST_PASSPOINT();

            tetengo2::gui::unit::pixel<int, int> unit1(456);

            unit1 += 123;

            BOOST_CHECK_EQUAL(unit1.value(), 579);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_minus_assign)
    {
        BOOST_TEST_PASSPOINT();

        {
            tetengo2::gui::unit::pixel<int, int> unit1(456);
            const tetengo2::gui::unit::pixel<int, int> unit2(123);

            unit1 -= unit2;

            BOOST_CHECK_EQUAL(unit1.value(), 333);
        }
        {
            tetengo2::gui::unit::pixel<int, int> unit1(456);

            unit1 -= 123;

            BOOST_CHECK_EQUAL(unit1.value(), 333);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::gui::unit::pixel<int, int> unit1(123);
            const tetengo2::gui::unit::pixel<int, int> unit2(123);

            BOOST_CHECK(unit1 == unit2);
        }
        {
            const tetengo2::gui::unit::pixel<int, int> unit1(456);
            const tetengo2::gui::unit::pixel<int, int> unit2(123);

            BOOST_CHECK(unit1 != unit2);
        }
        {
            const tetengo2::gui::unit::pixel<int, int> unit1(123);

            BOOST_CHECK(unit1 == 123);
        }
        {
            const tetengo2::gui::unit::pixel<int, int> unit1(456);

            BOOST_CHECK(unit1 != 123);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_less)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::gui::unit::pixel<int, int> unit1(123);
            const tetengo2::gui::unit::pixel<int, int> unit2(456);

            BOOST_CHECK(unit1 < unit2);
        }
        {
            const tetengo2::gui::unit::pixel<int, int> unit1(456);
            const tetengo2::gui::unit::pixel<int, int> unit2(123);

            BOOST_CHECK(unit1 > unit2);
        }
        {
            const tetengo2::gui::unit::pixel<int, int> unit1(123);

            BOOST_CHECK(unit1 < 456);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_greater)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::gui::unit::pixel<int, int> unit1(456);

            BOOST_CHECK(unit1 > 123);
        }
    }

    BOOST_AUTO_TEST_CASE(value)
    {
        BOOST_TEST_PASSPOINT();

        const tetengo2::gui::unit::pixel<int, int> unit(123);

        BOOST_CHECK_EQUAL(unit.value(), 123);
    }

    BOOST_AUTO_TEST_CASE(to_pixels)
    {
        BOOST_TEST_PASSPOINT();

        const tetengo2::gui::unit::pixel<int, int> unit(123);

        BOOST_CHECK_EQUAL(unit.to_pixels(), 123);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
