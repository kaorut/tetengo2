/*! \file
    \brief Test of class tetengo2::gui::measure.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

//#include <utility>

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
            const tetengo2::gui::unit::pixel<int, int> value(123);

            const int pixels = tetengo2::gui::to_pixels<int>(value);

            BOOST_CHECK_EQUAL(pixels, 123);
        }
        {
            const int value = 456;

            const int pixels = tetengo2::gui::to_pixels<int>(value);

            BOOST_CHECK_EQUAL(pixels, 456);
        }
    }

    BOOST_AUTO_TEST_CASE(left)
    {
        BOOST_TEST_PASSPOINT();

        const std::pair<int, int> position = std::make_pair(123, 456);

        BOOST_CHECK_EQUAL(tetengo2::gui::left(position), 123);
    }

    BOOST_AUTO_TEST_CASE(top)
    {
        BOOST_TEST_PASSPOINT();

        const std::pair<int, int> position = std::make_pair(123, 456);

        BOOST_CHECK_EQUAL(tetengo2::gui::top(position), 456);
    }

    BOOST_AUTO_TEST_CASE(width)
    {
        BOOST_TEST_PASSPOINT();

        const std::pair<int, int> dimension = std::make_pair(123, 456);

        BOOST_CHECK_EQUAL(tetengo2::gui::width(dimension), 123);
    }

    BOOST_AUTO_TEST_CASE(height)
    {
        BOOST_TEST_PASSPOINT();

        const std::pair<int, int> dimension = std::make_pair(123, 456);

        BOOST_CHECK_EQUAL(tetengo2::gui::height(dimension), 456);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
