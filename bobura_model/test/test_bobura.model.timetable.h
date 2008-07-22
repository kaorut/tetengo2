/*! \file
    \brief Test of class bobura::model::timetable.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TIMETABLE_H)
#define TESTBOBURA_MODEL_TIMETABLE_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


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

        static void station_locations();

        static void insert_station_location();

        static void erase_station_locations();

        static void trains();

        static void insert_train();

        static void erase_trains();


    };


}}

#endif
