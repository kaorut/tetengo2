/*! \file
    \brief Test of class tetengo2::gui::widget::text_box.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/widget/text_box.h>
#include <tetengo2/gui/widget/window.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using widget_traits_type = common_type_list_type::widget_traits_type;

    using widget_details_traits_type = common_type_list_type::widget_details_traits_type;

    using menu_details_type = detail_type_list_type::menu_type;

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

        BOOST_TEST(!text_box.read_only());
    }

    BOOST_AUTO_TEST_CASE(set_read_only)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            text_box_type text_box{ parent, text_box_type::scroll_bar_style_type::none };

            text_box.set_read_only(false);

            BOOST_TEST(!text_box.read_only());
        }
        {
            window_type parent{};
            text_box_type text_box{ parent, text_box_type::scroll_bar_style_type::none };

            text_box.set_read_only(true);

            BOOST_TEST(text_box.read_only());
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
