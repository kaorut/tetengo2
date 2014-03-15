/*! \file
    \brief Test of class tetengo2::gui::widget::window.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::abstract_window>::type
        abstract_window_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type
        window_type;


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
            const window_type window;
        }
        {
            const window_type window(window_type::scroll_bar_style_type::none, false);
        }
        {
            const window_type window(window_type::scroll_bar_style_type::both, false);
        }
        {
            const window_type window(window_type::scroll_bar_style_type::none, true);
        }
        {
            window_type parent;
            const window_type window(
                static_cast<abstract_window_type&>(parent), window_type::scroll_bar_style_type::none, false
            );
        }
        {
            window_type parent;
            const window_type window(
                static_cast<abstract_window_type&>(parent), window_type::scroll_bar_style_type::both, false
            );
        }
        {
            window_type parent;
            const window_type window(
                static_cast<abstract_window_type&>(parent), window_type::scroll_bar_style_type::none, true
            );
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
