/*! \file
    \brief Test of class tetengo2::gui::widget::custom_control.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using window_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type;

    using custom_control_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::custom_control>::type;

    using mouse_button_type = custom_control_type::mouse_button_type;

    using position_type = custom_control_type::position_type;

    using left_type = tetengo2::gui::position<position_type>::left_type;

    using top_type = tetengo2::gui::position<position_type>::top_type;

    using dimension_type = custom_control_type::dimension_type;

    using width_type = tetengo2::gui::dimension<dimension_type>::width_type;

    using height_type = tetengo2::gui::dimension<dimension_type>::height_type;

    using inner_item_type = custom_control_type::inner_item_type;

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
            parent,
            position_type{ left_type{ 42 }, top_type{ 24 } },
            dimension_type{ width_type{ 12 }, height_type{ 34 } }
        )
        {}

        const custom_control_type& call_parent()
        const
        {
            return parent();
        }

        custom_control_type& call_parent()
        {
            return parent();
        }

        template <typename T>
        const T& call_parent_to()
        const
        {
            return parent_to<T>();
        }

        template <typename T>
        T& call_parent_to()
        {
            return parent_to<T>();
        }

        bool call_inside(const position_type& position)
        const
        {
            return inside(position);
        }

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

        window_type parent{};
        const concrete_custom_control custom_control(parent);
    }

    BOOST_AUTO_TEST_CASE(mouse_captured)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_custom_control custom_control(parent);
        const concrete_inner_item inner_item(custom_control);

        BOOST_CHECK(!custom_control.mouse_captured(nullptr));
        BOOST_CHECK(!custom_control.mouse_captured(mouse_button_type::left, &inner_item));
        BOOST_CHECK(!custom_control.mouse_captured(mouse_button_type::right, &inner_item));
        BOOST_CHECK(!custom_control.mouse_captured(&inner_item));
    }

    BOOST_AUTO_TEST_CASE(set_mouse_capture)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_custom_control custom_control(parent);
        const concrete_inner_item inner_item1(custom_control);
        const concrete_inner_item inner_item2(custom_control);

        BOOST_CHECK(custom_control.set_mouse_capture(mouse_button_type::left, &inner_item1));

        BOOST_CHECK(custom_control.mouse_captured(&inner_item1));
        BOOST_CHECK(custom_control.mouse_captured(mouse_button_type::left, &inner_item1));
        BOOST_CHECK(!custom_control.set_mouse_capture(mouse_button_type::left, &inner_item2));
        BOOST_CHECK(custom_control.mouse_captured(nullptr));
    }

    BOOST_AUTO_TEST_CASE(release_mouse_capture)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_custom_control custom_control(parent);
        const concrete_inner_item inner_item(custom_control);

        custom_control.set_mouse_capture(mouse_button_type::left, &inner_item);
        custom_control.release_mouse_capture();

        BOOST_CHECK(!custom_control.mouse_captured(&inner_item));
        BOOST_CHECK(!custom_control.mouse_captured(nullptr));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(inner_item)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_custom_control custom_control(parent);
        const concrete_inner_item inner_item(custom_control);
    }

    BOOST_AUTO_TEST_CASE(position)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_custom_control custom_control(parent);
        const concrete_inner_item inner_item(custom_control);

        BOOST_CHECK((inner_item.position() == position_type{ left_type{ 42 }, top_type{ 24 } }));
    }

    BOOST_AUTO_TEST_CASE(set_position)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_custom_control custom_control(parent);
        concrete_inner_item inner_item(custom_control);

        inner_item.set_position(position_type{ left_type{ 53 }, top_type{ 35 } });

        BOOST_CHECK((inner_item.position() == position_type{ left_type{ 53 }, top_type{ 35 } }));
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_custom_control custom_control(parent);
        const concrete_inner_item inner_item(custom_control);

        BOOST_CHECK((inner_item.dimension() == dimension_type{ width_type{ 12 }, height_type{ 34 } }));
    }

    BOOST_AUTO_TEST_CASE(set_dimension)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_custom_control custom_control(parent);
        concrete_inner_item inner_item(custom_control);

        inner_item.set_dimension(dimension_type{ width_type{ 56 }, height_type{ 78 } });

        BOOST_CHECK((inner_item.dimension() == dimension_type{ width_type{ 56 }, height_type{ 78 } }));
    }

    BOOST_AUTO_TEST_CASE(resized)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_custom_control custom_control(parent);
        concrete_inner_item inner_item(custom_control);

        inner_item.resized();
    }

    BOOST_AUTO_TEST_CASE(paint)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_custom_control custom_control(parent);
        const concrete_inner_item inner_item(custom_control);

        const auto p_canvas = custom_control.create_canvas();
        inner_item.paint(*p_canvas);
    }

    BOOST_AUTO_TEST_CASE(mouse_pressed)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_custom_control custom_control(parent);
        concrete_inner_item inner_item(custom_control);

        inner_item.mouse_pressed(mouse_button_type::left, position_type{ left_type{ 11 }, top_type{ 22 } });
    }

    BOOST_AUTO_TEST_CASE(mouse_released)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_custom_control custom_control(parent);
        concrete_inner_item inner_item(custom_control);

        inner_item.mouse_released(mouse_button_type::left, position_type{ left_type{ 11 }, top_type{ 22 } });
    }

    BOOST_AUTO_TEST_CASE(mouse_moved)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_custom_control custom_control(parent);
        concrete_inner_item inner_item(custom_control);

        inner_item.mouse_moved(position_type{ left_type{ 11 }, top_type{ 22 } });
    }

    BOOST_AUTO_TEST_CASE(parent)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            concrete_custom_control custom_control(parent);
            const concrete_inner_item inner_item(custom_control);

            BOOST_CHECK_EQUAL(&inner_item.call_parent(), &custom_control);
        }
        {
            window_type parent{};
            concrete_custom_control custom_control(parent);
            concrete_inner_item inner_item(custom_control);

            BOOST_CHECK_EQUAL(&inner_item.call_parent(), &custom_control);
        }
    }

    BOOST_AUTO_TEST_CASE(parent_to)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            concrete_custom_control custom_control(parent);
            const concrete_inner_item inner_item(custom_control);

            BOOST_CHECK_EQUAL(&inner_item.call_parent_to<concrete_custom_control>(), &custom_control);
        }
        {
            window_type parent{};
            concrete_custom_control custom_control(parent);
            concrete_inner_item inner_item(custom_control);

            BOOST_CHECK_EQUAL(&inner_item.call_parent_to<concrete_custom_control>(), &custom_control);
        }
    }

    BOOST_AUTO_TEST_CASE(inside)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        concrete_custom_control custom_control(parent);
        const concrete_inner_item inner_item(custom_control);

        BOOST_CHECK(!inner_item.call_inside(position_type{ left_type{ 0 }, top_type{ 0 } }));
        BOOST_CHECK(inner_item.call_inside(position_type{ left_type{ 42 }, top_type{ 24 } }));
        BOOST_CHECK(inner_item.call_inside(position_type{ left_type{ 50 }, top_type{ 50 } }));
        BOOST_CHECK(!inner_item.call_inside(position_type{ left_type{ 100 }, top_type{ 100 } }));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
