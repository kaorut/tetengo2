/*! \file
    \brief Test of class tetengo2::gui::drawing::canvas.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <cstddef>
//#include <stdexcept>
//#include <string>
//#include <utility>
//#include <vector>

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.drawing.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.gui.drawing.font.h"
#include "tetengo2.gui.drawing.picture.h"
#include "tetengo2.gui.drawing.transparent_background.h"
#include "tetengo2.text.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"
#include "tetengo2.unique.h"

#include "tetengo2.gui.drawing.canvas.h"


namespace
{
    // types

    typedef std::pair<std::size_t, std::size_t> dimension_type;

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::encoding::locale<std::wstring, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::encoding::locale<std::wstring, encoding_details_type>
        ui_encoding_type;

    typedef
        tetengo2::text::encoder<internal_encoding_type, ui_encoding_type>
        ui_encoder_type;

    typedef tetengo2::detail::stub::drawing drawing_details_type;

    typedef
        tetengo2::gui::drawing::transparent_background<drawing_details_type>
        transparent_background_type;

    typedef
        tetengo2::gui::drawing::font<
            std::wstring, std::size_t, drawing_details_type
        >
        font_type;

    typedef
        tetengo2::gui::drawing::picture<std::size_t, drawing_details_type>
        picture_type;

    typedef drawing_details_type::canvas_details_type canvas_details_type;

    typedef
        drawing_details_type::canvas_details_ptr_type canvas_details_ptr_type;

    typedef
        tetengo2::gui::drawing::canvas<
            std::size_t,
            std::wstring,
            dimension_type,
            ui_encoder_type,
            transparent_background_type,
            font_type,
            picture_type,
            drawing_details_type
        >
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

    BOOST_AUTO_TEST_CASE(installed_font_families)
    {
        BOOST_TEST_PASSPOINT();

        typedef std::vector<canvas_type::string_type> string_vector_type;
        const string_vector_type families =
            canvas_type::installed_font_families();

        BOOST_CHECK(families == string_vector_type(1, L"TetengoFont"));
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_canvas canvas;
        }
        {
            BOOST_CHECK_THROW(
                const concrete_canvas0 canvas, std::invalid_argument
            );
        }
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

        const font_type font(L"AnotherFont", 42, true, true, true, true);
        canvas.set_font(font);

        BOOST_CHECK(canvas.font() == font);
    }

    BOOST_AUTO_TEST_CASE(fill_rectangle)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        canvas.fill_rectangle(
            std::make_pair(12, 34),
            std::make_pair(56, 78),
            transparent_background_type()
        );
    }

    BOOST_AUTO_TEST_CASE(calc_text_dimension)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_canvas canvas;

        const dimension_type dimension =
            canvas.calc_text_dimension(
                canvas_type::string_type(TETENGO2_TEXT("hoge"))
            );

        BOOST_CHECK(dimension == dimension_type(123, 456));
    }

    BOOST_AUTO_TEST_CASE(draw_text)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        canvas.draw_text(
            canvas_type::string_type(TETENGO2_TEXT("hoge")),
            std::make_pair(12, 34)
        );
    }

    BOOST_AUTO_TEST_CASE(paint_picture)
    {
        BOOST_TEST_PASSPOINT();

        concrete_canvas canvas;

        const picture_type picture(std::make_pair(123, 456), canvas);
        canvas.paint_picture(
            picture, std::make_pair(12, 34), std::make_pair(56, 78)
        );
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
