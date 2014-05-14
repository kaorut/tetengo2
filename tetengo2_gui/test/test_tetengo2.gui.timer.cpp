/*! \file
    \brief Test of class tetengo2::gui::timer.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <chrono>

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/stub/timer.h>

#include <tetengo2.gui.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using widget_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::widget>::type;

    using window_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type;

    using timer_type = tetengo2::gui::timer<widget_type, tetengo2::detail::stub::timer>;


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
        const timer_type timer(window, timer_function, std::chrono::milliseconds(42), false);
    }

    BOOST_AUTO_TEST_CASE(stopped)
    {
        BOOST_TEST_PASSPOINT();

        const window_type window;
        const timer_type timer(window, timer_function, std::chrono::milliseconds(42), false);

        timer.stopped();
    }

    BOOST_AUTO_TEST_CASE(stop)
    {
        BOOST_TEST_PASSPOINT();

        const window_type window;
        timer_type timer(window, timer_function, std::chrono::milliseconds(42), false);

        timer.stop();

        BOOST_CHECK(timer.stopped());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
