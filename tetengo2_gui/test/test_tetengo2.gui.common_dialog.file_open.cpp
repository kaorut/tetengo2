/*! \file
    \brief Test of class tetengo2::gui::common_dialog::file_open.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <sstream>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/common_dialog/file_open.h>
#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/widget/window.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using widget_traits_type = common_type_list_type::widget_traits_type;

    using widget_details_traits_type = common_type_list_type::widget_details_traits_type;

    using menu_details_type = detail_type_list_type::menu_type;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using common_dialog_details_type = detail_type_list_type::common_dialog_type;

    using file_open_dialog_type =
        tetengo2::gui::common_dialog::file_open<
            string_type, widget_traits_type, common_dialog_details_type, widget_details_traits_type, menu_details_type
        >;


    // functions

    file_open_dialog_type::file_filters_type make_file_filters()
    {
        return { { string_type{ TETENGO2_TEXT("All Files") }, string_type{ TETENGO2_TEXT("*.*") } } };
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
            window_type parent{};
            const file_open_dialog_type file_open{ string_type{}, make_file_filters(), parent };
        }
        {
            window_type parent{};
            const file_open_dialog_type file_open{
                string_type{ TETENGO2_TEXT("hoge") }, file_open_dialog_type::file_filters_type{}, parent
            };
        }
        {
            window_type parent{};
            const file_open_dialog_type file_open{ string_type{ TETENGO2_TEXT("hoge") }, make_file_filters(), parent };
        }
    }

    BOOST_AUTO_TEST_CASE(result)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const file_open_dialog_type file_open{ string_type{ TETENGO2_TEXT("hoge") }, make_file_filters(), parent };

            BOOST_TEST(file_open.result().empty());
        }
        {
            window_type parent{};
            file_open_dialog_type file_open{ string_type{ TETENGO2_TEXT("hoge") }, make_file_filters(), parent };

            file_open.do_modal();

            BOOST_TEST(!file_open.result().empty());
        }
    }

    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        file_open_dialog_type file_open{ string_type{ TETENGO2_TEXT("hoge") }, make_file_filters(), parent };

        file_open.do_modal();
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const file_open_dialog_type file_open{ string_type{ TETENGO2_TEXT("hoge") }, make_file_filters(), parent };


            file_open.details();
        }
        {
            window_type parent{};
            file_open_dialog_type file_open{ string_type{ TETENGO2_TEXT("hoge") }, make_file_filters(), parent };

            file_open.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
