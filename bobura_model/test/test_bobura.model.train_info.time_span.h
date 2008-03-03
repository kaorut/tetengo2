/*! \file
    \brief Test of class bobura::model::train_info::time_span.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TRAININFO_TIMESPAN_H)
#define TESTBOBURA_MODEL_TRAININFO_TIMESPAN_H

#include <boost/test/unit_test.hpp>


namespace test_bobura { namespace model { namespace train_info
{
    class time_span
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void swap();

        static void operator_assign();

        static void operator_equal();

        static void seconds();

        static void hours_minutes_seconds();


    };


}}}

#endif
