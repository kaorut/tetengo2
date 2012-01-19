/*! \file
    \brief Test of class tetengo2::gui::common_dialog::message_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cstddef>
//#include <memory>
//#include <string>
//#include <tuple>
//#include <utility>
//#include <vector>

//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.alert.h"
#include "tetengo2.detail.stub.common_dialog.h"
#include "tetengo2.detail.stub.cursor.h"
#include "tetengo2.detail.stub.drawing.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.message_handler.h"
#include "tetengo2.detail.stub.unit.h"
#include "tetengo2.detail.stub.widget.h"
#include "tetengo2.gui.alert.h"
#include "tetengo2.gui.cursor.system.h"
#include "tetengo2.gui.drawing.background.h"
#include "tetengo2.gui.drawing.color.h"
#include "tetengo2.gui.drawing.font.h"
#include "tetengo2.gui.drawing.picture.h"
#include "tetengo2.gui.drawing.transparent_background.h"
#include "tetengo2.gui.drawing.widget_canvas.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.message.menu_observer_set.h"
#include "tetengo2.gui.message.mouse_observer_set.h"
#include "tetengo2.gui.message.paint_observer_set.h"
#include "tetengo2.gui.unit.em.h"
#include "tetengo2.gui.widget.abstract_window.h"
#include "tetengo2.gui.widget.traits.widget_traits.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"
#include "tetengo2.unique.h"

#include "tetengo2.gui.common_dialog.message_box.h"


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
            tetengo2::gui::message::paint_observer_set<canvas_type>,
            tetengo2::gui::message::mouse_observer_set
        >
        widget_traits_type;

    typedef tetengo2::gui::drawing::color<unsigned char> color_type;

    typedef tetengo2::detail::stub::widget widget_details_type;

    typedef
        tetengo2::detail::stub::message_handler<widget_details_type>
        message_handler_details_type;

    typedef
        tetengo2::gui::widget::widget<
            widget_traits_type,
            widget_details_type,
            message_handler_details_type
        >
        widget_type;

    typedef
        tetengo2::gui::common_dialog::message_box<
            widget_type,
            std::wstring,
            ui_encoder_type,
            tetengo2::detail::stub::common_dialog
        >
        message_box_type;

    typedef
        std::tuple<std::wstring, std::size_t, bool, bool, bool, bool>
        details_font_type;

    class concrete_widget : public widget_type
    {
    public:
        static const encoder_type& test_encoder()
        {
            return encoder();
        }

        explicit concrete_widget(widget_type* const p_parent = NULL)
        :
        widget_type(message_handler_map_type()),
        m_p_details(
            tetengo2::make_unique<widget_details_type::widget_details_type>(
                p_parent,
                true,
                true,
                std::make_pair(0, 0),
                std::make_pair(1, 1),
                string_type(),
                details_font_type(
                    std::wstring(), 12, false, false, false, false
                ),
                std::vector<void*>()
            )
        )
        {
            initialize(this);
        }

        virtual ~concrete_widget()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        std::unique_ptr<details_type> m_p_details;

        virtual boost::optional<const details_type&> details_impl()
        const
        {
            return *m_p_details;
        }

        virtual boost::optional<details_type&> details_impl()
        {
            return *m_p_details;
        }


    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(common_dialog)
BOOST_AUTO_TEST_SUITE(message_box)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        //{
        //    concrete_widget parent;
        //    const message_box_type message_box(
        //        std::wstring(), parent
        //    );
        //}
    }

    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        //concrete_widget parent;
        //message_box_type message_box(L"hoge", make_file_filters(), parent);

        //message_box.do_modal();
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        //{
        //    concrete_widget parent;
        //    const message_box_type message_box(
        //        L"hoge", make_file_filters(), parent
        //    );

        //    message_box.details();
        //}
        //{
        //    concrete_widget parent;
        //    message_box_type message_box(L"hoge", make_file_filters(), parent);

        //    message_box.details();
        //}
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
