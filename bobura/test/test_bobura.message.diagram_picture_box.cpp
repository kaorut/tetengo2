/*! \file
    \brief Test of class bobura::message::diagram_picture_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>

//#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"

#include "bobura.message.diagram_picture_box.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::canvas>::type canvas_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::position>::type position_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::picture_reader>::type picture_reader_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(diagram_picture_box)
BOOST_AUTO_TEST_SUITE(paint_paint)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::diagram_picture_box::paint_paint<canvas_type, position_type, picture_reader_type> paint(
            boost::filesystem::path("image_path")
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::diagram_picture_box::paint_paint<canvas_type, position_type, picture_reader_type> paint(
            boost::filesystem::path("image_path")
        );

        const window_type window;
        std::unique_ptr<canvas_type> p_canvas(window.create_canvas());
        paint(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
