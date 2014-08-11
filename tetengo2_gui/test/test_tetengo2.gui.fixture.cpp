/*! \file
    \brief Test of class tetengo2::gui::fixture.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.detail_type_list.h"


namespace
{
    // types

    using fixture_type =
        boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::gui_fixture>::type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(fixture)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const fixture_type fixture;
        boost::ignore_unused(fixture);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
