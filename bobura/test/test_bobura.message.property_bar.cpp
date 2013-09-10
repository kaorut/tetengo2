/*! \file
    \brief Test of class bobura::message::property_bar.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"

#include "bobura.message.property_bar.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::side_bar>::type side_bar_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::map_box>::type map_box_type;

    typedef bobura::message::property_bar::resized<side_bar_type, map_box_type> resized_type;


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
        map_box_type map_box(side_bar, map_box_type::scroll_bar_style_type::vertical);
        resized_type observer(side_bar, map_box);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        side_bar_type side_bar(window);
        map_box_type map_box(side_bar, map_box_type::scroll_bar_style_type::vertical);
        resized_type observer(side_bar, map_box);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
