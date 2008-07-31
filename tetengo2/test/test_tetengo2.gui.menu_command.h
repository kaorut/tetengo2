/*! \file
    \brief Test of class tetengo2::gui::win32::menu_command.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_MENUCOMMAND_H)
#define TESTTETENGO2_GUI_MENUCOMMAND_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_tetengo2 { namespace gui
{
    class menu_command
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void is_command();

        static void is_popup();

        static void handle();

        static void command();

        static void set_command();


    };


}}

#endif
