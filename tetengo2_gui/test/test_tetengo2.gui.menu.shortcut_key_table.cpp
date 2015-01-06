/*! \file
    \brief Test of class tetengo2::gui::menu::shortcut_key_table.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <iterator>
#include <memory>
#include <utility>
#include <vector>

#include <boost/iterator/indirect_iterator.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using ui_encoder_type = common_type_list_type::ui_encoder_type;

    using menu_details_type = detail_type_list_type::menu_type;

    using virtual_key_details_type = detail_type_list_type::virtual_key_type;

    using menu_base_type =
        tetengo2::gui::menu::menu_base<string_type, ui_encoder_type, menu_details_type, virtual_key_details_type>;

    using virtual_key_type = tetengo2::gui::virtual_key<string_type, virtual_key_details_type>;

    using shortcut_key_type = tetengo2::gui::menu::shortcut_key<string_type, virtual_key_details_type>;

    using shortcut_key_table_type =
        tetengo2::gui::menu::shortcut_key_table<
            string_type, ui_encoder_type, menu_details_type, virtual_key_details_type
        >;

    class concrete_menu : public menu_base_type
    {
    public:
        // constructors and destructor

        explicit concrete_menu(string_type text)
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
        const override
        {
            return menu_details_type::menu_command_style<menu_base_type>();
        }


    };


    // functions

    std::vector<std::unique_ptr<concrete_menu>> make_menus0()
    {
        return std::vector<std::unique_ptr<concrete_menu>>();
    }

    std::vector<std::unique_ptr<concrete_menu>> make_menus1()
    {
        std::vector<std::unique_ptr<concrete_menu>> menus{};

        menus.push_back(tetengo2::stdalt::make_unique<concrete_menu>(string_type{ TETENGO2_TEXT("hoge") }));
        menus.push_back(
            tetengo2::stdalt::make_unique<concrete_menu>(
                string_type{ TETENGO2_TEXT("fuga") },
                shortcut_key_type{ virtual_key_type::char_a(), false, true, false }
            )
        );
        menus.push_back(
            tetengo2::stdalt::make_unique<concrete_menu>(
                string_type{ TETENGO2_TEXT("piyo") }, shortcut_key_type{ virtual_key_type::del(), false, true, true }
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
            const shortcut_key_table_type shortcut_key_table{};
        }
        {
            const auto menus = make_menus0();
            const shortcut_key_table_type shortcut_key_table{
                boost::make_indirect_iterator(menus.begin()), boost::make_indirect_iterator(menus.end())
            };
        }
        {
            const auto menus = make_menus1();
            const shortcut_key_table_type shortcut_key_table{
                boost::make_indirect_iterator(menus.begin()), boost::make_indirect_iterator(menus.end())
            };
        }
    }

    BOOST_AUTO_TEST_CASE(begin)
    {
        BOOST_TEST_PASSPOINT();

        {
            const auto menus = make_menus0();
            const shortcut_key_table_type shortcut_key_table{
                boost::make_indirect_iterator(menus.begin()), boost::make_indirect_iterator(menus.end())
            };

            shortcut_key_table.begin();
        }
        {
            const auto menus = make_menus1();
            const shortcut_key_table_type shortcut_key_table{
                boost::make_indirect_iterator(menus.begin()), boost::make_indirect_iterator(menus.end())
            };

            const auto iterator = shortcut_key_table.begin();

            BOOST_CHECK(iterator->first == shortcut_key_type(virtual_key_type::char_a(), false, true, false));
        }
    }

    BOOST_AUTO_TEST_CASE(end)
    {
        BOOST_TEST_PASSPOINT();

        {
            const auto menus = make_menus0();
            const shortcut_key_table_type shortcut_key_table{
                boost::make_indirect_iterator(menus.begin()), boost::make_indirect_iterator(menus.end())
            };

            const auto iterator = shortcut_key_table.end();

            BOOST_CHECK(std::distance(shortcut_key_table.begin(), iterator) == 0);
        }
        {
            const auto menus = make_menus1();
            const shortcut_key_table_type shortcut_key_table{
                boost::make_indirect_iterator(menus.begin()), boost::make_indirect_iterator(menus.end())
            };

            const auto iterator = shortcut_key_table.end();

            BOOST_CHECK(std::distance(shortcut_key_table.begin(), iterator) == 2);
        }
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const auto menus = make_menus0();
            const shortcut_key_table_type shortcut_key_table{
                boost::make_indirect_iterator(menus.begin()), boost::make_indirect_iterator(menus.end())
            };

            shortcut_key_table.details();
        }
        {
            const auto menus = make_menus0();
            shortcut_key_table_type shortcut_key_table{
                boost::make_indirect_iterator(menus.begin()), boost::make_indirect_iterator(menus.end())
            };

            shortcut_key_table.details();
        }
        {
            const auto menus = make_menus1();
            const shortcut_key_table_type shortcut_key_table{
                boost::make_indirect_iterator(menus.begin()), boost::make_indirect_iterator(menus.end())
            };

            shortcut_key_table.details();
        }
        {
            const auto menus = make_menus1();
            shortcut_key_table_type shortcut_key_table{
                boost::make_indirect_iterator(menus.begin()), boost::make_indirect_iterator(menus.end())
            };

            shortcut_key_table.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
