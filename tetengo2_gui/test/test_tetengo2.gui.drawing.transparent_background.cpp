/*! \file
    \brief Test of class tetengo2::gui::drawing::transparent_background.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/transparent_background.h>


namespace {
    // types

    using background_type = tetengo2::gui::drawing::transparent_background;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(drawing)
            BOOST_AUTO_TEST_SUITE(transparent_background)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const background_type background{};
                }

                BOOST_AUTO_TEST_CASE(clone)
                {
                    BOOST_TEST_PASSPOINT();

                    const background_type background{};

                    const auto p_clone = background.clone();

                    BOOST_TEST_REQUIRE(p_clone.get());
                    BOOST_TEST(dynamic_cast<background_type*>(p_clone.get()));
                }

                BOOST_AUTO_TEST_CASE(details)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const background_type background{};

                        background.details();
                    }
                    {
                        background_type background{};

                        background.details();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
