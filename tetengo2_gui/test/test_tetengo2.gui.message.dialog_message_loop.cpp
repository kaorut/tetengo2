/*! \file
    \brief Test of class tetengo2::gui::message::dialog_message_loop.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>
//#include <utility>

//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.alert.h"
#include "tetengo2.detail.stub.cursor.h"
#include "tetengo2.detail.stub.drawing.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.menu.h"
#include "tetengo2.detail.stub.message_handler.h"
#include "tetengo2.detail.stub.message_loop.h"
#include "tetengo2.detail.stub.unit.h"
#include "tetengo2.detail.stub.virtual_key.h"
#include "tetengo2.detail.stub.widget.h"
#include "tetengo2.gui.alert.h"
#include "tetengo2.gui.cursor.system.h"
#include "tetengo2.gui.drawing.background.h"
#include "tetengo2.gui.drawing.font.h"
#include "tetengo2.gui.drawing.picture.h"
#include "tetengo2.gui.drawing.widget_canvas.h"
#include "tetengo2.gui.menu.menu_bar.h"
#include "tetengo2.gui.menu.menu_base.h"
#include "tetengo2.gui.menu.shortcut_key.h"
#include "tetengo2.gui.menu.shortcut_key_table.h"
#include "tetengo2.gui.menu.traits.h"
#include "tetengo2.gui.message.focus_observer_set.h"
#include "tetengo2.gui.message.keyboard_observer_set.h"
#include "tetengo2.gui.message.menu_observer_set.h"
#include "tetengo2.gui.message.mouse_observer_set.h"
#include "tetengo2.gui.message.paint_observer_set.h"
#include "tetengo2.gui.message.window_observer_set.h"
#include "tetengo2.gui.unit.em.h"
#include "tetengo2.gui.virtual_key.h"
#include "tetengo2.gui.widget.abstract_window.h"
#include "tetengo2.gui.widget.traits.abstract_window_traits.h"
#include "tetengo2.gui.widget.traits.widget_traits.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"
#include "tetengo2.unique.h"

#include "tetengo2.gui.message.dialog_message_loop.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::text::encoding::locale<std::wstring, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::text::encoding::locale<std::wstring, encoding_details_type>
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
        tetengo2::gui::cursor::system<tetengo2::detail::stub::cursor>
        system_cursor_type;

    typedef
        tetengo2::gui::widget::traits::widget_traits<
            canvas_type,
            alert_type,
            position_type,
            dimension_type,
            std::wstring,
            ui_encoder_type,
            background_type,
            font_type,
            system_cursor_type,
            tetengo2::gui::message::focus_observer_set,
            tetengo2::gui::message::paint_observer_set<canvas_type>,
            tetengo2::gui::message::keyboard_observer_set<wchar_t>,
            tetengo2::gui::message::mouse_observer_set
        >
        widget_traits_type;

    typedef
        tetengo2::gui::menu::shortcut_key<
            tetengo2::gui::virtual_key<
                tetengo2::detail::stub::virtual_key<std::wstring>
            >
        >
        shortcut_key_type;

    typedef
        tetengo2::gui::menu::traits<
            std::wstring,
            shortcut_key_type,
            ui_encoder_type,
            tetengo2::gui::message::menu_observer_set
        >
        menu_traits_type;

    typedef tetengo2::detail::stub::menu menu_details_type;

    typedef
        tetengo2::gui::menu::menu_base<menu_traits_type, menu_details_type>
        menu_base_type;

    typedef
        tetengo2::gui::menu::shortcut_key_table<
            shortcut_key_type, menu_base_type, menu_details_type
        >
        shortcut_key_table_type;

    typedef
        tetengo2::gui::menu::menu_bar<
            menu_traits_type, shortcut_key_table_type, menu_details_type
        >
        menu_bar_type;

    typedef
        tetengo2::gui::widget::traits::abstract_window_traits<
            widget_traits_type,
            menu_bar_type,
            tetengo2::gui::message::window_observer_set
        >
        abstract_window_traits_type;

    typedef tetengo2::detail::stub::widget widget_details_type;

    typedef
        tetengo2::detail::stub::message_handler<widget_details_type>
        message_handler_details_type;

    typedef
        tetengo2::gui::widget::abstract_window<
            abstract_window_traits_type,
            widget_details_type,
            message_handler_details_type
        >
        abstract_window_type;

    typedef
        tetengo2::gui::message::dialog_message_loop<
            abstract_window_type,
            tetengo2::detail::stub::message_loop
        >
        dialog_message_loop_type;

    class concrete_window : public abstract_window_type
    {
    public:
        concrete_window()
        :
        abstract_window_type(message_handler_map_type()),
        m_p_details(tetengo2::make_unique<details_type>())
        {
            initialize(this);
        }

        virtual ~concrete_window()
        TETENGO2_CPP11_NOEXCEPT
        {}

        virtual boost::optional<const details_type&> details_impl()
        const
        {
            return boost::make_optional<const details_type&>(*m_p_details);
        }

        virtual boost::optional<details_type&> details_impl()
        {
            return boost::make_optional<details_type&>(*m_p_details);
        }


    private:
        details_ptr_type m_p_details;


    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(dialog_message_loop)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        concrete_window window;
        const dialog_message_loop_type dialog_message_loop(window);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        concrete_window window;
        const dialog_message_loop_type dialog_message_loop(window);

        dialog_message_loop();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
