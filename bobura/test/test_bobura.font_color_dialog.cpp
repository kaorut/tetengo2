/*! \file
    \brief Test of class bobura::font_color_dialog.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <stdexcept>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef
        boost::mpl::at<bobura::dialog_type_list, bobura::type::dialog::font_color_dialog>::type
        font_color_dialog_type;

    typedef font_color_dialog_type::font_type font_type;

    typedef font_color_dialog_type::color_type color_type;


}


#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(font_color_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const font_color_dialog_type font_color_dialog(window, message_catalog);
    }

    BOOST_AUTO_TEST_CASE(background)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const font_color_dialog_type font_color_dialog(window, message_catalog);

        BOOST_CHECK_THROW(font_color_dialog.background(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(set_background)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        font_color_dialog_type font_color_dialog(window, message_catalog);

        font_color_dialog.set_background(color_type(12, 34, 56));

        BOOST_CHECK(font_color_dialog.background() == color_type(12, 34, 56));
    }

    BOOST_AUTO_TEST_CASE(company_line_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const font_color_dialog_type font_color_dialog(window, message_catalog);

        BOOST_CHECK_THROW(font_color_dialog.company_line_name(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(set_company_line_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        font_color_dialog_type font_color_dialog(window, message_catalog);

        font_color_dialog.set_company_line_name(
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true),
            color_type(12, 34, 56)
        );

        BOOST_CHECK(
            font_color_dialog.company_line_name().first ==
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true)
        );
        BOOST_CHECK(font_color_dialog.company_line_name().second == color_type(12, 34, 56));
    }

    BOOST_AUTO_TEST_CASE(note)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const font_color_dialog_type font_color_dialog(window, message_catalog);

        BOOST_CHECK_THROW(font_color_dialog.note(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(set_note)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        font_color_dialog_type font_color_dialog(window, message_catalog);

        font_color_dialog.set_note(
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true),
            color_type(12, 34, 56)
        );

        BOOST_CHECK(
            font_color_dialog.note().first ==
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true)
        );
        BOOST_CHECK(font_color_dialog.note().second == color_type(12, 34, 56));
    }

    BOOST_AUTO_TEST_CASE(time_line)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const font_color_dialog_type font_color_dialog(window, message_catalog);

        BOOST_CHECK_THROW(font_color_dialog.time_line(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(set_time_line)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        font_color_dialog_type font_color_dialog(window, message_catalog);

        font_color_dialog.set_time_line(
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true),
            color_type(12, 34, 56)
        );

        BOOST_CHECK(
            font_color_dialog.time_line().first ==
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true)
        );
        BOOST_CHECK(font_color_dialog.time_line().second == color_type(12, 34, 56));
    }

    BOOST_AUTO_TEST_CASE(local_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const font_color_dialog_type font_color_dialog(window, message_catalog);

        BOOST_CHECK_THROW(font_color_dialog.local_station(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(set_local_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        font_color_dialog_type font_color_dialog(window, message_catalog);

        font_color_dialog.set_local_station(
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true),
            color_type(12, 34, 56)
        );

        BOOST_CHECK(
            font_color_dialog.local_station().first ==
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true)
        );
        BOOST_CHECK(font_color_dialog.local_station().second == color_type(12, 34, 56));
    }

    BOOST_AUTO_TEST_CASE(principal_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const font_color_dialog_type font_color_dialog(window, message_catalog);

        BOOST_CHECK_THROW(font_color_dialog.principal_station(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(set_principal_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        font_color_dialog_type font_color_dialog(window, message_catalog);

        font_color_dialog.set_principal_station(
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true),
            color_type(12, 34, 56)
        );

        BOOST_CHECK(
            font_color_dialog.principal_station().first ==
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true)
        );
        BOOST_CHECK(font_color_dialog.principal_station().second == color_type(12, 34, 56));
    }

    BOOST_AUTO_TEST_CASE(local_terminal_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const font_color_dialog_type font_color_dialog(window, message_catalog);

        BOOST_CHECK_THROW(font_color_dialog.local_terminal_station(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(set_local_terminal_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        font_color_dialog_type font_color_dialog(window, message_catalog);

        font_color_dialog.set_local_terminal_station(
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true),
            color_type(12, 34, 56)
        );

        BOOST_CHECK(
            font_color_dialog.local_terminal_station().first ==
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true)
        );
        BOOST_CHECK(font_color_dialog.local_terminal_station().second == color_type(12, 34, 56));
    }

    BOOST_AUTO_TEST_CASE(principal_terminal_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const font_color_dialog_type font_color_dialog(window, message_catalog);

        BOOST_CHECK_THROW(font_color_dialog.principal_terminal_station(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(set_principal_terminal_station)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        font_color_dialog_type font_color_dialog(window, message_catalog);

        font_color_dialog.set_principal_terminal_station(
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true),
            color_type(12, 34, 56)
        );

        BOOST_CHECK(
            font_color_dialog.principal_terminal_station().first ==
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true)
        );
        BOOST_CHECK(font_color_dialog.principal_terminal_station().second == color_type(12, 34, 56));
    }

    BOOST_AUTO_TEST_CASE(train_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const font_color_dialog_type font_color_dialog(window, message_catalog);

        BOOST_CHECK_THROW(font_color_dialog.train_name(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(set_train_name)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        font_color_dialog_type font_color_dialog(window, message_catalog);

        font_color_dialog.set_train_name(font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true));

        BOOST_CHECK(
            font_color_dialog.train_name() ==
            font_type(string_type(TETENGO2_TEXT("hoge")), 42, false, true, false, true)
        );
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif
