/*! \file
    \brief Test of class bobura::type_list.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_TYPELIST_H)
#define TESTBOBURA_TYPELIST_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_bobura
{
    class type_list
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void options();

        static void construction();


    };


}

#endif
