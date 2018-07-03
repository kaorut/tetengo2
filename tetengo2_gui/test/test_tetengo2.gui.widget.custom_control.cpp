/*! \file
    \brief Test of class tetengo2::gui::widget::custom_control.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/position.h>
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/custom_control.h>
#include <tetengo2/gui/widget/window.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using widget_details_traits_type = common_type_list_type::widget_details_traits_type;

    using menu_details_type = detail_type_list_type::menu_type;

    using window_type = tetengo2::gui::widget::window<widget_details_traits_type, menu_details_type>;

    using mouse_capture_details_type = detail_type_list_type::mouse_capture_type;

    using custom_control_type =
        tetengo2::gui::widget::custom_control<widget_details_traits_type, mouse_capture_details_type>;

    using mouse_button_type = custom_control_type::mouse_button_type;

    using position_type = custom_control_type::position_type;

    using position_unit_type = position_type::unit_type;

    using dimension_type = custom_control_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using inner_item_type = custom_control_type::inner_item_type;

    class concrete_custom_control : public custom_control_type
    {
    public:
        explicit concrete_custom_control(window_type& parent)
        : custom_control_type{ parent, false, custom_control_type::scroll_bar_style_type::none }
        {}
    };

    class concrete_inner_item : public inner_item_type
    {
    public:
        concrete_inner_item(custom_control_type& parent)
        : inner_item_type{ parent,
                           position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } },
                           dimension_type{ dimension_unit_type{ 12 }, dimension_unit_type{ 34 } } }
        {}

        const custom_control_type& call_parent() const
        {
            return parent();
        }

        custom_control_type& call_parent()
        {
            return parent();
        }

        template <typename T>
        const T& call_parent_to() const
        {
            return parent_to<T>();
        }

        template <typename T>
        T& call_parent_to()
        {
            return parent_to<T>();
        }

        bool call_inside(const position_type& position) const
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

                    window_type                   parent{};
                    const concrete_custom_control custom_control{ parent };
                }

                BOOST_AUTO_TEST_CASE(mouse_captured)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type               parent{};
                    concrete_custom_control   custom_control{ parent };
                    const concrete_inner_item inner_item{ custom_control };

                    BOOST_TEST(!custom_control.mouse_captured(nullptr));
                    BOOST_TEST(!custom_control.mouse_captured(mouse_button_type::left, &inner_item));
                    BOOST_TEST(!custom_control.mouse_captured(mouse_button_type::right, &inner_item));
                    BOOST_TEST(!custom_control.mouse_captured(&inner_item));
                }

                BOOST_AUTO_TEST_CASE(set_mouse_capture)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type               parent{};
                    concrete_custom_control   custom_control{ parent };
                    const concrete_inner_item inner_item1{ custom_control };
                    const concrete_inner_item inner_item2{ custom_control };

                    BOOST_TEST(custom_control.set_mouse_capture(mouse_button_type::left, &inner_item1));

                    BOOST_TEST(custom_control.mouse_captured(&inner_item1));
                    BOOST_TEST(custom_control.mouse_captured(mouse_button_type::left, &inner_item1));
                    BOOST_TEST(!custom_control.set_mouse_capture(mouse_button_type::left, &inner_item2));
                    BOOST_TEST(custom_control.mouse_captured(nullptr));
                }

                BOOST_AUTO_TEST_CASE(release_mouse_capture)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type               parent{};
                    concrete_custom_control   custom_control{ parent };
                    const concrete_inner_item inner_item{ custom_control };

                    custom_control.set_mouse_capture(mouse_button_type::left, &inner_item);
                    custom_control.release_mouse_capture();

                    BOOST_TEST(!custom_control.mouse_captured(&inner_item));
                    BOOST_TEST(!custom_control.mouse_captured(nullptr));
                }


            BOOST_AUTO_TEST_SUITE_END()
            BOOST_AUTO_TEST_SUITE(inner_item)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type               parent{};
                    concrete_custom_control   custom_control{ parent };
                    const concrete_inner_item inner_item{ custom_control };
                }

                BOOST_AUTO_TEST_CASE(position)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type               parent{};
                    concrete_custom_control   custom_control{ parent };
                    const concrete_inner_item inner_item{ custom_control };

                    BOOST_CHECK(
                        (inner_item.position() == position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } }));
                }

                BOOST_AUTO_TEST_CASE(set_position)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type             parent{};
                    concrete_custom_control custom_control{ parent };
                    concrete_inner_item     inner_item{ custom_control };

                    inner_item.set_position(position_type{ position_unit_type{ 53 }, position_unit_type{ 35 } });

                    BOOST_CHECK(
                        (inner_item.position() == position_type{ position_unit_type{ 53 }, position_unit_type{ 35 } }));
                }

                BOOST_AUTO_TEST_CASE(dimension)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type               parent{};
                    concrete_custom_control   custom_control{ parent };
                    const concrete_inner_item inner_item{ custom_control };

                    BOOST_CHECK(
                        (inner_item.dimension() ==
                         dimension_type{ dimension_unit_type{ 12 }, dimension_unit_type{ 34 } }));
                }

                BOOST_AUTO_TEST_CASE(set_dimension)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type             parent{};
                    concrete_custom_control custom_control{ parent };
                    concrete_inner_item     inner_item{ custom_control };

                    inner_item.set_dimension(dimension_type{ dimension_unit_type{ 56 }, dimension_unit_type{ 78 } });

                    BOOST_CHECK(
                        (inner_item.dimension() ==
                         dimension_type{ dimension_unit_type{ 56 }, dimension_unit_type{ 78 } }));
                }

                BOOST_AUTO_TEST_CASE(resized)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type             parent{};
                    concrete_custom_control custom_control{ parent };
                    concrete_inner_item     inner_item{ custom_control };

                    inner_item.resized();
                }

                BOOST_AUTO_TEST_CASE(paint)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type               parent{};
                    concrete_custom_control   custom_control{ parent };
                    const concrete_inner_item inner_item{ custom_control };

                    const auto p_canvas = custom_control.create_canvas();
                    inner_item.paint(*p_canvas);
                }

                BOOST_AUTO_TEST_CASE(parent)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type               parent{};
                        concrete_custom_control   custom_control{ parent };
                        const concrete_inner_item inner_item{ custom_control };

                        BOOST_TEST(&inner_item.call_parent() == &custom_control);
                    }
                    {
                        window_type             parent{};
                        concrete_custom_control custom_control{ parent };
                        concrete_inner_item     inner_item{ custom_control };

                        BOOST_TEST(&inner_item.call_parent() == &custom_control);
                    }
                }

                BOOST_AUTO_TEST_CASE(parent_to)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type               parent{};
                        concrete_custom_control   custom_control{ parent };
                        const concrete_inner_item inner_item{ custom_control };

                        BOOST_TEST(&inner_item.call_parent_to<concrete_custom_control>() == &custom_control);
                    }
                    {
                        window_type             parent{};
                        concrete_custom_control custom_control{ parent };
                        concrete_inner_item     inner_item{ custom_control };

                        BOOST_TEST(&inner_item.call_parent_to<concrete_custom_control>() == &custom_control);
                    }
                }

                BOOST_AUTO_TEST_CASE(inside)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type               parent{};
                    concrete_custom_control   custom_control{ parent };
                    const concrete_inner_item inner_item{ custom_control };

                    BOOST_TEST(!inner_item.call_inside(position_type{}));
                    BOOST_TEST(
                        inner_item.call_inside(position_type{ position_unit_type{ 42 }, position_unit_type{ 24 } }));
                    BOOST_TEST(
                        inner_item.call_inside(position_type{ position_unit_type{ 50 }, position_unit_type{ 50 } }));
                    BOOST_TEST(
                        !inner_item.call_inside(position_type{ position_unit_type{ 100 }, position_unit_type{ 100 } }));
                }

                BOOST_AUTO_TEST_CASE(mouse_pressed)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type             parent{};
                    concrete_custom_control custom_control{ parent };
                    concrete_inner_item     inner_item{ custom_control };

                    inner_item.mouse_pressed(
                        mouse_button_type::left, position_type{ position_unit_type{ 11 }, position_unit_type{ 22 } });
                }

                BOOST_AUTO_TEST_CASE(mouse_released)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type             parent{};
                    concrete_custom_control custom_control{ parent };
                    concrete_inner_item     inner_item{ custom_control };

                    inner_item.mouse_released(
                        mouse_button_type::left, position_type{ position_unit_type{ 11 }, position_unit_type{ 22 } });
                }

                BOOST_AUTO_TEST_CASE(mouse_moved)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type             parent{};
                    concrete_custom_control custom_control{ parent };
                    concrete_inner_item     inner_item{ custom_control };

                    inner_item.mouse_moved(position_type{ position_unit_type{ 11 }, position_unit_type{ 22 } });
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
