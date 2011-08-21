/*! \file
    \brief Test of class tetengo2::gui::abstract_window.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <cstddef>
//#include <stdexcept>
//#include <string>
//#include <utility>

//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.detail.stub.alert.h"
#include "tetengo2.detail.stub.cursor.h"
#include "tetengo2.detail.stub.drawing.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.menu.h"
#include "tetengo2.detail.stub.message_handler.h"
#include "tetengo2.detail.stub.unit.h"
#include "tetengo2.detail.stub.widget.h"
#include "tetengo2.encoder.h"
#include "tetengo2.encoding.locale.h"
#include "tetengo2.gui.alert.h"
#include "tetengo2.gui.drawing.background.h"
#include "tetengo2.gui.drawing.font.h"
#include "tetengo2.gui.drawing.picture.h"
#include "tetengo2.gui.drawing.widget_canvas.h"
#include "tetengo2.gui.main_menu.h"
#include "tetengo2.gui.menu.h"
#include "tetengo2.gui.menu_observer_set.h"
#include "tetengo2.gui.mouse_observer_set.h"
#include "tetengo2.gui.paint_observer_set.h"
#include "tetengo2.gui.system_cursor.h"
#include "tetengo2.gui.traits.abstract_window_traits.h"
#include "tetengo2.gui.traits.menu_traits.h"
#include "tetengo2.gui.traits.widget_traits.h"
#include "tetengo2.gui.unit.em.h"
#include "tetengo2.gui.window_observer_set.h"

#include "tetengo2.gui.abstract_window.h"


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
        tetengo2::gui::system_cursor<tetengo2::detail::stub::cursor>
        system_cursor_type;

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
            system_cursor_type,
            tetengo2::gui::paint_observer_set<canvas_type>,
            tetengo2::gui::mouse_observer_set
        >
        widget_traits_type;

    typedef
        tetengo2::gui::traits::menu_traits<
            std::wstring,
            ui_encoder_type,
            tetengo2::gui::menu_observer_set
        >
        menu_traits_type;

    typedef tetengo2::detail::stub::menu menu_details_type;

    typedef
        tetengo2::gui::menu<menu_traits_type, menu_details_type> menu_type;

    typedef
        tetengo2::gui::main_menu<menu_traits_type, menu_details_type>
        main_menu_type;

    typedef
        tetengo2::gui::traits::abstract_window_traits<
            widget_traits_type,
            main_menu_type,
            tetengo2::gui::window_observer_set
        >
        abstract_window_traits_type;

    typedef tetengo2::detail::stub::widget widget_details_type;

    typedef
        tetengo2::detail::stub::message_handler<widget_details_type>
        message_handler_details_type;

    typedef
        tetengo2::gui::abstract_window<
            abstract_window_traits_type,
            widget_details_type,
            message_handler_details_type
        >
        abstract_window_type;

    class concrete_window : public abstract_window_type
    {
    public:
        concrete_window()
        :
        abstract_window_type(message_handler_map_type()),
        m_p_details(new details_type())
        {
            initialize(this);
        }

        virtual ~concrete_window()
        TETENGO2_CPP0X_NOEXCEPT
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
BOOST_AUTO_TEST_SUITE(abstract_window)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_window window;
    }

    BOOST_AUTO_TEST_CASE(activate)
    {
        BOOST_TEST_PASSPOINT();

        concrete_window window;

        window.activate();
    }

    BOOST_AUTO_TEST_CASE(has_main_menu)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_window window;

            BOOST_CHECK(!window.has_main_menu());
        }
        {
            concrete_window window;

            tetengo2::cpp0x::unique_ptr<main_menu_type>::type p_main_menu(
                new main_menu_type()
            );
            window.set_main_menu(std::move(p_main_menu));

            BOOST_CHECK(window.has_main_menu());
       }
    }

    BOOST_AUTO_TEST_CASE(main_menu)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_window window;

            BOOST_CHECK_THROW(window.main_menu(), std::logic_error);
        }
        {
            concrete_window window;

            BOOST_CHECK_THROW(window.main_menu(), std::logic_error);
        }
        {
            concrete_window window;

            tetengo2::cpp0x::unique_ptr<main_menu_type>::type p_main_menu(
                new main_menu_type()
            );
            window.set_main_menu(std::move(p_main_menu));

            window.main_menu();

            const abstract_window_type& const_window = window;
            const_window.main_menu();
        }
    }

    BOOST_AUTO_TEST_CASE(set_main_menu)
    {
        BOOST_TEST_PASSPOINT();

        concrete_window window;

        tetengo2::cpp0x::unique_ptr<main_menu_type>::type p_main_menu(
            new main_menu_type()
        );
        window.set_main_menu(std::move(p_main_menu));

        tetengo2::cpp0x::unique_ptr<main_menu_type>::type p_main_menu2(
            new main_menu_type()
        );
        window.set_main_menu(std::move(p_main_menu2));
    }

    BOOST_AUTO_TEST_CASE(window_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_window window;

            window.window_observer_set();
        }
        {
            concrete_window window;

            window.window_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(close)
    {
        BOOST_TEST_PASSPOINT();

        concrete_window window;

        window.close();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
