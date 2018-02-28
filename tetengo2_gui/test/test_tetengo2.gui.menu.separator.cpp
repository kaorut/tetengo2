/*! \file
    \brief Test of class tetengo2::gui::menu::separator.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/gui/menu/separator.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
// types

using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

using string_type = common_type_list_type::string_type;

using ui_encoder_type = common_type_list_type::ui_encoder_type;

using menu_details_type = detail_type_list_type::menu_type;

using virtual_key_details_type = detail_type_list_type::virtual_key_type;

using menu_base_type =
    tetengo2::gui::menu::menu_base<string_type, ui_encoder_type, menu_details_type, virtual_key_details_type>;

using menu_separator_type =
    tetengo2::gui::menu::separator<string_type, ui_encoder_type, menu_details_type, virtual_key_details_type>;
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

                    BOOST_CHECK(&menu_separator.style() == &menu_details_type::menu_separator_style<menu_base_type>());
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
