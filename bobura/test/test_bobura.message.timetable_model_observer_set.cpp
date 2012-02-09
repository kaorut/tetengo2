/*! \file
    \brief Test of class bobura::message::timetable_model_observer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <cstddef>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.model.message.timetable_observer_set.h"
#include "bobura.model.station.h"
#include "bobura.model.train.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.timetable.h"
#include "bobura.model.timetable_info.station_location.h"
#include "bobura.model.train_info.stop.h"
#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"

#include "bobura.message.timetable_model_observer_set.h"


namespace
{
    // types

    typedef
        bobura::model::station_info::grade_type_set<std::wstring>
        station_grade_type_set_type;

    typedef station_grade_type_set_type::grade_type grade_type;

    typedef station_grade_type_set_type::local_type local_type;

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
        bobura::message::timetable_model_observer_set<
            timetable_type, boost::filesystem::path
        >
        timetable_model_observer_set_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(timetable_model_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(reset)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_model_observer_set_type observer_set;

            observer_set.reset();
        }
        {
            timetable_model_observer_set_type observer_set;

            observer_set.reset();
        }
    }

    BOOST_AUTO_TEST_CASE(changed)
    {
        BOOST_TEST_PASSPOINT();

        {
            const timetable_model_observer_set_type observer_set;

            observer_set.changed();
        }
        {
            timetable_model_observer_set_type observer_set;

            observer_set.changed();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
