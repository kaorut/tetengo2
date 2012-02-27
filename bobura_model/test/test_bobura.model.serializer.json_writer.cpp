/*! \file
    \brief Test of class bobura::model::serializer::json_writer.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cstddef>
#include <memory>
#include <ostream>
#include <sstream>
//#include <string>

#include <boost/test/unit_test.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.detail.stub.encoding.h>
#include <tetengo2.text.encoder.h>
#include <tetengo2.text.encoding.locale.h>
#include <tetengo2.unique.h>

#include "bobura.model.message.timetable_observer_set.h"
#include "bobura.model.station.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.timetable.h"
#include "bobura.model.timetable_info.station_location.h"
#include "bobura.model.train.h"
#include "bobura.model.train_info.stop.h"
#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"

#include "bobura.model.serializer.json_writer.h"


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
        bobura::model::serializer::json_writer<
            timetable_type,
            grade_type_set_type,
            std::ostream,
            timetable_file_encoder_type
        >
        writer_type;


    // variables

    const std::string json0 =
        "[\n"
        "    {\n"
        "        \"title\": \"\"\n"
        "    },\n"
        "    [],\n"
        "    [],\n"
        "    []\n"
        "]\n";

    const std::string json1 =
        "[\n"
        "    {\n"
        "        \"title\": \"hoge\"\n"
        "    },\n"
        "    [\n"
        "        { \"name\": \"stationA\", \"grade\": \"local\", \"meterage\": 42 },\n"
        "        { \"name\": \"stationB\", \"grade\": \"principal\", \"meterage\": 4242 }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\": \"101D\",\n"
        "            \"note\": \"fuga\",\n"
        "            \"stops\": [\n"
        "                [    -1,     -1, \"\"],\n"
        "                [    -1,     -1, \"\"]\n"
        "            ]\n"
        "        },\n"
        "        {\n"
        "            \"number\": \"123D\",\n"
        "            \"note\": \"\",\n"
        "            \"stops\": [\n"
        "                [    -1,  60030, \"1\"],\n"
        "                [ 60545,     -1, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ],\n"
        "    [\n"
        "        {\n"
        "            \"number\": \"9324M\",\n"
        "            \"note\": \"piyo\",\n"
        "            \"stops\": [\n"
        "                [    -1,  62000, \"0A\"],\n"
        "                [    -1,     -1, \"\"]\n"
        "            ]\n"
        "        }\n"
        "    ]\n"
        "]\n";


    // functions

    std::unique_ptr<const timetable_type> create_timetable1()
    {
        std::unique_ptr<timetable_type> p_timetable =
            tetengo2::make_unique<timetable_type>();

        p_timetable->set_title("hoge");

        {
            p_timetable->insert_station_location(
                p_timetable->station_locations().end(),
                station_location_type(
                    station_type(
                        "stationA",
                        grade_type_set_type::local_type::instance()
                    ),
                    42
                )
            );
            p_timetable->insert_station_location(
                p_timetable->station_locations().end(),
                station_location_type(
                    station_type(
                        "stationB",
                        grade_type_set_type::principal_type::instance()
                    ),
                    4242
                )
            );
        }
        {
            {
                train_type train("101D", "fuga");
                train.insert_stop(
                    train.stops().end(),
                    stop_type(
                        time_type::uninitialized(),
                        time_type::uninitialized(),
                        ""
                    )
                );
                train.insert_stop(
                    train.stops().end(),
                    stop_type(
                        time_type::uninitialized(),
                        time_type::uninitialized(),
                        ""
                    )
                );
                p_timetable->insert_down_train(
                    p_timetable->down_trains().end(), train
                );
            }
            {
                train_type train("123D", "");
                train.insert_stop(
                    train.stops().end(),
                    stop_type(
                        time_type::uninitialized(),
                        time_type( 6, 0, 30),
                        "1"
                    )
                );
                train.insert_stop(
                    train.stops().end(),
                    stop_type(
                        time_type(6, 5, 45),
                        time_type::uninitialized(),
                        ""
                    )
                );
                p_timetable->insert_down_train(
                    p_timetable->down_trains().end(), train
                );
            }
        }
        {
            {
                train_type train("9324M", "piyo");
                train.insert_stop(
                    train.stops().end(),
                    stop_type(
                        time_type::uninitialized(),
                        time_type(6, 20, 0),
                        "0A"
                    )
                );
                train.insert_stop(
                    train.stops().end(),
                    stop_type(
                        time_type::uninitialized(),
                        time_type::uninitialized(),
                        ""
                    )
                );
                p_timetable->insert_up_train(
                    p_timetable->up_trains().end(), train
                );
            }
        }
        return std::move(p_timetable);
    }


}

BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(json_writer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const writer_type json_writer;
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        {
            writer_type json_writer;

            const timetable_type timetable;
            std::ostringstream stream;

            json_writer.write(timetable, stream);

            const std::string result = stream.str();
            BOOST_CHECK(result == json0);
        }
        {
            writer_type json_writer;

            const std::unique_ptr<const timetable_type> p_timetable =
                create_timetable1();
            std::ostringstream stream;

            json_writer.write(*p_timetable, stream);

            const std::string result = stream.str();
            BOOST_CHECK(result == json1);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
