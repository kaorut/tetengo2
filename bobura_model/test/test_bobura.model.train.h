/*! \file
    \brief Test of class bobura::model::train.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TRAIN_H)
#define TESTBOBURA_MODEL_TRAIN_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_bobura { namespace model
{
    class train
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void swap();

        static void operator_assign();

        static void operator_equal();

        static void number();

        static void note();

        static void stops();

        static void insert_stop();

        static void erase_stops();


    };


}}

#endif
