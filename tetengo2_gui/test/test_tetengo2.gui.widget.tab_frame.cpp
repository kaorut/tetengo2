/*! \file
    \brief Test of class tetengo2::gui::widget::tab_frame.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <memory>
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

    using widget_type = tab_frame_type::widget_type;

    using tab_type = tetengo2::gui::widget::tab<string_type, widget_type>;


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


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(tab)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        std::unique_ptr<widget_type> p_tab_frame = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
        const tab_type tab( std::move(p_tab_frame), string_type{ TETENGO2_TEXT("hoge") } );
    }

    BOOST_AUTO_TEST_CASE(widget)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            std::unique_ptr<widget_type> p_tab_frame = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
            const widget_type* const rp_tab_frame = p_tab_frame.get();
            const tab_type tab( std::move(p_tab_frame), string_type{ TETENGO2_TEXT("hoge") } );

            BOOST_CHECK(&tab.template widget<tab_frame_type>() == rp_tab_frame);
        }
        {
            window_type parent{};
            std::unique_ptr<widget_type> p_tab_frame = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
            widget_type* const rp_tab_frame = p_tab_frame.get();
            tab_type tab( std::move(p_tab_frame), string_type{ TETENGO2_TEXT("hoge") } );

            BOOST_CHECK(&tab.template widget<tab_frame_type>() == rp_tab_frame);
        }
    }

    BOOST_AUTO_TEST_CASE(title)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        std::unique_ptr<widget_type> p_tab_frame = tetengo2::stdalt::make_unique<tab_frame_type>(parent);
        const tab_type tab( std::move(p_tab_frame), string_type{ TETENGO2_TEXT("hoge") } );

        BOOST_CHECK(tab.title() == string_type{ TETENGO2_TEXT("hoge") });
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
