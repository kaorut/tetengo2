/*! \file
    \brief Test of class tetengo2::gui::dimension.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/dimension.h>


namespace
{
    using dimension_type = tetengo2::gui::dimension;

    using value_type = dimension_type::value_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(dimension)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const dimension_type dimension{ value_type{ 42 }, value_type{ 24 } };
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        const dimension_type dimension1{ value_type{ 42 }, value_type{ 24 } };
        const dimension_type dimension2{ value_type{ 42 }, value_type{ 24 } };
        const dimension_type dimension3{ value_type{ 42 }, value_type{ 42 } };
        const dimension_type dimension4{ value_type{ 24 }, value_type{ 42 } };
        const dimension_type dimension5{ value_type{ 24 }, value_type{ 24 } };

        BOOST_CHECK(dimension1 == dimension2);
        BOOST_CHECK(dimension1 != dimension3);
        BOOST_CHECK(dimension1 != dimension4);
        BOOST_CHECK(dimension1 != dimension5);
    }

    BOOST_AUTO_TEST_CASE(width)
    {
        BOOST_TEST_PASSPOINT();

        const dimension_type dimension{ value_type{ 42 }, value_type{ 24 } };

        BOOST_TEST(dimension.width() == value_type{ 42 });
    }

    BOOST_AUTO_TEST_CASE(height)
    {
        BOOST_TEST_PASSPOINT();

        const dimension_type dimension{ value_type{ 42 }, value_type{ 24 } };

        BOOST_TEST(dimension.height() == value_type{ 24 });
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
