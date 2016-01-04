/*! \file
    \brief Test of class tetengo2::gui::widget::dialog.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <chrono>
#include <future>

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using widget_traits_type = common_type_list_type::widget_traits_type;

    using widget_details_traits_type = common_type_list_type::widget_details_traits_type;

    using menu_details_type = detail_type_list_type::menu_type;

    using abstract_window_type =
        tetengo2::gui::widget::abstract_window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using message_loop_details_type = detail_type_list_type::message_loop_type;

    using timer_details_type = detail_type_list_type::timer_type;

    using system_color_details_type = detail_type_list_type::system_color_type;

    using message_catalog_type = common_type_list_type::message_catalog_type;

    using dialog_type =
        tetengo2::gui::widget::progress_dialog<
            widget_traits_type,
            int,
            message_catalog_type,
            widget_details_traits_type,
            menu_details_type,
            message_loop_details_type,
            timer_details_type,
            system_color_details_type
        >;

    using promise_type = dialog_type::promise_type;

    using future_type = dialog_type::future_type;


    // functions

    void task(promise_type& promise)
    {
        promise.set_value(42);
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(progress_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog;
        const dialog_type dialog{
            parent,
            string_type{ TETENGO2_TEXT("title") },
            string_type{ TETENGO2_TEXT("waiting") },
            string_type{ TETENGO2_TEXT("canceling") },
            task,
            message_catalog
        };
    }

    BOOST_AUTO_TEST_CASE(task_future)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog;
        dialog_type dialog{
            parent,
            string_type{ TETENGO2_TEXT("title") },
            string_type{ TETENGO2_TEXT("waiting") },
            string_type{ TETENGO2_TEXT("canceling") },
            task,
            message_catalog
        };
        const auto& future = dialog.task_future();

        BOOST_CHECK(future.wait_for(std::chrono::seconds{ 0 }) == std::future_status::timeout);
    }


    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const message_catalog_type message_catalog;
        dialog_type dialog{
            parent,
            string_type{ TETENGO2_TEXT("title") },
            string_type{ TETENGO2_TEXT("waiting") },
            string_type{ TETENGO2_TEXT("canceling") },
            task,
            message_catalog
        };
        auto& future = dialog.task_future();

        dialog.do_modal();

        BOOST_TEST(future.get() == 42);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
