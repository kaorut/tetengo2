/*! \file
    \brief Test of class tetengo2::gui::win32::alert.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

//#include <cstddef>

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.win32.alert.h"

#include "stub_tetengo2.encode.h"


namespace
{
    // types

    typedef
        tetengo2::gui::win32::alert< ::HWND, stub_tetengo2::encode>
        alert_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(win32)
BOOST_AUTO_TEST_SUITE(alert)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        alert_type(NULL);

        alert_type(reinterpret_cast< ::HWND>(0x123456));
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
