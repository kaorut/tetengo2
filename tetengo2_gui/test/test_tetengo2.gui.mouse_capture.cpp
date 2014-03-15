/*! \file
    \brief Test of class tetengo2::gui::mouse_capture.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.mouse_capture.h"

#include "test_tetengo2.gui.type_list.h"

#include "tetengo2.gui.mouse_capture.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::widget>::type
        widget_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type
        window_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::observer_set_type_list, test_tetengo2::gui::type::observer_set::mouse_observer_set
        >::type::mouse_button_type
        mouse_button_type;

    typedef
        tetengo2::gui::mouse_capture<widget_type, mouse_button_type, tetengo2::detail::stub::mouse_capture>
        mouse_capture_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(mouse_capture)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const window_type window;
        const mouse_capture_type mouse_capture(window, mouse_button_type::left);
    }

    BOOST_AUTO_TEST_CASE(button)
    {
        BOOST_TEST_PASSPOINT();

        {
            const window_type window;
            const mouse_capture_type mouse_capture(window, mouse_button_type::left);

            BOOST_CHECK(mouse_capture.button() == mouse_button_type::left);
        }
        {
            const window_type window;
            const mouse_capture_type mouse_capture(window, mouse_button_type::right);

            BOOST_CHECK(mouse_capture.button() == mouse_button_type::right);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
