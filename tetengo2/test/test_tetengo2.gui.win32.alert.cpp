/*! \file
    \brief Test of class tetengo2::gui::win32::alert.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>

#include <boost/test/unit_test.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.encoder.h"
#include "tetengo2.encoding.locale.h"

#include "tetengo2.gui.win32.alert.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::encoding::locale<std::wstring, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::encoding::locale<std::wstring, encoding_details_type>
        encoding_type;

    typedef
        tetengo2::encoder<internal_encoding_type, encoding_type>
        encoder_type;

    typedef
        tetengo2::gui::win32::alert< ::HWND, encoder_type, encoder_type>
        alert_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(win32)
BOOST_AUTO_TEST_SUITE(alert)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        alert_type(NULL);

        alert_type(reinterpret_cast< ::HWND>(0x123456));
    }

    BOOST_AUTO_TEST_CASE(operator_paren_boost_exception)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }

    BOOST_AUTO_TEST_CASE(operator_paren_std_exception)
    {
        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
