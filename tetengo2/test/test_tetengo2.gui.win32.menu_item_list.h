/*! \file
    \brief Test of class tetengo2::gui::win32::menu_item_list.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_WIN32_MENUITEMLIST_H)
#define TESTTETENGO2_GUI_WIN32_MENUITEMLIST_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_tetengo2 { namespace gui { namespace win32
{
    class menu_item_list
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void begin();

        static void end();

        static void insert();

        static void erase();

        static void find_by_id();

        static void find_by_handle();


    };


}}}

#endif
