/*! \file
    \brief Test of class tetengo2::gui::timer.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <chrono>

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::detail_type_list;

    using type_list_type = test_tetengo2::gui::type_list<detail_type_list_type>;

    using widget_traits_type = boost::mpl::at<type_list_type, test_tetengo2::gui::type::widget_traits>::type;

    using widget_details_traits_type =
        boost::mpl::at<type_list_type, test_tetengo2::gui::type::widget_details_traits>::type;

    using widget_type = tetengo2::gui::widget::widget<widget_traits_type, widget_details_traits_type>;

    using menu_details_type = boost::mpl::at<detail_type_list_type, test_tetengo2::gui::type::detail::menu>::type;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using timer_type =
        tetengo2::gui::timer<
            widget_type, boost::mpl::at<detail_type_list_type, test_tetengo2::gui::type::detail::timer>::type
        >;


    // functions

    void timer_function(bool&)
    {}


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(timer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const window_type window;
        const timer_type timer{ window, timer_function, std::chrono::milliseconds(42), false };
    }

    BOOST_AUTO_TEST_CASE(stopped)
    {
        BOOST_TEST_PASSPOINT();

        const window_type window;
        const timer_type timer{ window, timer_function, std::chrono::milliseconds(42), false };

        timer.stopped();
    }

    BOOST_AUTO_TEST_CASE(stop)
    {
        BOOST_TEST_PASSPOINT();

        const window_type window;
        timer_type timer{ window, timer_function, std::chrono::milliseconds(42), false };

        timer.stop();

        BOOST_CHECK(timer.stopped());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
