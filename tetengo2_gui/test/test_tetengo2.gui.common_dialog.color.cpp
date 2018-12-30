/*! \file
    \brief Test of class tetengo2::gui::common_dialog::color.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <sstream>

#include <boost/operators.hpp>
#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/common_dialog/color.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/widget/window.h>
#include <tetengo2/stdalt.h>


namespace {
    // types

    using window_type = tetengo2::gui::widget::window;

    using color_type = tetengo2::gui::drawing::color;

    using color_dialog_type = tetengo2::gui::common_dialog::color;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(common_dialog)
            BOOST_AUTO_TEST_SUITE(color)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type             parent{};
                        const color_dialog_type color{ TETENGO2_STDALT_NULLOPT, parent };
                    }
                    {
                        window_type             parent{};
                        const color_dialog_type color{ tetengo2::stdalt::make_optional(color_type{ 12, 34, 56 }),
                                                       parent };
                    }
                }

                BOOST_AUTO_TEST_CASE(result)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type             parent{};
                        const color_dialog_type color{ TETENGO2_STDALT_NULLOPT, parent };

                        BOOST_CHECK((color.result() == color_type{ 0, 0, 0 }));
                    }
                    {
                        window_type       parent{};
                        color_dialog_type color{ TETENGO2_STDALT_NULLOPT, parent };

                        color.do_modal();

                        BOOST_CHECK((color.result() != color_type{ 0, 0, 0 }));
                    }
                }

                BOOST_AUTO_TEST_CASE(do_modal)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type       parent{};
                    color_dialog_type color{ TETENGO2_STDALT_NULLOPT, parent };

                    color.do_modal();
                }

                BOOST_AUTO_TEST_CASE(details)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type             parent{};
                        const color_dialog_type color{ TETENGO2_STDALT_NULLOPT, parent };

                        color.details();
                    }
                    {
                        window_type       parent{};
                        color_dialog_type color{ TETENGO2_STDALT_NULLOPT, parent };

                        color.details();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
