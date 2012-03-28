/*! \file
    \brief Test of class tetengo2::gui::common_dialog::message_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

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
            test_tetengo2::gui::type_list, test_tetengo2::gui::type::string
        >::type
        string_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::common_dialog_type_list,
            test_tetengo2::gui::type::common_dialog::button_style
        >::type
        button_style_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::common_dialog_type_list,
            test_tetengo2::gui::type::common_dialog::message_box
        >::type
        message_box_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(common_dialog)
BOOST_AUTO_TEST_SUITE(message_box)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const string_type title;
            const string_type main_content;
            const string_type sub_content;
            const message_box_type message_box(
                parent,
                title,
                main_content,
                sub_content,
                button_style_type::ok(true),
                message_box_type::icon_style_warning
            );
        }
    }

    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const string_type title;
        const string_type main_content;
        const string_type sub_content;
        message_box_type message_box(
            parent,
            title,
            main_content,
            sub_content,
            button_style_type::ok(true),
            message_box_type::icon_style_warning
        );

        message_box.do_modal();
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const string_type title;
            const string_type main_content;
            const string_type sub_content;
            const message_box_type message_box(
                parent,
                title,
                main_content,
                sub_content,
                button_style_type::ok(true),
                message_box_type::icon_style_warning
            );

            message_box.details();
        }
        {
            window_type parent;
            const string_type title;
            const string_type main_content;
            const string_type sub_content;
            message_box_type message_box(
                parent,
                title,
                main_content,
                sub_content,
                button_style_type::ok(true),
                message_box_type::icon_style_warning
            );

            message_box.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
