/*! \file
    \brief Test of class tetengo2::gui::menu::popup.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::detail_type_list_for_test;

    using type_list_type = test_tetengo2::gui::type_list<detail_type_list_type>;

    using string_type = boost::mpl::at<type_list_type, test_tetengo2::gui::type::string>::type;

    using ui_encoder_type = boost::mpl::at<type_list_type, test_tetengo2::gui::type::ui_encoder>::type;

    using menu_details_type = boost::mpl::at<detail_type_list_type, test_tetengo2::gui::type::detail::menu>::type;

    using virtual_key_details_type =
        boost::mpl::at<detail_type_list_type, test_tetengo2::gui::type::detail::virtual_key>::type;

    using menu_base_type =
        tetengo2::gui::menu::menu_base<string_type, ui_encoder_type, menu_details_type, virtual_key_details_type>;

    using popup_menu_type =
        tetengo2::gui::menu::popup<string_type, ui_encoder_type, menu_details_type, virtual_key_details_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
BOOST_AUTO_TEST_SUITE(popup)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const popup_menu_type popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        const popup_menu_type popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };

        BOOST_CHECK(&popup_menu.style() == &menu_details_type::popup_menu_style<menu_base_type>());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
