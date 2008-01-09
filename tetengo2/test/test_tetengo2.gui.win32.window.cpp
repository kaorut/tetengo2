/*! \file
    \brief Test of class tetengo2::gui::win32::window.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "tetengo2.gui.win32.window.h"

#include "test_tetengo2.gui.win32.window.h"


namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* window::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32::window");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(handle));
        p_suite->add(BOOST_TEST_CASE(add_window_observer));

        return p_suite;
    }

    void window::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void window::handle()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void window::add_window_observer()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}
