/*! \file
    \brief Test of class tetengo2::gui::win32::message_loop.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_WIN32_MESSAGELOOP_H)
#define TESTTETENGO2_GUI_WIN32_MESSAGELOOP_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_tetengo2 { namespace gui { namespace win32
{
    class message_loop
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void operator_paren();


    };


}}}

#endif
