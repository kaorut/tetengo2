/*! \file
    \brief Test of class tetengo2::gui::win32::window.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

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
        p_suite->add(BOOST_TEST_CASE(has_main_menu));
        p_suite->add(BOOST_TEST_CASE(main_menu));
        p_suite->add(BOOST_TEST_CASE(set_main_menu));
        p_suite->add(BOOST_TEST_CASE(add_window_observer));
        p_suite->add(BOOST_TEST_CASE(close));

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

    void window::has_main_menu()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void window::main_menu()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void window::set_main_menu()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void window::add_window_observer()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void window::close()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}
