/*! \file
    \brief Test of class tetengo2::gui::widget::link_label.

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

    using widget_traits_type =
        boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::widget_traits>::type;

    using widget_details_traits_type =
        boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::widget_details_traits>::type;

    using menu_details_type =
        boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::menu>::type;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using system_color_details_type =
        boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::system_color>::type;

    using shell_details_type =
        boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::shell>::type;

    using link_label_type =
        tetengo2::gui::widget::link_label<
            widget_traits_type, widget_details_traits_type, system_color_details_type, shell_details_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(link_label)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const link_label_type label{ parent };
    }

    BOOST_AUTO_TEST_CASE(target)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const link_label_type label{ parent };

        BOOST_CHECK(label.target().empty());
    }

    BOOST_AUTO_TEST_CASE(set_target)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        link_label_type label{ parent };

        label.set_target(string_type{ TETENGO2_TEXT("http://www.tetengo.org") });

        BOOST_CHECK(label.target() == string_type{ TETENGO2_TEXT("http://www.tetengo.org") });
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
