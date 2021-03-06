/*! \file
    \brief Test of class tetengo2::gui::mouse_capture.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/gui/mouse_capture.h>
#include <tetengo2/gui/widget/window.h>


namespace {
    // types

    using window_type = tetengo2::gui::widget::window;

    using mouse_button_type = tetengo2::gui::message::mouse_observer_set::mouse_button_type;

    using mouse_capture_type = tetengo2::gui::mouse_capture;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(mouse_capture)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                const window_type        window;
                const mouse_capture_type mouse_capture{ window, mouse_button_type::left };
            }

            BOOST_AUTO_TEST_CASE(button)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const window_type        window{};
                    const mouse_capture_type mouse_capture{ window, mouse_button_type::left };

                    BOOST_CHECK(mouse_capture.button() == mouse_button_type::left);
                }
                {
                    const window_type        window{};
                    const mouse_capture_type mouse_capture{ window, mouse_button_type::right };

                    BOOST_CHECK(mouse_capture.button() == mouse_button_type::right);
                }
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
