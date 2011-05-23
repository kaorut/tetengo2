/*! \file
    \brief Test of class tetengo2::gui::widget.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <cstddef>
//#include <stdexcept>
//#include <string>
//#include <tuple>
//#include <utility>
//#include <vector>

//#include <boost/optional.hpp>
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
#include "tetengo2.gui.drawing.transparent_background.h"
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

    typedef
        tetengo2::gui::drawing::transparent_background<drawing_details_type>
        transparent_background_type;

    typedef
        std::tuple<std::wstring, std::size_t, bool, bool, bool, bool>
        details_font_type;

    class concrete_widget : public widget_type
    {
    public:
        explicit concrete_widget(widget_type* const p_parent = NULL)
        :
        widget_type(message_handler_map_type()),
        m_p_details(
            new widget_details_type::widget_details_type(
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
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            BOOST_CHECK(!widget.has_parent());
        }
        {
            concrete_widget parent;
            const concrete_widget widget(&parent);

            BOOST_CHECK(widget.has_parent());
        }
    }

    BOOST_AUTO_TEST_CASE(parent)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            BOOST_CHECK_THROW(widget.parent(), std::logic_error);
        }
        {
            concrete_widget parent;
            const concrete_widget widget(&parent);

            BOOST_CHECK_EQUAL(&widget.parent(), &parent);
        }
        {
            concrete_widget parent;
            concrete_widget widget(&parent);

            BOOST_CHECK_EQUAL(&widget.parent(), &parent);
        }
    }

    BOOST_AUTO_TEST_CASE(root_ancestor)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            BOOST_CHECK_THROW(widget.root_ancestor(), std::logic_error);
        }
        {
            concrete_widget parent;
            const concrete_widget widget(&parent);

            widget.root_ancestor();
        }
        {
            concrete_widget parent;
            concrete_widget widget(&parent);

            widget.root_ancestor();
        }
    }

    BOOST_AUTO_TEST_CASE(set_enabled)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget;

            widget.set_enabled(true);

            BOOST_CHECK(widget.enabled());
        }
        {
            concrete_widget widget;

            widget.set_enabled(false);

            BOOST_CHECK(!widget.enabled());
        }
    }

    BOOST_AUTO_TEST_CASE(enabled)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget;

            widget.set_enabled(true);

            BOOST_CHECK(widget.enabled());
        }
        {
            concrete_widget widget;

            widget.set_enabled(false);

            BOOST_CHECK(!widget.enabled());
        }
    }

    BOOST_AUTO_TEST_CASE(set_visible)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget;

            widget.set_visible(true);

            BOOST_CHECK(widget.visible());
        }
        {
            concrete_widget widget;

            widget.set_visible(false);

            BOOST_CHECK(!widget.visible());
        }
    }

    BOOST_AUTO_TEST_CASE(visible)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget;

            widget.set_visible(true);

            BOOST_CHECK(widget.visible());
        }
        {
            concrete_widget widget;

            widget.set_visible(false);

            BOOST_CHECK(!widget.visible());
        }
    }

    BOOST_AUTO_TEST_CASE(create_canvas)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_widget widget;

        widget.create_canvas();
    }

    BOOST_AUTO_TEST_CASE(set_position)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_position(position_type(123, 456));

        const position_type position = widget.position();
        BOOST_CHECK(position == position_type(123, 456));
    }

    BOOST_AUTO_TEST_CASE(position)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_position(position_type(123, 456));

        const position_type position = widget.position();
        BOOST_CHECK(position == position_type(123, 456));
    }

    BOOST_AUTO_TEST_CASE(set_dimension)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_dimension(dimension_type(123, 456));

        const dimension_type dimension = widget.dimension();
        BOOST_CHECK(dimension == dimension_type(123, 456));
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_dimension(dimension_type(123, 456));

        const dimension_type dimension = widget.dimension();
        BOOST_CHECK(dimension == dimension_type(123, 456));
    }

    BOOST_AUTO_TEST_CASE(set_client_dimension)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_client_dimension(dimension_type(123, 456));

        const dimension_type client_dimension = widget.client_dimension();
        BOOST_CHECK(client_dimension == dimension_type(123, 456));
    }

    BOOST_AUTO_TEST_CASE(client_dimension)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_client_dimension(dimension_type(123, 456));

        const dimension_type client_dimension = widget.client_dimension();
        BOOST_CHECK(client_dimension == dimension_type(123, 456));
    }

    BOOST_AUTO_TEST_CASE(set_text)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_text(L"Tetengo");

        BOOST_CHECK(widget.text() == L"Tetengo");
    }

    BOOST_AUTO_TEST_CASE(text)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        widget.set_text(L"Tetengo");

        BOOST_CHECK(widget.text() == L"Tetengo");
    }

    BOOST_AUTO_TEST_CASE(set_background)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget;

            tetengo2::cpp0x::unique_ptr<background_type>::type p_background;
            widget.set_background(std::move(p_background));
        }
        {
            concrete_widget widget;

            tetengo2::cpp0x::unique_ptr<background_type>::type p_background(
                new transparent_background_type()
            );
            widget.set_background(std::move(p_background));
        }
    }

    BOOST_AUTO_TEST_CASE(background)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget;

            tetengo2::cpp0x::unique_ptr<background_type>::type p_background;
            widget.set_background(std::move(p_background));

            BOOST_CHECK(!widget.background());
        }
        {
            concrete_widget widget;

            tetengo2::cpp0x::unique_ptr<background_type>::type p_background(
                new transparent_background_type()
            );
            widget.set_background(std::move(p_background));

            BOOST_CHECK(widget.background());
        }
    }

    BOOST_AUTO_TEST_CASE(set_font)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        const font_type font(
            font_type::dialog_font().family(), 42, false, true, false, true
        );
        widget.set_font(font);

        BOOST_CHECK(widget.font() == font);
    }

    BOOST_AUTO_TEST_CASE(font)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget;

        const font_type font(
            font_type::dialog_font().family(), 42, false, true, false, true
        );
        widget.set_font(font);

        BOOST_CHECK(widget.font() == font);
    }

    BOOST_AUTO_TEST_CASE(children)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            BOOST_CHECK(widget.children().empty());
        }
        {
            concrete_widget widget;
            concrete_widget child1(&widget);
            child1.set_text(L"hoge");
            concrete_widget child2(&widget);
            child2.set_text(L"fuga");

            BOOST_CHECK_EQUAL(widget.children().size(), 2U);
            BOOST_CHECK(
                widget.children()[0].get().text() == L"hoge" ||
                widget.children()[1].get().text() == L"hoge"
            );
            BOOST_CHECK(
                widget.children()[0].get().text() == L"fuga" ||
                widget.children()[1].get().text() == L"fuga"
            );
        }
    }

    BOOST_AUTO_TEST_CASE(click)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget;

            widget.click();
        }
        {
            concrete_widget widget;

            widget.click();
        }
    }

    BOOST_AUTO_TEST_CASE(erase_background)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_widget widget;

        const tetengo2::cpp0x::unique_ptr<canvas_type>::type p_canvas(
            widget.create_canvas()
        );
        widget.erase_background(*p_canvas);
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

    BOOST_AUTO_TEST_CASE(set_destroyed)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(message_handler_map)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(encoder)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(initialize)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
