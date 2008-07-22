/*! \file
    \brief Test of namespace tetengo2::win32.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(INITTETENGO2_WIN32_H)
#define INITTETENGO2_WIN32_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_tetengo2 { namespace win32
{
    // functions

    boost::unit_test::test_suite* suite();

}}

#endif
