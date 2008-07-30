/*! \file
    \brief Test of class tetengo2::gui::win32::menu_command.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.menu_command.h"

#include "test_tetengo2.gui.menu_command.h"


namespace test_tetengo2 { namespace gui
{
    // functions

    boost::unit_test::test_suite* menu_command::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::menu_command");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(command));
        p_suite->add(BOOST_TEST_CASE(set_command));

        return p_suite;
    }

    void menu_command::construction()
    {
        BOOST_CHECKPOINT("");

        typedef
            tetengo2::gui::menu_command<std::wstring, std::wstring>
            menu_command_type;

        {
            const menu_command_type menu_command(L"", L"");

            BOOST_CHECK(menu_command.command() == L"");
        }
        {
            const menu_command_type menu_command(L"", L"a");

            BOOST_CHECK(menu_command.command() == L"a");
        }
        {
            const menu_command_type menu_command(L"a", L"");

            BOOST_CHECK(menu_command.command() == L"");
        }
        {
            const menu_command_type menu_command(L"a", L"a");

            BOOST_CHECK(menu_command.command() == L"a");
        }
    }

    void menu_command::command()
    {
        BOOST_CHECKPOINT("");

        typedef
            tetengo2::gui::menu_command<std::wstring, std::wstring>
            menu_command_type;

        {
            const menu_command_type menu_command(L"", L"");

            BOOST_CHECK(menu_command.command() == L"");
        }
        {
            const menu_command_type menu_command(L"", L"a");

            BOOST_CHECK(menu_command.command() == L"a");
        }
    }

    void menu_command::set_command()
    {
        BOOST_CHECKPOINT("");

        typedef
            tetengo2::gui::menu_command<std::wstring, std::wstring>
            menu_command_type;

        {
            menu_command_type menu_command(L"", L"");

            menu_command.set_command(L"x");

            BOOST_CHECK(menu_command.command() == L"x");
        }
        {
            menu_command_type menu_command(L"", L"a");

            menu_command.set_command(L"x");

            BOOST_CHECK(menu_command.command() == L"x");
        }
        {
            menu_command_type menu_command(L"", L"a");

            menu_command.set_command(L"");

            BOOST_CHECK(menu_command.command() == L"");
        }
    }


}}
