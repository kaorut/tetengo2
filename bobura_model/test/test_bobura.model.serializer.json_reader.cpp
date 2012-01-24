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

    typedef bobura::model::station_info::local<std::string> local_type;

    typedef bobura::model::station<std::string, local_type> station_type;

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
            std::string, station_location_type, train_type
        >
        timetable_type;

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
            local_type,
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
        "    []\n"
        "]\n";

    const std::string json3 =
        "[\n"
        "    {\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [\n"
        "    ]\n"
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
        "    ]\n"
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
            BOOST_CHECK(
                p_timetable->station_locations()[0].station().name() ==
                "stationA"
            );
            BOOST_CHECK(
                p_timetable->station_locations()[1].station().name() ==
                "stationB"
            );
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
