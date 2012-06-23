/*! \file
    \brief Test of class bobura::command::horizontally_zoom_in.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"

#include "bobura.command.horizontally_zoom_in.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::abstract_window >::type abstract_window_type;

    typedef boost::mpl::at<bobura::view_type_list, bobura::type::view::view>::type diagram_view_type;

    typedef boost::mpl::at<bobura::view_type_list, bobura::type::view::scale_list>::type view_scale_list_type;

    typedef
        bobura::command::horizontally_zoom_in<
            model_type, abstract_window_type, diagram_view_type, view_scale_list_type
        >
        horizontally_zoom_in_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(horizontally_zoom_in)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        diagram_view_type diagram_view(model);
        const horizontally_zoom_in_type horizontally_zoom_in(diagram_view);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
