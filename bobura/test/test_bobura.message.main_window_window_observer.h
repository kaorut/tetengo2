/*! \file
    \brief Test of class bobura::message::main_window_window_observer.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MESSAGE_MAINWINDOWWINDOWOBSERVER_H)
#define TESTBOBURA_MESSAGE_MAINWINDOWWINDOWOBSERVER_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_bobura { namespace message
{
    class main_window_window_observer
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void destroyed();


    };


}}

#endif
