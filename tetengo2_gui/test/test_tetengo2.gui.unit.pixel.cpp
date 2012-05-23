/*! \file
    \brief Test of class tetengo2::gui::unit::pixel.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<test_tetengo2::gui::unit_type_list, test_tetengo2::gui::type::unit::pixel>::type unit_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(unit)
BOOST_AUTO_TEST_SUITE(pixel)
    // test cases

    BOOST_AUTO_TEST_CASE(from_pixels)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit = unit_type::from_pixels(123);

        BOOST_CHECK_EQUAL(unit.value(), 123);
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const int value = 123;
            const unit_type unit(value);
        }
        {
            const unit_type unit(123);
        }
    }

    BOOST_AUTO_TEST_CASE(add)
    {
        BOOST_TEST_PASSPOINT();

        unit_type unit1(456);

        unit1 += 123;

        BOOST_CHECK_EQUAL(unit1.value(), 579);
    }

    BOOST_AUTO_TEST_CASE(subtract)
    {
        BOOST_TEST_PASSPOINT();

        unit_type unit1(456);

        unit1 -= 123;

        BOOST_CHECK_EQUAL(unit1.value(), 333);
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

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

        const unit_type unit1(123);

        BOOST_CHECK(unit1 < 456);
    }

    BOOST_AUTO_TEST_CASE(operator_greater)
    {
        BOOST_TEST_PASSPOINT();

        const unit_type unit1(456);

        BOOST_CHECK(unit1 > 123);
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

        BOOST_CHECK_EQUAL(unit.to_pixels<int>(), 123);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
