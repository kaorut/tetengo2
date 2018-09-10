/*! \file
    \brief Test of class tetengo2::gui::widget::picture_box.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/widget/picture_box.h>
#include <tetengo2/gui/widget/window.h>


namespace {
    // types

    using window_type = tetengo2::gui::widget::window;

    using picture_box_type = tetengo2::gui::widget::picture_box;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(widget)
            BOOST_AUTO_TEST_SUITE(picture_box)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type            parent{};
                        const picture_box_type picture_box{ parent, picture_box_type::scroll_bar_style_type::none };
                    }
                    {
                        window_type            parent{};
                        const picture_box_type picture_box{ parent, picture_box_type::scroll_bar_style_type::both };
                    }
                }

                BOOST_AUTO_TEST_CASE(create_fast_canvas)
                {
                    BOOST_TEST_PASSPOINT();

                    window_type            parent{};
                    const picture_box_type picture_box{ parent, picture_box_type::scroll_bar_style_type::none };

                    picture_box.create_fast_canvas();
                }

                BOOST_AUTO_TEST_CASE(fast_paint_observer_set)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        window_type            parent{};
                        const picture_box_type picture_box{ parent, picture_box_type::scroll_bar_style_type::none };

                        picture_box.fast_paint_observer_set();
                    }
                    {
                        window_type      parent{};
                        picture_box_type picture_box{ parent, picture_box_type::scroll_bar_style_type::none };

                        picture_box.fast_paint_observer_set();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
