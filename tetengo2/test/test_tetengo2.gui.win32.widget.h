/*! \file
    \brief Test of class tetengo2::gui::win32::widget.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_WIN32_WIDGET_H)
#define TESTTETENGO2_GUI_WIN32_WIDGET_H

#include <boost/test/unit_test.hpp>


namespace test_tetengo2 { namespace gui { namespace win32
{
    class widget
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void handle();

        static void set_visible();

        static void visible();

        static void set_text();

        static void text();

        static void add_paint_observer();


    };


}}}

#endif
