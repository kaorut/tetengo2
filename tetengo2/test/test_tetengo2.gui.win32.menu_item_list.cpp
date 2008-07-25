/*! \file
    \brief Test of class tetengo2::gui::win32::menu_item_list.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.win32.menu_item_list.h"

#include "test_tetengo2.gui.win32.menu_item_list.h"


namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* menu_item_list::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32::menu_item_list");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(begin));
        p_suite->add(BOOST_TEST_CASE(end));
        p_suite->add(BOOST_TEST_CASE(insert));
        p_suite->add(BOOST_TEST_CASE(erase));

        return p_suite;
    }

    void menu_item_list::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void menu_item_list::begin()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void menu_item_list::end()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void menu_item_list::insert()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void menu_item_list::erase()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}
