/*! \file
    \brief Test of class tetengo2::gui::widget::picture_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type
        window_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::picture_box>::type
        picture_box_type;


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
            window_type parent;
            const picture_box_type picture_box(parent, picture_box_type::scroll_bar_style_none);
        }
        {
            window_type parent;
            const picture_box_type picture_box(parent, picture_box_type::scroll_bar_style_both);
        }
    }

    BOOST_AUTO_TEST_CASE(create_fast_canvas)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const picture_box_type picture_box(parent, picture_box_type::scroll_bar_style_none);

        picture_box.create_fast_canvas();
    }

    BOOST_AUTO_TEST_CASE(fast_paint_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const picture_box_type picture_box(parent, picture_box_type::scroll_bar_style_none);

            picture_box.fast_paint_observer_set();
        }
        {
            window_type parent;
            picture_box_type picture_box(parent, picture_box_type::scroll_bar_style_none);

            picture_box.fast_paint_observer_set();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
