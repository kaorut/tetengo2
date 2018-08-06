/*! \file
    \brief Test of class tetengo2::gui::widget::map_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/gui/widget/map_box.h>
#include <tetengo2/gui/widget/window.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using window_type = tetengo2::gui::widget::window;

    using mouse_capture_details_type = detail_type_list_type::mouse_capture_type;

    using map_box_type = tetengo2::gui::widget::map_box;

    using value_type = map_box_type::value_type;

    using key_type = value_type::first_type;

    using mapped_type = value_type::second_type;

    using position_type = common_type_list_type::position_type;

    using position_unit_type = position_type::unit_type;

    using dimension_type = common_type_list_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;


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
                    const map_box_type map_box{ parent };
                }

                BOOST_AUTO_TEST_CASE(value_count)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type        parent{};
                        const map_box_type map_box{ parent };

                        BOOST_TEST(map_box.value_count() == 0U);
                    }
                    {
                        window_type  parent{};
                        map_box_type map_box{ parent };
                        map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));

                        BOOST_TEST(map_box.value_count() == 1U);
                    }
                }

                BOOST_AUTO_TEST_CASE(value)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type  parent{};
                        map_box_type map_box{ parent };
                        map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));

                        BOOST_CHECK(map_box.value(0) == make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));
                    }
                    {
                        window_type        parent{};
                        const map_box_type map_box{ parent };

                        BOOST_CHECK_THROW(map_box.value(0), std::out_of_range);
                    }
                }

                BOOST_AUTO_TEST_CASE(set_value)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type  parent{};
                        map_box_type map_box{ parent };
                        map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));

                        map_box.set_value(0, make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("baz")));

                        BOOST_CHECK(map_box.value(0) == make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("baz")));
                    }
                    {
                        window_type  parent{};
                        map_box_type map_box{ parent };

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
                        map_box_type map_box{ parent };

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
                        map_box_type map_box{ parent };

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
                        map_box_type map_box{ parent };
                        map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));

                        map_box.erase_value(0);

                        BOOST_TEST(map_box.value_count() == 0U);
                    }
                    {
                        window_type  parent{};
                        map_box_type map_box{ parent };

                        BOOST_CHECK_THROW(map_box.erase_value(0), std::out_of_range);
                    }
                }

                BOOST_AUTO_TEST_CASE(clear)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type  parent{};
                    map_box_type map_box{ parent };
                    map_box.insert_value(0, make_value(TETENGO2_TEXT("hoge"), TETENGO2_TEXT("foo")));
                    map_box.insert_value(1, make_value(TETENGO2_TEXT("fuga"), TETENGO2_TEXT("bar")));

                    map_box.clear();

                    BOOST_TEST(map_box.value_count() == 0U);
                }

                BOOST_AUTO_TEST_CASE(selected_value_index)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type        parent{};
                    const map_box_type map_box{ parent };

                    BOOST_TEST(!map_box.selected_value_index());
                }

                BOOST_AUTO_TEST_CASE(select_value)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type  parent{};
                        map_box_type map_box{ parent };
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
                        map_box_type map_box{ parent };

                        BOOST_CHECK_THROW(map_box.select_value(0), std::out_of_range);
                    }
                }

                BOOST_AUTO_TEST_CASE(splitter_position)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type  parent{};
                    map_box_type map_box{ parent };

                    map_box.splitter_position();
                }

                BOOST_AUTO_TEST_CASE(set_splitter_position)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type  parent{};
                    map_box_type map_box{ parent };
                    map_box.set_dimension(dimension_type{ dimension_unit_type{ 42 }, dimension_unit_type{ 24 } });

                    map_box.set_splitter_position(position_unit_type{ 24 });

                    BOOST_CHECK(map_box.splitter_position() == position_unit_type{ 24 });
                }

                BOOST_AUTO_TEST_CASE(list_selection_observer_set)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type        parent{};
                        const map_box_type map_box{ parent };

                        map_box.list_selection_observer_set();
                    }
                    {
                        window_type  parent{};
                        map_box_type map_box{ parent };

                        map_box.list_selection_observer_set();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
