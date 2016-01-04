/*! \file
    \brief Test of class tetengo2::gui::widget::button.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

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

    using button_type = tetengo2::gui::widget::button<widget_traits_type, widget_details_traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(button)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const button_type button{ parent, button_type::style_type::normal };
        }
        {
            window_type parent{};
            const button_type button{ parent, button_type::style_type::default_ };
        }
        {
            window_type parent{};
            const button_type button{ parent, button_type::style_type::cancel };
        }
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const button_type button{ parent, button_type::style_type::normal };

            BOOST_CHECK(button.style() == button_type::style_type::normal);
        }
        {
            window_type parent{};
            const button_type button{ parent, button_type::style_type::default_ };

            BOOST_CHECK(button.style() == button_type::style_type::default_);
        }
        {
            window_type parent{};
            const button_type button{ parent, button_type::style_type::cancel };

            BOOST_CHECK(button.style() == button_type::style_type::cancel);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
