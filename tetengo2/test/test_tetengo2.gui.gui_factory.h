/*! \file
    \brief Test of class tetengo2::gui::gui_factory.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_GUIFACTORY_H)
#define TESTTETENGO2_GUI_GUIFACTORY_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_tetengo2 { namespace gui
{
    class gui_factory
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void create_window();


    };


}}

#endif
