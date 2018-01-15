/*! \file
    \brief Test of class tetengo2::gui::common_dialog::color.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/none.hpp>
#include <boost/operators.hpp>
#include <boost/optional.hpp>
#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/common_dialog/color.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/widget/window.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using widget_traits_type = common_type_list_type::widget_traits_type;

    using widget_details_traits_type = common_type_list_type::widget_details_traits_type;

    using menu_details_type = detail_type_list_type::menu_type;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using color_type = tetengo2::gui::drawing::color;

    using common_dialog_details_type = detail_type_list_type::common_dialog_type;

    using color_dialog_type =
        tetengo2::gui::common_dialog::color<
            color_type, widget_traits_type, common_dialog_details_type, widget_details_traits_type, menu_details_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(common_dialog)
BOOST_AUTO_TEST_SUITE(color)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const color_dialog_type color{ boost::none, parent };
        }
        {
            window_type parent{};
            const color_dialog_type color{ boost::make_optional(color_type{ 12, 34, 56 }), parent };
        }
    }

    BOOST_AUTO_TEST_CASE(result)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const color_dialog_type color{ boost::none, parent };

            BOOST_CHECK((color.result() == color_type{ 0, 0, 0 }));
        }
        {
            window_type parent{};
            color_dialog_type color{ boost::none, parent };

            color.do_modal();

            BOOST_CHECK((color.result() != color_type{ 0, 0, 0 }));
        }
    }

    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        color_dialog_type color{ boost::none, parent };

        color.do_modal();
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const color_dialog_type color{ boost::none, parent };

            color.details();
        }
        {
            window_type parent{};
            color_dialog_type color{ boost::none, parent };

            color.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
