/*! \file
    \brief Test of class tetengo2::gui::alert.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <cstddef>
//#include <stdexcept>
//#include <string>

//#include <boost/exception/all.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.alert.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.encoder.h"
#include "tetengo2.encoding.locale.h"

#include "tetengo2.gui.alert.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::encoding::locale<std::wstring, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::encoding::locale<std::wstring, encoding_details_type>
        ui_encoding_type;

    typedef
        tetengo2::encoder<internal_encoding_type, ui_encoding_type>
        ui_encoder_type;

    typedef
        tetengo2::encoding::locale<std::string, encoding_details_type>
        exception_encoding_type;

    typedef
        tetengo2::encoder<internal_encoding_type, exception_encoding_type>
        exception_encoder_type;

    typedef
        tetengo2::detail::stub::alert<std::wstring, ui_encoder_type>
        alert_details_type;

    typedef
        tetengo2::gui::alert<
            ui_encoder_type, exception_encoder_type, alert_details_type
        >
        alert_type;

    struct boost_exception : public boost::exception
    {};


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(alert)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const alert_type alert(NULL);
        }
    }

    BOOST_AUTO_TEST_CASE(operator_paren_boost_exception)
    {
        BOOST_TEST_PASSPOINT();

        const alert_type alert(NULL);

        const boost_exception exception;
        alert(exception);
    }

    BOOST_AUTO_TEST_CASE(operator_paren_std_exception)
    {
        BOOST_TEST_PASSPOINT();

        const alert_type alert(NULL);

        const std::runtime_error exception("Tetengo2");
        alert(exception);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
