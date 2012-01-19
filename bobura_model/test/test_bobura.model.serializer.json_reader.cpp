/*! \file
    \brief Test of class bobura::model::serializer::json_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cstddef>
//#include <memory>
#include <string>

#include <boost/test/unit_test.hpp>

#include <tetengo2.cpp11.h>

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

    typedef bobura::model::station_info::local<std::wstring> local_type;
    typedef bobura::model::station<std::wstring, local_type> station_type;
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
        bobura::model::serializer::json_reader<timetable_type> reader_type;


    // variables

    const std::string json0;


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
            std::istringstream input_stream(json0);
            const std::unique_ptr<timetable_type> p_timetable =
                json_reader.read(input_stream);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
