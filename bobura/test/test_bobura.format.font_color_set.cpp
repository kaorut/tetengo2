/*! \file
    \brief Test of class bobura::format::font_color_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::font_color>::type font_color_type;

    typedef font_color_type::font_type font_type;

    typedef font_type::string_type string_type;

    typedef font_color_type::color_type color_type;

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::font_color_set>::type font_color_set_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(format)
BOOST_AUTO_TEST_SUITE(font_color)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_type font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const font_color_type font_color1(
                font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type font_color2(
                font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
            );

            BOOST_CHECK(font_color1 == font_color2);
        }
        {
            const font_color_type font_color1(
                font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type font_color2(
                font_type(string_type(TETENGO2_TEXT("ABC")), 24, true, true, false, false), color_type(21, 43, 65)
            );

            BOOST_CHECK(font_color1 != font_color2);
        }
    }

    BOOST_AUTO_TEST_CASE(font)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_type font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );

        BOOST_CHECK(font_color.font() == font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true));
    }

    BOOST_AUTO_TEST_CASE(color)
    {
        BOOST_TEST_PASSPOINT();

        const font_color_type font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );

        BOOST_CHECK(font_color.color() == color_type(12, 34, 56));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(font_color_set)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const color_type background_color(12, 34, 56);
        const font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            background_color,
            company_line_name_font_color,
            note_font_color,
            time_line_font_color,
            local_station_font_color,
            principal_station_font_color,
            local_terminal_station_font_color,
            principal_terminal_station_font_color,
            train_name_font
        );
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const color_type background_color1(12, 34, 56);
            const font_color_type compnay_line_name_font_color1(
                font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type note_font_color1(
                font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type time_line_font_color1(
                font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type local_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type principal_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type local_terminal_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type principal_terminal_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_type train_name_font1(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

            const font_color_set_type font_color_set1(
                background_color1,
                compnay_line_name_font_color1,
                note_font_color1,
                time_line_font_color1,
                local_station_font_color1,
                principal_station_font_color1,
                local_terminal_station_font_color1,
                principal_terminal_station_font_color1,
                train_name_font1
            );

            const color_type background_color2(12, 34, 56);
            const font_color_type compnay_line_name_font_color2(
                font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type note_font_color2(
                font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type time_line_font_color2(
                font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type local_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type principal_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type local_terminal_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type principal_terminal_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_type train_name_font2(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

            const font_color_set_type font_color_set2(
                background_color2,
                compnay_line_name_font_color2,
                note_font_color2,
                time_line_font_color2,
                local_station_font_color2,
                principal_station_font_color2,
                local_terminal_station_font_color2,
                principal_terminal_station_font_color2,
                train_name_font1
            );

            BOOST_CHECK(font_color_set1 == font_color_set2);
        }
        {
            const color_type background_color1(12, 34, 56);
            const font_color_type compnay_line_name_font_color1(
                font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type note_font_color1(
                font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type time_line_font_color1(
                font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type local_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type principal_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type local_terminal_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type principal_terminal_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_type train_name_font1(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

            const font_color_set_type font_color_set1(
                background_color1,
                compnay_line_name_font_color1,
                note_font_color1,
                time_line_font_color1,
                local_station_font_color1,
                principal_station_font_color1,
                local_terminal_station_font_color1,
                principal_terminal_station_font_color1,
                train_name_font1
            );

            const color_type background_color2(12, 34, 56);
            const font_color_type compnay_line_name_font_color2(
                font_type(string_type(TETENGO2_TEXT("ABC")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type note_font_color2(
                font_type(string_type(TETENGO2_TEXT("DEF")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type time_line_font_color2(
                font_type(string_type(TETENGO2_TEXT("GHI")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type local_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("JKL")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type principal_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("MNO")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type local_terminal_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("PQR")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_color_type principal_terminal_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("STU")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            const font_type train_name_font2(string_type(TETENGO2_TEXT("VWX")), 42, false, true, false, true);

            const font_color_set_type font_color_set2(
                background_color2,
                compnay_line_name_font_color2,
                note_font_color2,
                time_line_font_color2,
                local_station_font_color2,
                principal_station_font_color2,
                local_terminal_station_font_color2,
                principal_terminal_station_font_color2,
                train_name_font2
            );


            BOOST_CHECK(font_color_set1 != font_color_set2);
        }
    }

    BOOST_AUTO_TEST_CASE(background)
    {
        BOOST_TEST_PASSPOINT();

        const color_type background_color(12, 34, 56);
        const font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            background_color,
            company_line_name_font_color,
            note_font_color,
            time_line_font_color,
            local_station_font_color,
            principal_station_font_color,
            local_terminal_station_font_color,
            principal_terminal_station_font_color,
            train_name_font
        );

        BOOST_CHECK(font_color_set.background() == background_color);
    }

    BOOST_AUTO_TEST_CASE(company_line_name)
    {
        BOOST_TEST_PASSPOINT();

        const color_type background_color(12, 34, 56);
        const font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            background_color,
            company_line_name_font_color,
            note_font_color,
            time_line_font_color,
            local_station_font_color,
            principal_station_font_color,
            local_terminal_station_font_color,
            principal_terminal_station_font_color,
            train_name_font
        );

        BOOST_CHECK(font_color_set.company_line_name() == company_line_name_font_color);
    }

    BOOST_AUTO_TEST_CASE(note)
    {
        BOOST_TEST_PASSPOINT();

        const color_type background_color(12, 34, 56);
        const font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            background_color,
            company_line_name_font_color,
            note_font_color,
            time_line_font_color,
            local_station_font_color,
            principal_station_font_color,
            local_terminal_station_font_color,
            principal_terminal_station_font_color,
            train_name_font
        );

        BOOST_CHECK(font_color_set.note() == note_font_color);
    }

    BOOST_AUTO_TEST_CASE(time_line)
    {
        BOOST_TEST_PASSPOINT();

        const color_type background_color(12, 34, 56);
        const font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            background_color,
            company_line_name_font_color,
            note_font_color,
            time_line_font_color,
            local_station_font_color,
            principal_station_font_color,
            local_terminal_station_font_color,
            principal_terminal_station_font_color,
            train_name_font
        );

        BOOST_CHECK(font_color_set.time_line() == time_line_font_color);
    }

    BOOST_AUTO_TEST_CASE(local_station)
    {
        BOOST_TEST_PASSPOINT();

        const color_type background_color(12, 34, 56);
        const font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            background_color,
            company_line_name_font_color,
            note_font_color,
            time_line_font_color,
            local_station_font_color,
            principal_station_font_color,
            local_terminal_station_font_color,
            principal_terminal_station_font_color,
            train_name_font
        );

        BOOST_CHECK(font_color_set.local_station() == local_station_font_color);
    }

    BOOST_AUTO_TEST_CASE(principal_station)
    {
        BOOST_TEST_PASSPOINT();

        const color_type background_color(12, 34, 56);
        const font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            background_color,
            company_line_name_font_color,
            note_font_color,
            time_line_font_color,
            local_station_font_color,
            principal_station_font_color,
            local_terminal_station_font_color,
            principal_terminal_station_font_color,
            train_name_font
        );

        BOOST_CHECK(font_color_set.principal_station() == principal_station_font_color);
    }

    BOOST_AUTO_TEST_CASE(local_terminal_station)
    {
        BOOST_TEST_PASSPOINT();

        const color_type background_color(12, 34, 56);
        const font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            background_color,
            company_line_name_font_color,
            note_font_color,
            time_line_font_color,
            local_station_font_color,
            principal_station_font_color,
            local_terminal_station_font_color,
            principal_terminal_station_font_color,
            train_name_font
        );

        BOOST_CHECK(font_color_set.local_terminal_station() == local_terminal_station_font_color);
    }

    BOOST_AUTO_TEST_CASE(principal_terminal_station)
    {
        BOOST_TEST_PASSPOINT();

        const color_type background_color(12, 34, 56);
        const font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            background_color,
            company_line_name_font_color,
            note_font_color,
            time_line_font_color,
            local_station_font_color,
            principal_station_font_color,
            local_terminal_station_font_color,
            principal_terminal_station_font_color,
            train_name_font
        );

        BOOST_CHECK(font_color_set.principal_terminal_station() == principal_terminal_station_font_color);
    }

    BOOST_AUTO_TEST_CASE(train_name)
    {
        BOOST_TEST_PASSPOINT();

        const color_type background_color(12, 34, 56);
        const font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        const font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            background_color,
            company_line_name_font_color,
            note_font_color,
            time_line_font_color,
            local_station_font_color,
            principal_station_font_color,
            local_terminal_station_font_color,
            principal_terminal_station_font_color,
            train_name_font
        );

        BOOST_CHECK(font_color_set.train_name() == train_name_font);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
