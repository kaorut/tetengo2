/*! \file
    \brief Test of class tetengo2::gui::common_dialog::file_open.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.text.h"

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type
        window_type;

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type string_type;

    typedef
        boost::mpl::at<
            test_tetengo2::gui::common_dialog_type_list, test_tetengo2::gui::type::common_dialog::file_open
        >::type
        file_open_dialog_type;


    // functions

    file_open_dialog_type::file_filters_type make_file_filters()
    {
        file_open_dialog_type::file_filters_type filters;

        filters.emplace_back(string_type(TETENGO2_TEXT("All Files")), string_type(TETENGO2_TEXT("*.*")));

        return filters;
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(common_dialog)
BOOST_AUTO_TEST_SUITE(file_open)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const file_open_dialog_type file_open(string_type(), make_file_filters(), parent);
        }
        {
            window_type parent;
            const file_open_dialog_type file_open(
                string_type(TETENGO2_TEXT("hoge")), file_open_dialog_type::file_filters_type(), parent
            );
        }
        {
            window_type parent;
            const file_open_dialog_type file_open(string_type(TETENGO2_TEXT("hoge")), make_file_filters(), parent);
        }
    }

    BOOST_AUTO_TEST_CASE(result)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const file_open_dialog_type file_open(string_type(TETENGO2_TEXT("hoge")), make_file_filters(), parent);

            BOOST_CHECK(file_open.result().empty());
        }
        {
            window_type parent;
            file_open_dialog_type file_open(string_type(TETENGO2_TEXT("hoge")), make_file_filters(), parent);

            file_open.do_modal();

            BOOST_CHECK(!file_open.result().empty());
        }
    }

    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        file_open_dialog_type file_open(string_type(TETENGO2_TEXT("hoge")), make_file_filters(), parent);

        file_open.do_modal();
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const file_open_dialog_type file_open(string_type(TETENGO2_TEXT("hoge")), make_file_filters(), parent);

            file_open.details();
        }
        {
            window_type parent;
            file_open_dialog_type file_open(string_type(TETENGO2_TEXT("hoge")), make_file_filters(), parent);

            file_open.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
