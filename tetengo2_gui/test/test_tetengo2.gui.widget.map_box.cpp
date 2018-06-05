/*! \file
    \brief Test of class tetengo2::gui::widget::map_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <boost/operators.hpp>
#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/stub/cursor.h> // for cursor
#include <tetengo2/gui/dimension.h> // for dimension
#include <tetengo2/gui/drawing/solid_background.h> // for solid_background<>::details_type
#include <tetengo2/gui/menu/abstract_popup.h> // for abstract_popup<>::const_iterator, abstract_popup<>::const_recursive_iterator_type, abstract_popup<>::iterator, abstract_popup<>::recursive_iterator_type
#include <tetengo2/gui/menu/menu_bar.h> // for menu_bar<>::style_type
#include <tetengo2/gui/unit/pixel.h> // for operator==
#include <tetengo2/gui/unit/unit.h> // for operator<, operator==, operator-
#include <tetengo2/gui/widget/control.h> // for control<>::details_type
#include <tetengo2/gui/widget/map_box.h>
#include <tetengo2/gui/widget/window.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h> // for TETENGO2_TEXT, text_value_holder

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using widget_traits_type = common_type_list_type::widget_traits_type;

    using widget_details_traits_type = common_type_list_type::widget_details_traits_type;

    using menu_details_type = detail_type_list_type::menu_type;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using mouse_capture_details_type = detail_type_list_type::mouse_capture_type;

    using map_box_type = tetengo2::gui::widget::
        map_box<widget_traits_type, widget_details_traits_type, mouse_capture_details_type>;

    using value_type = map_box_type::value_type;

    using key_type = value_type::first_type;

    using mapped_type = value_type::second_type;

    using position_type = common_type_list_type::position_type;

    using position_unit_type = position_type::unit_type;

    using dimension_type = common_type_list_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using cursor_details_type = detail_type_list_type::cursor_type;


    // functions

    template <typename T, typename U>
    value_type make_value(const T& key, const U& mapped)
    {
        return { key_type{ key }, mapped_type{ mapped } };
    }
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(widget)
            BOOST_AUTO_TEST_SUITE(map_box)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type        parent{};
                    const map_box_type map_box{ parent, cursor_details_type::instance() };
                }

                BOOST_AUTO_TEST_CASE(value_count)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type        parent{};
                        const map_box_type map_box{ parent, cursor_details_type::instance() };

                        BOOST_TEST(map_box.value_count() == 0U);
                    }
                    {
                        window_type  parent{};
                        map_box_type map_box{ parent, cursor_details_type::instance() };
                        map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));

                        BOOST_TEST(map_box.value_count() == 1U);
                    }
                }

                BOOST_AUTO_TEST_CASE(value)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type  parent{};
                        map_box_type map_box{ parent, cursor_details_type::instance() };
                        map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));

                        BOOST_CHECK(map_box.value(0) == make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));
                    }
                    {
                        window_type        parent{};
                        const map_box_type map_box{ parent, cursor_details_type::instance() };

                        BOOST_CHECK_THROW(map_box.value(0), std::out_of_range);
                    }
                }

                BOOST_AUTO_TEST_CASE(set_value)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type  parent{};
                        map_box_type map_box{ parent, cursor_details_type::instance() };
                        map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));

                        map_box.set_value(0, make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("baz")));

                        BOOST_CHECK(map_box.value(0) == make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("baz")));
                    }
                    {
                        window_type  parent{};
                        map_box_type map_box{ parent, cursor_details_type::instance() };

                        BOOST_CHECK_THROW(
                            map_box.set_value(0, make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("baz"))),
                            std::out_of_range);
                    }
                }

                BOOST_AUTO_TEST_CASE(insert_value)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type  parent{};
                        map_box_type map_box{ parent, cursor_details_type::instance() };

                        map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));
                        map_box.insert_value(1, make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("bar")));
                        map_box.insert_value(0, make_value(TETENGO2_TEXT("piyo"), TETENGO2_TEXT("baz")));
                        map_box.insert_value(2, make_value(TETENGO2_TEXT("piyoyo"), TETENGO2_TEXT("bazz")));

                        BOOST_TEST(map_box.value_count() == 4U);
                        BOOST_CHECK(map_box.value(0) == make_value(TETENGO2_TEXT("piyo"), TETENGO2_TEXT("baz")));
                        BOOST_CHECK(map_box.value(1) == make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));
                        BOOST_CHECK(map_box.value(2) == make_value(TETENGO2_TEXT("piyoyo"), TETENGO2_TEXT("bazz")));
                        BOOST_CHECK(map_box.value(3) == make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("bar")));
                    }
                    {
                        window_type  parent{};
                        map_box_type map_box{ parent, cursor_details_type::instance() };

                        BOOST_CHECK_THROW(
                            map_box.insert_value(1, make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("bar"))),
                            std::out_of_range);
                    }
                }

                BOOST_AUTO_TEST_CASE(erase_value)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type  parent{};
                        map_box_type map_box{ parent, cursor_details_type::instance() };
                        map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));

                        map_box.erase_value(0);

                        BOOST_TEST(map_box.value_count() == 0U);
                    }
                    {
                        window_type  parent{};
                        map_box_type map_box{ parent, cursor_details_type::instance() };

                        BOOST_CHECK_THROW(map_box.erase_value(0), std::out_of_range);
                    }
                }

                BOOST_AUTO_TEST_CASE(clear)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type  parent{};
                    map_box_type map_box{ parent, cursor_details_type::instance() };
                    map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));
                    map_box.insert_value(1, make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("bar")));

                    map_box.clear();

                    BOOST_TEST(map_box.value_count() == 0U);
                }

                BOOST_AUTO_TEST_CASE(selected_value_index)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type        parent{};
                    const map_box_type map_box{ parent, cursor_details_type::instance() };

                    BOOST_TEST(!map_box.selected_value_index());
                }

                BOOST_AUTO_TEST_CASE(select_value)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type  parent{};
                        map_box_type map_box{ parent, cursor_details_type::instance() };
                        map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));

                        map_box.select_value(0);

                        BOOST_TEST_REQUIRE(tetengo2::stdalt::has_value(map_box.selected_value_index()));
                        BOOST_TEST(*map_box.selected_value_index() == 0U);

                        map_box.insert_value(0, make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("bar")));
                        map_box.insert_value(2, make_value(TETENGO2_TEXT("piyo"), TETENGO2_TEXT("baz")));

                        BOOST_TEST_REQUIRE(tetengo2::stdalt::has_value(map_box.selected_value_index()));
                        BOOST_TEST(*map_box.selected_value_index() == 1U);

                        map_box.erase_value(0);

                        BOOST_TEST_REQUIRE(tetengo2::stdalt::has_value(map_box.selected_value_index()));
                        BOOST_TEST(*map_box.selected_value_index() == 0U);

                        map_box.erase_value(0);

                        BOOST_TEST(!map_box.selected_value_index());
                    }
                    {
                        window_type  parent{};
                        map_box_type map_box{ parent, cursor_details_type::instance() };

                        BOOST_CHECK_THROW(map_box.select_value(0), std::out_of_range);
                    }
                }

                BOOST_AUTO_TEST_CASE(splitter_position)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type  parent{};
                    map_box_type map_box{ parent, cursor_details_type::instance() };

                    map_box.splitter_position();
                }

                BOOST_AUTO_TEST_CASE(set_splitter_position)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type  parent{};
                    map_box_type map_box{ parent, cursor_details_type::instance() };
                    map_box.set_dimension(dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } });

                    map_box.set_splitter_position(position_unit_type{ 24 });

                    BOOST_CHECK(map_box.splitter_position() == position_unit_type{ 24 });
                }

                BOOST_AUTO_TEST_CASE(list_selection_observer_set)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type        parent{};
                        const map_box_type map_box{ parent, cursor_details_type::instance() };

                        map_box.list_selection_observer_set();
                    }
                    {
                        window_type  parent{};
                        map_box_type map_box{ parent, cursor_details_type::instance() };

                        map_box.list_selection_observer_set();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
