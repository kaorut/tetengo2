/*! \file
    \brief Test of class tetengo2::gui::win32::widget.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.win32.widget.h"

#include "test_tetengo2.gui.win32.widget.h"


namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* widget::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32::widget");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(handle));
        p_suite->add(BOOST_TEST_CASE(set_visible));
        p_suite->add(BOOST_TEST_CASE(visible));
        p_suite->add(BOOST_TEST_CASE(set_text));
        p_suite->add(BOOST_TEST_CASE(text));
        p_suite->add(BOOST_TEST_CASE(add_paint_observer));

        return p_suite;
    }

    void widget::construction()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void widget::handle()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void widget::set_visible()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void widget::visible()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void widget::set_text()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void widget::text()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void widget::add_paint_observer()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}
