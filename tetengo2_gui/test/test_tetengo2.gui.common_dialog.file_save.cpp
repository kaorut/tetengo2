/*! \file
    \brief Test of class tetengo2::gui::common_dialog::file_save.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>
//#include <utility>

#include <boost/filesystem.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.alert.h"
#include "tetengo2.detail.stub.common_dialog.h"
#include "tetengo2.detail.stub.cursor.h"
#include "tetengo2.detail.stub.drawing.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.menu.h"
#include "tetengo2.detail.stub.message_handler.h"
#include "tetengo2.detail.stub.unit.h"
#include "tetengo2.detail.stub.virtual_key.h"
#include "tetengo2.detail.stub.widget.h"
#include "tetengo2.gui.alert.h"
#include "tetengo2.gui.cursor.system.h"
#include "tetengo2.gui.drawing.background.h"
#include "tetengo2.gui.drawing.font.h"
#include "tetengo2.gui.drawing.picture.h"
#include "tetengo2.gui.drawing.transparent_background.h"
#include "tetengo2.gui.drawing.widget_canvas.h"
#include "tetengo2.gui.measure.h"
#include "tetengo2.gui.message.focus_observer_set.h"
#include "tetengo2.gui.message.keyboard_observer_set.h"
#include "tetengo2.gui.message.menu_observer_set.h"
#include "tetengo2.gui.message.mouse_observer_set.h"
#include "tetengo2.gui.message.paint_observer_set.h"
#include "tetengo2.gui.message.window_observer_set.h"
#include "tetengo2.gui.menu.menu_bar.h"
#include "tetengo2.gui.menu.menu_base.h"
#include "tetengo2.gui.menu.shortcut_key.h"
#include "tetengo2.gui.menu.shortcut_key_table.h"
#include "tetengo2.gui.menu.traits.h"
#include "tetengo2.gui.unit.em.h"
#include "tetengo2.gui.virtual_key.h"
#include "tetengo2.gui.widget.abstract_window.h"
#include "tetengo2.gui.widget.window.h"
#include "tetengo2.gui.widget.traits.widget_traits.h"
#include "tetengo2.gui.widget.traits.abstract_window_traits.h"
#include "tetengo2.gui.widget.traits.window_traits.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"
#include "tetengo2.unique.h"

#include "tetengo2.gui.common_dialog.file_save.h"


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
        tetengo2::gui::virtual_key<
            tetengo2::detail::stub::virtual_key<std::wstring>
        >
        virtual_key_type;

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
            tetengo2::gui::message::keyboard_observer_set<
                virtual_key_type, wchar_t
            >,
            tetengo2::gui::message::mouse_observer_set
        >
        widget_traits_type;

    typedef
        tetengo2::gui::menu::shortcut_key<virtual_key_type> shortcut_key_type;

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

    typedef
        tetengo2::gui::widget::traits::window_traits<
            abstract_window_traits_type
        >
        window_traits_type;

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
        tetengo2::gui::widget::window<
            window_traits_type,
            widget_details_type,
            message_handler_details_type
        >
        window_type;

    typedef
        tetengo2::gui::common_dialog::file_save<
            abstract_window_type,
            std::wstring,
            boost::filesystem::path,
            ui_encoder_type,
            tetengo2::detail::stub::common_dialog
        >
        file_save_dialog_type;


    // functions

    file_save_dialog_type::file_filters_type make_file_filters()
    {
        file_save_dialog_type::file_filters_type filters;

        filters.push_back(std::make_pair(L"All Files", L"*.*"));

        return filters;
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(common_dialog)
BOOST_AUTO_TEST_SUITE(file_save)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const file_save_dialog_type file_save(
                std::wstring(), boost::none, make_file_filters(), parent
            );
        }
        {
            window_type parent;
            const file_save_dialog_type file_save(
                L"hoge",
                boost::none,
                file_save_dialog_type::file_filters_type(),
                parent
            );
        }
        {
            window_type parent;
            const file_save_dialog_type file_save(
                L"hoge", boost::none, make_file_filters(), parent
            );
        }
    }

    BOOST_AUTO_TEST_CASE(result)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const file_save_dialog_type file_save(
                L"hoge", boost::none, make_file_filters(), parent
            );

            BOOST_CHECK(file_save.result() == boost::filesystem::path());
        }
        {
            window_type parent;
            file_save_dialog_type file_save(
                L"hoge", boost::none, make_file_filters(), parent
            );

            file_save.do_modal();

            BOOST_CHECK(
                file_save.result() == boost::filesystem::path(L"hoge.txt")
            );
        }
        {
            window_type parent;
            const file_save_dialog_type file_save(
                L"hoge",
                boost::make_optional(boost::filesystem::path(L"fuga.jpg")),
                make_file_filters(),
                parent
            );

            BOOST_CHECK(file_save.result() == boost::filesystem::path());
        }
        {
            window_type parent;
            file_save_dialog_type file_save(
                L"hoge",
                boost::make_optional(boost::filesystem::path(L"fuga.jpg")),
                make_file_filters(),
                parent
            );

            file_save.do_modal();

            BOOST_CHECK(
                file_save.result() == boost::filesystem::path(L"hoge.txt")
            );
        }
    }

    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        file_save_dialog_type file_save(
            L"hoge", boost::none, make_file_filters(), parent
        );

        file_save.do_modal();
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const file_save_dialog_type file_save(
                L"hoge", boost::none, make_file_filters(), parent
            );

            file_save.details();
        }
        {
            window_type parent;
            file_save_dialog_type file_save(
                L"hoge", boost::none, make_file_filters(), parent
            );

            file_save.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()