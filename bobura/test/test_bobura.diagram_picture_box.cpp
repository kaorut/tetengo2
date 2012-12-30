/*! \file
    \brief Test of class bobura::diagram_picture_box.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.gui.measure.h>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef
        boost::mpl::at<bobura::main_window_type_list, bobura::type::main_window::diagram_picture_box>::type
        diagram_picture_box_type;

    typedef diagram_picture_box_type::dimension_type dimension_type;

    typedef tetengo2::gui::dimension<dimension_type>::width_type width_type;

    typedef tetengo2::gui::dimension<dimension_type>::height_type height_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(diagram_picture_box)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const diagram_picture_box_type picture_box(window);
    }

    BOOST_AUTO_TEST_CASE(update_scroll_bars)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        diagram_picture_box_type picture_box(window);

        picture_box.update_scroll_bars(
            dimension_type(width_type(24), height_type(24)), dimension_type(width_type(42), width_type(42))
        );
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
