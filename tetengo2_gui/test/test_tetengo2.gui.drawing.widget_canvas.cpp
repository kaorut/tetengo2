/*! \file
    \brief Test of class tetengo2::gui::drawing::widget_canvas.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>
#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/canvas_traits.h>
#include <tetengo2/gui/drawing/widget_canvas.h>
#include <tetengo2/gui/drawing/solid_background.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using canvas_traits_type =
        tetengo2::gui::drawing::canvas_traits<
            size_type,
            common_type_list_type::string_type,
            common_type_list_type::position_type,
            common_type_list_type::dimension_type,
            common_type_list_type::ui_encoder_type
        >;

    using drawing_details_type = detail_type_list_type::drawing_type;

    using canvas_type =
        tetengo2::gui::drawing::widget_canvas<
            canvas_traits_type, drawing_details_type, detail_type_list_type::icon_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(widget_canvas)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const canvas_type canvas{ 42 };
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
