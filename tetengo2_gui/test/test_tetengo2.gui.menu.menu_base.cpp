/*! \file
    \brief Test of class tetengo2::gui::menu::menu_base.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <memory>
//#include <stdexcept>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.text.h"
#include "tetengo2.unique.h"

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_tetengo2::gui::gui_common_type_list, test_tetengo2::gui::type::gui_common::virtual_key
        >::type
        virtual_key_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::shortcut_key>::type
        shortcut_key_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::menu_details>::type
        menu_details_type;

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type string_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::menu_base>::type
        menu_base_type;

    class concrete_menu : public menu_base_type
    {
    public:
        // constructors and destructor

        concrete_menu(string_type text)
        :
        menu_base_type(std::move(text), menu_details_type::create_menu())
        {}

        concrete_menu(string_type text, shortcut_key_type shortcut_key_type)
        :
        menu_base_type(std::move(text), std::move(shortcut_key_type), menu_details_type::create_menu())
        {}


    private:
        // virtual functions

        virtual const style_type& style_impl()
        const
        {
            return menu_details_type::menu_command_style<menu_base_type>();
        }


    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
BOOST_AUTO_TEST_SUITE(menu_base)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));
    }

    BOOST_AUTO_TEST_CASE(text)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

        BOOST_CHECK(menu.text() == string_type(TETENGO2_TEXT("Tetengo")));
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

        BOOST_CHECK(&menu.style() == &menu_details_type::menu_command_style<menu_base_type>());
    }

    BOOST_AUTO_TEST_CASE(enabled)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

        BOOST_CHECK(menu.enabled());
    }

    BOOST_AUTO_TEST_CASE(set_enabled)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.set_enabled(true);

            BOOST_CHECK(menu.enabled());
        }
        {
            concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.set_enabled(false);

            BOOST_CHECK(!menu.enabled());
        }
    }

    BOOST_AUTO_TEST_CASE(state)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

        BOOST_CHECK(menu.state() == menu_base_type::state_type::default_);
    }

    BOOST_AUTO_TEST_CASE(set_state)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.set_state(menu_base_type::state_type::default_);

            BOOST_CHECK(menu.state() == menu_base_type::state_type::default_);
        }
        {
            concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.set_state(menu_base_type::state_type::checked);

            BOOST_CHECK(menu.state() == menu_base_type::state_type::checked);
        }
        {
            concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.set_state(menu_base_type::state_type::selected);

            BOOST_CHECK(menu.state() == menu_base_type::state_type::selected);
        }
    }

    BOOST_AUTO_TEST_CASE(has_shortcut_key)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            BOOST_CHECK(!menu.has_shortcut_key());
        }
        {
            const concrete_menu menu(
                string_type(TETENGO2_TEXT("Tetengo")),
                shortcut_key_type(virtual_key_type::char_a(), false, true, false)
            );

            BOOST_CHECK(menu.has_shortcut_key());
        }
    }

    BOOST_AUTO_TEST_CASE(shortcut_key)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            BOOST_CHECK_THROW(menu.shortcut_key(), std::logic_error);
        }
        {
            const concrete_menu menu(
                string_type(TETENGO2_TEXT("Tetengo")),
                shortcut_key_type(virtual_key_type::char_a(), false, true, false)
            );

            const auto& shortcut_key = menu.shortcut_key();
            BOOST_CHECK(shortcut_key.key() == virtual_key_type::char_a());
            BOOST_CHECK(!shortcut_key.shift());
            BOOST_CHECK(shortcut_key.control());
            BOOST_CHECK(!shortcut_key.meta());
        }
    }

    BOOST_AUTO_TEST_CASE(select)
    {
        BOOST_TEST_PASSPOINT();

        concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

        menu.select();
    }

    BOOST_AUTO_TEST_CASE(menu_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.menu_observer_set();
        }
        {
            concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.menu_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(begin)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.begin();
        }
        {
            concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.begin();
        }
    }

    BOOST_AUTO_TEST_CASE(end)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.end();
        }
        {
            concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.end();
        }
    }

    BOOST_AUTO_TEST_CASE(recursive_begin)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.recursive_begin();
        }
        {
            concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.recursive_begin();
        }
    }

    BOOST_AUTO_TEST_CASE(recursive_end)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.recursive_end();
        }
        {
            concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.recursive_end();
        }
    }

    BOOST_AUTO_TEST_CASE(insert)
    {
        BOOST_TEST_PASSPOINT();

        concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));
        auto p_child = tetengo2::make_unique<concrete_menu>(string_type(TETENGO2_TEXT("Hoge")));

        BOOST_CHECK_THROW(menu.insert(menu.begin(), std::move(p_child)), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(erase)
    {
        BOOST_TEST_PASSPOINT();

        concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

        BOOST_CHECK_THROW(menu.erase(menu.begin(), menu.begin()), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.details();
        }
        {
            concrete_menu menu(string_type(TETENGO2_TEXT("Tetengo")));

            menu.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
