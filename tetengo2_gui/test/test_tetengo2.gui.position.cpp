/*! \file
    \brief Test of class tetengo2::gui::position.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/stub/unit.h>
#include <tetengo2/gui/position.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/factory.h>
#include <tetengo2/type_list.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    using unit_type = tetengo2::gui::unit::em_for_test;

    using unit_factory_type = tetengo2::gui::unit::factory<unit_type>;

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using unit_details_type = detail_type_list_type::unit_type;

    using position_type = tetengo2::gui::position<unit_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(position)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const unit_factory_type unit_factory{ unit_details_type::instance() };

        {
            const position_type position{ unit_factory.make(42), unit_factory.make(24) };
        }
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        const unit_factory_type unit_factory{ unit_details_type::instance() };

        const position_type position1{ unit_factory.make(42), unit_factory.make(24) };
        const position_type position2{ unit_factory.make(42), unit_factory.make(24) };
        const position_type position3{ unit_factory.make(42), unit_factory.make(42) };
        const position_type position4{ unit_factory.make(24), unit_factory.make(42) };
        const position_type position5{ unit_factory.make(24), unit_factory.make(24) };

        BOOST_CHECK(position1 == position2);
        BOOST_CHECK(position1 != position3);
        BOOST_CHECK(position1 != position4);
        BOOST_CHECK(position1 != position5);
    }

    BOOST_AUTO_TEST_CASE(left)
    {
        BOOST_TEST_PASSPOINT();

        const unit_factory_type unit_factory{ unit_details_type::instance() };

        const position_type position{ unit_factory.make(42), unit_factory.make(24) };

        BOOST_CHECK((position.left() == unit_factory.make(42)));
    }

    BOOST_AUTO_TEST_CASE(top)
    {
        BOOST_TEST_PASSPOINT();

        const unit_factory_type unit_factory{ unit_details_type::instance() };

        const position_type position{ unit_factory.make(42), unit_factory.make(24) };

        BOOST_CHECK((position.top() == unit_factory.make(24)));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
