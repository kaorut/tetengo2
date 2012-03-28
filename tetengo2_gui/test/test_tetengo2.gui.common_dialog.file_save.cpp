/*! \file
    \brief Test of class tetengo2::gui::common_dialog::file_save.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>
//#include <utility>

//#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
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
            test_tetengo2::gui::common_dialog_type_list,
            test_tetengo2::gui::type::common_dialog::file_save
        >::type
        file_save_dialog_type;


    // functions

    file_save_dialog_type::file_filters_type make_file_filters()
    {
        file_save_dialog_type::file_filters_type filters;

        filters.push_back(std::make_pair("All Files", "*.*"));

        return filters;
    }


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(common_dialog)
BOOST_AUTO_TEST_SUITE(file_save)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const file_save_dialog_type file_save(
                std::string(), boost::none, make_file_filters(), parent
            );
        }
        {
            window_type parent;
            const file_save_dialog_type file_save(
                "hoge",
                boost::none,
                file_save_dialog_type::file_filters_type(),
                parent
            );
        }
        {
            window_type parent;
            const file_save_dialog_type file_save(
                "hoge", boost::none, make_file_filters(), parent
            );
        }
    }

    BOOST_AUTO_TEST_CASE(result)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const file_save_dialog_type file_save(
                "hoge", boost::none, make_file_filters(), parent
            );

            BOOST_CHECK(file_save.result().empty());
        }
        {
            window_type parent;
            file_save_dialog_type file_save(
                "hoge", boost::none, make_file_filters(), parent
            );

            file_save.do_modal();

            BOOST_CHECK(!file_save.result().empty());
        }
        {
            window_type parent;
            const file_save_dialog_type file_save(
                "hoge",
                boost::make_optional(boost::filesystem::path("fuga.jpg")),
                make_file_filters(),
                parent
            );

            BOOST_CHECK(file_save.result().empty());
        }
        {
            window_type parent;
            file_save_dialog_type file_save(
                "hoge",
                boost::make_optional(boost::filesystem::path("fuga.jpg")),
                make_file_filters(),
                parent
            );

            file_save.do_modal();

            BOOST_CHECK(!file_save.result().empty());
        }
    }

    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        file_save_dialog_type file_save(
            "hoge", boost::none, make_file_filters(), parent
        );

        file_save.do_modal();
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const file_save_dialog_type file_save(
                "hoge", boost::none, make_file_filters(), parent
            );

            file_save.details();
        }
        {
            window_type parent;
            file_save_dialog_type file_save(
                "hoge", boost::none, make_file_filters(), parent
            );

            file_save.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
