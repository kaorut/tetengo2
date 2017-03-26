/*! \file
    \brief Test of class tetengo2::gui::fixture.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/core/ignore_unused.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using fixture_type = detail_type_list_type::gui_fixture_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(fixture)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const fixture_type fixture{};
        boost::ignore_unused(fixture);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
