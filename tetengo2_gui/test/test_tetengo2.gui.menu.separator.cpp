/*! \file
    \brief Test of class tetengo2::gui::menu::separator.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/stub/menu.h>
#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/gui/menu/separator.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using menu_details_type = detail_type_list_type::menu_type;

    using menu_base_type = tetengo2::gui::menu::menu_base;

    using menu_separator_type = tetengo2::gui::menu::separator;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(menu)
            BOOST_AUTO_TEST_SUITE(separator)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const menu_separator_type menu_separator;
                }

                BOOST_AUTO_TEST_CASE(style)
                {
                    BOOST_TEST_PASSPOINT();

                    const menu_separator_type menu_separator;

                    BOOST_CHECK(&menu_separator.style() == &menu_details_type::instance().menu_separator_style());
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
