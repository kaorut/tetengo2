/*! \file
    \brief Test of class tetengo2::gui::widget::button.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_tetengo2::gui::widget_type_list,
            test_tetengo2::gui::type::widget::window
        >::type
        window_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::widget_type_list,
            test_tetengo2::gui::type::widget::button
        >::type
        button_type;


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
            window_type parent;
            const button_type button(parent, button_type::style_normal);
        }
        {
            window_type parent;
            const button_type button(parent, button_type::style_default);
        }
        {
            window_type parent;
            const button_type button(parent, button_type::style_cancel);
        }
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const button_type button(parent, button_type::style_normal);

            BOOST_CHECK_EQUAL(button.style(), button_type::style_normal);
        }
        {
            window_type parent;
            const button_type button(parent, button_type::style_default);

            BOOST_CHECK_EQUAL(button.style(), button_type::style_default);
        }
        {
            window_type parent;
            const button_type button(parent, button_type::style_cancel);

            BOOST_CHECK_EQUAL(button.style(), button_type::style_cancel);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
