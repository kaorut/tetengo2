/*! \file
    \brief Test of class bobura::model::train_info::time.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TRAININFO_TIME_H)
#define TESTBOBURA_MODEL_TRAININFO_TIME_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_bobura { namespace model { namespace train_info
{
    class time
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void uninitialized();

        static void construction();

        static void swap();

        static void operator_assign();

        static void operator_plus_assign();

        static void operator_minus_assign();

        static void operator_minus();

        static void operator_equal();

        static void operator_less_than();

        static void seconds_from_midnight();

        static void hours_minutes_seconds();


    };


}}}

#endif
