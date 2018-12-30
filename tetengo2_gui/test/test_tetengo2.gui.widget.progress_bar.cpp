/*! \file
    \brief Test of class tetengo2::gui::widget::progress_bar.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/widget/progress_bar.h>
#include <tetengo2/gui/widget/window.h>


namespace {
    // types

    using window_type = tetengo2::gui::widget::window;

    using progress_bar_type = tetengo2::gui::widget::progress_bar;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(widget)
            BOOST_AUTO_TEST_SUITE(progress_bar)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type             parent{};
                    const progress_bar_type progress_bar{ parent };
                }

                BOOST_AUTO_TEST_CASE(goal)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type             parent{};
                    const progress_bar_type progress_bar{ parent };

                    progress_bar.goal();
                }

                BOOST_AUTO_TEST_CASE(set_goal)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type       parent{};
                    progress_bar_type progress_bar{ parent };

                    progress_bar.set_goal(42);
                    BOOST_TEST(progress_bar.goal() == 42U);
                }

                BOOST_AUTO_TEST_CASE(progress)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type             parent{};
                    const progress_bar_type progress_bar{ parent };

                    progress_bar.progress();
                }

                BOOST_AUTO_TEST_CASE(set_progress)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type       parent{};
                    progress_bar_type progress_bar{ parent };

                    progress_bar.set_progress(42);
                    BOOST_TEST(progress_bar.progress() == 42U);
                }

                BOOST_AUTO_TEST_CASE(state)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type             parent{};
                    const progress_bar_type progress_bar{ parent };

                    progress_bar.state();
                }

                BOOST_AUTO_TEST_CASE(set_state)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type       parent{};
                    progress_bar_type progress_bar{ parent };

                    progress_bar.set_state(progress_bar_type::state_type::pausing);
                    BOOST_CHECK(progress_bar.state() == progress_bar_type::state_type::pausing);
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
