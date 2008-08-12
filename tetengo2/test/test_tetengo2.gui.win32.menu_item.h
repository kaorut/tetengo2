/*! \file
    \brief Test of class tetengo2::gui::win32::menu_item.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_WIN32_MENUITEM_H)
#define TESTTETENGO2_GUI_WIN32_MENUITEM_H

#include <boost/noncopyable.hpp>

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_tetengo2 { namespace gui { namespace win32
{
    class menu_item : private boost::noncopyable
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void id();

        static void text();

        static void set_text();

        static void select();

        static void add_menu_observer();


    };


}}}

#endif
