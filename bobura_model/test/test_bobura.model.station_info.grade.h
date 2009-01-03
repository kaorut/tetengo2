/*! \file
    \brief Test of class bobura::model::station_info::grade.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_STATIONINFO_GRADE_H)
#define TESTBOBURA_MODEL_STATIONINFO_GRADE_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_bobura { namespace model { namespace station_info
{
    class grade
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void instance();

        static void name();


    };


}}}

#endif
