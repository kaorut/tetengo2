/*! \file
    \brief Test of class tetengo2::gui::widget::control.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/stub/widget.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/widget/control.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using color_type = tetengo2::gui::drawing::color;

    using control_type = tetengo2::gui::widget::control;

    class concrete_control : public control_type
    {
    public:
        concrete_control()
        : control_type{ control_type::scroll_bar_style_type::none,
                        message_handler_map_type{},
                        widget_details_type::widget_details_ptr_type(
                            std::make_unique<tetengo2::detail::stub::widget::widget_details_type>()) }
        {
            tetengo2::gui::widget::widget::initialize(this);
        }

        virtual ~concrete_control() = default;
    };
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(widget)
            BOOST_AUTO_TEST_SUITE(control)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const concrete_control control;
                }

                BOOST_AUTO_TEST_CASE(text_color)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const concrete_control control;

                        BOOST_TEST(!control.text_color());
                    }
                    {
                        concrete_control control;
                        control.set_text_color(color_type{ 0x12, 0x34, 0x56 });

                        BOOST_CHECK((*control.text_color() == color_type{ 0x12, 0x34, 0x56 }));
                    }
                }

                BOOST_AUTO_TEST_CASE(set_text_color)
                {
                    BOOST_TEST_PASSPOINT();

                    concrete_control control;

                    control.set_text_color(color_type{ 0x12, 0x34, 0x56 });

                    BOOST_CHECK((*control.text_color() == color_type{ 0x12, 0x34, 0x56 }));

                    control.set_text_color();

                    BOOST_TEST(!control.text_color());
                }

                BOOST_AUTO_TEST_CASE(focusable)
                {
                    BOOST_TEST_PASSPOINT();

                    const concrete_control control;

                    control.focusable();
                }

                BOOST_AUTO_TEST_CASE(set_focusable)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        concrete_control control;

                        control.set_focusable(false);

                        BOOST_TEST(!control.focusable());
                    }
                    {
                        concrete_control control;

                        control.set_focusable(true);

                        BOOST_TEST(control.focusable());
                    }
                }

                BOOST_AUTO_TEST_CASE(details_impl)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const concrete_control control;

                        control.details();
                    }
                    {
                        concrete_control control;

                        control.details();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
