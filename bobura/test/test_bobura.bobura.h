/*! \file
    \brief Test of class bobura::bobura.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_BOBURA_H)
#define TESTBOBURA_BOBURA_H

#include <boost/test/unit_test.hpp>


namespace test_bobura
{
    class bobura
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void run();


    };


}

#endif
