/*! \file
    \brief Test of class tetengo2::gui::widget::window.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/widget/abstract_window.h>
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

    using abstract_window_type =
        tetengo2::gui::widget::abstract_window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(window)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const window_type window{};
        }
        {
            const window_type window{ window_type::scroll_bar_style_type::none, false };
        }
        {
            const window_type window{ window_type::scroll_bar_style_type::both, false };
        }
        {
            const window_type window{ window_type::scroll_bar_style_type::none, true };
        }
        {
            window_type parent{};
            const window_type window{
                static_cast<abstract_window_type&>(parent), window_type::scroll_bar_style_type::none, false
            };
        }
        {
            window_type parent{};
            const window_type window{
                static_cast<abstract_window_type&>(parent), window_type::scroll_bar_style_type::both, false
            };
        }
        {
            window_type parent{};
            const window_type window{
                static_cast<abstract_window_type&>(parent), window_type::scroll_bar_style_type::none, true
            };
        }
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const window_type window{};

            window.details();
        }
        {
            window_type window{};

            window.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
