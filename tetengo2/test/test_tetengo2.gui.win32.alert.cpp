/*! \file
    \brief Test of class tetengo2::gui::win32::alert.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include "precompiled.h"

#include <cstddef>

//#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.win32.alert.h"

#include "stub_tetengo2.encode.h"

#include "test_tetengo2.gui.win32.alert.h"


namespace
{
    // types

    typedef
        tetengo2::gui::win32::alert<::HWND, stub_tetengo2::encode>
        alert_type;

}

namespace test_tetengo2 { namespace gui { namespace win32
{
    // functions

    boost::unit_test::test_suite* alert::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::win32::alert");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(operator_paren));

        return p_suite;
    }

    void alert::construction()
    {
        BOOST_CHECKPOINT("");

        alert_type(NULL);

        alert_type(reinterpret_cast< ::HWND>(0x123456));
    }

    void alert::operator_paren()
    {
        BOOST_WARN("Not implemented yet.");
    }


}}}
