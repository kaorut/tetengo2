/*! \file
    \brief Test of class tetengo2::gui::menu::menu_base.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>
//#include <string>
//#include <utility>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.menu.h"
#include "tetengo2.detail.stub.virtual_key.h"
#include "tetengo2.gui.menu.shortcut_key.h"
#include "tetengo2.gui.menu.traits.h"
#include "tetengo2.gui.message.menu_observer_set.h"
#include "tetengo2.gui.virtual_key.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"
#include "tetengo2.unique.h"

#include "tetengo2.gui.menu.menu_base.h"


namespace
{
    // types

    typedef
        tetengo2::gui::virtual_key<
            tetengo2::detail::stub::virtual_key<std::string>
        >
        virtual_key_type;

    typedef
        tetengo2::gui::menu::shortcut_key<virtual_key_type> shortcut_key_type;

    typedef
        tetengo2::text::encoding::locale<
            std::string, tetengo2::detail::stub::encoding
        >
        encoding_type;

    typedef
        tetengo2::text::encoder<encoding_type, encoding_type> encoder_type;

    typedef
        tetengo2::gui::menu::traits<
            std::string,
            shortcut_key_type,
            encoder_type,
            tetengo2::gui::message::menu_observer_set
        >
        menu_traits_type;

    typedef tetengo2::detail::stub::menu menu_details_type;

    typedef
        tetengo2::gui::menu::menu_base<menu_traits_type, menu_details_type>
        menu_base_type;

    class concrete_menu : public menu_base_type
    {
    public:
        // constructors and destructor

        concrete_menu(std::string&& text)
        :
        menu_base_type(
            std::forward<std::string>(text),
            menu_details_type::create_menu()
        )
        {}

        concrete_menu(
            std::string&&       text,
            shortcut_key_type&& shortcut_key_type
        )
        :
        menu_base_type(
            std::forward<std::string>(text),
            shortcut_key_type,
            menu_details_type::create_menu()
        )
        {}


    private:
        // virtual functions

        virtual const style_type& style_impl()
        const
        {
            return menu_details_type::menu_command_style();
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

        const concrete_menu menu(std::string("Tetengo"));
    }

    BOOST_AUTO_TEST_CASE(text)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_menu menu(std::string("Tetengo"));

        BOOST_CHECK(menu.text() == "Tetengo");
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_menu menu(std::string("Tetengo"));

        BOOST_CHECK(
            &menu.style() == &menu_details_type::menu_command_style()
        );
    }

    BOOST_AUTO_TEST_CASE(has_shortcut_key)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(std::string("Tetengo"));

            BOOST_CHECK(!menu.has_shortcut_key());
        }
        {
            const concrete_menu menu(
                std::string("Tetengo"),
                shortcut_key_type(
                    virtual_key_type::char_a(), false, true, false
                )
            );

            BOOST_CHECK(menu.has_shortcut_key());
        }
    }

    BOOST_AUTO_TEST_CASE(shortcut_key)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(std::string("Tetengo"));

            BOOST_CHECK_THROW(menu.shortcut_key(), std::logic_error);
        }
        {
            const concrete_menu menu(
                std::string("Tetengo"),
                shortcut_key_type(
                    virtual_key_type::char_a(), false, true, false
                )
            );

            const shortcut_key_type& shortcut_key = menu.shortcut_key();
            BOOST_CHECK(shortcut_key.key() == virtual_key_type::char_a());
            BOOST_CHECK(!shortcut_key.shift());
            BOOST_CHECK(shortcut_key.control());
            BOOST_CHECK(!shortcut_key.meta());
        }
    }

    BOOST_AUTO_TEST_CASE(select)
    {
        BOOST_TEST_PASSPOINT();

        concrete_menu menu(std::string("Tetengo"));

        menu.select();
    }

    BOOST_AUTO_TEST_CASE(menu_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(std::string("Tetengo"));

            menu.menu_observer_set();
        }
        {
            concrete_menu menu(std::string("Tetengo"));

            menu.menu_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(begin)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(std::string("Tetengo"));

            menu.begin();
        }
        {
            concrete_menu menu(std::string("Tetengo"));

            menu.begin();
        }
    }

    BOOST_AUTO_TEST_CASE(end)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(std::string("Tetengo"));

            menu.end();
        }
        {
            concrete_menu menu(std::string("Tetengo"));

            menu.end();
        }
    }

    BOOST_AUTO_TEST_CASE(recursive_begin)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(std::string("Tetengo"));

            menu.recursive_begin();
        }
        {
            concrete_menu menu(std::string("Tetengo"));

            menu.recursive_begin();
        }
    }

    BOOST_AUTO_TEST_CASE(recursive_end)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(std::string("Tetengo"));

            menu.recursive_end();
        }
        {
            concrete_menu menu(std::string("Tetengo"));

            menu.recursive_end();
        }
    }

    BOOST_AUTO_TEST_CASE(insert)
    {
        BOOST_TEST_PASSPOINT();

        concrete_menu menu(std::string("Tetengo"));
        std::unique_ptr<menu_base_type> p_child(
            tetengo2::make_unique<concrete_menu>(std::string("Hoge"))
        );

        // Assertion fails.
        //menu.insert(menu.begin(), std::move(p_child));
    }

    BOOST_AUTO_TEST_CASE(erase)
    {
        BOOST_TEST_PASSPOINT();

        concrete_menu menu(std::string("Tetengo"));

        // Assertion fails.
        //menu.erase(menu.begin(), menu.begin());
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(std::string("Tetengo"));

            menu.details();
        }
        {
            concrete_menu menu(std::string("Tetengo"));

            menu.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
