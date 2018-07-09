/*! \file
    \brief Test of class tetengo2::gui::widget::link_label.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <string>

#include <boost/preprocessor.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/link_label.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/gui/widget/window.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using menu_details_type = detail_type_list_type::menu_type;

    using window_type = tetengo2::gui::widget::window;

    using link_label_type = tetengo2::gui::widget::link_label<
        common_type_list_type::widget_details_type,
        common_type_list_type::drawing_details_type,
        common_type_list_type::scroll_details_type,
        common_type_list_type::message_handler_details_type>;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(widget)
            BOOST_AUTO_TEST_SUITE(link_label)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type           parent{};
                    const link_label_type label{ parent };
                }

                BOOST_AUTO_TEST_CASE(target)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type           parent{};
                    const link_label_type label{ parent };

                    BOOST_TEST(label.target().empty());
                }

                BOOST_AUTO_TEST_CASE(set_target)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type     parent{};
                    link_label_type label{ parent };

                    label.set_target(string_type{ TETENGO2_TEXT("http://www.tetengo.org") });

                    BOOST_CHECK(label.target() == string_type{ TETENGO2_TEXT("http://www.tetengo.org") });
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
