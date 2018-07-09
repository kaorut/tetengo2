/*! \file
    \brief Test of class tetengo2::gui::widget::button.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/widget/button.h>
#include <tetengo2/gui/widget/window.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using menu_details_type = detail_type_list_type::menu_type;

    using window_type = tetengo2::gui::widget::window;

    using button_type = tetengo2::gui::widget::button<
        common_type_list_type::widget_details_type,
        common_type_list_type::drawing_details_type,
        common_type_list_type::scroll_details_type,
        common_type_list_type::message_handler_details_type>;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(widget)
            BOOST_AUTO_TEST_SUITE(button)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type       parent{};
                        const button_type button{ parent, button_type::style_type::normal };
                    }
                    {
                        window_type       parent{};
                        const button_type button{ parent, button_type::style_type::default_ };
                    }
                    {
                        window_type       parent{};
                        const button_type button{ parent, button_type::style_type::cancel };
                    }
                }

                BOOST_AUTO_TEST_CASE(style)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type       parent{};
                        const button_type button{ parent, button_type::style_type::normal };

                        BOOST_CHECK(button.style() == button_type::style_type::normal);
                    }
                    {
                        window_type       parent{};
                        const button_type button{ parent, button_type::style_type::default_ };

                        BOOST_CHECK(button.style() == button_type::style_type::default_);
                    }
                    {
                        window_type       parent{};
                        const button_type button{ parent, button_type::style_type::cancel };

                        BOOST_CHECK(button.style() == button_type::style_type::cancel);
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
