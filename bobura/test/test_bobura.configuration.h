/*! \file
    \brief Test of class bobura::configuration.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_CONFIGURATION_H)
#define TESTBOBURA_CONFIGURATION_H

#include <boost/test/unit_test.hpp>


namespace test_bobura
{
    class configuration
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void options();

        static void construction();


    };


}

#endif
