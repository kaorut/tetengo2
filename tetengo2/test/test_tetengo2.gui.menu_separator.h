/*! \file
    \brief Test of class tetengo2::gui::menu_separator.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_MENUSEPARATOR_H)
#define TESTTETENGO2_GUI_MENUSEPARATOR_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_tetengo2 { namespace gui
{
    class menu_separator
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void is_command();

        static void is_popup();

        static void is_separator();

        static void handle();


    };


}}

#endif
