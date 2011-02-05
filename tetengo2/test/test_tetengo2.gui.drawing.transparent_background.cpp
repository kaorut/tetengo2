/*! \file
    \brief Test of class tetengo2::gui::drawing::win32::gdiplus::transparent_background.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.drawing.h"

#include "tetengo2.gui.drawing.transparent_background.h"


namespace
{
    // types

    typedef
        tetengo2::gui::drawing::transparent_background<
            tetengo2::detail::stub::drawing
        >
        background_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(win32)
BOOST_AUTO_TEST_SUITE(gdiplus)
BOOST_AUTO_TEST_SUITE(transparent_background)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const background_type background;
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
