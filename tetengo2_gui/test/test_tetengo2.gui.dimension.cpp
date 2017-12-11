/*! \file
    \brief Test of class tetengo2::gui::dimension.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/stub/unit.h>
#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/factory.h>
#include <tetengo2/type_list.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    using unit_type = tetengo2::gui::unit::uem;

    using unit_factory_type = tetengo2::gui::unit::factory<unit_type>;

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using unit_details_type = detail_type_list_type::unit_type;

    using dimension_type = tetengo2::gui::dimension<unit_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(dimension)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const unit_factory_type unit_factory{ unit_details_type::instance() };

        {
            const dimension_type dimension{ unit_factory.make(42), unit_factory.make(24) };
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        const unit_factory_type unit_factory{ unit_details_type::instance() };

        const dimension_type dimension1{ unit_factory.make(42), unit_factory.make(24) };
        const dimension_type dimension2{ unit_factory.make(42), unit_factory.make(24) };
        const dimension_type dimension3{ unit_factory.make(42), unit_factory.make(42) };
        const dimension_type dimension4{ unit_factory.make(24), unit_factory.make(42) };
        const dimension_type dimension5{ unit_factory.make(24), unit_factory.make(24) };

        BOOST_CHECK(dimension1 == dimension2);
        BOOST_CHECK(dimension1 != dimension3);
        BOOST_CHECK(dimension1 != dimension4);
        BOOST_CHECK(dimension1 != dimension5);
    }

    BOOST_AUTO_TEST_CASE(width)
    {
        BOOST_TEST_PASSPOINT();

        const unit_factory_type unit_factory{ unit_details_type::instance() };

        const dimension_type dimension{ unit_factory.make(42), unit_factory.make(24) };

        BOOST_CHECK((dimension.width() == unit_factory.make(42)));
    }

    BOOST_AUTO_TEST_CASE(height)
    {
        BOOST_TEST_PASSPOINT();

        const unit_factory_type unit_factory{ unit_details_type::instance() };

        const dimension_type dimension{ unit_factory.make(42), unit_factory.make(24) };

        BOOST_CHECK((dimension.height() == unit_factory.make(24)));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
