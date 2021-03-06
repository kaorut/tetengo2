/*! \file
    \brief Test of class tetengo2::gui::drawing::system_color_set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/system_color_set.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using system_color_set_type = tetengo2::gui::drawing::system_color_set;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(drawing)
            BOOST_AUTO_TEST_SUITE(system_color_set)
                // test cases

                BOOST_AUTO_TEST_CASE(instance)
                {
                    BOOST_TEST_PASSPOINT();

                    system_color_set_type::instance();
                }

                BOOST_AUTO_TEST_CASE(title_bar_background)
                {
                    BOOST_TEST_PASSPOINT();

                    system_color_set_type::instance().title_bar_background();
                }

                BOOST_AUTO_TEST_CASE(title_bar_text)
                {
                    BOOST_TEST_PASSPOINT();

                    system_color_set_type::instance().title_bar_text();
                }

                BOOST_AUTO_TEST_CASE(dialog_background)
                {
                    BOOST_TEST_PASSPOINT();

                    system_color_set_type::instance().dialog_background();
                }

                BOOST_AUTO_TEST_CASE(control_background)
                {
                    BOOST_TEST_PASSPOINT();

                    system_color_set_type::instance().control_background();
                }

                BOOST_AUTO_TEST_CASE(control_text)
                {
                    BOOST_TEST_PASSPOINT();

                    system_color_set_type::instance().control_text();
                }

                BOOST_AUTO_TEST_CASE(selected_background)
                {
                    BOOST_TEST_PASSPOINT();

                    system_color_set_type::instance().selected_background();
                }

                BOOST_AUTO_TEST_CASE(selected_text)
                {
                    BOOST_TEST_PASSPOINT();

                    system_color_set_type::instance().selected_text();
                }

                BOOST_AUTO_TEST_CASE(hyperlink_text)
                {
                    BOOST_TEST_PASSPOINT();

                    system_color_set_type::instance().hyperlink_text();
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
