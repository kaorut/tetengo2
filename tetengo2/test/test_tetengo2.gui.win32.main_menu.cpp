/*! \file
    \brief Test of class tetengo2::gui::win32::main_menu.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.win32.main_menu.h"

#include "test_tetengo2.gui.win32.main_menu.h"


namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* main_menu::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32::main_menu");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(handle));
        p_suite->add(BOOST_TEST_CASE(menu_item_begin));
        p_suite->add(BOOST_TEST_CASE(menu_item_end));
        p_suite->add(BOOST_TEST_CASE(insert));
        p_suite->add(BOOST_TEST_CASE(erase));
        p_suite->add(BOOST_TEST_CASE(find_by_id));
        p_suite->add(BOOST_TEST_CASE(find_by_handle));

        return p_suite;
    }

    void main_menu::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void main_menu::handle()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void main_menu::menu_item_begin()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void main_menu::menu_item_end()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void main_menu::insert()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void main_menu::erase()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void main_menu::find_by_id()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void main_menu::find_by_handle()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}
