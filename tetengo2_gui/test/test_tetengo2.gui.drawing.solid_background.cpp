/*! \file
    \brief Test of class tetengo2::gui::drawing::solid_background.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.drawing.h"
#include "tetengo2.gui.drawing.color.h"

#include "tetengo2.gui.drawing.solid_background.h"


namespace
{
    // types

    typedef tetengo2::gui::drawing::color<unsigned char> color_type;

    typedef
        tetengo2::gui::drawing::solid_background<
            color_type, tetengo2::detail::stub::drawing
        >
        background_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(solid_background)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const background_type background(color_type(0x12, 0x34, 0x56, 0x78));
    }

    BOOST_AUTO_TEST_CASE(color)
    {
        BOOST_TEST_PASSPOINT();

        const background_type background(color_type(0x12, 0x34, 0x56, 0x78));

        BOOST_CHECK(background.color() == color_type(0x12, 0x34, 0x56, 0x78));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
