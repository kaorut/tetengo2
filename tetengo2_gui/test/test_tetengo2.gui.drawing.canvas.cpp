/*! \file
    \brief Test of class tetengo2::gui::drawing::canvas.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <stdexcept>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.measure.h"
#include "tetengo2.text.h"
#include "tetengo2.unique.h"

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::size>::type size_type;

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::position>::type position_type;

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::dimension>::type dimension_type;

    typedef tetengo2::gui::dimension<dimension_type>::width_type width_type;

    typedef tetengo2::gui::dimension<dimension_type>::height_type height_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::color>::type
        color_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::background
        >::type
        background_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::solid_background
        >::type
        solid_background_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::transparent_background
        >::type
        transparent_background_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::font>::type font_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::picture>::type
        picture_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::canvas_details>::type
        canvas_details_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::canvas_details_ptr
        >::type
        canvas_details_ptr_type;

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type string_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::canvas>::type
        canvas_type;

    struct concrete_canvas : public canvas_type
    {
        concrete_canvas()
        :
        canvas_type(tetengo2::make_unique<canvas_details_type>())
        {}


    };

    struct concrete_canvas0 : public canvas_type
    {
        concrete_canvas0()
        :
        canvas_type(canvas_details_ptr_type())
        {}


    };


    // functions

    template <typename Int>
    position_type make_position(const Int x, const Int y)
    {
        return
            position_type(
                tetengo2::gui::position<position_type>::left_type(x),
                tetengo2::gui::position<position_type>::top_type(y)
            );
    }

    template <typename Int>
    dimension_type make_dimension(const Int w, const Int h)
    {
        return
            dimension_type(
                tetengo2::gui::dimension<dimension_type>::width_type(w),
                tetengo2::gui::dimension<dimension_type>::height_type(h)
            );
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
            const concrete_canvas canvas;
        }
        {
            BOOST_CHECK_THROW(const concrete_canvas0 canvas, std::invalid_argument);
        }
    }

    BOOST_AUTO_TEST_CASE(color)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas;

        const auto& color = canvas.color();

        BOOST_CHECK(color == color_type(0, 0, 0, 255));
    }

    BOOST_AUTO_TEST_CASE(set_color)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        color_type color(12, 34, 56, 78);
        canvas.set_color(std::move(color));

        BOOST_CHECK(canvas.color() == color);
    }

    BOOST_AUTO_TEST_CASE(background)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas;

        const auto& background = canvas.background();
        const auto* const p_solid_background = dynamic_cast<const solid_background_type*>(&background);

        BOOST_REQUIRE(p_solid_background);
        BOOST_CHECK(p_solid_background->color() == color_type(255, 255, 255, 255));
    }

    BOOST_AUTO_TEST_CASE(set_background)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        canvas.set_background(tetengo2::make_unique<const transparent_background_type>());

        BOOST_CHECK(dynamic_cast<const transparent_background_type*>(&canvas.background()));
    }

    BOOST_AUTO_TEST_CASE(line_width)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas;

        const auto line_width = canvas.line_width();

        BOOST_CHECK_EQUAL(line_width, 1U);
    }

    BOOST_AUTO_TEST_CASE(set_line_width)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        canvas.set_line_width(42);

        BOOST_CHECK_EQUAL(canvas.line_width(), 42U);
    }

    BOOST_AUTO_TEST_CASE(line_style)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas;

        const auto line_style = canvas.line_style();

        BOOST_CHECK(line_style == canvas_type::line_style_type::solid);
    }

    BOOST_AUTO_TEST_CASE(set_line_style)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        canvas.set_line_style(canvas_type::line_style_type::dashed);

        BOOST_CHECK(canvas.line_style() == canvas_type::line_style_type::dashed);
    }

    BOOST_AUTO_TEST_CASE(font)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas;

        const auto& font = canvas.font();

        BOOST_CHECK(font == font_type::dialog_font());
    }

    BOOST_AUTO_TEST_CASE(set_font)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        font_type font(string_type(TETENGO2_TEXT("AnotherFont")), 42, true, true, true, true);
        canvas.set_font(std::move(font));

        BOOST_CHECK(
            canvas.font() == font_type(string_type(TETENGO2_TEXT("AnotherFont")), 42, true, true, true, true)
        );
    }

    BOOST_AUTO_TEST_CASE(draw_line)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        canvas.draw_line(make_position(12, 34), make_position(56, 78));
    }

    BOOST_AUTO_TEST_CASE(draw_focus_indication)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        canvas.draw_focus_indication(make_position(12, 34), make_dimension(56, 78));
    }

    BOOST_AUTO_TEST_CASE(fill_rectangle)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        canvas.fill_rectangle(make_position(12, 34), make_dimension(56, 78));
    }

    BOOST_AUTO_TEST_CASE(draw_polygon)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        std::vector<position_type> positions;
        positions.push_back(make_position(12, 34));
        positions.push_back(make_position(56, 78));
        positions.push_back(make_position(90, 12));

        canvas.draw_polygon(positions.begin(), positions.end());
    }

    BOOST_AUTO_TEST_CASE(fill_polygon)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        std::vector<position_type> positions;
        positions.push_back(make_position(12, 34));
        positions.push_back(make_position(56, 78));
        positions.push_back(make_position(90, 12));

        canvas.fill_polygon(positions.begin(), positions.end());
    }

    BOOST_AUTO_TEST_CASE(calc_text_dimension)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas;

        const auto dimension = canvas.calc_text_dimension(string_type(TETENGO2_TEXT("hoge")));

        BOOST_CHECK(dimension == make_dimension(width_type(123), height_type(456)));
    }

    BOOST_AUTO_TEST_CASE(draw_text)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        canvas.draw_text(string_type(TETENGO2_TEXT("hoge")), make_position(12, 34), 56.78);
    }

    BOOST_AUTO_TEST_CASE(paint_picture)
    {
        BOOST_TEST_PASSPOINT();

        {
            concrete_canvas canvas;

            const picture_type picture(make_dimension(123, 456));
            canvas.paint_picture(picture, make_position(12, 34), make_dimension(56, 78));
        }
        {
            concrete_canvas canvas;

            const picture_type picture(make_dimension(123, 456));
            canvas.paint_picture(picture, make_position(12, 34));
        }
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_canvas canvas;

            canvas.details();
        }
        {
            concrete_canvas canvas;

            canvas.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
