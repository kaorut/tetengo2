/*! \file
    \brief Test of class tetengo2::gui::fixture.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.gui_fixture.h"

#include "tetengo2.gui.fixture.h"


namespace
{
    // types

    using fixture_type = tetengo2::gui::fixture<tetengo2::detail::stub::gui_fixture>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(fixture)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const fixture_type fixture;
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
