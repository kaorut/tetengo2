/*! \file
    \brief Test of class bobura::model::timetable.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TIMETABLE_H)
#define TESTBOBURA_MODEL_TIMETABLE_H

#include <boost/test/unit_test.hpp>


namespace test_bobura { namespace model
{
    class timetable
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void swap();

        static void operator_assign();

        static void operator_equal();

        static void stations_and_meters();

        static void insert_station_and_meters();


    };


}}

#endif
