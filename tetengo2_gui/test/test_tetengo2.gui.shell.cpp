/*! \file
    \brief Test of class tetengo2::gui::shell.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.shell.h"
#include "tetengo2.text.h"

#include "test_tetengo2.gui.type_list.h"

#include "tetengo2.gui.shell.h"


namespace
{
    // types

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type string_type;

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::ui_encoder>::type encoder_type;

    typedef tetengo2::gui::shell<string_type, encoder_type, tetengo2::detail::stub::shell> shell_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(shell)
    // test cases

    BOOST_AUTO_TEST_CASE(instance)
    {
        BOOST_TEST_PASSPOINT();

        shell_type::instance();
    }

    BOOST_AUTO_TEST_CASE(execute)
    {
        BOOST_TEST_PASSPOINT();

        {
            const string_type command(TETENGO2_TEXT("command"));

            const auto result = shell_type::instance().execute(command);
            BOOST_CHECK(result);
        }
        {
            const string_type command(TETENGO2_TEXT("command_to_fail"));

            const auto result = shell_type::instance().execute(command);
            BOOST_CHECK(!result);
        }
        {
            const string_type command(TETENGO2_TEXT("command"));
            const std::vector<string_type> parameters;

            const auto result = shell_type::instance().execute(command, parameters.begin(), parameters.end());
            BOOST_CHECK(result);
        }
        {
            const string_type command(TETENGO2_TEXT("command"));
            std::vector<string_type> parameters;
            parameters.emplace_back(TETENGO2_TEXT("param1"));

            const auto result = shell_type::instance().execute(command, parameters.begin(), parameters.end());
            BOOST_CHECK(result);
        }
        {
            const string_type command(TETENGO2_TEXT("command"));
            std::vector<string_type> parameters;
            parameters.emplace_back(TETENGO2_TEXT("param1"));
            parameters.emplace_back(TETENGO2_TEXT("param2"));

            const auto result = shell_type::instance().execute(command, parameters.begin(), parameters.end());
            BOOST_CHECK(result);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
