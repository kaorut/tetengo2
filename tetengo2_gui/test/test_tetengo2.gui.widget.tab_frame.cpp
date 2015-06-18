/*! \file
    \brief Test of class tetengo2::gui::widget::tab_frame.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <stdexcept>

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

    using mouse_capture_details_type = detail_type_list_type::mouse_capture_type;

    using tab_frame_type =
        tetengo2::gui::widget::tab_frame<widget_traits_type, widget_details_traits_type, mouse_capture_details_type>;

    using tab_type = tab_frame_type::tab_type;

    using string_type = tab_frame_type::string_type;

    using control_type = tab_frame_type::control_type;

    using label_type = tetengo2::gui::widget::label<widget_traits_type, widget_details_traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(tab_frame)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const tab_frame_type tab_frame{ parent };
    }

    BOOST_AUTO_TEST_CASE(tab_count)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        tab_frame_type tab_frame{ parent };

        BOOST_CHECK_EQUAL(tab_frame.tab_count(), 0);

        label_type label1{ tab_frame };

        BOOST_CHECK_EQUAL(tab_frame.tab_count(), 1);

        {
            label_type label2{ tab_frame };

            BOOST_CHECK_EQUAL(tab_frame.tab_count(), 2);
        }

        BOOST_CHECK_EQUAL(tab_frame.tab_count(), 1);
    }

    BOOST_AUTO_TEST_CASE(tab_at)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const tab_frame_type tab_frame{ parent };

            BOOST_CHECK_THROW(tab_frame.tab_at(0), std::out_of_range);
        }
        {
            window_type parent{};
            tab_frame_type tab_frame{ parent };
            label_type label1{ tab_frame };
            label_type label2{ tab_frame };

            BOOST_CHECK(&tab_frame.tab_at(0).template get<label_type>() == &label1);
            BOOST_CHECK(&tab_frame.tab_at(1).template get<label_type>() == &label2);
            BOOST_CHECK_THROW(tab_frame.tab_at(2), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(selected_tab_index)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const tab_frame_type tab_frame{ parent };
        
        BOOST_CHECK_THROW(tab_frame.selected_tab_index(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(select_tab)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
