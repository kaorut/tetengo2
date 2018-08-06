/*! \file
    \brief Test of class tetengo2::gui::menu::shortcut_key_table.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <iterator>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/menu/command.h>
#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/gui/menu/popup.h>
#include <tetengo2/gui/menu/shortcut_key.h>
#include <tetengo2/gui/menu/shortcut_key_table.h>
#include <tetengo2/gui/virtual_key.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using menu_base_type = tetengo2::gui::menu::menu_base;

    using virtual_key_type = tetengo2::gui::virtual_key;

    using shortcut_key_type = tetengo2::gui::menu::shortcut_key;

    using shortcut_key_table_type = tetengo2::gui::menu::shortcut_key_table;


    // functions

    std::unique_ptr<menu_base_type> create_menu0()
    {
        return std::make_unique<tetengo2::gui::menu::popup>(string_type{ TETENGO2_TEXT("hoge") });
    }

    std::unique_ptr<menu_base_type> create_menu1()
    {
        auto p_root = std::make_unique<tetengo2::gui::menu::popup>(string_type{ TETENGO2_TEXT("hoge") });

        p_root->insert(
            p_root->end(),
            std::make_unique<tetengo2::gui::menu::command>(
                string_type{ TETENGO2_TEXT("fuga") },
                shortcut_key_type{ virtual_key_type::char_a(), false, true, false }));
        p_root->insert(
            p_root->end(),
            std::make_unique<tetengo2::gui::menu::command>(
                string_type{ TETENGO2_TEXT("piyo") }, shortcut_key_type{ virtual_key_type::del(), false, true, true }));

        return p_root;
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
                        const shortcut_key_table_type shortcut_key_table{ *create_menu0() };
                    }
                    {
                        const shortcut_key_table_type shortcut_key_table{ *create_menu1() };
                    }
                }

                BOOST_AUTO_TEST_CASE(begin)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const shortcut_key_table_type shortcut_key_table{ *create_menu0() };

                        shortcut_key_table.begin();
                    }
                    {
                        const shortcut_key_table_type shortcut_key_table{ *create_menu1() };

                        const auto iterator = shortcut_key_table.begin();

                        BOOST_CHECK(
                            iterator->first == shortcut_key_type(virtual_key_type::char_a(), false, true, false));
                    }
                }

                BOOST_AUTO_TEST_CASE(end)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const shortcut_key_table_type shortcut_key_table{ *create_menu0() };

                        const auto iterator = shortcut_key_table.end();

                        BOOST_CHECK(std::distance(shortcut_key_table.begin(), iterator) == 0);
                    }
                    {
                        const shortcut_key_table_type shortcut_key_table{ *create_menu1() };

                        const auto iterator = shortcut_key_table.end();

                        BOOST_CHECK(std::distance(shortcut_key_table.begin(), iterator) == 2);
                    }
                }

                BOOST_AUTO_TEST_CASE(details)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const shortcut_key_table_type shortcut_key_table{ *create_menu0() };

                        shortcut_key_table.details();
                    }
                    {
                        const shortcut_key_table_type shortcut_key_table{ *create_menu0() };

                        shortcut_key_table.details();
                    }
                    {
                        const shortcut_key_table_type shortcut_key_table{ *create_menu1() };

                        shortcut_key_table.details();
                    }
                    {
                        const shortcut_key_table_type shortcut_key_table{ *create_menu1() };

                        shortcut_key_table.details();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
