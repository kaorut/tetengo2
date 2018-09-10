/*! \file
    \brief Test of class tetengo2::gui::drawing::solid_background.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/solid_background.h>


namespace {
    // types

    using color_type = tetengo2::gui::drawing::color;

    using background_type = tetengo2::gui::drawing::solid_background;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(drawing)
            BOOST_AUTO_TEST_SUITE(solid_background)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const background_type background{ tetengo2::detail::gui_detail_impl_set().drawing_(),
                                                          color_type{ 0x12, 0x34, 0x56, 0x78 } };
                    }
                    {
                        const background_type background{ color_type{ 0x12, 0x34, 0x56, 0x78 } };
                    }
                }

                BOOST_AUTO_TEST_CASE(get_color)
                {
                    BOOST_TEST_PASSPOINT();

                    const background_type background{ tetengo2::detail::gui_detail_impl_set().drawing_(),
                                                      color_type{ 0x12, 0x34, 0x56, 0x78 } };

                    BOOST_CHECK((background.get_color() == color_type{ 0x12, 0x34, 0x56, 0x78 }));
                }

                BOOST_AUTO_TEST_CASE(clone)
                {
                    BOOST_TEST_PASSPOINT();

                    const background_type background{ tetengo2::detail::gui_detail_impl_set().drawing_(),
                                                      color_type{ 0x12, 0x34, 0x56, 0x78 } };

                    const auto p_clone = background.clone();

                    BOOST_TEST_REQUIRE(p_clone.get());
                    BOOST_TEST_REQUIRE(dynamic_cast<background_type*>(p_clone.get()));
                    BOOST_CHECK(dynamic_cast<background_type*>(p_clone.get())->get_color() == background.get_color());
                }

                BOOST_AUTO_TEST_CASE(drawing_details)
                {
                    BOOST_TEST_PASSPOINT();

                    const background_type background{ tetengo2::detail::gui_detail_impl_set().drawing_(),
                                                      color_type{ 0x12, 0x34, 0x56, 0x78 } };

                    background.drawing_details();
                }

                BOOST_AUTO_TEST_CASE(details)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const background_type background{ tetengo2::detail::gui_detail_impl_set().drawing_(),
                                                          color_type{ 0x12, 0x34, 0x56, 0x78 } };

                        background.details();
                    }
                    {
                        background_type background{ tetengo2::detail::gui_detail_impl_set().drawing_(),
                                                    color_type{ 0x12, 0x34, 0x56, 0x78 } };

                        background.details();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
