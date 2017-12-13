/*! \file
    \brief Test of class tetengo2::gui::unit::factory.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/rational.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/unit/factory.h>
#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/type_list.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using difference_rational_type = boost::rational<tetengo2::type_list::difference_type>;

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using unit_details_type = detail_type_list_type::unit_type;

    using unit_type = tetengo2::gui::unit::em_for_test;

    using factory_type = tetengo2::gui::unit::factory<unit_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(unit)
BOOST_AUTO_TEST_SUITE(factory)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const factory_type factory{ unit_details_type::instance() };
    }

    BOOST_AUTO_TEST_CASE(make)
    {
        BOOST_TEST_PASSPOINT();

        const factory_type factory{ unit_details_type::instance() };

        BOOST_CHECK((factory.make(42) == unit_type{ 42 }));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
