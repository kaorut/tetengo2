/*! \file
    \brief Test of class tetengo2::gui::drawing::system_color_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.drawing.h"

#include "tetengo2.gui.drawing.color.h"

#include "tetengo2.gui.drawing.system_color_set.h"


namespace
{
    // types

    typedef
        tetengo2::gui::drawing::system_color_set<
            tetengo2::gui::drawing::color<unsigned char>,
            tetengo2::detail::stub::drawing
        >
        system_color_set_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(system_color_set)
    // test cases

    BOOST_AUTO_TEST_CASE(dialog_background)
    {
        BOOST_TEST_PASSPOINT();

        system_color_set_type::dialog_background();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
