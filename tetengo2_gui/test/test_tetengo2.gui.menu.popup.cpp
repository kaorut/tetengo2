/*! \file
    \brief Test of class tetengo2::gui::menu::popup.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using menu_details_type =
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::menu_details>::type;

    using string_type = boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type;

    using menu_base_type =
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::menu_base>::type;

    using popup_menu_type =
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::popup>::type;


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
