/*! \file
    \brief Test of class tetengo2::gui::measure.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <utility>

//#include <boost/rational.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.unit.pixel.h"

#include "tetengo2.gui.measure.h"


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
    // test cases

    BOOST_AUTO_TEST_CASE(to_pixels)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::gui::unit::pixel<int> value(123);

            const int pixels = tetengo2::gui::to_pixels<int>(value);

            BOOST_CHECK_EQUAL(pixels, 123);
        }
        {
            const int value = 456;

            const int pixels = tetengo2::gui::to_pixels<int>(value);

            BOOST_CHECK_EQUAL(pixels, 456);
        }
    }

    BOOST_AUTO_TEST_CASE(to_unit)
    {
        BOOST_TEST_PASSPOINT();

        {
            typedef tetengo2::gui::unit::pixel<int> unit_type;
            const int value = 123;

            const unit_type unit = tetengo2::gui::to_unit<unit_type>(value);

            BOOST_CHECK_EQUAL(unit.value(), 123);
        }
        {
            typedef int unit_type;
            const int value = 456;

            const unit_type unit = tetengo2::gui::to_unit<unit_type>(value);

            BOOST_CHECK_EQUAL(unit, 456);
        }
    }

    BOOST_AUTO_TEST_CASE(ceil)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::gui::unit::pixel<boost::rational<int>> value(boost::rational<int>(3, 2));

            const int ceiling = tetengo2::gui::ceil<int>(value);

            BOOST_CHECK_EQUAL(ceiling, 2);
        }
        {
            const int value = 42;

            const int ceiling = tetengo2::gui::ceil<int>(value);

            BOOST_CHECK_EQUAL(ceiling, 42);
        }
    }

    BOOST_AUTO_TEST_CASE(floor)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::gui::unit::pixel<boost::rational<int>> value(boost::rational<int>(3, 2));

            const int floor = tetengo2::gui::floor<int>(value);

            BOOST_CHECK_EQUAL(floor, 1);
        }
        {
            const int value = 42;

            const int floor = tetengo2::gui::floor<int>(value);

            BOOST_CHECK_EQUAL(floor, 42);
        }
    }


BOOST_AUTO_TEST_SUITE(position)
    // test cases

    BOOST_AUTO_TEST_CASE(left)
    {
        BOOST_TEST_PASSPOINT();

        typedef std::pair<int, int> position_type;
        const position_type position = position_type(123, 456);

        BOOST_CHECK_EQUAL(tetengo2::gui::position<position_type>::left(position), 123);
    }

    BOOST_AUTO_TEST_CASE(top)
    {
        BOOST_TEST_PASSPOINT();

        typedef std::pair<int, int> position_type;
        const position_type position = position_type(123, 456);

        BOOST_CHECK_EQUAL(tetengo2::gui::position<position_type>::top(position), 456);
    }

    BOOST_AUTO_TEST_CASE(make_position)
    {
        BOOST_TEST_PASSPOINT();

        typedef std::pair<int, int> position_type;
        const position_type position = tetengo2::gui::position<position_type>::make(123, 456);

        BOOST_CHECK_EQUAL(position.first, 123);
        BOOST_CHECK_EQUAL(position.second, 456);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(dimension)
    // test cases

    BOOST_AUTO_TEST_CASE(width)
    {
        BOOST_TEST_PASSPOINT();

        typedef std::pair<int, int> dimension_type;
        const dimension_type dimension = dimension_type(123, 456);

        BOOST_CHECK_EQUAL(tetengo2::gui::dimension<dimension_type>::width(dimension), 123);
    }

    BOOST_AUTO_TEST_CASE(height)
    {
        BOOST_TEST_PASSPOINT();

        typedef std::pair<int, int> dimension_type;
        const dimension_type dimension = dimension_type(123, 456);

        BOOST_CHECK_EQUAL(tetengo2::gui::dimension<dimension_type>::height(dimension), 456);
    }

    BOOST_AUTO_TEST_CASE(make_dimension)
    {
        BOOST_TEST_PASSPOINT();

        typedef std::pair<int, int> dimension_type;
        const dimension_type dimension = tetengo2::gui::dimension<dimension_type>::make(123, 456);

        BOOST_CHECK_EQUAL(dimension.first, 123);
        BOOST_CHECK_EQUAL(dimension.second, 456);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
