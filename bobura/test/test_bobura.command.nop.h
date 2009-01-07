/*! \file
    \brief Test of class bobura::command::nop.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_COMMAND_NOP_H)
#define TESTBOBURA_COMMAND_NOP_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_bobura { namespace command
{
    class nop
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void operator_paren();


    };


}}

#endif
