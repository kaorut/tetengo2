/*! \file
    \brief Test of class bobura::model::serializer::writer.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <cstddef>
#include <ostream>
#include <sstream>
#include <string>

#include <boost/test/unit_test.hpp>

#include <tetengo2.cpp11.h>

#include "bobura.model.message.timetable_observer_set.h"
#include "bobura.model.station.h"
#include "bobura.model.train.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.timetable.h"
#include "bobura.model.timetable_info.station_location.h"
#include "bobura.model.train_info.stop.h"
#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"

#include "bobura.model.serializer.writer.h"


namespace
{
    // types

    typedef
        bobura::model::station_info::grade_type_set<std::wstring>
        grade_type_set_type;

    typedef grade_type_set_type::grade_type grade_type;

    typedef bobura::model::station<std::wstring, grade_type> station_type;

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
        bobura::model::serializer::writer<std::ostream, timetable_type>
        writer_type;

    class concrete_writer : public writer_type
    {
    public:
        concrete_writer()
        :
        writer_type()
        {}

        virtual ~concrete_writer()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        virtual void write_impl(
            const timetable_type& timetable,
            output_stream_type&   output_stream
        )
        {}


    };

}

BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(model)
BOOST_AUTO_TEST_SUITE(serializer)
BOOST_AUTO_TEST_SUITE(writer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_writer writer;
    }

    BOOST_AUTO_TEST_CASE(read)
    {
        BOOST_TEST_PASSPOINT();

        concrete_writer writer;
        const timetable_type timetable;
        std::ostringstream stream;
        writer.write(timetable, stream);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
