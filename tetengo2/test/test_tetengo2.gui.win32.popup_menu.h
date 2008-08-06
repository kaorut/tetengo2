/*! \file
    \brief Test of class tetengo2::gui::win32::popup_menu.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_WIN32_POPUPMENU_H)
#define TESTTETENGO2_GUI_WIN32_POPUPMENU_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_tetengo2 { namespace gui
{
    class popup_menu
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void is_command();

        static void is_popup();

        static void is_separator();

        static void handle();

        static void menu_item_begin();

        static void menu_item_end();

        static void insert();

        static void erase();

        static void find_by_id();

        static void find_by_handle();


    };


}}

#endif
