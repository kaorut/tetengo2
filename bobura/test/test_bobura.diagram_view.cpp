/*! \file
    \brief Test of class bobura::diagram_view.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.unique.h>

#include "bobura.type_list.h"

#include "bobura.diagram_view.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::canvas>::type canvas_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::solid_background>::type solid_background_type;

    typedef bobura::diagram_view<model_type, canvas_type, solid_background_type> view_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(diagram_view)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const view_type view(model);
    }

    BOOST_AUTO_TEST_CASE(draw_to)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const view_type view(model);

        const window_type window;
        std::unique_ptr<canvas_type> p_canvas(window.create_canvas());
        view.draw_to(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
