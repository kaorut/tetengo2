/*! \file
    \brief Test of class tetengo2::gui::scroll_bar.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>
#include <stdexcept>
#include <utility>

#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/scroll_bar.h>
#include <tetengo2/gui/widget/window.h>

#include "test_tetengo2.gui.detail_type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using window_type = tetengo2::gui::widget::window;

    using scroll_bar_type = tetengo2::gui::scroll_bar<detail_type_list_type::scroll_type>;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(scroll_bar)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const window_type     window;
                    const scroll_bar_type scroll_bar{ window, scroll_bar_type::style_type::vertical };
                }
                {
                    const window_type     window;
                    const scroll_bar_type scroll_bar{ window, scroll_bar_type::style_type::horizontal };
                }
            }

            BOOST_AUTO_TEST_CASE(position)
            {
                BOOST_TEST_PASSPOINT();

                const window_type     window;
                const scroll_bar_type scroll_bar{ window, scroll_bar_type::style_type::vertical };

                scroll_bar.position();
            }

            BOOST_AUTO_TEST_CASE(set_position)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const window_type window;
                    scroll_bar_type   scroll_bar{ window, scroll_bar_type::style_type::vertical };
                    scroll_bar.set_range(scroll_bar_type::range_type{ 0, 100 });

                    scroll_bar.set_position(42);

                    BOOST_TEST(scroll_bar.position() == 42U);
                }
                {
                    const window_type window;
                    scroll_bar_type   scroll_bar{ window, scroll_bar_type::style_type::vertical };
                    scroll_bar.set_range(scroll_bar_type::range_type{ 0, 100 });

                    BOOST_CHECK_THROW(scroll_bar.set_position(128), std::out_of_range);
                }
            }

            BOOST_AUTO_TEST_CASE(tracking_position)
            {
                BOOST_TEST_PASSPOINT();

                const window_type window;
                scroll_bar_type   scroll_bar{ window, scroll_bar_type::style_type::vertical };

                scroll_bar.tracking_position();
            }

            BOOST_AUTO_TEST_CASE(range)
            {
                BOOST_TEST_PASSPOINT();

                const window_type     window;
                const scroll_bar_type scroll_bar{ window, scroll_bar_type::style_type::vertical };

                scroll_bar.range();
            }

            BOOST_AUTO_TEST_CASE(set_range)
            {
                BOOST_TEST_PASSPOINT();

                {
                    const window_type window;
                    scroll_bar_type   scroll_bar{ window, scroll_bar_type::style_type::vertical };

                    scroll_bar.set_range(scroll_bar_type::range_type{ 0, 42 });

                    BOOST_CHECK((scroll_bar.range() == scroll_bar_type::range_type{ 0, 42 }));
                }
                {
                    const window_type window;
                    scroll_bar_type   scroll_bar{ window, scroll_bar_type::style_type::vertical };

                    BOOST_CHECK_THROW(scroll_bar.set_range(scroll_bar_type::range_type{ 42, 10 }), std::out_of_range);
                }
            }

            BOOST_AUTO_TEST_CASE(page_size)
            {
                BOOST_TEST_PASSPOINT();

                const window_type     window;
                const scroll_bar_type scroll_bar{ window, scroll_bar_type::style_type::vertical };

                scroll_bar.page_size();
            }

            BOOST_AUTO_TEST_CASE(set_page_size)
            {
                BOOST_TEST_PASSPOINT();

                const window_type window;
                scroll_bar_type   scroll_bar{ window, scroll_bar_type::style_type::vertical };

                scroll_bar.set_page_size(42);

                BOOST_TEST(scroll_bar.page_size() == 42U);
            }

            BOOST_AUTO_TEST_CASE(enabled)
            {
                BOOST_TEST_PASSPOINT();

                const window_type     window;
                const scroll_bar_type scroll_bar{ window, scroll_bar_type::style_type::vertical };

                scroll_bar.enabled();
            }

            BOOST_AUTO_TEST_CASE(set_enabled)
            {
                BOOST_TEST_PASSPOINT();

                const window_type window;
                scroll_bar_type   scroll_bar{ window, scroll_bar_type::style_type::vertical };

                scroll_bar.set_enabled(true);

                BOOST_TEST(scroll_bar.enabled());

                scroll_bar.set_enabled(false);

                BOOST_TEST(!scroll_bar.enabled());
            }

            BOOST_AUTO_TEST_CASE(scroll_bar_observer_set)
            {
                BOOST_TEST_PASSPOINT();

                const window_type window;
                scroll_bar_type   scroll_bar{ window, scroll_bar_type::style_type::vertical };

                scroll_bar.scroll_bar_observer_set();
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
