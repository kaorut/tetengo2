/*! \file
    \brief Test of class tetengo2::win32::encode.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_WIN32_ENCODE_H)
#define TESTTETENGO2_WIN32_ENCODE_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_tetengo2 { namespace win32
{
    class encode
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void operator_paren();


    };


}}

#endif
