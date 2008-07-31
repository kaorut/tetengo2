/*! \file
    \brief Test of class tetengo2::gui::win32::menu_item.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.menu_item.h"

#include "test_tetengo2.gui.menu_item.h"


namespace
{
    template <typename Handle, typename String>
    class menu_item_driver : public tetengo2::gui::menu_item<Handle, String>
    {
    public:
        // constructors and destructor

        menu_item_driver(const string_type& text)
        :
        menu_item(text)
        {}

        virtual ~menu_item_driver()
        throw ()
        {}


        // functions

        virtual bool is_command()
        const
        {
            return false;
        }

        virtual bool is_popup()
        const
        {
            return false;
        }

        virtual handle_type handle()
        const
        {
            return NULL;
        }


    };


}


namespace test_tetengo2 { namespace gui
{
    // functions

    boost::unit_test::test_suite* menu_item::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::menu_item");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(text));
        p_suite->add(BOOST_TEST_CASE(set_text));

        return p_suite;
    }

    void menu_item::construction()
    {
        BOOST_CHECKPOINT("");

        {
            const menu_item_driver<const void*, std::wstring> menu_item(L"");

            BOOST_CHECK(menu_item.text() == L"");
        }
        {
            const menu_item_driver<const void*, std::wstring> menu_item(L"a");

            BOOST_CHECK(menu_item.text() == L"a");
        }
    }

    void menu_item::text()
    {
        BOOST_CHECKPOINT("");

        {
            const menu_item_driver<const void*, std::wstring> menu_item(L"");

            BOOST_CHECK(menu_item.text() == L"");
        }
        {
            const menu_item_driver<const void*, std::wstring> menu_item(L"a");

            BOOST_CHECK(menu_item.text() == L"a");
        }
    }

    void menu_item::set_text()
    {
        BOOST_CHECKPOINT("");

        {
            menu_item_driver<const void*, std::wstring> menu_item(L"");

            menu_item.set_text(L"x");

            BOOST_CHECK(menu_item.text() == L"x");
        }
        {
            menu_item_driver<const void*, std::wstring> menu_item(L"a");

            menu_item.set_text(L"x");

            BOOST_CHECK(menu_item.text() == L"x");
        }
        {
            menu_item_driver<const void*, std::wstring> menu_item(L"a");

            menu_item.set_text(L"");

            BOOST_CHECK(menu_item.text() == L"");
        }
    }


}}
