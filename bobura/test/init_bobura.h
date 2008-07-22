/*! \file
    \brief Test of namespace bobura.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(INITBOBURA_H)
#define INITBOBURA_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_bobura
{
    // functions

    boost::unit_test::test_suite* suite();

}

#endif
