/*! \file
    \brief Test of class bobura::model::serializer::json_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cstddef>
//#include <memory>
//#include <string>

#include <boost/test/unit_test.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.detail.stub.encoding.h>
#include <tetengo2.text.encoder.h>
#include <tetengo2.text.encoding.locale.h>
#include <tetengo2.text.grammar.json.h>
#include <tetengo2.text.pull_parser.h>
#include <tetengo2.text.push_parser.h>

#include "bobura.model.message.timetable_observer_set.h"
#include "bobura.model.station.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.timetable.h"
#include "bobura.model.timetable_info.station_location.h"
#include "bobura.model.train.h"
#include "bobura.model.train_info.stop.h"
#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"

#include "bobura.model.serializer.json_reader.h"


namespace
{
    // types

    typedef
        bobura::model::station_info::grade_type_set<std::string>
        station_grade_type_set_type;

    typedef station_grade_type_set_type::grade_type grade_type;

    typedef bobura::model::station<std::string, grade_type> station_type;

    typedef
        bobura::model::timetable_info::station_location<
            station_type, std::size_t
        >
        station_location_type;

    typedef
        bobura::model::train_info::time<
            std::size_t, bobura::model::train_info::time_span<std::ptrdiff_t>
        >
        time_type;

    typedef bobura::model::train_info::stop<time_type, std::string> stop_type;

    typedef
        bobura::model::train<std::string, std::string, stop_type> train_type;

    typedef
        bobura::model::timetable<
            std::string,
            station_location_type,
            train_type,
            bobura::model::message::timetable_observer_set
        >
        timetable_type;

    typedef
        bobura::model::station_info::grade_type_set<std::string>
        grade_type_set_type;

    typedef
        tetengo2::text::grammar::json<std::string::const_iterator>
        grammar_type;

    typedef
        tetengo2::text::push_parser<
            std::string::const_iterator, grammar_type, int, double
        >
        push_parser_type;

    typedef
        tetengo2::text::pull_parser<push_parser_type, std::size_t>
        pull_parser_type;

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::text::encoding::locale<std::string, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::text::encoding::locale<std::string, encoding_details_type>
        timetable_file_encoding_type;

    typedef
        tetengo2::text::encoder<
            internal_encoding_type, timetable_file_encoding_type
        >
        timetable_file_encoder_type;

    typedef
        bobura::model::serializer::json_reader<
            timetable_type,
            grade_type_set_type,
            pull_parser_type,
            timetable_file_encoder_type
        >
        reader_type;


    // variables

    const std::string json0;

    const std::string json1 =
        "[]";

    const std::string json2 =
        "[\n"
        "    {\n"
        "    },\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n";

    const std::string json3 =
        "[\n"
        "    {\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n";

    const std::string json4 =
        "[\n"
        "    {\n"
        "        \"piyo\":  \"piyopiyo\",\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [\n"
        "        {\n"
        "            \"name\":     \"stationA\",\n"
        "            \"grade\":    \"local\",\n"
        "            \"meterage\": 42\n"
        "        },\n"
        "        {\n"
        "            \"name\":     \"stationB\",\n"
        "            \"grade\":    \"principal\",\n"
        "            \"meterage\": 4242\n"
        "        }\n"
        "    ],\n"
        "    [],\n"
        "    []\n"
        "]\n";

    const std::string json5 =
        "[\n"
        "    {\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [\n"
        "        {\n"
        "            \"name\":     \"stationA\",\n"
        "            \"grade\":    \"hoge\",\n"
        "            \"meterage\": 42\n"
        "        }\n"
        "    ],\n"
        "    [],\n"
        "    []\n"
        "]\n";

    const std::string json6 =
        "[\n"
        "    {\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [\n"
        "        {\n"
        "            \"name\":     \"stationA\",\n"
        "            \"grade\":    \"local\",\n"
        "            \"meterage\": 42\n"
        "        },\n"
        "        {\n"
        "            \"name\":     \"stationB\",\n"
        "            \"grade\":    \"principal\",\n"
        "            \"meterage\": 4242\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\": \"101D\",\n"
        "            \"note\":   \"fuga\",\n"
        "            \"stops\":  []\n"
        "        },\n"
        "        {\n"
        "            \"number\": \"123D\",\n"
        "            \"note\":   \"\",\n"
        "            \"stops\":  [\n"
        "                [    -1,  60030, \"1\"],\n"
        "                [ 60545,     -1, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\": \"9324M\",\n"
        "            \"note\":   \"piyo\",\n"
        "            \"stops\":  [\n"
        "                [  -1,  62000, \"0A\"]\n"
        "            ]\n"
        "        }\n"
        "    ]\n"
        "]\n";

    const std::string json7 =
        "[\n"
        "    {\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [\n"
        "        {\n"
        "            \"name\":     \"stationA\",\n"
        "            \"grade\":    \"local\",\n"
        "            \"meterage\": 42\n"
        "        },\n"
        "        {\n"
        "            \"name\":     \"stationB\",\n"
        "            \"grade\":    \"principal\",\n"
        "            \"meterage\": 4242\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\": \"123D\",\n"
        "            \"note\":   \"\",\n"
        "            \"stops\":  [\n"
        "                [    -1,  66030, \"1\"],\n"
        "                [ 60545,     -1, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    []\n"
        "]\n";

    const std::string json8 =
        "[\n"
        "    {\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [\n"
        "        {\n"
        "            \"name\":     \"stationA\",\n"
        "            \"grade\":    \"local\",\n"
        "            \"meterage\": 42\n"
        "        },\n"
        "        {\n"
        "            \"name\":     \"stationB\",\n"
        "            \"grade\":    \"principal\",\n"
        "            \"meterage\": 4242\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\": \"123D\",\n"
        "            \"note\":   \"\",\n"
        "            \"stops\":  [\n"
        "                [    -1,  60030, \"1\"],\n"
        "                [ 60230,  60315, \"\"],\n"
        "                [ 60545,     -1, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    []\n"
        "]\n";


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

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        reader_type json_reader;
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json0.begin(), json0.end());

            BOOST_CHECK(!p_timetable);
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json1.begin(), json1.end());

            BOOST_CHECK(!p_timetable);
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json2.begin(), json2.end());

            BOOST_CHECK(p_timetable);
            BOOST_CHECK(p_timetable->title().empty());
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json3.begin(), json3.end());

            BOOST_CHECK(p_timetable);
            BOOST_CHECK(p_timetable->title() == "hoge");
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json4.begin(), json4.end());

            BOOST_CHECK(p_timetable);
            BOOST_CHECK(p_timetable->title() == "hoge");
            BOOST_CHECK_EQUAL(p_timetable->station_locations().size(), 2U);
            {
                const station_location_type& station_location =
                    p_timetable->station_locations()[0];
                const station_type& station = station_location.station();
                BOOST_CHECK(station.name() == "stationA");
                BOOST_CHECK(station.grade().name() == "local");
                BOOST_CHECK_EQUAL(station_location.meterage(), 42U);
            }
            {
                const station_location_type& station_location =
                    p_timetable->station_locations()[1];
                const station_type& station = station_location.station();
                BOOST_CHECK(station.name() == "stationB");
                BOOST_CHECK(station.grade().name() == "principal");
                BOOST_CHECK_EQUAL(station_location.meterage(), 4242U);
            }
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json5.begin(), json5.end());

            BOOST_CHECK(!p_timetable);
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json6.begin(), json6.end());

            BOOST_CHECK(p_timetable);
            BOOST_CHECK_EQUAL(p_timetable->down_trains().size(), 2U);
            {
                const train_type& train = p_timetable->down_trains()[0];
                BOOST_CHECK(train.number() == "101D");
                BOOST_CHECK(train.note() == "fuga");
                const train_type::stops_type& stops = train.stops();
                BOOST_CHECK_EQUAL(train.stops().size(), 2U);
                {
                    const stop_type& stop = stops[0];
                    BOOST_CHECK(stop.arrival() == time_type::uninitialized());
                    BOOST_CHECK(
                        stop.departure() == time_type::uninitialized()
                    );
                    BOOST_CHECK(stop.platform().empty());
                }
                {
                    const stop_type& stop = stops[1];
                    BOOST_CHECK(stop.arrival() == time_type::uninitialized());
                    BOOST_CHECK(
                        stop.departure() == time_type::uninitialized()
                    );
                    BOOST_CHECK(stop.platform().empty());
                }
            }
            {
                const train_type& train = p_timetable->down_trains()[1];
                BOOST_CHECK(train.number() == "123D");
                BOOST_CHECK(train.note().empty());
                const train_type::stops_type& stops = train.stops();
                BOOST_CHECK_EQUAL(train.stops().size(), 2U);
                {
                    const stop_type& stop = stops[0];
                    BOOST_CHECK(stop.arrival() == time_type::uninitialized());
                    BOOST_CHECK(stop.departure() == time_type(6, 0, 30));
                    BOOST_CHECK(stop.platform() == "1");
                }
                {
                    const stop_type& stop = stops[1];
                    BOOST_CHECK(stop.arrival() == time_type(6, 5, 45));
                    BOOST_CHECK(
                        stop.departure() == time_type::uninitialized()
                    );
                    BOOST_CHECK(stop.platform().empty());
                }
            }
            BOOST_CHECK_EQUAL(p_timetable->up_trains().size(), 1U);
            {
                const train_type& train = p_timetable->up_trains()[0];
                BOOST_CHECK(train.number() == "9324M");
                BOOST_CHECK(train.note() == "piyo");
                const train_type::stops_type& stops = train.stops();
                BOOST_CHECK_EQUAL(train.stops().size(), 2U);
                {
                    const stop_type& stop = stops[0];
                    BOOST_CHECK(stop.arrival() == time_type::uninitialized());
                    BOOST_CHECK(stop.departure() == time_type(6, 20, 0));
                    BOOST_CHECK(stop.platform() == "0A");
                }
                {
                    const stop_type& stop = stops[1];
                    BOOST_CHECK(stop.arrival() == time_type::uninitialized());
                    BOOST_CHECK(
                        stop.departure() == time_type::uninitialized()
                    );
                    BOOST_CHECK(stop.platform().empty());
                }
            }
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json7.begin(), json7.end());

            BOOST_CHECK(!p_timetable);
        }
        {
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(json8.begin(), json8.end());

            BOOST_CHECK(!p_timetable);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
