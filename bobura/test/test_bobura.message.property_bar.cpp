/*! \file
    \brief Test of class bobura::message::property_bar.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.gui.measure.h>

#include "bobura.type_list.h"

#include "bobura.message.property_bar.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::side_bar>::type side_bar_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::map_box>::type map_box_type;

    typedef bobura::message::property_bar::resized<side_bar_type, map_box_type> resized_type;

    typedef bobura::message::property_bar::mouse_pressed<map_box_type> mouse_pressed_type;

    typedef mouse_pressed_type::position_type position_type;

    typedef tetengo2::gui::position<position_type>::left_type left_type;

    typedef tetengo2::gui::position<position_type>::top_type top_type;

    typedef mouse_pressed_type::mouse_button_type mouse_button_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(property_bar)
BOOST_AUTO_TEST_SUITE(resized)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        side_bar_type side_bar(window);
        map_box_type map_box(side_bar);
        const resized_type observer(side_bar, map_box);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        side_bar_type side_bar(window);
        map_box_type map_box(side_bar);
        const resized_type observer(side_bar, map_box);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(mouse_pressed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        side_bar_type side_bar(window);
        map_box_type map_box(side_bar);
        const mouse_pressed_type observer(map_box);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        side_bar_type side_bar(window);
        map_box_type map_box(side_bar);
        const mouse_pressed_type observer(map_box);

        observer(mouse_button_type::left, position_type(left_type(42), top_type(24)), false, false, false);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
