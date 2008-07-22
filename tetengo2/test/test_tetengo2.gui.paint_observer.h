/*! \file
    \brief Test of class tetengo2::gui::paint_observer.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_PAINTOBSERVER_H)
#define TESTTETENGO2_GUI_PAINTOBSERVER_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_tetengo2 { namespace gui
{
    class paint_observer
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void paint();


    };


}}

#endif
