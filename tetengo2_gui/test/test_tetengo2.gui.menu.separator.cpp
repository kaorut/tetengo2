/*! \file
    \brief Test of class tetengo2::gui::menu::separator.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using menu_details_type =
        boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::menu>::type;

    using menu_base_type =
        tetengo2::gui::menu::menu_base<
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type,
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::ui_encoder>::type,
            menu_details_type,
            boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::virtual_key>::type
        >;

    using menu_separator_type =
        tetengo2::gui::menu::separator<
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type,
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::ui_encoder>::type,
            menu_details_type,
            boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::virtual_key>::type
        >;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
BOOST_AUTO_TEST_SUITE(separator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const menu_separator_type menu_separator;
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        const menu_separator_type menu_separator;

        BOOST_CHECK(&menu_separator.style() == &menu_details_type::menu_separator_style<menu_base_type>());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
