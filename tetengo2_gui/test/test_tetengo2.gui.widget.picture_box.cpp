/*! \file
    \brief Test of class tetengo2::gui::widget::picture_box.

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

    using fast_drawing_details_type =
        boost::mpl::at<detail_type_list_type, test_tetengo2::gui::type::detail::drawing>::type;

    using picture_box_type =
        tetengo2::gui::widget::picture_box<widget_traits_type, widget_details_traits_type, fast_drawing_details_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(picture_box)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const picture_box_type picture_box{ parent, picture_box_type::scroll_bar_style_type::none };
        }
        {
            window_type parent{};
            const picture_box_type picture_box{ parent, picture_box_type::scroll_bar_style_type::both };
        }
    }

    BOOST_AUTO_TEST_CASE(create_fast_canvas)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const picture_box_type picture_box{ parent, picture_box_type::scroll_bar_style_type::none };

        picture_box.create_fast_canvas();
    }

    BOOST_AUTO_TEST_CASE(fast_paint_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const picture_box_type picture_box{ parent, picture_box_type::scroll_bar_style_type::none };

            picture_box.fast_paint_observer_set();
        }
        {
            window_type parent{};
            picture_box_type picture_box{ parent, picture_box_type::scroll_bar_style_type::none };

            picture_box.fast_paint_observer_set();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
