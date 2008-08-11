/*! \file
    \brief Test of class tetengo2::gui::win32::menu_separator.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <cstddef>
#include <string>

#include <boost/test/unit_test.hpp>

#include "stub_tetengo2.encode.h"
#include "tetengo2.gui.menu_item.h"
#include "tetengo2.gui.menu_observer.h"

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

        typedef
            tetengo2::gui::menu_item<
                unsigned int,
                const void*,
                std::wstring,
                stub_tetengo2::encode,
                tetengo2::gui::menu_observer
            >
            menu_item_type;
        typedef
            tetengo2::gui::menu_separator<menu_item_type> menu_separator_type;

        {
            const menu_separator_type menu_separator;

            BOOST_CHECK(menu_separator.handle() == NULL);
        }
    }

    void menu_separator::is_command()
    {
        BOOST_CHECKPOINT("");

        typedef
            tetengo2::gui::menu_item<
                unsigned int,
                const void*,
                std::wstring,
                stub_tetengo2::encode,
                tetengo2::gui::menu_observer
            >
            menu_item_type;
        typedef
            tetengo2::gui::menu_separator<menu_item_type> menu_separator_type;

        {
            const menu_separator_type menu_separator;

            BOOST_CHECK(!menu_separator.is_command());
        }
    }

    void menu_separator::is_popup()
    {
        BOOST_CHECKPOINT("");

        typedef
            tetengo2::gui::menu_item<
                unsigned int,
                const void*,
                std::wstring,
                stub_tetengo2::encode,
                tetengo2::gui::menu_observer
            >
            menu_item_type;
        typedef
            tetengo2::gui::menu_separator<menu_item_type> menu_separator_type;

        {
            const menu_separator_type menu_separator;

            BOOST_CHECK(!menu_separator.is_popup());
        }
    }

    void menu_separator::is_separator()
    {
        BOOST_CHECKPOINT("");

        typedef
            tetengo2::gui::menu_item<
                unsigned int,
                const void*,
                std::wstring,
                stub_tetengo2::encode,
                tetengo2::gui::menu_observer
            >
            menu_item_type;
        typedef
            tetengo2::gui::menu_separator<menu_item_type> menu_separator_type;

        {
            const menu_separator_type menu_separator;

            BOOST_CHECK(menu_separator.is_separator());
        }
    }

    void menu_separator::handle()
    {
        BOOST_CHECKPOINT("");

        typedef
            tetengo2::gui::menu_item<
                unsigned int,
                const void*,
                std::wstring,
                stub_tetengo2::encode,
                tetengo2::gui::menu_observer
            >
            menu_item_type;
        typedef
            tetengo2::gui::menu_separator<menu_item_type> menu_separator_type;

        {
            const menu_separator_type menu_separator;

            BOOST_CHECK(menu_separator.handle() == NULL);
        }
    }

}}
