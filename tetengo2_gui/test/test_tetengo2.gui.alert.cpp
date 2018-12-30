/*! \file
    \brief Test of class tetengo2::gui::alert.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <sstream>
#include <stdexcept>

#include <boost/exception/all.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/alert.h>


namespace {
    // types

    using alert_type = tetengo2::gui::alert;

    struct boost_exception : public boost::exception
    {
    };
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(alert)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const alert_type alert{};
                }
                {
                    const alert_type alert{ nullptr };
                }
            }

            BOOST_AUTO_TEST_CASE(operator_paren_O_boost_exception)
            {
                BOOST_TEST_PASSPOINT();

                const alert_type alert{ nullptr };

                const boost_exception exception{};
                alert(exception);
            }

            BOOST_AUTO_TEST_CASE(operator_paren_O_std_exception)
            {
                BOOST_TEST_PASSPOINT();

                const alert_type alert{ nullptr };

                const std::runtime_error exception{ "Tetengo2" };
                alert(exception);
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
