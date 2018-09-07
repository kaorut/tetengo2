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
#include <tetengo2/type_list.h>


namespace {
    // types

    using string_type = tetengo2::type_list::string_type;

    using window_type = tetengo2::gui::widget::window;

    using font_type = tetengo2::gui::drawing::font;

    using font_dialog_type = tetengo2::gui::common_dialog::font;
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
