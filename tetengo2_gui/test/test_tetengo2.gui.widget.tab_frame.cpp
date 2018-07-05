/*! \file
    \brief Test of class tetengo2::gui::widget::tab_frame.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include <boost/operators.hpp>
#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/label.h>
#include <tetengo2/gui/widget/tab_frame.h>
#include <tetengo2/gui/widget/window.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using menu_details_type = detail_type_list_type::menu_type;

    using window_type = tetengo2::gui::widget::window<
        common_type_list_type::widget_details_type,
        common_type_list_type::drawing_details_type,
        common_type_list_type::scroll_details_type,
        common_type_list_type::message_handler_details_type,
        menu_details_type>;

    using mouse_capture_details_type = detail_type_list_type::mouse_capture_type;

    using tab_frame_type = tetengo2::gui::widget::tab_frame<
        common_type_list_type::widget_details_type,
        common_type_list_type::drawing_details_type,
        common_type_list_type::scroll_details_type,
        common_type_list_type::message_handler_details_type,
        mouse_capture_details_type>;

    using tab_type = tab_frame_type::tab_type;

    using string_type = tab_frame_type::string_type;

    using label_type = tetengo2::gui::widget::label<
        common_type_list_type::widget_details_type,
        common_type_list_type::drawing_details_type,
        common_type_list_type::scroll_details_type,
        common_type_list_type::message_handler_details_type>;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(widget)
            BOOST_AUTO_TEST_SUITE(tab_frame)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type          parent{};
                    const tab_frame_type tab_frame{ parent };
                }

                BOOST_AUTO_TEST_CASE(tab_count)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type    parent{};
                    tab_frame_type tab_frame{ parent };

                    BOOST_TEST(tab_frame.tab_count() == 0U);

                    label_type label1{ tab_frame };

                    BOOST_TEST(tab_frame.tab_count() == 1U);

                    {
                        label_type label2{ tab_frame };

                        BOOST_TEST(tab_frame.tab_count() == 2U);
                    }

                    BOOST_TEST(tab_frame.tab_count() == 1U);
                }

                BOOST_AUTO_TEST_CASE(tab_at)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type          parent{};
                        const tab_frame_type tab_frame{ parent };

                        BOOST_CHECK_THROW(tab_frame.tab_at(0), std::out_of_range);
                    }
                    {
                        window_type    parent{};
                        tab_frame_type tab_frame{ parent };
                        label_type     label1{ tab_frame };
                        label_type     label2{ tab_frame };

                        BOOST_CHECK(&tab_frame.tab_at(0).body().template get<label_type>() == &label1);
                        BOOST_CHECK(&tab_frame.tab_at(1).body().template get<label_type>() == &label2);
                        BOOST_CHECK_THROW(tab_frame.tab_at(2), std::out_of_range);

                        auto& tab = tab_frame.tab_at(0);

                        BOOST_TEST(tab.label().title().empty());

                        tab.label().set_title(string_type{ TETENGO2_TEXT("hoge") });

                        BOOST_CHECK(tab.label().title() == string_type{ TETENGO2_TEXT("hoge") });
                    }
                }

                BOOST_AUTO_TEST_CASE(selected_tab_index)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type    parent{};
                    tab_frame_type tab_frame{ parent };

                    BOOST_CHECK_THROW(tab_frame.selected_tab_index(), std::logic_error);

                    label_type label1{ tab_frame };

                    BOOST_TEST(tab_frame.selected_tab_index() == 0U);

                    {
                        label_type label2{ tab_frame };

                        BOOST_TEST(tab_frame.selected_tab_index() == 1U);
                    }

                    BOOST_TEST(tab_frame.selected_tab_index() == 0U);
                }

                BOOST_AUTO_TEST_CASE(select_tab)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type    parent{};
                    tab_frame_type tab_frame{ parent };

                    BOOST_CHECK_THROW(tab_frame.select_tab(0), std::out_of_range);

                    label_type label1{ tab_frame };

                    BOOST_TEST(tab_frame.selected_tab_index() == 0U);

                    {
                        label_type label2{ tab_frame };

                        BOOST_TEST(tab_frame.selected_tab_index() == 1U);

                        tab_frame.select_tab(0);

                        BOOST_TEST(tab_frame.selected_tab_index() == 0U);
                    }

                    BOOST_TEST(tab_frame.selected_tab_index() == 0U);
                }

                BOOST_AUTO_TEST_CASE(move_tab)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type    parent{};
                    tab_frame_type tab_frame{ parent };
                    label_type     label1{ tab_frame };
                    label_type     label2{ tab_frame };
                    label_type     label3{ tab_frame };
                    tab_frame.tab_at(0).label().set_title(string_type{ TETENGO2_TEXT("hoge") });
                    tab_frame.tab_at(1).label().set_title(string_type{ TETENGO2_TEXT("fuga") });
                    tab_frame.tab_at(2).label().set_title(string_type{ TETENGO2_TEXT("piyo") });

                    tab_frame.move_tab(2, 2);

                    BOOST_CHECK(tab_frame.tab_at(0).label().title() == string_type{ TETENGO2_TEXT("hoge") });
                    BOOST_CHECK(tab_frame.tab_at(1).label().title() == string_type{ TETENGO2_TEXT("fuga") });
                    BOOST_CHECK(tab_frame.tab_at(2).label().title() == string_type{ TETENGO2_TEXT("piyo") });
                    BOOST_TEST(tab_frame.tab_at(0).index() == 0U);
                    BOOST_TEST(tab_frame.tab_at(1).index() == 1U);
                    BOOST_TEST(tab_frame.tab_at(2).index() == 2U);
                    BOOST_TEST(tab_frame.selected_tab_index() == 2U);

                    tab_frame.move_tab(2, 1);

                    BOOST_CHECK(tab_frame.tab_at(0).label().title() == string_type{ TETENGO2_TEXT("hoge") });
                    BOOST_CHECK(tab_frame.tab_at(1).label().title() == string_type{ TETENGO2_TEXT("piyo") });
                    BOOST_CHECK(tab_frame.tab_at(2).label().title() == string_type{ TETENGO2_TEXT("fuga") });
                    BOOST_TEST(tab_frame.tab_at(0).index() == 0U);
                    BOOST_TEST(tab_frame.tab_at(1).index() == 1U);
                    BOOST_TEST(tab_frame.tab_at(2).index() == 2U);
                    BOOST_TEST(tab_frame.selected_tab_index() == 1U);

                    tab_frame.move_tab(0, 1);

                    BOOST_CHECK(tab_frame.tab_at(0).label().title() == string_type{ TETENGO2_TEXT("piyo") });
                    BOOST_CHECK(tab_frame.tab_at(1).label().title() == string_type{ TETENGO2_TEXT("hoge") });
                    BOOST_CHECK(tab_frame.tab_at(2).label().title() == string_type{ TETENGO2_TEXT("fuga") });
                    BOOST_TEST(tab_frame.tab_at(0).index() == 0U);
                    BOOST_TEST(tab_frame.tab_at(1).index() == 1U);
                    BOOST_TEST(tab_frame.tab_at(2).index() == 2U);
                    BOOST_TEST(tab_frame.selected_tab_index() == 0U);

                    tab_frame.move_tab(0, 2);

                    BOOST_CHECK(tab_frame.tab_at(0).label().title() == string_type{ TETENGO2_TEXT("hoge") });
                    BOOST_CHECK(tab_frame.tab_at(1).label().title() == string_type{ TETENGO2_TEXT("fuga") });
                    BOOST_CHECK(tab_frame.tab_at(2).label().title() == string_type{ TETENGO2_TEXT("piyo") });
                    BOOST_TEST(tab_frame.tab_at(0).index() == 0U);
                    BOOST_TEST(tab_frame.tab_at(1).index() == 1U);
                    BOOST_TEST(tab_frame.tab_at(2).index() == 2U);
                    BOOST_TEST(tab_frame.selected_tab_index() == 2U);

                    BOOST_CHECK_THROW(tab_frame.move_tab(3, 0), std::out_of_range);
                    BOOST_CHECK_THROW(tab_frame.move_tab(0, 3), std::out_of_range);
                    BOOST_CHECK_THROW(tab_frame.move_tab(3, 3), std::out_of_range);
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
