/*! \file
    \brief Test of class tetengo2::gui::dimension.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/stub/unit.h>
#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/type_list.h>


namespace
{
    using unit_type = tetengo2::gui::unit::em<tetengo2::type_list::size_type, tetengo2::detail::stub::unit>;

    using dimension_type = tetengo2::gui::dimension<unit_type>;

    using unit_type = typename dimension_type::unit_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(dimension)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const dimension_type dimension{ unit_type{ 42 }, unit_type{ 24 } };
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        const dimension_type dimension1{ unit_type{ 42 }, unit_type{ 24 } };
        const dimension_type dimension2{ unit_type{ 42 }, unit_type{ 24 } };
        const dimension_type dimension3{ unit_type{ 42 }, unit_type{ 42 } };
        const dimension_type dimension4{ unit_type{ 24 }, unit_type{ 42 } };
        const dimension_type dimension5{ unit_type{ 24 }, unit_type{ 24 } };

        BOOST_CHECK(dimension1 == dimension2);
        BOOST_CHECK(dimension1 != dimension3);
        BOOST_CHECK(dimension1 != dimension4);
        BOOST_CHECK(dimension1 != dimension5);
    }

    BOOST_AUTO_TEST_CASE(width)
    {
        BOOST_TEST_PASSPOINT();

        const dimension_type dimension{ unit_type{ 42 }, unit_type{ 24 } };

        BOOST_CHECK(dimension.width() == unit_type{ 42 });
    }

    BOOST_AUTO_TEST_CASE(height)
    {
        BOOST_TEST_PASSPOINT();

        const dimension_type dimension{ unit_type{ 42 }, unit_type{ 24 } };

        BOOST_CHECK(dimension.height() == unit_type{ 24 });
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
