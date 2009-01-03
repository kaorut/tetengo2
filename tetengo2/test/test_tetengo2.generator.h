/*! \file
    \brief Test of class tetengo2::generator.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GENERATOR_H)
#define TESTTETENGO2_GENERATOR_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_tetengo2
{
    class generator
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();


    };


}

#endif
