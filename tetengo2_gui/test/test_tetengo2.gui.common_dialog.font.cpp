/*! \file
    \brief Test of class tetengo2::gui::common_dialog::font.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>
#include <string>

#include <boost/operators.hpp>
#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/common_dialog/font.h>
#include <tetengo2/gui/drawing/font.h>
#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/widget/window.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using window_type = tetengo2::gui::widget::window;

    using drawing_details_type = detail_type_list_type::drawing_type;

    using font_type = tetengo2::gui::drawing::font;

    using common_dialog_details_type = detail_type_list_type::common_dialog_type;

    using font_dialog_type = tetengo2::gui::common_dialog::font<
        font_type,
        common_dialog_details_type,
        common_type_list_type::widget_details_type,
        common_type_list_type::drawing_details_type,
        common_type_list_type::scroll_details_type,
        common_type_list_type::message_handler_details_type>;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(common_dialog)
            BOOST_AUTO_TEST_SUITE(font)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type            parent{};
                        const font_dialog_type font{ TETENGO2_STDALT_NULLOPT, parent };
                    }
                    {
                        window_type            parent{};
                        const font_dialog_type font{
                            tetengo2::stdalt::make_optional(
                                font_type{ string_type{ TETENGO2_TEXT("fuga") }, 42, false, true, false, true }),
                            parent
                        };
                    }
                }

                BOOST_AUTO_TEST_CASE(result)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type            parent{};
                        const font_dialog_type font{ TETENGO2_STDALT_NULLOPT, parent };

                        BOOST_CHECK(
                            font.result() ==
                            font_type::dialog_font(tetengo2::detail::gui_detail_impl_set().drawing_()));
                    }
                    {
                        window_type      parent{};
                        font_dialog_type font{ TETENGO2_STDALT_NULLOPT, parent };

                        font.do_modal();

                        BOOST_CHECK(
                            font.result() !=
                            font_type::dialog_font(tetengo2::detail::gui_detail_impl_set().drawing_()));
                    }
                }

                BOOST_AUTO_TEST_CASE(do_modal)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type      parent{};
                    font_dialog_type font{ TETENGO2_STDALT_NULLOPT, parent };

                    font.do_modal();
                }

                BOOST_AUTO_TEST_CASE(details)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type            parent{};
                        const font_dialog_type font{ TETENGO2_STDALT_NULLOPT, parent };

                        font.details();
                    }
                    {
                        window_type      parent{};
                        font_dialog_type font{ TETENGO2_STDALT_NULLOPT, parent };

                        font.details();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
