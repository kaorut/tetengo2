/*! \file
    \brief Test of class tetengo2::gui::widget::side_bar.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/widget/side_bar.h>
#include <tetengo2/gui/widget/window.h>

#include "test_tetengo2.gui.detail_type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using window_type = tetengo2::gui::widget::window;

    using mouse_capture_details_type = detail_type_list_type::mouse_capture_type;

    using side_bar_type = tetengo2::gui::widget::side_bar;

    using dimension_unit_type = side_bar_type::dimension_unit_type;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(widget)
            BOOST_AUTO_TEST_SUITE(side_bar)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type         parent{};
                    const side_bar_type side_bar{ parent };
                }

                BOOST_AUTO_TEST_CASE(preferred_width)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type   parent{};
                    side_bar_type side_bar{ parent };

                    side_bar.preferred_width();
                }

                BOOST_AUTO_TEST_CASE(normal_preferred_width)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type   parent{};
                    side_bar_type side_bar{ parent };

                    side_bar.normal_preferred_width();
                }

                BOOST_AUTO_TEST_CASE(set_width)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type   parent{};
                    side_bar_type side_bar{ parent };

                    side_bar.set_width(dimension_unit_type{ 42 });
                }

                BOOST_AUTO_TEST_CASE(minimized)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type         parent{};
                    const side_bar_type side_bar{ parent };

                    side_bar.minimized();
                }

                BOOST_AUTO_TEST_CASE(set_minimized)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type   parent{};
                    side_bar_type side_bar{ parent };

                    BOOST_TEST(!side_bar.minimized());

                    side_bar.set_minimized(true);

                    BOOST_TEST(side_bar.minimized());

                    side_bar.set_minimized(false);

                    BOOST_TEST(!side_bar.minimized());
                }

                BOOST_AUTO_TEST_CASE(child_control_area_position)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type         parent{};
                    const side_bar_type side_bar{ parent };

                    side_bar.child_control_area_position();
                }

                BOOST_AUTO_TEST_CASE(child_control_area_dimension)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type         parent{};
                    const side_bar_type side_bar{ parent };

                    side_bar.child_control_area_dimension();
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
