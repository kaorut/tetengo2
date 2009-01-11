/*! \file
    \brief Test of class bobura::settings.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_SETTINGS_H)
#define TESTBOBURA_SETTINGS_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_bobura
{
    class settings
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();


    };


}

#endif
