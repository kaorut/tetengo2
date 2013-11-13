/*! \file
    \brief Test of class bobura::view::diagram::station_line.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>

#include "bobura.message.diagram_selection_observer_set.h"
#include "bobura.type_list.h"
#include "bobura.view.diagram.selection.h"

#include "bobura.view.diagram.station_line.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef model_type::timetable_type::station_location_type::station_type station_type;

    typedef model_type::timetable_type::font_color_set_type::font_color_type font_color_type;

    typedef model_type::timetable_type::train_type train_type;

    typedef
        bobura::message::diagram_selection_observer_set<station_type, train_type> diagram_selection_observer_set_type;

    typedef
        bobura::view::diagram::selection<station_type, train_type, diagram_selection_observer_set_type> selection_type;

    typedef model_type::timetable_type::train_type::stop_type::time_type time_type;

    typedef time_type::time_span_type time_span_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::picture_box>::type picture_box_type;

    typedef picture_box_type::position_type position_type;

    typedef tetengo2::gui::position<position_type>::left_type left_type;

    typedef tetengo2::gui::position<position_type>::top_type top_type;

    typedef picture_box_type::dimension_type dimension_type;

    typedef tetengo2::gui::dimension<dimension_type>::width_type width_type;

    typedef tetengo2::gui::dimension<dimension_type>::height_type height_type;

    typedef width_type::value_type horizontal_scale_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::canvas>::type canvas_type;

    typedef canvas_type::font_type font_type;

    typedef canvas_type::color_type color_type;

    typedef
        boost::mpl::at<bobura::model_type_list, bobura::type::model::station_grade_type_set>::type
        station_grade_type_set_type;
    
    typedef bobura::view::diagram::station_line<model_type, selection_type, canvas_type> station_line_type;

    typedef
        bobura::view::diagram::station_line_list<model_type, selection_type, canvas_type, station_grade_type_set_type>
        station_line_list_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
BOOST_AUTO_TEST_SUITE(station_line)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const station_type station(
            string_type(TETENGO2_TEXT("name")),
            station_grade_type_set_type::local_type::instance(),
            false,
            false,
            string_type(TETENGO2_TEXT("note"))
        );
        selection_type selection;
        station_line_type station_line1(
            station,
            selection,
            left_type(42),
            left_type(12),
            top_type(24),
            font_color_type(font_type::dialog_font(), color_type(12, 34, 56))
        );
        const station_line_type station_line2(std::move(station_line1));
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const station_type station1(
            string_type(TETENGO2_TEXT("name1")),
            station_grade_type_set_type::local_type::instance(),
            false,
            false,
            string_type(TETENGO2_TEXT("note1"))
        );
        selection_type selection;
        station_line_type station_line1(
            station1,
            selection,
            left_type(42),
            left_type(12),
            top_type(24),
            font_color_type(font_type::dialog_font(), color_type(12, 34, 56))
        );
        const station_type station2(
            string_type(TETENGO2_TEXT("name2")),
            station_grade_type_set_type::local_type::instance(),
            false,
            false,
            string_type(TETENGO2_TEXT("note2"))
        );
        station_line_type station_line2(
            station2,
            selection,
            left_type(42),
            left_type(12),
            top_type(24),
            font_color_type(font_type::dialog_font(), color_type(12, 34, 56))
        );
        station_line1 = std::move(station_line2);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(station_line_list)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        selection_type selection;
        station_line_list_type station_line_list1(
            model,
            time_span_type(42 * 60),
            selection,
            dimension_type(width_type(42), height_type(24)),
            position_type(left_type(24), top_type(42)),
            left_type(24),
            top_type(42),
            height_type(24),
            horizontal_scale_type(42),
            std::vector<top_type>(2, top_type(42))
        );
        const station_line_list_type station_line_list2(std::move(station_line_list1));
    }

    BOOST_AUTO_TEST_CASE(operator_assign)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        selection_type selection;
        station_line_list_type station_line_list1(
            model,
            time_span_type(42 * 60),
            selection,
            dimension_type(width_type(42), height_type(24)),
            position_type(left_type(24), top_type(42)),
            left_type(24),
            top_type(42),
            height_type(24),
            horizontal_scale_type(42),
            std::vector<top_type>(2, top_type(42))
        );
        station_line_list_type station_line_list2(
            model,
            time_span_type(42 * 60),
            selection,
            dimension_type(width_type(42), height_type(24)),
            position_type(left_type(24), top_type(42)),
            left_type(24),
            top_type(42),
            height_type(24),
            horizontal_scale_type(42),
            std::vector<top_type>(2, top_type(42))
        );

        station_line_list1 = std::move(station_line_list2);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
