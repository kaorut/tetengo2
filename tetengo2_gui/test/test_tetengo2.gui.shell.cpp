/*! \file
    \brief Test of class tetengo2::gui::shell.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/stub/shell.h>
#include <tetengo2/gui/shell.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using shell_details_type = detail_type_list_type::shell_type;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using shell_type = tetengo2::gui::shell;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(shell)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                const shell_type shell{ shell_details_type::instance() };
            }

            BOOST_AUTO_TEST_CASE(execute)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const string_type command{ TETENGO2_TEXT("command") };

                    const auto result = shell_type{ shell_details_type::instance() }.execute(command);
                    BOOST_TEST(result);
                }
                {
                    const string_type command{ TETENGO2_TEXT("command_to_fail") };

                    const auto result = shell_type{ shell_details_type::instance() }.execute(command);
                    BOOST_TEST(!result);
                }
                {
                    const string_type              command{ TETENGO2_TEXT("command") };
                    const std::vector<string_type> parameters{};

                    const auto result = shell_type{ shell_details_type::instance() }.execute(
                        command, parameters.begin(), parameters.end());
                    BOOST_TEST(result);
                }
                {
                    const string_type              command{ TETENGO2_TEXT("command") };
                    const std::vector<string_type> parameters{ string_type{ TETENGO2_TEXT("param1") } };

                    const auto result = shell_type{ shell_details_type::instance() }.execute(
                        command, parameters.begin(), parameters.end());
                    BOOST_TEST(result);
                }
                {
                    const string_type              command{ TETENGO2_TEXT("command") };
                    const std::vector<string_type> parameters{ string_type{ TETENGO2_TEXT("param1") },
                                                               string_type{ TETENGO2_TEXT("param2") } };

                    const auto result = shell_type{ shell_details_type::instance() }.execute(
                        command, parameters.begin(), parameters.end());
                    BOOST_TEST(result);
                }
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
