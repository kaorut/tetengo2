/*! \file
    \brief Test of class tetengo2::gui::widget::text_box.

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

    using widget_traits_type = boost::mpl::at<type_list_type, test_tetengo2::gui::type::widget_traits>::type;

    using widget_details_traits_type =
        boost::mpl::at<type_list_type, test_tetengo2::gui::type::widget_details_traits>::type;

    using menu_details_type = boost::mpl::at<detail_type_list_type, test_tetengo2::gui::type::detail::menu>::type;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using text_box_type = tetengo2::gui::widget::text_box<widget_traits_type, widget_details_traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(text_box)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const text_box_type text_box{ parent, text_box_type::scroll_bar_style_type::none };
        }
        {
            window_type parent{};
            const text_box_type text_box{ parent, text_box_type::scroll_bar_style_type::both };
        }
    }

    BOOST_AUTO_TEST_CASE(read_only)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const text_box_type text_box{ parent, text_box_type::scroll_bar_style_type::none };

        BOOST_CHECK(!text_box.read_only());
    }

    BOOST_AUTO_TEST_CASE(set_read_only)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            text_box_type text_box{ parent, text_box_type::scroll_bar_style_type::none };

            text_box.set_read_only(false);

            BOOST_CHECK(!text_box.read_only());
        }
        {
            window_type parent{};
            text_box_type text_box{ parent, text_box_type::scroll_bar_style_type::none };

            text_box.set_read_only(true);

            BOOST_CHECK(text_box.read_only());
        }
    }

    BOOST_AUTO_TEST_CASE(text_box_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const text_box_type text_box{ parent, text_box_type::scroll_bar_style_type::none };

            text_box.text_box_observer_set();
        }
        {
            window_type parent{};
            text_box_type text_box{ parent, text_box_type::scroll_bar_style_type::none };

            text_box.text_box_observer_set();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
