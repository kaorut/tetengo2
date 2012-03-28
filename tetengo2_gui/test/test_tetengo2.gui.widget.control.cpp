/*! \file
    \brief Test of class tetengo2::gui::widget::control.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>
//#include <utility>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.alert.h"
#include "tetengo2.detail.stub.cursor.h"
#include "tetengo2.detail.stub.drawing.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.message_handler.h"
#include "tetengo2.detail.stub.unit.h"
#include "tetengo2.detail.stub.virtual_key.h"
#include "tetengo2.detail.stub.widget.h"
#include "tetengo2.gui.alert.h"
#include "tetengo2.gui.cursor.system.h"
#include "tetengo2.gui.drawing.background.h"
#include "tetengo2.gui.drawing.color.h"
#include "tetengo2.gui.drawing.font.h"
#include "tetengo2.gui.drawing.picture.h"
#include "tetengo2.gui.drawing.widget_canvas.h"
#include "tetengo2.gui.message.focus_observer_set.h"
#include "tetengo2.gui.message.keyboard_observer_set.h"
#include "tetengo2.gui.message.menu_observer_set.h"
#include "tetengo2.gui.message.mouse_observer_set.h"
#include "tetengo2.gui.message.paint_observer_set.h"
#include "tetengo2.gui.unit.em.h"
#include "tetengo2.gui.virtual_key.h"
#include "tetengo2.gui.widget.abstract_window.h"
#include "tetengo2.gui.widget.traits.control_traits.h"
#include "tetengo2.gui.widget.traits.widget_traits.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"
#include "tetengo2.unique.h"

#include "tetengo2.gui.widget.control.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::text::encoding::locale<std::string, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::text::encoding::locale<std::string, encoding_details_type>
        ui_encoding_type;

    typedef
        tetengo2::text::encoder<internal_encoding_type, ui_encoding_type>
        ui_encoder_type;

    typedef
        tetengo2::text::encoding::locale<std::string, encoding_details_type>
        exception_encoding_type;

    typedef
        tetengo2::text::encoder<
            internal_encoding_type, exception_encoding_type
        >
        exception_encoder_type;

    typedef tetengo2::detail::stub::drawing drawing_details_type;

    typedef
        tetengo2::gui::drawing::font<
            std::string, std::size_t, drawing_details_type
        >
        font_type;

    typedef
        tetengo2::gui::drawing::picture<std::size_t, drawing_details_type>
        picture_type;

    typedef
        tetengo2::gui::drawing::background<drawing_details_type>
        background_type;

    typedef tetengo2::detail::stub::unit unit_details_type;

    typedef
        tetengo2::gui::unit::em<std::size_t, std::size_t, unit_details_type>
        unit_size_type;

    typedef std::pair<unit_size_type, unit_size_type> dimension_type;

    typedef
        tetengo2::gui::drawing::widget_canvas<
            std::size_t,
            std::string,
            dimension_type,
            ui_encoder_type,
            background_type,
            font_type,
            picture_type,
            drawing_details_type
        >
        canvas_type;

    typedef tetengo2::detail::stub::alert alert_details_type;

    typedef
        tetengo2::gui::alert<
            ui_encoder_type, exception_encoder_type, alert_details_type
        >
        alert_type;

    typedef
        tetengo2::gui::unit::em<
            std::ptrdiff_t, std::ptrdiff_t, unit_details_type
        >
        unit_difference_type;

    typedef
        std::pair<unit_difference_type, unit_difference_type> position_type;

    typedef
        tetengo2::gui::cursor::system<tetengo2::detail::stub::cursor>
        system_cursor_type;

    typedef
        tetengo2::gui::virtual_key<
            std::string, tetengo2::detail::stub::virtual_key
        >
        virtual_key_type;

    typedef
        tetengo2::gui::widget::traits::widget_traits<
            canvas_type,
            alert_type,
            position_type,
            dimension_type,
            std::string,
            ui_encoder_type,
            background_type,
            font_type,
            system_cursor_type,
            tetengo2::gui::message::focus_observer_set,
            tetengo2::gui::message::paint_observer_set<canvas_type>,
            tetengo2::gui::message::keyboard_observer_set<
                virtual_key_type, wchar_t
            >,
            tetengo2::gui::message::mouse_observer_set
        >
        widget_traits_type;

    typedef tetengo2::gui::drawing::color<unsigned char> color_type;

    typedef
        tetengo2::gui::widget::traits::control_traits<
            widget_traits_type, color_type
        >
        control_traits_type;

    typedef tetengo2::detail::stub::widget widget_details_type;

    typedef
        tetengo2::detail::stub::message_handler message_handler_details_type;

    typedef
        tetengo2::gui::widget::control<
            control_traits_type,
            widget_details_type,
            message_handler_details_type
        >
        control_type;

    class concrete_control : public control_type
    {
    public:
        concrete_control()
        :
        control_type(
            message_handler_map_type(),
            widget_details_type::widget_details_ptr_type(
                tetengo2::make_unique<
                    widget_details_type::widget_details_type
                >()
            )
        )
        {
            initialize(this);
        }

        virtual ~concrete_control()
        TETENGO2_CPP11_NOEXCEPT
        {}


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
            control.set_text_color(color_type(0x12, 0x34, 0x56));

            BOOST_CHECK(
                *control.text_color() == color_type(0x12, 0x34, 0x56)
            );
        }
    }

    BOOST_AUTO_TEST_CASE(set_text_color)
    {
        BOOST_TEST_PASSPOINT();

        concrete_control control;

        control.set_text_color(color_type(0x12, 0x34, 0x56));

        BOOST_CHECK(
            *control.text_color() == color_type(0x12, 0x34, 0x56)
        );

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
