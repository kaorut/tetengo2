/*! \file
    \brief Test of class tetengo2::gui::mouse_capture.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.mouse_capture.h"

#include "tetengo2.gui.mouse_capture.h"


namespace
{
    // types

    typedef tetengo2::gui::mouse_capture<tetengo2::detail::stub::mouse_capture> mouse_capture_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(mouse_capture)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const mouse_capture_type mouse_capture;
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
