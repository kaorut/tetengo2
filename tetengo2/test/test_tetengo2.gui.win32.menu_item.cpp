/*! \file
    \brief Test of class tetengo2::gui::win32::menu_item.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.win32.menu_item.h"

#include "test_tetengo2.gui.win32.menu_item.h"


namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* menu_item::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32::menu_item");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(id));
        p_suite->add(BOOST_TEST_CASE(text));
        p_suite->add(BOOST_TEST_CASE(set_text));
        p_suite->add(BOOST_TEST_CASE(select));
        p_suite->add(BOOST_TEST_CASE(add_menu_observer));

        return p_suite;
    }

    void menu_item::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void menu_item::id()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void menu_item::text()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void menu_item::set_text()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void menu_item::select()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void menu_item::add_menu_observer()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}
