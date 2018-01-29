/*! \file
    \brief Test of class tetengo2::gui::widget::widget.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/none.hpp>
#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/stub/cursor.h>
#include <tetengo2/detail/stub/widget.h>
#include <tetengo2/gui/cursor/cursor_base.h>
#include <tetengo2/gui/cursor/system.h>
#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/transparent_background.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/message/focus_observer_set.h>
#include <tetengo2/gui/position.h>
#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/gui/unit/unit.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using string_type = common_type_list_type::string_type;

    using details_font_type = detail_type_list_type::widget_type::details_font_type;

    using position_type = common_type_list_type::position_type;

    using position_unit_type = position_type::unit_type;

    using dimension_type = common_type_list_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using drawing_details_type = detail_type_list_type::drawing_type;

    using background_type = tetengo2::gui::drawing::background<drawing_details_type>;

    using transparent_background_type = tetengo2::gui::drawing::transparent_background<drawing_details_type>;

    using font_type = tetengo2::gui::drawing::font<string_type, size_type, drawing_details_type>;

    using system_cursor_type = tetengo2::gui::cursor::system;

    using cursor_details_type = tetengo2::detail::stub::cursor;

    using widget_type =
        tetengo2::gui::widget::widget<
            common_type_list_type::widget_traits_type, common_type_list_type::widget_details_traits_type
        >;

    class concrete_widget : public widget_type
    {
    public:
        static const encoder_type& test_encoder()
        {
            return encoder();
        }

        explicit concrete_widget(
            widget_type* const                       p_parent = nullptr,
            const widget_type::scroll_bar_style_type scroll_bar_style = widget_type::scroll_bar_style_type::none
        )
        :
        widget_type(scroll_bar_style, message_handler_map_type{}),
        m_p_details(
            tetengo2::stdalt::make_unique<widget_details_type::widget_details_type>(
                p_parent,
                true,
                true,
                0,
                std::make_pair(0, 0),
                std::make_pair(1, 1),
                string_type{},
                details_font_type{ string_type{}, 12, false, false, false, false },
                std::vector<void*>{},
                false,
                false,
                std::vector<string_type>{},
                boost::none,
                100,
                0,
                0
            )
        )
        {
            widget_type::initialize(this);
        }

        virtual ~concrete_widget()
        = default;


    private:
        std::unique_ptr<details_type> m_p_details;

        virtual const details_type& details_impl()
        const override
        {
            return *m_p_details;
        }

        virtual details_type& details_impl()
        override
        {
            return *m_p_details;
        }


    };

    position_type make_position(const std::ptrdiff_t left, const std::ptrdiff_t top)
    {
        return { position_unit_type{ left }, position_unit_type{ top } };
    }

    dimension_type make_dimension(const std::size_t width, const std::size_t height)
    {
        return { dimension_unit_type{ width }, dimension_unit_type{ height } };
    }

}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(widget)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_widget widget{};
    }

    BOOST_AUTO_TEST_CASE(has_parent)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{};

            BOOST_TEST(!widget.has_parent());
        }
        {
            concrete_widget parent;
            const concrete_widget widget{ &parent };

            BOOST_TEST(widget.has_parent());
        }
    }

    BOOST_AUTO_TEST_CASE(parent)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{};

            BOOST_CHECK_THROW(widget.parent(), std::logic_error);
        }
        {
            concrete_widget parent;
            const concrete_widget widget{ &parent };

            BOOST_TEST(&widget.parent() == &parent);
        }
        {
            concrete_widget parent;
            concrete_widget widget{ &parent };

            BOOST_TEST(&widget.parent() == &parent);
        }
    }

    BOOST_AUTO_TEST_CASE(root_ancestor)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{};

            BOOST_CHECK_THROW(widget.root_ancestor(), std::logic_error);
        }
        {
            concrete_widget parent;
            const concrete_widget widget{ &parent };

            widget.root_ancestor();
        }
        {
            concrete_widget parent;
            concrete_widget widget{ &parent };

            widget.root_ancestor();
        }
    }

    BOOST_AUTO_TEST_CASE(enabled)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget{};

            widget.set_enabled(true);

            BOOST_TEST(widget.enabled());
        }
        {
            concrete_widget widget{};

            widget.set_enabled(false);

            BOOST_TEST(!widget.enabled());
        }
    }

    BOOST_AUTO_TEST_CASE(set_enabled)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget{};

            widget.set_enabled(true);

            BOOST_TEST(widget.enabled());
        }
        {
            concrete_widget widget{};

            widget.set_enabled(false);

            BOOST_TEST(!widget.enabled());
        }
    }

    BOOST_AUTO_TEST_CASE(visible)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget{};

            widget.set_visible(true);

            BOOST_TEST(widget.visible());
        }
        {
            concrete_widget widget{};

            widget.set_visible(false);

            BOOST_TEST(!widget.visible());
        }
    }

    BOOST_AUTO_TEST_CASE(set_visible)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget{};

            widget.set_visible(true);

            BOOST_TEST(widget.visible());
        }
        {
            concrete_widget widget{};

            widget.set_visible(false);

            BOOST_TEST(!widget.visible());
        }
    }

    BOOST_AUTO_TEST_CASE(focused)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget{};

            widget.focus_observer_set().got_focus()();

            BOOST_TEST(widget.focused());
        }
        {
            concrete_widget widget{};

            widget.focus_observer_set().lost_focus()();

            BOOST_TEST(!widget.focused());
        }
    }

    BOOST_AUTO_TEST_CASE(set_focus)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget{};

        widget.set_focus();
    }

    BOOST_AUTO_TEST_CASE(position)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget{};

        widget.set_position(make_position(123, 456));

        const auto position = widget.position();
        BOOST_CHECK(position == make_position(123, 456));
    }

    BOOST_AUTO_TEST_CASE(set_position)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget{};

        widget.set_position(make_position(123, 456));

        const auto position = widget.position();
        BOOST_CHECK(position == make_position(123, 456));
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget{};

        widget.set_dimension(make_dimension(123, 456));

        const auto dimension = widget.dimension();
        BOOST_CHECK(dimension == make_dimension(123, 456));
    }

    BOOST_AUTO_TEST_CASE(set_dimension)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget{};

        widget.set_dimension(make_dimension(123, 456));

        const auto dimension = widget.dimension();
        BOOST_CHECK(dimension == make_dimension(123, 456));
    }

    BOOST_AUTO_TEST_CASE(client_dimension)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget{};

        widget.set_client_dimension(make_dimension(123, 456));

        const auto client_dimension = widget.client_dimension();
        BOOST_CHECK(client_dimension == make_dimension(123, 456));
    }

    BOOST_AUTO_TEST_CASE(set_client_dimension)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget{};

            widget.set_client_dimension(make_dimension(123, 456));

            const auto client_dimension = widget.client_dimension();
            BOOST_CHECK(client_dimension == make_dimension(123, 456));
        }
        {
            concrete_widget widget{};

            BOOST_CHECK_THROW(widget.set_client_dimension(make_dimension(0, 456)), std::invalid_argument);
        }
        {
            concrete_widget widget{};

            BOOST_CHECK_THROW(widget.set_client_dimension(make_dimension(123, 0)), std::invalid_argument);
        }
    }

    BOOST_AUTO_TEST_CASE(set_position_and_dimension)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget{};

        widget.set_position_and_dimension(make_position(123, 456), make_dimension(789, 012));

        const auto position = widget.position();
        const auto dimension = widget.dimension();
        BOOST_CHECK(position == make_position(123, 456));
        BOOST_CHECK(dimension == make_dimension(789, 012));
    }

    BOOST_AUTO_TEST_CASE(text)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget{};

        widget.set_text(string_type{ TETENGO2_TEXT("Tetengo") });

        BOOST_CHECK(widget.text() == string_type{ TETENGO2_TEXT("Tetengo") });
    }

    BOOST_AUTO_TEST_CASE(set_text)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget{};

        widget.set_text(string_type{ TETENGO2_TEXT("Tetengo") });

        BOOST_CHECK(widget.text() == string_type{ TETENGO2_TEXT("Tetengo") });
    }

    BOOST_AUTO_TEST_CASE(p_background)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget{};

            std::unique_ptr<background_type> p_background{};
            widget.set_background(std::move(p_background));

            BOOST_TEST(!widget.p_background());
        }
        {
            concrete_widget widget{};

            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            widget.set_background(std::move(p_background));

            BOOST_TEST(widget.p_background());
        }
    }

    BOOST_AUTO_TEST_CASE(set_background)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_widget widget{};

            std::unique_ptr<background_type> p_background{};
            widget.set_background(std::move(p_background));
        }
        {
            concrete_widget widget{};

            auto p_background = tetengo2::stdalt::make_unique<transparent_background_type>();
            widget.set_background(std::move(p_background));
        }
    }

    BOOST_AUTO_TEST_CASE(font)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget{};

        const font_type font{ font_type::dialog_font().family(), 42, false, true, false, true };
        widget.set_font(font);

        BOOST_CHECK(widget.font() == font);
    }

    BOOST_AUTO_TEST_CASE(set_font)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget{};

        const font_type font{ font_type::dialog_font().family(), 42, false, true, false, true };
        widget.set_font(font);

        BOOST_CHECK(widget.font() == font);
    }

    BOOST_AUTO_TEST_CASE(p_cursor)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_widget widget{};

        BOOST_TEST(!widget.p_cursor());
    }

    BOOST_AUTO_TEST_CASE(set_cursor)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget{};

        auto p_cursor =
            tetengo2::stdalt::make_unique<system_cursor_type>(
                system_cursor_type::style_type::hand, cursor_details_type::instance()
            );
        widget.set_cursor(std::move(p_cursor));

        const auto p_cursor_regot = widget.p_cursor();
        BOOST_TEST_REQUIRE(p_cursor_regot);
        BOOST_CHECK(
            dynamic_cast<const system_cursor_type&>(*p_cursor_regot).style() == system_cursor_type::style_type::hand
        );
    }

    BOOST_AUTO_TEST_CASE(has_vertical_scroll_bar)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::none };

            BOOST_TEST(!widget.has_vertical_scroll_bar());
        }
        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::vertical };

            BOOST_TEST(widget.has_vertical_scroll_bar());
        }
        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::horizontal };

            BOOST_TEST(!widget.has_vertical_scroll_bar());
        }
        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::both };

            BOOST_TEST(widget.has_vertical_scroll_bar());
        }
    }

    BOOST_AUTO_TEST_CASE(vertical_scroll_bar)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::none };

            BOOST_CHECK_THROW(widget.vertical_scroll_bar(), std::logic_error);
        }
        {
            concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::none };

            BOOST_CHECK_THROW(widget.vertical_scroll_bar(), std::logic_error);
        }
        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::vertical };

            widget.vertical_scroll_bar();
        }
        {
            concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::vertical };

            widget.vertical_scroll_bar();
        }
        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::horizontal };

            BOOST_CHECK_THROW(widget.vertical_scroll_bar(), std::logic_error);
        }
        {
            concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::horizontal };

            BOOST_CHECK_THROW(widget.vertical_scroll_bar(), std::logic_error);
        }
        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::both };

            widget.vertical_scroll_bar();
        }
        {
            concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::both };

            widget.vertical_scroll_bar();
        }
    }

    BOOST_AUTO_TEST_CASE(has_horizontal_scroll_bar)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::none };

            BOOST_TEST(!widget.has_horizontal_scroll_bar());
        }
        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::vertical };

            BOOST_TEST(!widget.has_horizontal_scroll_bar());
        }
        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::horizontal };

            BOOST_TEST(widget.has_horizontal_scroll_bar());
        }
        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::both };

            BOOST_TEST(widget.has_horizontal_scroll_bar());
        }
    }

    BOOST_AUTO_TEST_CASE(horizontal_scroll_bar)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::none };

            BOOST_CHECK_THROW(widget.horizontal_scroll_bar(), std::logic_error);
        }
        {
            concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::none };

            BOOST_CHECK_THROW(widget.horizontal_scroll_bar(), std::logic_error);
        }
        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::vertical };

            BOOST_CHECK_THROW(widget.horizontal_scroll_bar(), std::logic_error);
        }
        {
            concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::vertical };

            BOOST_CHECK_THROW(widget.horizontal_scroll_bar(), std::logic_error);
        }
        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::horizontal };

            widget.horizontal_scroll_bar();
        }
        {
            concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::horizontal };

            widget.horizontal_scroll_bar();
        }
        {
            const concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::both };

            widget.horizontal_scroll_bar();
        }
        {
            concrete_widget widget{ nullptr, widget_type::scroll_bar_style_type::both };

            widget.horizontal_scroll_bar();
        }
    }

    BOOST_AUTO_TEST_CASE(children)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{};

            BOOST_TEST(widget.children().empty());
        }
        {
            concrete_widget widget{};
            concrete_widget child1{ &widget };
            child1.set_text(string_type{ TETENGO2_TEXT("hoge") });
            concrete_widget child2{ &widget };
            child2.set_text(string_type{ TETENGO2_TEXT("fuga") });

            BOOST_TEST_REQUIRE(widget.children().size() == 2U);
            BOOST_CHECK(
                widget.children()[0].get().text() == string_type{ TETENGO2_TEXT("hoge") } ||
                widget.children()[1].get().text() == string_type{ TETENGO2_TEXT("hoge") }
            );
            BOOST_CHECK(
                widget.children()[0].get().text() == string_type{ TETENGO2_TEXT("fuga") } ||
                widget.children()[1].get().text() == string_type{ TETENGO2_TEXT("fuga") }
            );
        }
    }

    BOOST_AUTO_TEST_CASE(repaint)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{};

            widget.repaint(true);
        }
        {
            const concrete_widget widget{};

            widget.repaint(false);
        }
    }

    BOOST_AUTO_TEST_CASE(repaint_partially)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_widget widget{};

        widget.repaint_partially(make_position(12, 34), make_dimension(56, 78));
    }

    BOOST_AUTO_TEST_CASE(create_canvas)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_widget widget{};

        widget.create_canvas();
    }

    BOOST_AUTO_TEST_CASE(click)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{};

            widget.click();
        }
        {
            concrete_widget widget{};

            widget.click();
        }
    }

    BOOST_AUTO_TEST_CASE(child_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{};

            widget.child_observer_set();
        }
        {
            concrete_widget widget{};

            widget.child_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(size_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{};

            widget.size_observer_set();
        }
        {
            concrete_widget widget{};

            widget.size_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(focus_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{};

            widget.focus_observer_set();
        }
        {
            concrete_widget widget{};

            widget.focus_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(paint_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{};

            widget.paint_observer_set();
        }
        {
            concrete_widget widget{};

            widget.paint_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(keyboard_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{};

            widget.keyboard_observer_set();
        }
        {
            concrete_widget widget{};

            widget.keyboard_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(mouse_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{};

            widget.mouse_observer_set();
        }
        {
            concrete_widget widget{};

            widget.mouse_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(destroyed)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{};

            BOOST_TEST(!widget.destroyed());
        }
        {
            concrete_widget widget{};
            widget.set_destroyed();

            BOOST_TEST(widget.destroyed());
        }
    }

    BOOST_AUTO_TEST_CASE(set_destroyed)
    {
        BOOST_TEST_PASSPOINT();

        concrete_widget widget{};

        widget.set_destroyed();
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_widget widget{};

            widget.details();
        }
        {
            concrete_widget widget{};

            widget.details();
        }
    }

    BOOST_AUTO_TEST_CASE(message_handler_map)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_widget widget{};

        widget.message_handler_map();
    }

    BOOST_AUTO_TEST_CASE(encoder)
    {
        BOOST_TEST_PASSPOINT();

        // encoder() is called in test_encoder().
        concrete_widget::test_encoder();
    }

    BOOST_AUTO_TEST_CASE(initialize)
    {
        BOOST_TEST_PASSPOINT();

        // initialize() is called in the constructor of concrete_widget.
        const concrete_widget widget{};
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
