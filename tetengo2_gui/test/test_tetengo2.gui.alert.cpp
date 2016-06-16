/*! \file
    \brief Test of class tetengo2::gui::alert.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#include <stdexcept>

#include <boost/exception/all.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/alert.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using alert_type =
        tetengo2::gui::alert<
            common_type_list_type::ui_encoder_type,
            common_type_list_type::exception_encoder_type,
            detail_type_list_type::alert_type
        >;

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
