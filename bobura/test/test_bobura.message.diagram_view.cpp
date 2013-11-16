/*! \file
    \brief Test of class bobura::message::diagram_view.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <utility>

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

#include "bobura.type_list.h"

#include "bobura.message.diagram_view.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

    typedef
        boost::mpl::at<bobura::main_window_type_list, bobura::type::main_window::property_bar>::type property_bar_type;

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef model_type::timetable_type timetable_type;

    typedef timetable_type::station_location_type station_location_type;

    typedef station_location_type::station_type station_type;

    typedef
        boost::mpl::at<bobura::model_type_list, bobura::type::model::station_grade_type_set>::type
        station_grade_type_set_type;
    
    typedef
        bobura::message::diagram_view::station_selected<
            property_bar_type, model_type, station_grade_type_set_type, message_catalog_type
        >
        station_selected_type;

    typedef model_type::timetable_type::train_type train_type;

    typedef model_type::timetable_type::train_kind_type train_kind_type;

    typedef train_kind_type::color_type color_type;

    typedef
        bobura::message::diagram_view::train_selected<
            property_bar_type, model_type, station_grade_type_set_type, message_catalog_type
        >
        train_selected_type;

    typedef bobura::message::diagram_view::all_unselected<property_bar_type> all_unselected_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(diagram_view)
BOOST_AUTO_TEST_SUITE(station_selected)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        property_bar_type property_bar(window, message_catalog);
        const model_type model;
        const station_selected_type station_selected(property_bar, model, message_catalog);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        property_bar_type property_bar(window, message_catalog);
        const model_type model;
        station_selected_type station_selected(property_bar, model, message_catalog);

        station_type station(
            string_type(TETENGO2_TEXT("name")),
            station_grade_type_set_type::local_type::instance(),
            false,
            false,
            string_type(TETENGO2_TEXT("note"))
        );
        station_location_type station_location(std::move(station), 42);
        station_selected(station_location);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(train_selected)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        property_bar_type property_bar(window, message_catalog);
        const model_type model;
        const train_selected_type train_selected(property_bar, model, message_catalog);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        property_bar_type property_bar(window, message_catalog);
        model_type model;
        model.timetable().insert_train_kind(
            model.timetable().train_kinds().end(),
            train_kind_type(
                string_type(TETENGO2_TEXT("Express")),
                string_type(TETENGO2_TEXT("Exp.")),
                color_type(255, 0, 0),
                train_kind_type::weight_type::bold,
                train_kind_type::line_style_type::solid
            )
        );
        train_selected_type train_selected(property_bar, model, message_catalog);

        const train_type train(
            train_type::direction_type::down,
            string_type(TETENGO2_TEXT("number")),
            0,
            string_type(TETENGO2_TEXT("name")),
            string_type(TETENGO2_TEXT("name_number")),
            string_type(TETENGO2_TEXT("note"))
        );
        train_selected(train, boost::none);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(all_unselected)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        property_bar_type property_bar(window, message_catalog);
        const all_unselected_type all_unselected(property_bar);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        property_bar_type property_bar(window, message_catalog);
        all_unselected_type all_unselected(property_bar);

        all_unselected();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
