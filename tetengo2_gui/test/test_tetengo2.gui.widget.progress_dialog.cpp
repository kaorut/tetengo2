/*! \file
    \brief Test of class tetengo2::gui::widget::dialog.

    Copyright (C) 2007-2015 kaoru

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

    using widget_traits_type = common_type_list_type::widget_traits_type;

    using widget_details_traits_type = common_type_list_type::widget_details_traits_type;

    using menu_details_type = detail_type_list_type::menu_type;

    using abstract_window_type =
        tetengo2::gui::widget::abstract_window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using message_loop_details_type = detail_type_list_type::message_loop_type;

    using timer_details_type = detail_type_list_type::timer_type;

    using dialog_type =
        tetengo2::gui::widget::progress_dialog<
            widget_traits_type,
            int,
            widget_details_traits_type,
            menu_details_type,
            message_loop_details_type,
            timer_details_type
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
        const dialog_type dialog{ parent, task };
    }

    BOOST_AUTO_TEST_CASE(task_future)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        dialog_type dialog{ parent, task };
        const future_type& future = dialog.task_future();

        BOOST_CHECK(future.wait_for(std::chrono::seconds{ 0 }) == std::future_status::timeout);
    }


    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        dialog_type dialog{ parent, task };
        future_type& future = dialog.task_future();

        dialog.do_modal();

        BOOST_CHECK_EQUAL(future.get(), 42);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
