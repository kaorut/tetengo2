/*! \file
    \brief Test of class tetengo2::gui::menu_command.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if defined(_MSC_VER)

#include <cstddef>
#include <string>

#include <boost/test/unit_test.hpp>

#include "stub_tetengo2.encode.h"
#include "tetengo2.gui.menu_observer.h"
#include "tetengo2.gui.win32.menu_item.h"

#include "tetengo2.gui.menu_command.h"


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu_command)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_CHECKPOINT("");

        //typedef
        //    tetengo2::gui::win32::menu_item<
        //        unsigned int,
        //        const void*,
        //        std::wstring,
        //        stub_tetengo2::encode,
        //        tetengo2::gui::menu_observer
        //    >
        //    menu_item_type;
        //typedef tetengo2::gui::menu_command<menu_item_type> menu_command_type;

        //{
        //    const menu_command_type menu_command(L"");

        //    BOOST_CHECK(menu_command.text() == L"");
        //}
        //{
        //    const menu_command_type menu_command(L"a");

        //    BOOST_CHECK(menu_command.text() == L"a");
        //}
    }

    BOOST_AUTO_TEST_CASE(is_command)
    {
        BOOST_CHECKPOINT("");

        //typedef
        //    tetengo2::gui::win32::menu_item<
        //        unsigned int,
        //        const void*,
        //        std::wstring,
        //        stub_tetengo2::encode,
        //        tetengo2::gui::menu_observer
        //    >
        //    menu_item_type;
        //typedef tetengo2::gui::menu_command<menu_item_type> menu_command_type;

        //{
        //    const menu_command_type menu_command(L"");

        //    BOOST_CHECK(menu_command.is_command());
        //}
    }

    BOOST_AUTO_TEST_CASE(is_popup)
    {
        BOOST_CHECKPOINT("");

        //typedef
        //    tetengo2::gui::win32::menu_item<
        //        unsigned int,
        //        const void*,
        //        std::wstring,
        //        stub_tetengo2::encode,
        //        tetengo2::gui::menu_observer
        //    >
        //    menu_item_type;
        //typedef tetengo2::gui::menu_command<menu_item_type> menu_command_type;

        //{
        //    const menu_command_type menu_command(L"");

        //    BOOST_CHECK(!menu_command.is_popup());
        //}
    }

    BOOST_AUTO_TEST_CASE(is_separator)
    {
        BOOST_CHECKPOINT("");

        //typedef
        //    tetengo2::gui::win32::menu_item<
        //        unsigned int,
        //        const void*,
        //        std::wstring,
        //        stub_tetengo2::encode,
        //        tetengo2::gui::menu_observer
        //    >
        //    menu_item_type;
        //typedef tetengo2::gui::menu_command<menu_item_type> menu_command_type;

        //{
        //    const menu_command_type menu_command(L"");

        //    BOOST_CHECK(!menu_command.is_separator());
        //}
    }

    BOOST_AUTO_TEST_CASE(handle)
    {
        BOOST_CHECKPOINT("");

        //typedef
        //    tetengo2::gui::win32::menu_item<
        //        unsigned int,
        //        const void*,
        //        std::wstring,
        //        stub_tetengo2::encode,
        //        tetengo2::gui::menu_observer
        //    >
        //    menu_item_type;
        //typedef tetengo2::gui::menu_command<menu_item_type> menu_command_type;

        //{
        //    const menu_command_type menu_command(L"");

        //    BOOST_CHECK(menu_command.handle() == NULL);
        //}
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

#endif
