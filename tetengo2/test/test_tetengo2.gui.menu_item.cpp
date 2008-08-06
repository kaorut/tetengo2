/*! \file
    \brief Test of class tetengo2::gui::win32::menu_item.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <cstddef>
#include <memory>
#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.menu_observer.h"

#include "tetengo2.gui.menu_item.h"

#include "stub_tetengo2.encode.h"

#include "test_tetengo2.gui.menu_item.h"


namespace
{
    template <
        typename Id,
        typename Handle,
        typename String,
        template <typename Target, typename Source> class Encode,
        typename MenuObserver
    >
    class menu_item_driver :
        public tetengo2::gui::menu_item<
            Id, Handle, String, Encode, MenuObserver
        >
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

        virtual bool is_separator()
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
        p_suite->add(BOOST_TEST_CASE(id));
        p_suite->add(BOOST_TEST_CASE(text));
        p_suite->add(BOOST_TEST_CASE(set_text));
        p_suite->add(BOOST_TEST_CASE(select));
        p_suite->add(BOOST_TEST_CASE(add_menu_observer));

        return p_suite;
    }

    void menu_item::construction()
    {
        BOOST_CHECKPOINT("");

        typedef menu_item_driver<
            unsigned int,
            const void*,
            std::wstring,
            stub_tetengo2::encode,
            tetengo2::gui::menu_observer
        >
        menu_item_driver_type;

        {
            const menu_item_driver_type menu_item(L"");

            BOOST_CHECK(menu_item.text() == L"");
        }
        {
            const menu_item_driver_type menu_item(L"a");

            BOOST_CHECK(menu_item.text() == L"a");
        }
    }

    void menu_item::id()
    {
        BOOST_CHECKPOINT("");

        typedef menu_item_driver<
            unsigned int,
            const void*,
            std::wstring,
            stub_tetengo2::encode,
            tetengo2::gui::menu_observer
        >
        menu_item_driver_type;

        {
            const menu_item_driver_type menu_item1(L"");
            const menu_item_driver_type menu_item2(L"");

            BOOST_CHECK(menu_item1.id() != menu_item2.id());
        }
    }

    void menu_item::text()
    {
        BOOST_CHECKPOINT("");

        typedef menu_item_driver<
            unsigned int,
            const void*,
            std::wstring,
            stub_tetengo2::encode,
            tetengo2::gui::menu_observer
        >
        menu_item_driver_type;

        {
            const menu_item_driver_type menu_item(L"");

            BOOST_CHECK(menu_item.text() == L"");
        }
        {
            const menu_item_driver_type menu_item(L"a");

            BOOST_CHECK(menu_item.text() == L"a");
        }
    }

    void menu_item::set_text()
    {
        BOOST_CHECKPOINT("");

        typedef menu_item_driver<
            unsigned int,
            const void*,
            std::wstring,
            stub_tetengo2::encode,
            tetengo2::gui::menu_observer
        >
        menu_item_driver_type;

        {
            menu_item_driver_type menu_item(L"");

            menu_item.set_text(L"x");

            BOOST_CHECK(menu_item.text() == L"x");
        }
        {
            menu_item_driver_type menu_item(L"a");

            menu_item.set_text(L"x");

            BOOST_CHECK(menu_item.text() == L"x");
        }
        {
            menu_item_driver_type menu_item(L"a");

            menu_item.set_text(L"");

            BOOST_CHECK(menu_item.text() == L"");
        }
    }

    void menu_item::select()
    {
        BOOST_CHECKPOINT("");

        typedef menu_item_driver<
            unsigned int,
            const void*,
            std::wstring,
            stub_tetengo2::encode,
            tetengo2::gui::menu_observer
        >
        menu_item_driver_type;

        struct observer : public tetengo2::gui::menu_observer
        {
            bool m_selected;

            observer() : m_selected(false) {}

            virtual ~observer() throw () {}

            virtual void selected()
            {
                m_selected = true;
            }
        };

        {
            menu_item_driver_type menu_item(L"");
            
            std::auto_ptr<observer> p_observer(new observer());
            observer* const p_observer_alias = p_observer.get();
            menu_item.add_menu_observer(
                std::auto_ptr<tetengo2::gui::menu_observer>(p_observer)
            );

            menu_item.select();

            BOOST_CHECK(p_observer_alias->m_selected);
        }
    }

    void menu_item::add_menu_observer()
    {
        BOOST_CHECKPOINT("");

        typedef menu_item_driver<
            unsigned int,
            const void*,
            std::wstring,
            stub_tetengo2::encode,
            tetengo2::gui::menu_observer
        >
        menu_item_driver_type;

        {
            menu_item_driver_type menu_item(L"");

            std::auto_ptr<tetengo2::gui::menu_observer> p_observer(
                new tetengo2::gui::menu_observer()
            );

            menu_item.add_menu_observer(p_observer);
        }
    }


}}
