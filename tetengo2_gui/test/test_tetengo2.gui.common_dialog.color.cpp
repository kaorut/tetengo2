/*! \file
    \brief Test of class tetengo2::gui::common_dialog::color.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type
        window_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::color>::type
        color_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::common_dialog_type_list, test_tetengo2::gui::type::common_dialog::color
        >::type
        color_dialog_type;


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
            window_type parent;
            const color_dialog_type color(boost::none, parent);
        }
        {
            window_type parent;
            const color_dialog_type color(boost::make_optional(color_type(12, 34, 56)), parent);
        }
    }

    BOOST_AUTO_TEST_CASE(result)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const color_dialog_type color(boost::none, parent);

            BOOST_CHECK(color.result() == color_type(0, 0, 0));
        }
        {
            window_type parent;
            color_dialog_type color(boost::none, parent);

            color.do_modal();

            BOOST_CHECK(color.result() != color_type(0, 0, 0));
        }
    }

    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        color_dialog_type color(boost::none, parent);

        color.do_modal();
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const color_dialog_type color(boost::none, parent);

            color.details();
        }
        {
            window_type parent;
            color_dialog_type color(boost::none, parent);

            color.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
