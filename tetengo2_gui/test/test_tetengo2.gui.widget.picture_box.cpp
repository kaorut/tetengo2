/*! \file
    \brief Test of class tetengo2::gui::widget::picture_box.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>

#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/picture_box.h>
#include <tetengo2/gui/widget/window.h>

#include "test_tetengo2.gui.detail_type_list.h"
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

    using fast_drawing_details_type = detail_type_list_type::drawing_type;

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
