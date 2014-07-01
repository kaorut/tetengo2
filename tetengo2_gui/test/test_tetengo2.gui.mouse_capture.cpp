/*! \file
    \brief Test of class tetengo2::gui::mouse_capture.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.gui.h>
#include <tetengo2/detail/stub/mouse_capture.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using widget_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::widget>::type;

    using window_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type;

    using mouse_button_type =
        tetengo2::gui::message::mouse_observer_set<
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::position>::type,
            boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::difference>::type
        >::mouse_button_type;

    using mouse_capture_type =
        tetengo2::gui::mouse_capture<
            widget_type,
            mouse_button_type,
            boost::mpl::at<test_tetengo2::gui::detail_type_list, test_tetengo2::gui::type::detail::mouse_capture>::type
        >;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(mouse_capture)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const window_type window;
        const mouse_capture_type mouse_capture{ window, mouse_button_type::left };
    }

    BOOST_AUTO_TEST_CASE(button)
    {
        BOOST_TEST_PASSPOINT();

        {
            const window_type window{};
            const mouse_capture_type mouse_capture{ window, mouse_button_type::left };

            BOOST_CHECK(mouse_capture.button() == mouse_button_type::left);
        }
        {
            const window_type window{};
            const mouse_capture_type mouse_capture{ window, mouse_button_type::right };

            BOOST_CHECK(mouse_capture.button() == mouse_button_type::right);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
