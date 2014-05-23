/*! \file
    \brief Test of class tetengo2::gui::widget::control.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using color_type =
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::color>::type;

    using control_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::control>::type;

    class concrete_control : public control_type
    {
    public:
        concrete_control()
        :
        control_type(
            control_type::scroll_bar_style_type::none,
            message_handler_map_type{},
            widget_details_type::widget_details_ptr_type(
                tetengo2::stdalt::make_unique<widget_details_type::widget_details_type>()
            )
        )
        {
            this->initialize(this);
        }

        virtual ~concrete_control()
        TETENGO2_STDALT_DESTRUCTOR_DEFAULT_IMPLEMENTATION;


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

            BOOST_CHECK(!control.text_color());
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

        BOOST_CHECK(!control.text_color());
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

            BOOST_CHECK(!control.focusable());
        }
        {
            concrete_control control;

            control.set_focusable(true);

            BOOST_CHECK(control.focusable());
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
