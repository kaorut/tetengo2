/*! \file
    \brief Test of class tetengo2::gui::position.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/position.h>


namespace
{
    using position_type = tetengo2::gui::position;

    using value_type = position_type::value_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(position)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const position_type position{ value_type{ 42 }, value_type{ 24 } };
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        const position_type position1{ value_type{ 42 }, value_type{ 24 } };
        const position_type position2{ value_type{ 42 }, value_type{ 24 } };
        const position_type position3{ value_type{ 42 }, value_type{ 42 } };
        const position_type position4{ value_type{ 24 }, value_type{ 42 } };
        const position_type position5{ value_type{ 24 }, value_type{ 24 } };

        BOOST_CHECK(position1 == position2);
        BOOST_CHECK(position1 != position3);
        BOOST_CHECK(position1 != position4);
        BOOST_CHECK(position1 != position5);
    }

    BOOST_AUTO_TEST_CASE(left)
    {
        BOOST_TEST_PASSPOINT();

        const position_type position{ value_type{ 42 }, value_type{ 24 } };

        BOOST_TEST(position.left() == value_type{ 42 });
    }

    BOOST_AUTO_TEST_CASE(top)
    {
        BOOST_TEST_PASSPOINT();

        const position_type position{ value_type{ 42 }, value_type{ 24 } };

        BOOST_TEST(position.top() == value_type{ 24 });
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
