/*! \file
    \brief Test of class tetengo2::gui::common_dialog::file_save.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/filesystem.hpp>
#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::detail_type_list;

    using type_list_type = test_tetengo2::gui::type_list<detail_type_list_type>;

    using string_type = boost::mpl::at<type_list_type, test_tetengo2::gui::type::string>::type;

    using widget_traits_type = boost::mpl::at<type_list_type, test_tetengo2::gui::type::widget_traits>::type;

    using widget_details_traits_type =
        boost::mpl::at<type_list_type, test_tetengo2::gui::type::widget_details_traits>::type;

    using menu_details_type = boost::mpl::at<detail_type_list_type, test_tetengo2::gui::type::detail::menu>::type;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using common_dialog_details_type =
        boost::mpl::at<detail_type_list_type, test_tetengo2::gui::type::detail::common_dialog>::type;

    using file_save_dialog_type =
        tetengo2::gui::common_dialog::file_save<
            string_type, widget_traits_type, common_dialog_details_type, widget_details_traits_type, menu_details_type
        >;


    // functions

    file_save_dialog_type::file_filters_type make_file_filters()
    {
        return { { string_type{ TETENGO2_TEXT("All Files") }, string_type{ TETENGO2_TEXT("*.*") } } };
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
            window_type parent{};
            const file_save_dialog_type file_save{ string_type{}, boost::none, make_file_filters(), parent };
        }
        {
            window_type parent{};
            const file_save_dialog_type file_save{
                string_type{ TETENGO2_TEXT("hoge") }, boost::none, file_save_dialog_type::file_filters_type{}, parent
            };
        }
        {
            window_type parent{};
            const file_save_dialog_type file_save{
                string_type{ TETENGO2_TEXT("hoge") }, boost::none, make_file_filters(), parent
            };
        }
    }

    BOOST_AUTO_TEST_CASE(result)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const file_save_dialog_type file_save{
                string_type{ TETENGO2_TEXT("hoge") }, boost::none, make_file_filters(), parent
            };

            BOOST_CHECK(file_save.result().empty());
        }
        {
            window_type parent{};
            file_save_dialog_type file_save{
                string_type{ TETENGO2_TEXT("hoge") }, boost::none, make_file_filters(), parent
            };

            file_save.do_modal();

            BOOST_CHECK(!file_save.result().empty());
        }
        {
            window_type parent{};
            const file_save_dialog_type file_save{
                string_type{ TETENGO2_TEXT("hoge") },
                boost::make_optional(boost::filesystem::path{ "fuga.jpg" }),
                make_file_filters(),
                parent
            };

            BOOST_CHECK(file_save.result() == boost::filesystem::path{ "fuga.jpg" });
        }
        {
            window_type parent{};
            file_save_dialog_type file_save{
                string_type{ TETENGO2_TEXT("hoge") },
                boost::make_optional(boost::filesystem::path{ "fuga.jpg" }),
                make_file_filters(),
                parent
            };

            file_save.do_modal();

            BOOST_CHECK(file_save.result() != boost::filesystem::path{ "fuga.jpg" });
        }
    }

    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        file_save_dialog_type file_save{
            string_type{ TETENGO2_TEXT("hoge") }, boost::none, make_file_filters(), parent
        };

        file_save.do_modal();
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const file_save_dialog_type file_save{
                string_type{ TETENGO2_TEXT("hoge") }, boost::none, make_file_filters(), parent
            };

            file_save.details();
        }
        {
            window_type parent{};
            file_save_dialog_type file_save{
                string_type{ TETENGO2_TEXT("hoge") }, boost::none, make_file_filters(), parent
            };

            file_save.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
