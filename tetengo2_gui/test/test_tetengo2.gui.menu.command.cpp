/*! \file
    \brief Test of class tetengo2::gui::menu::command.

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

    using menu_command_type =
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::command>::type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
BOOST_AUTO_TEST_SUITE(command)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const menu_command_type menu_command{ string_type{ TETENGO2_TEXT("Tetengo") } };
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        const menu_command_type menu_command{ string_type{ TETENGO2_TEXT("Tetengo") } };

        BOOST_CHECK(&menu_command.style() == &menu_details_type::menu_command_style<menu_base_type>());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
