/*! \file
    \brief Test of class tetengo2::gui::message::child_observer_set.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/message/child_observer_set.h>
#include <tetengo2/gui/widget/widget.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using widget_type =
        tetengo2::gui::widget::widget<
            common_type_list_type::widget_traits_type, common_type_list_type::widget_details_traits_type
        >;

    using child_observer_set_type = tetengo2::gui::message::child_observer_set<widget_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(child_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(created)
    {
        BOOST_TEST_PASSPOINT();

        {
            const child_observer_set_type observer_set{};

            observer_set.created();
        }
        {
            child_observer_set_type observer_set{};

            observer_set.created();
        }
    }

    BOOST_AUTO_TEST_CASE(destroying)
    {
        BOOST_TEST_PASSPOINT();

        {
            const child_observer_set_type observer_set{};

            observer_set.destroying();
        }
        {
            child_observer_set_type observer_set{};

            observer_set.destroying();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
