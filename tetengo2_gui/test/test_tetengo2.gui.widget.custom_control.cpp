/*! \file
    \brief Test of class tetengo2::gui::widget::custom_control.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.measure.h"

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type
        window_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::custom_control>::type
        custom_control_type;

    typedef custom_control_type::position_type position_type;

    typedef tetengo2::gui::position<position_type>::left_type left_type;

    typedef tetengo2::gui::position<position_type>::top_type top_type;

    typedef custom_control_type::dimension_type dimension_type;

    typedef tetengo2::gui::dimension<dimension_type>::width_type width_type;

    typedef tetengo2::gui::dimension<dimension_type>::height_type height_type;

    typedef custom_control_type::inner_item_type inner_item_type;

    class concrete_custom_control : public custom_control_type
    {
    public:
        explicit concrete_custom_control(window_type& parent)
        :
        custom_control_type(parent, false, custom_control_type::scroll_bar_style_type::none)
        {}

    };

    class concrete_inner_item : public inner_item_type
    {
    public:
        concrete_inner_item(custom_control_type& parent)
        :
        inner_item_type(
            parent, position_type(left_type(42), top_type(24)), dimension_type(width_type(12), height_type(34))
        )
        {}

    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(custom_control)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const concrete_custom_control custom_control(parent);
    }

    BOOST_AUTO_TEST_CASE(mouse_captured)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        concrete_custom_control custom_control(parent);
        const concrete_inner_item inner_item(custom_control);

        BOOST_CHECK(!custom_control.mouse_captured(&inner_item));
    }

    BOOST_AUTO_TEST_CASE(set_mouse_capture)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(release_mouse_capture)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(inner_item)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(position)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_position)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_dimension)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(resized)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(paint)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(mouse_pressed)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(mouse_released)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(mouse_moved)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(parent)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(parent_to)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(inside)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
