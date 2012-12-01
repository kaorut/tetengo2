/*! \file
    \brief Test of class bobura::view::diagram::station_line.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>
#include <utility>

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>

#include "bobura.type_list.h"

#include "bobura.view.diagram.station_line.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::picture_box>::type picture_box_type;

    typedef picture_box_type::position_type position_type;

    typedef tetengo2::gui::position<position_type>::left_type left_type;

    typedef tetengo2::gui::position<position_type>::top_type top_type;

    typedef picture_box_type::dimension_type dimension_type;

    typedef tetengo2::gui::dimension<dimension_type>::width_type width_type;

    typedef tetengo2::gui::dimension<dimension_type>::height_type height_type;

    typedef width_type::value_type horizontal_scale_type;

    typedef height_type::value_type vertical_scale_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::canvas>::type canvas_type;

    typedef bobura::view::diagram::station_line<canvas_type> station_line_type;

    typedef bobura::view::diagram::station_line_list<model_type, canvas_type> station_line_list_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
BOOST_AUTO_TEST_SUITE(station_line)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const std::unique_ptr<canvas_type> p_canvas(picture_box.create_canvas());
        station_line_type station_line1(left_type(42), top_type(24));
        const station_line_type station_line2(std::move(station_line1));
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const std::unique_ptr<canvas_type> p_canvas(picture_box.create_canvas());
        station_line_type station_line1(left_type(42), top_type(24));
        station_line_type station_line2(left_type(42), top_type(24));

        station_line1 = std::move(station_line2);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(station_line_list)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const std::unique_ptr<canvas_type> p_canvas(picture_box.create_canvas());
        station_line_list_type station_line_list1(
            model,
            *p_canvas,
            dimension_type(width_type(42), height_type(24)),
            dimension_type(width_type(42), height_type(24)),
            position_type(left_type(24), top_type(42)),
            left_type(24),
            top_type(42),
            height_type(24),
            horizontal_scale_type(42),
            vertical_scale_type(24)
        );
        const station_line_list_type station_line_list2(std::move(station_line_list1));
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const std::unique_ptr<canvas_type> p_canvas(picture_box.create_canvas());
        station_line_list_type station_line_list1(
            model,
            *p_canvas,
            dimension_type(width_type(42), height_type(24)),
            dimension_type(width_type(42), height_type(24)),
            position_type(left_type(24), top_type(42)),
            left_type(24),
            top_type(42),
            height_type(24),
            horizontal_scale_type(42),
            vertical_scale_type(24)
        );
        station_line_list_type station_line_list2(
            model,
            *p_canvas,
            dimension_type(width_type(42), height_type(24)),
            dimension_type(width_type(42), height_type(24)),
            position_type(left_type(24), top_type(42)),
            left_type(24),
            top_type(42),
            height_type(24),
            horizontal_scale_type(42),
            vertical_scale_type(24)
        );

        station_line_list1 = std::move(station_line_list2);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
