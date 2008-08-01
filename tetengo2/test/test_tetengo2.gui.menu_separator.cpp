/*! \file
    \brief Test of class tetengo2::gui::win32::menu_separator.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <cstddef>
#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.menu_separator.h"

#include "test_tetengo2.gui.menu_separator.h"


namespace test_tetengo2 { namespace gui
{
    // functions

    boost::unit_test::test_suite* menu_separator::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::menu_separator");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(is_command));
        p_suite->add(BOOST_TEST_CASE(is_popup));
        p_suite->add(BOOST_TEST_CASE(is_separator));
        p_suite->add(BOOST_TEST_CASE(handle));

        return p_suite;
    }

    void menu_separator::construction()
    {
        BOOST_CHECKPOINT("");

        {
            const tetengo2::gui::menu_separator<const void*, std::wstring>
            menu_separator;

            BOOST_CHECK(menu_separator.handle() == NULL);
        }
    }

    void menu_separator::is_command()
    {
        BOOST_CHECKPOINT("");

        {
            const tetengo2::gui::menu_separator<const void*, std::wstring>
            menu_separator;

            BOOST_CHECK(!menu_separator.is_command());
        }
    }

    void menu_separator::is_popup()
    {
        BOOST_CHECKPOINT("");

        {
            const tetengo2::gui::menu_separator<const void*, std::wstring>
            menu_separator;

            BOOST_CHECK(!menu_separator.is_popup());
        }
    }

    void menu_separator::is_separator()
    {
        BOOST_CHECKPOINT("");

        {
            const tetengo2::gui::menu_separator<const void*, std::wstring>
            menu_separator;

            BOOST_CHECK(menu_separator.is_separator());
        }
    }

    void menu_separator::handle()
    {
        BOOST_CHECKPOINT("");

        {
            const tetengo2::gui::menu_separator<const void*, std::wstring>
            menu_separator;

            BOOST_CHECK(menu_separator.handle() == NULL);
        }
    }

}}
