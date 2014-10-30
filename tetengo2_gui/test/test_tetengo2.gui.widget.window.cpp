/*! \file
    \brief Test of class tetengo2::gui::widget::window.

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

    using detail_type_list_type = test_tetengo2::gui::detail_type_list_for_test;

    using type_list_type = test_tetengo2::gui::type_list<detail_type_list_type>;

    using widget_traits_type = boost::mpl::at<type_list_type, test_tetengo2::gui::type::widget_traits>::type;

    using widget_details_traits_type =
        boost::mpl::at<type_list_type, test_tetengo2::gui::type::widget_details_traits>::type;

    using menu_details_type = boost::mpl::at<detail_type_list_type, test_tetengo2::gui::type::detail::menu>::type;

    using abstract_window_type =
        tetengo2::gui::widget::abstract_window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(window)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const window_type window{};
        }
        {
            const window_type window{ window_type::scroll_bar_style_type::none, false };
        }
        {
            const window_type window{ window_type::scroll_bar_style_type::both, false };
        }
        {
            const window_type window{ window_type::scroll_bar_style_type::none, true };
        }
        {
            window_type parent{};
            const window_type window{
                static_cast<abstract_window_type&>(parent), window_type::scroll_bar_style_type::none, false
            };
        }
        {
            window_type parent{};
            const window_type window{
                static_cast<abstract_window_type&>(parent), window_type::scroll_bar_style_type::both, false
            };
        }
        {
            window_type parent{};
            const window_type window{
                static_cast<abstract_window_type&>(parent), window_type::scroll_bar_style_type::none, true
            };
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
