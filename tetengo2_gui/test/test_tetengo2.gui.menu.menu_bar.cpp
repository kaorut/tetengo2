/*! \file
    \brief Test of class tetengo2::gui::menu::menu_bar.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using string_type = boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type;

    using ui_encoder_type = boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::ui_encoder>::type;

    using menu_details_type =
        boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::menu>::type;

    using virtual_key_details_type =
        boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::virtual_key>::type;

    using menu_base_type =
        tetengo2::gui::menu::menu_base<string_type, ui_encoder_type, menu_details_type, virtual_key_details_type>;

    using shortcut_key_table_type =
        tetengo2::gui::menu::shortcut_key_table<
            string_type, ui_encoder_type, menu_details_type, virtual_key_details_type
        >;

    using menu_bar_type =
        tetengo2::gui::menu::menu_bar<
            string_type, shortcut_key_table_type, ui_encoder_type, menu_details_type, virtual_key_details_type
        >;


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

    BOOST_AUTO_TEST_CASE(shortcut_key_table)
    {
        BOOST_TEST_PASSPOINT();
    
        const menu_bar_type menu_bar;

        menu_bar.shortcut_key_table();
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
