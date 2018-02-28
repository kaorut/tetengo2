/*! \file
    \brief Test of class tetengo2::gui::mouse_capture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/message/mouse_observer_set.h>
#include <tetengo2/gui/mouse_capture.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/gui/widget/window.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using widget_traits_type = common_type_list_type::widget_traits_type;

    using widget_details_traits_type = common_type_list_type::widget_details_traits_type;

    using widget_type = tetengo2::gui::widget::widget<widget_traits_type, widget_details_traits_type>;

    using menu_details_type = detail_type_list_type::menu_type;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using mouse_button_type = tetengo2::gui::message::mouse_observer_set<
        common_type_list_type::position_type,
        common_type_list_type::difference_type>::mouse_button_type;

    using mouse_capture_type =
        tetengo2::gui::mouse_capture<widget_type, mouse_button_type, detail_type_list_type::mouse_capture_type>;
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
