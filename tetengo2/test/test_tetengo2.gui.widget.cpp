/*! \file
    \brief Test of class tetengo2::gui::widget.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>
//#include <utility>

#include <boost/test/unit_test.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.alert.h"
#include "tetengo2.detail.stub.drawing.h"
#include "tetengo2.detail.stub.message_handler.h"
#include "tetengo2.detail.stub.unit.h"
#include "tetengo2.detail.stub.widget.h"
#include "tetengo2.encoder.h"
#include "tetengo2.encoding.locale.h"
#include "tetengo2.gui.abstract_window.h"
#include "tetengo2.gui.alert.h"
#include "tetengo2.gui.drawing.background.h"
#include "tetengo2.gui.drawing.color.h"
#include "tetengo2.gui.drawing.font.h"
#include "tetengo2.gui.drawing.picture.h"
#include "tetengo2.gui.drawing.widget_canvas.h"
#include "tetengo2.gui.menu_observer_set.h"
#include "tetengo2.gui.mouse_observer_set.h"
#include "tetengo2.gui.paint_observer_set.h"
#include "tetengo2.gui.traits.widget_traits.h"
#include "tetengo2.gui.unit.em.h"

#include "tetengo2.gui.widget.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::encoding::locale<std::wstring, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::encoding::locale<std::wstring, encoding_details_type>
        ui_encoding_type;

    typedef
        tetengo2::encoder<internal_encoding_type, ui_encoding_type>
        ui_encoder_type;

    typedef
        tetengo2::encoding::locale<std::string, encoding_details_type>
        exception_encoding_type;

    typedef
        tetengo2::encoder<internal_encoding_type, exception_encoding_type>
        exception_encoder_type;

    typedef tetengo2::detail::stub::drawing drawing_details_type;

    typedef
        tetengo2::gui::drawing::font<
            std::wstring, std::size_t, drawing_details_type
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
            std::wstring,
            dimension_type,
            ui_encoder_type,
            background_type,
            font_type,
            picture_type,
            drawing_details_type
        >
        canvas_type;

    typedef
        tetengo2::detail::stub::alert<std::string, ui_encoder_type>
        alert_details_type;

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
        tetengo2::gui::traits::widget_traits<
            canvas_type,
            alert_type,
            position_type,
            dimension_type,
            std::wstring,
            ui_encoder_type,
            background_type,
            font_type,
            tetengo2::gui::paint_observer_set<canvas_type>,
            tetengo2::gui::mouse_observer_set
        >
        widget_traits_type;

    typedef tetengo2::gui::drawing::color<unsigned char> color_type;

    typedef tetengo2::detail::stub::widget widget_details_type;

    typedef
        tetengo2::detail::stub::message_handler<widget_details_type>
        message_handler_details_type;

    typedef
        tetengo2::gui::widget<
            widget_traits_type,
            widget_details_type,
            message_handler_details_type
        >
        widget_type;

    class concrete_widget : public widget_type
    {
    public:
        concrete_widget()
        :
        widget_type(message_handler_map_type()),
        m_p_details(new widget_details_type::widget_details_type())
        {}

        virtual ~concrete_widget()
        TETENGO2_CPP0X_NOEXCEPT
        {}


    private:
        tetengo2::cpp0x::unique_ptr<details_type>::type m_p_details;

        virtual boost::optional<details_type&> details_impl()
        {
            return *m_p_details;
        }

        virtual boost::optional<const details_type&> details_impl()
        const
        {
            return *m_p_details;
        }


    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_widget widget;
    }

    BOOST_AUTO_TEST_CASE(has_parent)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(parent)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(root_ancestor)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_enabled)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(enabled)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_visible)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(visible)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(create_canvas)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_position)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(position)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_dimension)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_client_dimension)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(client_dimension)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_text)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(text)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_background)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(background)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(set_font)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(font)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(children)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(paint_observer_set)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(mouse_observer_set)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(destroyed)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(p_static_window_procedure)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(initialize)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(p_widget_from)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(window_procedure)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
