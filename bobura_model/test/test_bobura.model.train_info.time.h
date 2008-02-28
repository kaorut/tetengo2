/*! \file
    \brief Test of class bobura::model::timetable_info::time.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TIMETABLEINFO_TIME_H)
#define TESTBOBURA_MODEL_TIMETABLEINFO_TIME_H

#include <boost/test/unit_test.hpp>


namespace test_bobura { namespace model { namespace timetable_info
{
    class time
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void swap();

        static void operator_assign();

        static void operator_equal();

        static void station();

        static void meterage();

        static void before();


    };


}}}

#endif
