/*! \file
    \brief Test of class bobura::model::serializer::json_reader.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

//#include <iterator>
//#include <sstream>
//#include <string>

//#include <boost/mpl/at.hpp>
//#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.model.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::station>::type
        station_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::station_location>::type
        station_location_type;

    typedef boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::time>::type time_type;

    typedef boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::stop>::type stop_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::train>::type train_type;

    typedef
        boost::mpl::at<test_bobura::model::model_type_list, test_bobura::model::type::model::timetable>::type
        timetable_type;

    typedef timetable_type::font_color_set_type font_color_set_type;
    
    typedef font_color_set_type::font_color_type font_color_type;

    typedef font_color_type::font_type font_type;

    typedef font_color_type::color_type color_type;

    typedef boost::mpl::at<test_bobura::model::type_list, test_bobura::model::type::string>::type string_type;

    typedef
        boost::mpl::at<
            test_bobura::model::serialization_type_list, test_bobura::model::type::serialization::json_reader
        >::type
        reader_type;

    typedef reader_type::error_type error_type;


    // variables

    const std::string json_empty0;

    const std::string json_empty1(
        "[]"
    );

    const std::string json_empty2(
        "[\n"
        "    {\n"
        "    },\n"
        "    {},\n"
        "    [],\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n"
    );

    const std::string json_line_name_only(
        "[\n"
        "    {\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [],\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n"
    );

    const std::string json_station_only(
        "[\n"
        "    {\n"
        "        \"piyo\":      \"piyopiyo\",\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   true,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        },\n"
        "        {\n"
        "            \"name\":                    \"stationB\",\n"
        "            \"grade\":                   \"principal\",\n"
        "            \"show_down_arrival_times\": true,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteB\",\n"
        "            \"operating_distance\":      42420\n"
        "        }\n"
        "    ],\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n"
    );

    const std::string json_invalid_station_grade(
        "[\n"
        "    {\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"hoge\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        }\n"
        "    ],\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n"
    );

    const std::string json_full_content(
        "[\n"
        "    {\n"
        "        \"company_name\": \"hoge\",\n"
        "        \"line_name\": \"fuga\",\n"
        "        \"note\": \"piyo\"\n"
        "    },\n"
        "    {\n"
        "        \"background\":                 \"ABCDEF\",\n"
        "        \"company_line_name\":          [[\"hogefont\", 42, false, true, false, true], \"ABCDEF\"],\n"
        "        \"note\":                       [[\"hogefont\", 42, false, true, false, true], \"ABCDEF\"],\n"
        "        \"time_line\":                  [[\"hogefont\", 42, false, true, false, true], \"ABCDEF\"],\n"
        "        \"local_station\":              [[\"hogefont\", 42, false, true, false, true], \"ABCDEF\"],\n"
        "        \"principal_station\":          [[\"hogefont\", 42, false, true, false, true], \"ABCDEF\"],\n"
        "        \"local_terminal_station\":     [[\"hogefont\", 42, false, true, false, true], \"ABCDEF\"],\n"
        "        \"principal_terminal_station\": [[\"hogefont\", 42, false, true, false, true], \"ABCDEF\"],\n"
        "        \"train_name\":                 [\"hogefont\", 42, false, true, false, true]\n"
        "    },\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        },\n"
        "        {\n"
        "            \"name\":                    \"stationB\",\n"
        "            \"grade\":                   \"principal\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteB\",\n"
        "            \"operating_distance\":      42420\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"name\":         \"nameA\",\n"
        "            \"abbreviation\": \"abbrA\",\n"
        "            \"color\":        \"ABCDEF\",\n"
        "            \"weight\":       0,\n"
        "            \"line_style\":   1\n"
        "        },\n"
        "        {\n"
        "            \"name\":         \"nameB\",\n"
        "            \"abbreviation\": \"abbrB\",\n"
        "            \"color\":        \"ABCDEF\",\n"
        "            \"weight\":       0,\n"
        "            \"line_style\":   1\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\":      \"101D\",\n"
        "            \"kind_index\":  0,\n"
        "            \"name\":        \"foo\",\n"
        "            \"name_number\": \"bar\",\n"
        "            \"note\":        \"fuga\",\n"
        "            \"stops\":       []\n"
        "        },\n"
        "        {\n"
        "            \"number\":      \"123D\",\n"
        "            \"kind_index\":  1,\n"
        "            \"name\":        \"baz\",\n"
        "            \"name_number\": \"bazz\",\n"
        "            \"note\":        \"\",\n"
        "            \"stops\":       [\n"
        "                [    -1,  60030,  true, \"1\"],\n"
        "                [ 60545,     -1, false, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\":      \"9324M\",\n"
        "            \"kind_index\":  0,\n"
        "            \"name\":        \"abc\",\n"
        "            \"name_number\": \"def\",\n"
        "            \"note\":        \"piyo\",\n"
        "            \"stops\":       [\n"
        "                [  -1,  62000, false, \"0A\"]\n"
        "            ]\n"
        "        }\n"
        "    ]\n"
        "]\n"
    );

    const std::string json_invalid_stop_time(
        "[\n"
        "    {\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        },\n"
        "        {\n"
        "            \"name\":                    \"stationB\",\n"
        "            \"grade\":                   \"principal\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteB\",\n"
        "            \"operating_distance\":      42420\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"name\":         \"nameA\",\n"
        "            \"abbreviation\": \"abbrA\",\n"
        "            \"color\":        \"ABCDEF\",\n"
        "            \"weight\":       0,\n"
        "            \"line_style\":   1\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\":      \"123D\",\n"
        "            \"kind_index\":  0,\n"
        "            \"name\":        \"foo\",\n"
        "            \"name_number\": \"bar\",\n"
        "            \"note\":        \"\",\n"
        "            \"stops\":       [\n"
        "                [    -1,  66030,  true, \"1\"],\n"
        "                [ 60545,     -1, false, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    []\n"
        "]\n"
    );

    const std::string json_too_many_stops(
        "[\n"
        "    {\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        },\n"
        "        {\n"
        "            \"name\":                    \"stationB\",\n"
        "            \"grade\":                   \"principal\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteB\",\n"
        "            \"operating_distance\":      42420\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"name\":         \"nameA\",\n"
        "            \"abbreviation\": \"abbrA\",\n"
        "            \"color\":        \"ABCDEF\",\n"
        "            \"weight\":       0,\n"
        "            \"line_style\":   1\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\":      \"123D\",\n"
        "            \"kind_index\":  0,\n"
        "            \"name\":        \"foo\",\n"
        "            \"name_number\": \"bar\",\n"
        "            \"note\":        \"\",\n"
        "            \"stops\":       [\n"
        "                [    -1,  60030,  true, \"1\"],\n"
        "                [ 60230,  60315, false, \"\"],\n"
        "                [ 60545,     -1, false, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    []\n"
        "]\n"
    );

    const std::string json_white_space_before_start_element(
        "    \t    \n    []\n"
    );

    const std::string json_not_json(
        "hoge\n"
    );

    const std::string json_invalid_time_format(
        "[\n"
        "    {\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        },\n"
        "        {\n"
        "            \"name\":                    \"stationB\",\n"
        "            \"grade\":                   \"principal\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteB\",\n"
        "            \"operating_distance\":      42420\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"name\":         \"nameA\",\n"
        "            \"abbreviation\": \"abbrA\",\n"
        "            \"color\":        \"ABCDEF\",\n"
        "            \"weight\":       0,\n"
        "            \"line_style\":   1\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\":      \"123D\",\n"
        "            \"kind_index\":  0,\n"
        "            \"name\":        \"foo\",\n"
        "            \"name_number\": \"bar\",\n"
        "            \"note\":        \"\",\n"
        "            \"stops\":       [\n"
        "                [    -1, 235000,  true, \"1\"],\n"
        "                [ 01000,     -1, false, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    []\n"
        "]\n"
    );

    const std::string json_train_with_no_stop(
        "[\n"
        "    {\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        },\n"
        "        {\n"
        "            \"name\":                    \"stationB\",\n"
        "            \"grade\":                   \"principal\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteB\",\n"
        "            \"operating_distance\":      42420\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"name\":         \"nameA\",\n"
        "            \"abbreviation\": \"abbrA\",\n"
        "            \"color\":        \"ABCDEF\",\n"
        "            \"weight\":       0,\n"
        "            \"line_style\":   1\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\":      \"101D\",\n"
        "            \"kind_index\":  0,\n"
        "            \"name_number\": \"bar\",\n"
        "            \"name\":        \"foo\",\n"
        "            \"note\":        \"fuga\",\n"
        "            \"stops\":       []\n"
        "        }\n"
        "    ],\n"
        "    []\n"
        "]\n"
    );

    const std::string json_invalid_kind_index(
        "[\n"
        "    {\n"
        "        \"line_name\": \"hoge\"\n"
        "    },\n"
        "    {},\n"
        "    [\n"
        "        {\n"
        "            \"name\":                    \"stationA\",\n"
        "            \"grade\":                   \"local\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteA\",\n"
        "            \"operating_distance\":      420\n"
        "        },\n"
        "        {\n"
        "            \"name\":                    \"stationB\",\n"
        "            \"grade\":                   \"principal\",\n"
        "            \"show_down_arrival_times\": false,\n"
        "            \"show_up_arrival_times\":   false,\n"
        "            \"note\":                    \"noteB\",\n"
        "            \"operating_distance\":      42420\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"name\":         \"nameA\",\n"
        "            \"abbreviation\": \"abbrA\",\n"
        "            \"color\":        \"ABCDEF\",\n"
        "            \"weight\":       0,\n"
        "            \"line_style\":   1\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\":      \"101D\",\n"
        "            \"kind_index\":  1,\n"
        "            \"name\":        \"foo\",\n"
        "            \"name_number\": \"bar\",\n"
        "            \"note\":        \"fuga\",\n"
        "            \"stops\":       []\n"
        "        }\n"
        "    ],\n"
        "    []\n"
        "]\n"
    );

}

BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(json_reader)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const reader_type json_reader;
    }

    BOOST_AUTO_TEST_CASE(selects)
    {
        BOOST_TEST_PASSPOINT();

        reader_type json_reader;
        {
            std::istringstream input_stream(json_empty0);
            BOOST_CHECK(
                !json_reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
        {
            std::istringstream input_stream(json_empty1);
            BOOST_CHECK(
                json_reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
        {
            std::istringstream input_stream(json_empty2);
            BOOST_CHECK(
                json_reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
        {
            std::istringstream input_stream(json_white_space_before_start_element);
            BOOST_CHECK(
                json_reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
        {
            std::istringstream input_stream(json_not_json);
            BOOST_CHECK(
                !json_reader.selects(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>())
                )
            );
        }
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        reader_type json_reader;
        {
            std::istringstream input_stream(json_not_json);
            auto error = error_type::none;
            const auto p_timetable =
                json_reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            std::istringstream input_stream(json_empty1);
            auto error = error_type::none;
            const auto p_timetable =
                json_reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            std::istringstream input_stream(json_empty2);
            auto error = error_type::none;
            const auto p_timetable =
                json_reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(p_timetable);
            BOOST_CHECK(error == error_type::none);
            BOOST_CHECK(p_timetable->line_name().empty());
        }
        {
            std::istringstream input_stream(json_line_name_only);
            auto error = error_type::none;
            const auto p_timetable =
                json_reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(p_timetable);
            BOOST_CHECK(error == error_type::none);
            BOOST_CHECK(p_timetable->line_name() == string_type(TETENGO2_TEXT("hoge")));
        }
        {
            std::istringstream input_stream(json_station_only);
            auto error = error_type::none;
            const auto p_timetable =
                json_reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(p_timetable);
            BOOST_CHECK(error == error_type::none);
            BOOST_CHECK(p_timetable->line_name() == string_type(TETENGO2_TEXT("hoge")));
            BOOST_REQUIRE_EQUAL(p_timetable->station_locations().size(), 2U);
            {
                const auto& station_location = p_timetable->station_locations()[0];
                const auto& station = station_location.station();
                BOOST_CHECK(station.name() == string_type(TETENGO2_TEXT("stationA")));
                BOOST_CHECK(station.grade().name() == string_type(TETENGO2_TEXT("local")));
                BOOST_CHECK(!station.shows_down_arrival_times());
                BOOST_CHECK(station.shows_up_arrival_times());
                BOOST_CHECK(station.note() == string_type(TETENGO2_TEXT("noteA")));
                BOOST_CHECK_EQUAL(station_location.operating_distance(), 42U);
            }
            {
                const auto& station_location = p_timetable->station_locations()[1];
                const auto& station = station_location.station();
                BOOST_CHECK(station.name() == string_type(TETENGO2_TEXT("stationB")));
                BOOST_CHECK(station.grade().name() == string_type(TETENGO2_TEXT("principal")));
                BOOST_CHECK(station.shows_down_arrival_times());
                BOOST_CHECK(!station.shows_up_arrival_times());
                BOOST_CHECK(station.note() == string_type(TETENGO2_TEXT("noteB")));
                BOOST_CHECK_EQUAL(station_location.operating_distance(), 4242U);
            }
        }
        {
            std::istringstream input_stream(json_invalid_station_grade);
            auto error = error_type::none;
            const auto p_timetable =
                json_reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            std::istringstream input_stream(json_full_content);
            auto error = error_type::none;
            const auto p_timetable =
                json_reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(p_timetable);
            BOOST_CHECK(error == error_type::none);

            BOOST_CHECK(p_timetable->company_name() == string_type(TETENGO2_TEXT("hoge")));
            BOOST_CHECK(p_timetable->line_name() == string_type(TETENGO2_TEXT("fuga")));
            BOOST_CHECK(p_timetable->note() == string_type(TETENGO2_TEXT("piyo")));

            {
                const auto& font_color_set = p_timetable->font_color_set();

                BOOST_CHECK(font_color_set.background() == color_type(0xAB, 0xCD, 0xEF));
                BOOST_CHECK(
                    font_color_set.company_line_name() ==
                    font_color_type(
                        font_type(string_type(TETENGO2_TEXT("hogefont")), 42, false, true, false, true),
                        color_type(0xAB, 0xCD, 0xEF)
                    )
                );
                BOOST_CHECK(
                    font_color_set.train_name() ==
                    font_type(string_type(TETENGO2_TEXT("hogefont")), 42, false, true, false, true)
                );
            }

            BOOST_REQUIRE_EQUAL(p_timetable->down_trains().size(), 2U);
            {
                const auto& train = p_timetable->down_trains()[0];
                BOOST_CHECK(train.number() == string_type(TETENGO2_TEXT("101D")));
                BOOST_CHECK(train.note() == string_type(TETENGO2_TEXT("fuga")));
                const auto& stops = train.stops();
                BOOST_REQUIRE_EQUAL(train.stops().size(), 2U);
                {
                    const auto& stop = stops[0];
                    BOOST_CHECK(!stop.arrival().initialized());
                    BOOST_CHECK(!stop.departure().initialized());
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
                {
                    const auto& stop = stops[1];
                    BOOST_CHECK(!stop.arrival().initialized());
                    BOOST_CHECK(!stop.departure().initialized());
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
            }
            {
                const auto& train = p_timetable->down_trains()[1];
                BOOST_CHECK(train.number() == string_type(TETENGO2_TEXT("123D")));
                BOOST_CHECK(train.note().empty());
                const auto& stops = train.stops();
                BOOST_REQUIRE_EQUAL(train.stops().size(), 2U);
                {
                    const auto& stop = stops[0];
                    BOOST_CHECK(!stop.arrival().initialized());
                    BOOST_CHECK(stop.departure() == time_type(6, 0, 30));
                    BOOST_CHECK(stop.operational());
                    BOOST_CHECK(stop.platform() == string_type(TETENGO2_TEXT("1")));
                }
                {
                    const auto& stop = stops[1];
                    BOOST_CHECK(stop.arrival() == time_type(6, 5, 45));
                    BOOST_CHECK(!stop.departure().initialized());
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
            }
            BOOST_REQUIRE_EQUAL(p_timetable->up_trains().size(), 1U);
            {
                const auto& train = p_timetable->up_trains()[0];
                BOOST_CHECK(train.number() == string_type(TETENGO2_TEXT("9324M")));
                BOOST_CHECK(train.note() == string_type(TETENGO2_TEXT("piyo")));
                const auto& stops = train.stops();
                BOOST_REQUIRE_EQUAL(train.stops().size(), 2U);
                {
                    const auto& stop = stops[0];
                    BOOST_CHECK(!stop.arrival().initialized());
                    BOOST_CHECK(stop.departure() == time_type(6, 20, 0));
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform() == string_type(TETENGO2_TEXT("0A")));
                }
                {
                    const auto& stop = stops[1];
                    BOOST_CHECK(!stop.arrival().initialized());
                    BOOST_CHECK(!stop.departure().initialized());
                    BOOST_CHECK(!stop.operational());
                    BOOST_CHECK(stop.platform().empty());
                }
            }
        }
        {
            std::istringstream input_stream(json_invalid_stop_time);
            auto error = error_type::none;
            const auto p_timetable =
                json_reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            std::istringstream input_stream(json_too_many_stops);
            auto error = error_type::none;
            const auto p_timetable =
                json_reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            std::istringstream input_stream(json_invalid_time_format);
            auto error = error_type::none;
            const auto p_timetable =
                json_reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            std::istringstream input_stream(json_train_with_no_stop);
            auto error = error_type::none;
            const auto p_timetable =
                json_reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
        {
            std::istringstream input_stream(json_invalid_kind_index);
            auto error = error_type::none;
            const auto p_timetable =
                json_reader.read(
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>(input_stream)),
                    boost::spirit::make_default_multi_pass(std::istreambuf_iterator<char>()),
                    error
                );

            BOOST_REQUIRE(!p_timetable);
            BOOST_CHECK(error == error_type::corrupted);
        }
    }

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
