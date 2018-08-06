/*! \file
    \brief Test of class tetengo2::gui::menu::popup.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/menu.h>
#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/gui/menu/popup.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using menu_base_type = tetengo2::gui::menu::menu_base;

    using popup_menu_type = tetengo2::gui::menu::popup;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(menu)
            BOOST_AUTO_TEST_SUITE(popup)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const popup_menu_type popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };
                }

                BOOST_AUTO_TEST_CASE(style)
                {
                    BOOST_TEST_PASSPOINT();

                    const popup_menu_type popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };

                    BOOST_CHECK(
                        &popup_menu.style() == &tetengo2::detail::gui_detail_impl_set().menu_().popup_menu_style());
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
