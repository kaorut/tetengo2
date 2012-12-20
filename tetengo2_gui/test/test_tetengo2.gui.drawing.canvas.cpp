/*! \file
    \brief Test of class tetengo2::gui::drawing::canvas.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <stdexcept>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.text.h"
#include "tetengo2.unique.h"

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::size>::type size_type;

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::dimension>::type dimension_type;

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

        const color_type& color = canvas.color();

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

        const background_type& background = canvas.background();
        const solid_background_type* const p_solid_background =
            dynamic_cast<const solid_background_type*>(&background);

        BOOST_CHECK(p_solid_background);
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

        const size_type line_width = canvas.line_width();

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

        const canvas_type::line_style_type::enum_t line_style = canvas.line_style();

        BOOST_CHECK_EQUAL(line_style, canvas_type::line_style_type::solid);
    }

    BOOST_AUTO_TEST_CASE(set_line_style)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        canvas.set_line_style(canvas_type::line_style_type::dashed);

        BOOST_CHECK_EQUAL(canvas.line_style(), canvas_type::line_style_type::dashed);
    }

    BOOST_AUTO_TEST_CASE(font)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas;

        const font_type& font = canvas.font();

        BOOST_CHECK(font == font_type::dialog_font());
    }

    BOOST_AUTO_TEST_CASE(set_font)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        font_type font(string_type(TETENGO2_TEXT("AnotherFont")), 42, true, true, true, true);
        canvas.set_font(std::move(font));

        BOOST_CHECK(canvas.font() == font);
    }

    BOOST_AUTO_TEST_CASE(draw_line)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        canvas.draw_line(std::make_pair(12, 34), std::make_pair(56, 78));
    }

    BOOST_AUTO_TEST_CASE(draw_focus_indication)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        canvas.draw_focus_indication(std::make_pair(12, 34), std::make_pair(56, 78));
    }

    BOOST_AUTO_TEST_CASE(fill_rectangle)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        canvas.fill_rectangle(std::make_pair(12, 34), std::make_pair(56, 78));
    }

    BOOST_AUTO_TEST_CASE(calc_text_dimension)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas;

        const dimension_type dimension = canvas.calc_text_dimension(string_type(TETENGO2_TEXT("hoge")));

        BOOST_CHECK(dimension == dimension_type(123, 456));
    }

    BOOST_AUTO_TEST_CASE(draw_text)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        canvas.draw_text(string_type(TETENGO2_TEXT("hoge")), std::make_pair(12, 34), 56.78);
    }

    BOOST_AUTO_TEST_CASE(paint_picture)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        const picture_type picture(std::make_pair(123, 456));
        canvas.paint_picture(picture, std::make_pair(12, 34), std::make_pair(56, 78));
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
