/*! \file
    \brief Test of class tetengo2::gui::win32::window.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_WIN32_WINDOW_H)
#define TESTTETENGO2_GUI_WIN32_WINDOW_H

#include <boost/test/unit_test.hpp>


namespace test_tetengo2 { namespace gui { namespace win32
{
    class window
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void handle();

        static void add_window_observer();


    };


}}}

#endif
