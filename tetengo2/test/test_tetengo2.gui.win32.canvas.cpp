/*! \file
    \brief Test of class tetengo2::gui::win32::canvas.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

#include "tetengo2.gui.win32.canvas.h"

#include "stub_tetengo2.encode.h"

#include "test_tetengo2.gui.win32.canvas.h"


namespace
{
    // types

    typedef
        tetengo2::gui::win32::canvas<
            int, std::size_t, std::wstring, stub_tetengo2::encode, ::HWND
        >
        canvas_type;

}

namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* canvas::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32::canvas");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(handle));
        p_suite->add(BOOST_TEST_CASE(draw_text));

        return p_suite;
    }

    void canvas::construction()
    {
        canvas_type(NULL);
        BOOST_WARN("Not implemented yet.");
    }

    void canvas::handle()
    {
        BOOST_WARN("Not implemented yet.");
    }

    void canvas::draw_text()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}
