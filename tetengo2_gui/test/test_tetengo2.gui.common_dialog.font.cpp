/*! \file
    \brief Test of class tetengo2::gui::common_dialog::font.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using window_type =
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type;

    using string_type = boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type;

    using font_type =
        boost::mpl::at<test_tetengo2::gui::drawing_type_list, test_tetengo2::gui::type::drawing::font>::type;

    using font_dialog_type =
        boost::mpl::at<
            test_tetengo2::gui::common_dialog_type_list, test_tetengo2::gui::type::common_dialog::font
        >::type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(common_dialog)
BOOST_AUTO_TEST_SUITE(font)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const font_dialog_type font(boost::none, parent);
        }
        {
            window_type parent;
            const font_dialog_type font(
                boost::make_optional(font_type(string_type(TETENGO2_TEXT("fuga")), 42, false, true, false, true)),
                parent
            );
        }
    }

    BOOST_AUTO_TEST_CASE(result)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const font_dialog_type font(boost::none, parent);

            BOOST_CHECK(font.result() == font_type::dialog_font());
        }
        {
            window_type parent;
            font_dialog_type font(boost::none, parent);

            font.do_modal();

            BOOST_CHECK(font.result() != font_type::dialog_font());
        }
    }

    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        font_dialog_type font(boost::none, parent);

        font.do_modal();
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const font_dialog_type font(boost::none, parent);

            font.details();
        }
        {
            window_type parent;
            font_dialog_type font(boost::none, parent);

            font.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
