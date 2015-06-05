/*! \file
    \brief Test of class tetengo2::gui::widget::tab_frame.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using widget_traits_type = common_type_list_type::widget_traits_type;

    using widget_details_traits_type = common_type_list_type::widget_details_traits_type;

    using menu_details_type = detail_type_list_type::menu_type;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using mouse_capture_details_type = detail_type_list_type::mouse_capture_type;

    using tab_frame_type =
        tetengo2::gui::widget::tab_frame<widget_traits_type, widget_details_traits_type, mouse_capture_details_type>;

    using string_type = tab_frame_type::string_type;

    using control_type = tab_frame_type::control_type;

    using tab_type = tetengo2::gui::widget::tab<string_type, control_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(tab_frame)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const tab_frame_type tab_frame{ parent };
    }

    BOOST_AUTO_TEST_CASE(tab_count)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const tab_frame_type tab_frame{ parent };

        BOOST_CHECK_EQUAL(tab_frame.tab_count(), 0);
    }

    BOOST_AUTO_TEST_CASE(tab_at)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const tab_frame_type tab_frame{ parent };

            BOOST_CHECK_THROW(tab_frame.tab_at(0), std::out_of_range);
        }
        {
            window_type parent{};
            tab_frame_type tab_frame{ parent };

            BOOST_CHECK_THROW(tab_frame.tab_at(0), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(insert_tab)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        tab_frame_type tab_frame{ parent };
        
        {
            auto p_child = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
            auto p_tab =
                tetengo2::stdalt::make_unique<tab_type>(std::move(p_child), string_type{ TETENGO2_TEXT("hoge") });
            tab_frame.insert_tab(0, std::move(p_tab));

            BOOST_CHECK_EQUAL(tab_frame.tab_count(), 1);
            BOOST_CHECK(tab_frame.tab_at(0).title() == string_type{ TETENGO2_TEXT("hoge") });
        }
        {
            auto p_child = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
            auto p_tab =
                tetengo2::stdalt::make_unique<tab_type>(std::move(p_child), string_type{ TETENGO2_TEXT("fuga") });
            tab_frame.insert_tab(0, std::move(p_tab));

            BOOST_CHECK_EQUAL(tab_frame.tab_count(), 2);
            BOOST_CHECK(tab_frame.tab_at(0).title() == string_type{ TETENGO2_TEXT("fuga") });
        }
        {
            auto p_child = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
            auto p_tab =
                tetengo2::stdalt::make_unique<tab_type>(std::move(p_child), string_type{ TETENGO2_TEXT("piyo") });
            BOOST_CHECK_THROW(tab_frame.insert_tab(3, std::move(p_tab)), std::out_of_range);

        }

        BOOST_CHECK_THROW(tab_frame.insert_tab(2, nullptr), std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(erase_tab)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        tab_frame_type tab_frame{ parent };
        
        {
            auto p_child = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
            auto p_tab =
                tetengo2::stdalt::make_unique<tab_type>(std::move(p_child), string_type{ TETENGO2_TEXT("hoge") });
            tab_frame.insert_tab(0, std::move(p_tab));
        }
        {
            auto p_child = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
            auto p_tab =
                tetengo2::stdalt::make_unique<tab_type>(std::move(p_child), string_type{ TETENGO2_TEXT("fuga") });
            tab_frame.insert_tab(0, std::move(p_tab));
        }
        {
            auto p_child = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
            auto p_tab =
                tetengo2::stdalt::make_unique<tab_type>(std::move(p_child), string_type{ TETENGO2_TEXT("piyo") });
            tab_frame.insert_tab(0, std::move(p_tab));
        }

        BOOST_CHECK_THROW(tab_frame.erase_tab(3), std::out_of_range);

        tab_frame.select_tab(1);

        tab_frame.erase_tab(0);

        BOOST_CHECK_EQUAL(tab_frame.tab_count(), 2);
        BOOST_CHECK_EQUAL(tab_frame.selected_tab_index(), 0);
        BOOST_CHECK(tab_frame.tab_at(0).visible());
        BOOST_CHECK(!tab_frame.tab_at(1).visible());

        tab_frame.erase_tab(0);

        BOOST_CHECK_EQUAL(tab_frame.tab_count(), 1);
        BOOST_CHECK_THROW(tab_frame.selected_tab_index(), std::logic_error);
        BOOST_CHECK(!tab_frame.tab_at(0).visible());

        tab_frame.erase_tab(0);

        BOOST_CHECK_EQUAL(tab_frame.tab_count(), 0);

        BOOST_CHECK_THROW(tab_frame.erase_tab(0), std::out_of_range);
    }

    BOOST_AUTO_TEST_CASE(selected_tab_index)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const tab_frame_type tab_frame{ parent };
        
        BOOST_CHECK_THROW(tab_frame.selected_tab_index(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(select_tab)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        tab_frame_type tab_frame{ parent };
        
        BOOST_CHECK_THROW(tab_frame.select_tab(0), std::out_of_range);

        {
            auto p_child = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
            auto p_tab =
                tetengo2::stdalt::make_unique<tab_type>(std::move(p_child), string_type{ TETENGO2_TEXT("hoge") });
            tab_frame.insert_tab(0, std::move(p_tab));

            BOOST_CHECK_EQUAL(tab_frame.selected_tab_index(), 0);
            BOOST_CHECK(tab_frame.tab_at(0).visible());
        }
        {
            auto p_child = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
            auto p_tab =
                tetengo2::stdalt::make_unique<tab_type>(std::move(p_child), string_type{ TETENGO2_TEXT("fuga") });
            tab_frame.insert_tab(0, std::move(p_tab));

            BOOST_CHECK_EQUAL(tab_frame.selected_tab_index(), 0);
            BOOST_CHECK(tab_frame.tab_at(0).visible());
            BOOST_CHECK(!tab_frame.tab_at(1).visible());
        }

        tab_frame.select_tab(1);

        BOOST_CHECK_EQUAL(tab_frame.selected_tab_index(), 1);
        BOOST_CHECK(!tab_frame.tab_at(0).visible());
        BOOST_CHECK(tab_frame.tab_at(1).visible());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(tab)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            auto p_tab_frame = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
            const tab_type tab{ std::move(p_tab_frame), string_type{ TETENGO2_TEXT("hoge") } };
        }
        {
            window_type parent{};
            std::unique_ptr<control_type> p_tab_frame{};
            string_type title{ TETENGO2_TEXT("hoge") };
            BOOST_CHECK_THROW(const tab_type tab(std::move(p_tab_frame), std::move(title)), std::invalid_argument);
        }
    }

    BOOST_AUTO_TEST_CASE(control)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            auto p_tab_frame = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
            const auto* const rp_tab_frame = p_tab_frame.get();
            const tab_type tab{ std::move(p_tab_frame), string_type{ TETENGO2_TEXT("hoge") } };

            BOOST_CHECK(&tab.template control<tab_frame_type>() == rp_tab_frame);
        }
        {
            window_type parent{};
            auto p_tab_frame = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
            auto* const rp_tab_frame = p_tab_frame.get();
            tab_type tab{ std::move(p_tab_frame), string_type{ TETENGO2_TEXT("hoge") } };

            BOOST_CHECK(&tab.template control<tab_frame_type>() == rp_tab_frame);
        }
    }

    BOOST_AUTO_TEST_CASE(title)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        auto p_tab_frame = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
        const tab_type tab{ std::move(p_tab_frame), string_type{ TETENGO2_TEXT("hoge") } };

        BOOST_CHECK(tab.title() == string_type{ TETENGO2_TEXT("hoge") });
    }

    BOOST_AUTO_TEST_CASE(visible)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        auto p_tab_frame = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
        const tab_type tab{ std::move(p_tab_frame), string_type{ TETENGO2_TEXT("hoge") } };

        BOOST_CHECK_EQUAL(tab.visible(), tab.template control<control_type>().visible());
    }

    BOOST_AUTO_TEST_CASE(set_visible)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        auto p_tab_frame = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
        tab_type tab{ std::move(p_tab_frame), string_type{ TETENGO2_TEXT("hoge") } };

        tab.set_visible(true);

        BOOST_CHECK(tab.visible());

        tab.set_visible(false);

        BOOST_CHECK(!tab.visible());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
