/*! \file
    \brief Test of class tetengo2::gui::menu::menu_bar.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/menu/menu_base.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using menu_details_type = detail_type_list_type::menu_type;

    using menu_base_type = tetengo2::gui::menu::menu_base<menu_details_type>;

    using menu_bar_type = tetengo2::gui::menu::menu_bar<menu_details_type>;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(menu)
            BOOST_AUTO_TEST_SUITE(menu_bar)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const menu_bar_type menu_bar;
                }

                BOOST_AUTO_TEST_CASE(style)
                {
                    BOOST_TEST_PASSPOINT();

                    const menu_bar_type menu_bar;

                    BOOST_CHECK(&menu_bar.style() == &menu_details_type::menu_bar_style<menu_base_type>());
                }

                BOOST_AUTO_TEST_CASE(get_shortcut_key_table)
                {
                    BOOST_TEST_PASSPOINT();

                    const menu_bar_type menu_bar;

                    menu_bar.get_shortcut_key_table();
                }

                BOOST_AUTO_TEST_CASE(update_shortcut_key_table)
                {
                    BOOST_TEST_PASSPOINT();

                    menu_bar_type menu_bar;

                    menu_bar.update_shortcut_key_table();
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
