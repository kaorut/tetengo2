/*! \file
    \brief Test of class bobura::model::timetable_info::font_color_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::font_color_set>::type
        font_color_set_type;

    typedef font_color_set_type::font_color_type font_color_type;

    typedef font_color_type::font_type font_type;

    typedef font_type::string_type string_type;

    typedef font_color_type::color_type color_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(timetable_info)
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

    BOOST_AUTO_TEST_CASE(default_)
    {
        BOOST_TEST_PASSPOINT();

        font_color_set_type::default_();
    }

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        color_type background_color(12, 34, 56);
        font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            std::move(background_color),
            std::move(company_line_name_font_color),
            std::move(note_font_color),
            std::move(time_line_font_color),
            std::move(local_station_font_color),
            std::move(principal_station_font_color),
            std::move(local_terminal_station_font_color),
            std::move(principal_terminal_station_font_color),
            std::move(train_name_font)
        );
    }

    BOOST_AUTO_TEST_CASE(operator_equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            color_type background_color1(12, 34, 56);
            font_color_type company_line_name_font_color1(
                font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type note_font_color1(
                font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type time_line_font_color1(
                font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type local_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type principal_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type local_terminal_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type principal_terminal_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_type train_name_font1(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

            const font_color_set_type font_color_set1(
                std::move(background_color1),
                std::move(company_line_name_font_color1),
                std::move(note_font_color1),
                std::move(time_line_font_color1),
                std::move(local_station_font_color1),
                std::move(principal_station_font_color1),
                std::move(local_terminal_station_font_color1),
                std::move(principal_terminal_station_font_color1),
                std::move(train_name_font1)
            );

            color_type background_color2(12, 34, 56);
            font_color_type company_line_name_font_color2(
                font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type note_font_color2(
                font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type time_line_font_color2(
                font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type local_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type principal_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type local_terminal_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type principal_terminal_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_type train_name_font2(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

            const font_color_set_type font_color_set2(
                std::move(background_color2),
                std::move(company_line_name_font_color2),
                std::move(note_font_color2),
                std::move(time_line_font_color2),
                std::move(local_station_font_color2),
                std::move(principal_station_font_color2),
                std::move(local_terminal_station_font_color2),
                std::move(principal_terminal_station_font_color2),
                std::move(train_name_font2)
            );

            BOOST_CHECK(font_color_set1 == font_color_set2);
        }
        {
            color_type background_color1(12, 34, 56);
            font_color_type company_line_name_font_color1(
                font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type note_font_color1(
                font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type time_line_font_color1(
                font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type local_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type principal_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type local_terminal_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type principal_terminal_station_font_color1(
                font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_type train_name_font1(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

            const font_color_set_type font_color_set1(
                std::move(background_color1),
                std::move(company_line_name_font_color1),
                std::move(note_font_color1),
                std::move(time_line_font_color1),
                std::move(local_station_font_color1),
                std::move(principal_station_font_color1),
                std::move(local_terminal_station_font_color1),
                std::move(principal_terminal_station_font_color1),
                std::move(train_name_font1)
            );

            color_type background_color2(12, 34, 56);
            font_color_type company_line_name_font_color2(
                font_type(string_type(TETENGO2_TEXT("ABC")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type note_font_color2(
                font_type(string_type(TETENGO2_TEXT("DEF")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type time_line_font_color2(
                font_type(string_type(TETENGO2_TEXT("GHI")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type local_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("JKL")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type principal_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("MNO")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type local_terminal_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("PQR")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_color_type principal_terminal_station_font_color2(
                font_type(string_type(TETENGO2_TEXT("STU")), 42, false, true, false, true), color_type(12, 34, 56)
            );
            font_type train_name_font2(string_type(TETENGO2_TEXT("VWX")), 42, false, true, false, true);

            const font_color_set_type font_color_set2(
                std::move(background_color2),
                std::move(company_line_name_font_color2),
                std::move(note_font_color2),
                std::move(time_line_font_color2),
                std::move(local_station_font_color2),
                std::move(principal_station_font_color2),
                std::move(local_terminal_station_font_color2),
                std::move(principal_terminal_station_font_color2),
                std::move(train_name_font2)
            );

            BOOST_CHECK(font_color_set1 != font_color_set2);
        }
    }

    BOOST_AUTO_TEST_CASE(background)
    {
        BOOST_TEST_PASSPOINT();

        color_type background_color(12, 34, 56);
        font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            std::move(background_color),
            std::move(company_line_name_font_color),
            std::move(note_font_color),
            std::move(time_line_font_color),
            std::move(local_station_font_color),
            std::move(principal_station_font_color),
            std::move(local_terminal_station_font_color),
            std::move(principal_terminal_station_font_color),
            std::move(train_name_font)
        );

        BOOST_CHECK(font_color_set.background() == color_type(12, 34, 56));
    }

    BOOST_AUTO_TEST_CASE(company_line_name)
    {
        BOOST_TEST_PASSPOINT();

        color_type background_color(12, 34, 56);
        font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            std::move(background_color),
            std::move(company_line_name_font_color),
            std::move(note_font_color),
            std::move(time_line_font_color),
            std::move(local_station_font_color),
            std::move(principal_station_font_color),
            std::move(local_terminal_station_font_color),
            std::move(principal_terminal_station_font_color),
            std::move(train_name_font)
        );

        BOOST_CHECK(
            font_color_set.company_line_name() ==
            font_color_type(
                font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
            )
        );
    }

    BOOST_AUTO_TEST_CASE(note)
    {
        BOOST_TEST_PASSPOINT();

        color_type background_color(12, 34, 56);
        font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            std::move(background_color),
            std::move(company_line_name_font_color),
            std::move(note_font_color),
            std::move(time_line_font_color),
            std::move(local_station_font_color),
            std::move(principal_station_font_color),
            std::move(local_terminal_station_font_color),
            std::move(principal_terminal_station_font_color),
            std::move(train_name_font)
        );

        BOOST_CHECK(
            font_color_set.note() ==
            font_color_type(
                font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
            )
        );
    }

    BOOST_AUTO_TEST_CASE(time_line)
    {
        BOOST_TEST_PASSPOINT();

        color_type background_color(12, 34, 56);
        font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            std::move(background_color),
            std::move(company_line_name_font_color),
            std::move(note_font_color),
            std::move(time_line_font_color),
            std::move(local_station_font_color),
            std::move(principal_station_font_color),
            std::move(local_terminal_station_font_color),
            std::move(principal_terminal_station_font_color),
            std::move(train_name_font)
        );

        BOOST_CHECK(
            font_color_set.time_line() ==
            font_color_type(
                font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
            )
        );
    }

    BOOST_AUTO_TEST_CASE(local_station)
    {
        BOOST_TEST_PASSPOINT();

        color_type background_color(12, 34, 56);
        font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            std::move(background_color),
            std::move(company_line_name_font_color),
            std::move(note_font_color),
            std::move(time_line_font_color),
            std::move(local_station_font_color),
            std::move(principal_station_font_color),
            std::move(local_terminal_station_font_color),
            std::move(principal_terminal_station_font_color),
            std::move(train_name_font)
        );

        BOOST_CHECK(
            font_color_set.local_station() ==
            font_color_type(
                font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
            )
        );
    }

    BOOST_AUTO_TEST_CASE(principal_station)
    {
        BOOST_TEST_PASSPOINT();

        color_type background_color(12, 34, 56);
        font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            std::move(background_color),
            std::move(company_line_name_font_color),
            std::move(note_font_color),
            std::move(time_line_font_color),
            std::move(local_station_font_color),
            std::move(principal_station_font_color),
            std::move(local_terminal_station_font_color),
            std::move(principal_terminal_station_font_color),
            std::move(train_name_font)
        );

        BOOST_CHECK(
            font_color_set.principal_station() ==
            font_color_type(
                font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
            )
        );
    }

    BOOST_AUTO_TEST_CASE(local_terminal_station)
    {
        BOOST_TEST_PASSPOINT();

        color_type background_color(12, 34, 56);
        font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            std::move(background_color),
            std::move(company_line_name_font_color),
            std::move(note_font_color),
            std::move(time_line_font_color),
            std::move(local_station_font_color),
            std::move(principal_station_font_color),
            std::move(local_terminal_station_font_color),
            std::move(principal_terminal_station_font_color),
            std::move(train_name_font)
        );

        BOOST_CHECK(
            font_color_set.local_terminal_station() ==
            font_color_type(
                font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
            )
        );
    }

    BOOST_AUTO_TEST_CASE(principal_terminal_station)
    {
        BOOST_TEST_PASSPOINT();

        color_type background_color(12, 34, 56);
        font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            std::move(background_color),
            std::move(company_line_name_font_color),
            std::move(note_font_color),
            std::move(time_line_font_color),
            std::move(local_station_font_color),
            std::move(principal_station_font_color),
            std::move(local_terminal_station_font_color),
            std::move(principal_terminal_station_font_color),
            std::move(train_name_font)
        );

        BOOST_CHECK(
            font_color_set.principal_terminal_station() ==
            font_color_type(
                font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
            )
        );
    }

    BOOST_AUTO_TEST_CASE(train_name)
    {
        BOOST_TEST_PASSPOINT();

        color_type background_color(12, 34, 56);
        font_color_type company_line_name_font_color(
            font_type(string_type(TETENGO2_TEXT("abc")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type note_font_color(
            font_type(string_type(TETENGO2_TEXT("def")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type time_line_font_color(
            font_type(string_type(TETENGO2_TEXT("ghi")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_station_font_color(
            font_type(string_type(TETENGO2_TEXT("jkl")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("mno")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type local_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("pqr")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_color_type principal_terminal_station_font_color(
            font_type(string_type(TETENGO2_TEXT("stu")), 42, false, true, false, true), color_type(12, 34, 56)
        );
        font_type train_name_font(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true);

        const font_color_set_type font_color_set(
            std::move(background_color),
            std::move(company_line_name_font_color),
            std::move(note_font_color),
            std::move(time_line_font_color),
            std::move(local_station_font_color),
            std::move(principal_station_font_color),
            std::move(local_terminal_station_font_color),
            std::move(principal_terminal_station_font_color),
            std::move(train_name_font)
        );

        BOOST_CHECK(
            font_color_set.train_name() == font_type(string_type(TETENGO2_TEXT("vwx")), 42, false, true, false, true)
        );
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
