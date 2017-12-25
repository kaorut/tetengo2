/*! \file
    \brief Test of class tetengo2::gui::widget::label.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/widget/label.h>
#include <tetengo2/gui/widget/window.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using widget_traits_type = common_type_list_type::widget_traits_type;

    using widget_details_traits_type = common_type_list_type::widget_details_traits_type;

    using menu_details_type = detail_type_list_type::menu_type;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using dimension_type = common_type_list_type::dimension_type;

    using dimension_unit_type = dimension_type::unit_type;

    using label_type = tetengo2::gui::widget::label<widget_traits_type, widget_details_traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(label)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const label_type label{ parent };
    }

    BOOST_AUTO_TEST_CASE(fit_to_content)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        label_type label{ parent };
        label.set_text(string_type{ TETENGO2_TEXT("Tetengo") });

        label.fit_to_content();

        const auto dimension = label.dimension();

        const auto answer_dimension =
            label.create_canvas()->calc_text_dimension(string_type{ TETENGO2_TEXT("Tetengo") });
        BOOST_CHECK(dimension == answer_dimension);
    }

    BOOST_AUTO_TEST_CASE(fit_to_content_O_max_width)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        label_type label{ parent };
        label.set_text(string_type{ TETENGO2_TEXT("Tetengo") });

        label.fit_to_content(dimension_unit_type{ 42 });
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
