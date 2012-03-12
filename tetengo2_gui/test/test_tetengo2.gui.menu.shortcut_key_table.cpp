/*! \file
    \brief Test of class tetengo2::gui::menu::shortcut_key_table.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <iterator>
//#include <memory>
//#include <string>
//#include <utility>
//#include <vector>

//#include <boost/iterator/indirect_iterator.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.menu.h"
#include "tetengo2.detail.stub.virtual_key.h"
#include "tetengo2.gui.menu.menu_base.h"
#include "tetengo2.gui.menu.shortcut_key.h"
#include "tetengo2.gui.menu.traits.h"
#include "tetengo2.gui.message.menu_observer_set.h"
#include "tetengo2.gui.virtual_key.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"
#include "tetengo2.unique.h"

#include "tetengo2.gui.menu.shortcut_key_table.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::virtual_key virtual_key_details_type;

    typedef
        tetengo2::gui::virtual_key<std::string, virtual_key_details_type>
        virtual_key_type;

    typedef
        tetengo2::gui::menu::shortcut_key<virtual_key_type>
        shortcut_key_type;

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

    typedef
        tetengo2::gui::menu::shortcut_key_table<
            shortcut_key_type, menu_base_type, menu_details_type
        >
        shortcut_key_table_type;

    class concrete_menu : public menu_base_type
    {
    public:
        // constructors and destructor

        explicit concrete_menu(std::string&& text)
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


    // functions

    std::vector<std::unique_ptr<concrete_menu>> make_menus0()
    {
        return std::vector<std::unique_ptr<concrete_menu>>();
    }

    std::vector<std::unique_ptr<concrete_menu>> make_menus1()
    {
        std::vector<std::unique_ptr<concrete_menu>> menus;

        menus.push_back(
            tetengo2::make_unique<concrete_menu>(
                std::string("hoge")
            )
        );
        menus.push_back(
            tetengo2::make_unique<concrete_menu>(
                std::string("fuga"),
                shortcut_key_type(
                    virtual_key_type::char_a(), false, true, false
                )
            )
        );
        menus.push_back(
            tetengo2::make_unique<concrete_menu>(
                std::string("piyo"),
                shortcut_key_type(
                    virtual_key_type::del(), false, true, true
                )
            )
        );

        return menus;
    }

}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
BOOST_AUTO_TEST_SUITE(shortcut_key_table)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const shortcut_key_table_type shortcut_key_table;
        }
        {
            const std::vector<std::unique_ptr<concrete_menu>> menus =
                make_menus0();
            const shortcut_key_table_type shortcut_key_table(
                boost::make_indirect_iterator(menus.begin()),
                boost::make_indirect_iterator(menus.end())
            );
        }
        {
            const std::vector<std::unique_ptr<concrete_menu>> menus =
                make_menus1();
            const shortcut_key_table_type shortcut_key_table(
                boost::make_indirect_iterator(menus.begin()),
                boost::make_indirect_iterator(menus.end())
            );
        }
    }

    BOOST_AUTO_TEST_CASE(begin)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::vector<std::unique_ptr<concrete_menu>> menus =
                make_menus0();
            const shortcut_key_table_type shortcut_key_table(
                boost::make_indirect_iterator(menus.begin()),
                boost::make_indirect_iterator(menus.end())
            );

            shortcut_key_table.begin();
        }
        {
            const std::vector<std::unique_ptr<concrete_menu>> menus =
                make_menus1();
            const shortcut_key_table_type shortcut_key_table(
                boost::make_indirect_iterator(menus.begin()),
                boost::make_indirect_iterator(menus.end())
            );

            const shortcut_key_table_type::iterator iterator =
                shortcut_key_table.begin();

            BOOST_CHECK(
                iterator->first ==
                shortcut_key_type(
                    virtual_key_type::char_a(), false, true, false
                )
            );
        }
    }

    BOOST_AUTO_TEST_CASE(end)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::vector<std::unique_ptr<concrete_menu>> menus =
                make_menus0();
            const shortcut_key_table_type shortcut_key_table(
                boost::make_indirect_iterator(menus.begin()),
                boost::make_indirect_iterator(menus.end())
            );

            const shortcut_key_table_type::iterator iterator =
                shortcut_key_table.end();

            BOOST_CHECK(
                std::distance(shortcut_key_table.begin(), iterator) == 0
            );
        }
        {
            const std::vector<std::unique_ptr<concrete_menu>> menus =
                make_menus1();
            const shortcut_key_table_type shortcut_key_table(
                boost::make_indirect_iterator(menus.begin()),
                boost::make_indirect_iterator(menus.end())
            );

            const shortcut_key_table_type::iterator iterator =
                shortcut_key_table.end();

            BOOST_CHECK(
                std::distance(shortcut_key_table.begin(), iterator) == 2
            );
        }
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const std::vector<std::unique_ptr<concrete_menu>> menus =
                make_menus0();
            const shortcut_key_table_type shortcut_key_table(
                boost::make_indirect_iterator(menus.begin()),
                boost::make_indirect_iterator(menus.end())
            );

            shortcut_key_table.details();
        }
        {
            const std::vector<std::unique_ptr<concrete_menu>> menus =
                make_menus0();
            shortcut_key_table_type shortcut_key_table(
                boost::make_indirect_iterator(menus.begin()),
                boost::make_indirect_iterator(menus.end())
            );

            shortcut_key_table.details();
        }
        {
            const std::vector<std::unique_ptr<concrete_menu>> menus =
                make_menus1();
            const shortcut_key_table_type shortcut_key_table(
                boost::make_indirect_iterator(menus.begin()),
                boost::make_indirect_iterator(menus.end())
            );

            shortcut_key_table.details();
        }
        {
            const std::vector<std::unique_ptr<concrete_menu>> menus =
                make_menus1();
            shortcut_key_table_type shortcut_key_table(
                boost::make_indirect_iterator(menus.begin()),
                boost::make_indirect_iterator(menus.end())
            );

            shortcut_key_table.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
