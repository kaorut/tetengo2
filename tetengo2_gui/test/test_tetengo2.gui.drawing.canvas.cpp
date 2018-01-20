/*! \file
    \brief Test of class tetengo2::gui::drawing::canvas.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/dimension.h>
#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/drawing/canvas_traits.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/drawing/picture.h>
#include <tetengo2/gui/drawing/solid_background.h>
#include <tetengo2/gui/drawing/transparent_background.h>
#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/gui/unit/unit.h>
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

    using position_type = common_type_list_type::position_type;

    using position_unit_type = position_type::unit_type;

    using dimension_type = common_type_list_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using color_type = tetengo2::gui::drawing::color;

    using drawing_details_type = detail_type_list_type::drawing_type;

    using background_type = tetengo2::gui::drawing::background<drawing_details_type>;

    using solid_background_type = tetengo2::gui::drawing::solid_background<drawing_details_type>;

    using transparent_background_type = tetengo2::gui::drawing::transparent_background<drawing_details_type>;

    using font_type = tetengo2::gui::drawing::font<string_type, size_type, drawing_details_type>;

    using picture_type = tetengo2::gui::drawing::picture<dimension_type, drawing_details_type>;

    using icon_details_type = detail_type_list_type::icon_type;

    using icon_type = tetengo2::gui::icon<dimension_type, icon_details_type>;

    using canvas_details_type = drawing_details_type::canvas_details_type;

    using canvas_details_ptr_type = drawing_details_type::canvas_details_ptr_type;

    using encoder_type = common_type_list_type::ui_encoder_type;

    using canvas_traits_type =
        tetengo2::gui::drawing::canvas_traits<size_type, string_type, position_type, dimension_type, encoder_type>;

    using canvas_type = tetengo2::gui::drawing::canvas<canvas_traits_type, drawing_details_type, icon_details_type>;

    struct concrete_canvas : public canvas_type
    {
        concrete_canvas()
        :
        canvas_type(tetengo2::stdalt::make_unique<canvas_details_type>())
        {}


    };

    struct concrete_canvas0 : public canvas_type
    {
        concrete_canvas0()
        :
        canvas_type(canvas_details_ptr_type{})
        {}


    };


    // functions

    template <typename Int>
    position_type make_position(const Int x, const Int y)
    {
        return { position_unit_type{ x }, position_unit_type{ y } };
    }

    template <typename Int>
    dimension_type make_dimension(const Int w, const Int h)
    {
        return { dimension_unit_type{ w }, dimension_unit_type{ h } };
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(canvas)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_canvas canvas{};
        }
        {
            BOOST_CHECK_THROW(const concrete_canvas0 canvas, std::invalid_argument);
        }
    }

    BOOST_AUTO_TEST_CASE(begin_transaction)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        canvas.begin_transaction(make_dimension(123U, 456U));
        canvas.end_transaction();
    }

    BOOST_AUTO_TEST_CASE(end_transaction)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        canvas.begin_transaction(make_dimension(123U, 456U));
        canvas.end_transaction();
    }

    BOOST_AUTO_TEST_CASE(get_color)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas{};

        const auto& color = canvas.get_color();

        BOOST_CHECK((color == color_type{ 0, 0, 0, 255 }));
    }

    BOOST_AUTO_TEST_CASE(set_color)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        color_type color{ 12, 34, 56, 78 };
        canvas.set_color(std::move(color));

        BOOST_CHECK(canvas.get_color() == color);
    }

    BOOST_AUTO_TEST_CASE(get_background)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas{};

        const auto& background = canvas.get_background();
        const auto* const p_solid_background = dynamic_cast<const solid_background_type*>(&background);

        BOOST_TEST_REQUIRE(p_solid_background);
        BOOST_CHECK((p_solid_background->get_color() == color_type{ 255, 255, 255, 255 }));
    }

    BOOST_AUTO_TEST_CASE(set_background)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        canvas.set_background(tetengo2::stdalt::make_unique<const transparent_background_type>());

        BOOST_TEST(dynamic_cast<const transparent_background_type*>(&canvas.get_background()));
    }

    BOOST_AUTO_TEST_CASE(line_width)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas{};

        const auto line_width = canvas.line_width();

        BOOST_CHECK(line_width == dimension_unit_type{ 1 });
    }

    BOOST_AUTO_TEST_CASE(set_line_width)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        canvas.set_line_width(dimension_unit_type{ 42 });

        BOOST_CHECK(canvas.line_width() == dimension_unit_type{ 42 });
    }

    BOOST_AUTO_TEST_CASE(line_style)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas{};

        const auto line_style = canvas.line_style();

        BOOST_CHECK(line_style == canvas_type::line_style_type::solid);
    }

    BOOST_AUTO_TEST_CASE(set_line_style)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        canvas.set_line_style(canvas_type::line_style_type::dashed);

        BOOST_CHECK(canvas.line_style() == canvas_type::line_style_type::dashed);
    }

    BOOST_AUTO_TEST_CASE(get_font)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas{};

        const auto& font = canvas.get_font();

        BOOST_CHECK(font == font_type::dialog_font());
    }

    BOOST_AUTO_TEST_CASE(set_font)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        font_type font{ string_type{ TETENGO2_TEXT("AnotherFont") }, 42, true, true, true, true };
        canvas.set_font(std::move(font));

        BOOST_CHECK(
            canvas.get_font() == font_type(string_type{ TETENGO2_TEXT("AnotherFont") }, 42, true, true, true, true)
        );
    }

    BOOST_AUTO_TEST_CASE(draw_line)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        canvas.draw_line(make_position(12, 34), make_position(56, 78));
    }

    BOOST_AUTO_TEST_CASE(draw_focus_indication)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        canvas.draw_focus_indication(make_position(12, 34), make_dimension(56U, 78U));
    }

    BOOST_AUTO_TEST_CASE(draw_rectangle)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        canvas.draw_rectangle(make_position(12, 34), make_dimension(56U, 78U));
    }

    BOOST_AUTO_TEST_CASE(fill_rectangle)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        canvas.fill_rectangle(make_position(12, 34), make_dimension(56U, 78U));
    }

    BOOST_AUTO_TEST_CASE(draw_polygon)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        const std::vector<position_type> positions{
            make_position(12, 34), make_position(56, 78), make_position(90, 12)
        };

        canvas.draw_polygon(positions.begin(), positions.end());
    }

    BOOST_AUTO_TEST_CASE(fill_polygon)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        const std::vector<position_type> positions{
            make_position(12, 34), make_position(56, 78), make_position(90, 12)
        };

        canvas.fill_polygon(positions.begin(), positions.end());
    }

    BOOST_AUTO_TEST_CASE(calc_text_dimension)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_canvas canvas{};

            const auto dimension = canvas.calc_text_dimension(string_type{ TETENGO2_TEXT("hoge") });

            BOOST_CHECK(dimension == make_dimension(123U, 456U));
        }
        {
            const concrete_canvas canvas{};

            const auto dimension =
                canvas.calc_text_dimension(string_type{ TETENGO2_TEXT("hoge") }, dimension_unit_type{ 256 });

            BOOST_CHECK(dimension == make_dimension(123U, 456U));
        }
        {
            const concrete_canvas canvas{};

            const auto dimension =
                canvas.calc_text_dimension(string_type{ TETENGO2_TEXT("hoge") }, dimension_unit_type{ 64 });

            BOOST_CHECK(dimension == make_dimension(46U, 890U));
        }
    }

    BOOST_AUTO_TEST_CASE(calc_vertical_text_dimension)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas{};

        const auto dimension = canvas.calc_vertical_text_dimension(string_type{ TETENGO2_TEXT("hoge") });

        BOOST_CHECK(dimension == make_dimension(456U, 123U));
    }

    BOOST_AUTO_TEST_CASE(draw_text)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_canvas canvas{};

            canvas.draw_text(string_type{ TETENGO2_TEXT("hoge") }, make_position(12, 34), 56.78);
        }
        {
            concrete_canvas canvas{};

            canvas.draw_text(
                string_type{ TETENGO2_TEXT("hoge") }, make_position(12, 34), dimension_unit_type{ 256 }, 56.78
            );
        }
        {
            concrete_canvas canvas{};

            canvas.draw_text(
                string_type{ TETENGO2_TEXT("hoge") }, make_position(12, 34), dimension_unit_type{ 64 }, 56.78
            );
        }
    }

    BOOST_AUTO_TEST_CASE(draw_vertical_text)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        canvas.draw_text(string_type{ TETENGO2_TEXT("hoge") }, make_position(12, 34));
    }

    BOOST_AUTO_TEST_CASE(paint_picture)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_canvas canvas{};

            const picture_type picture{ make_dimension(123U, 456U) };
            canvas.paint_picture(picture, make_position(12, 34), make_dimension(56U, 78U));
        }
        {
            concrete_canvas canvas{};

            const picture_type picture{ make_dimension(123U, 456U) };
            canvas.paint_picture(picture, make_position(12, 34));
        }
    }

    BOOST_AUTO_TEST_CASE(paint_icon)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas{};

        const icon_type icon{ boost::filesystem::path{ TETENGO2_TEXT("hoge.ico") } };
        canvas.paint_icon(icon, make_position(12, 34));
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_canvas canvas{};

            canvas.details();
        }
        {
            concrete_canvas canvas{};

            canvas.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
