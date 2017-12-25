/*! \file
    \brief Test of class tetengo2::gui::drawing::solid_background.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/background.h>
#include <tetengo2/gui/drawing/color.h>
#include <tetengo2/gui/drawing/solid_background.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using color_type = tetengo2::gui::drawing::color;

    using drawing_details_type = detail_type_list_type::drawing_type;

    using background_type = tetengo2::gui::drawing::solid_background<drawing_details_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(solid_background)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const background_type background{ color_type{ 0x12, 0x34, 0x56, 0x78 } };
    }

    BOOST_AUTO_TEST_CASE(get_color)
    {
        BOOST_TEST_PASSPOINT();

        const background_type background{ color_type{ 0x12, 0x34, 0x56, 0x78 } };

        BOOST_CHECK((background.get_color() == color_type{ 0x12, 0x34, 0x56, 0x78 }));
    }

    BOOST_AUTO_TEST_CASE(clone)
    {
        BOOST_TEST_PASSPOINT();

        const background_type background{ color_type{ 0x12, 0x34, 0x56, 0x78 } };

        const auto p_clone = background.clone();
        
        BOOST_TEST_REQUIRE(p_clone.get());
        BOOST_TEST_REQUIRE(dynamic_cast<background_type*>(p_clone.get()));
        BOOST_CHECK(dynamic_cast<background_type*>(p_clone.get())->get_color() == background.get_color());
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            const background_type background{ color_type{ 0x12, 0x34, 0x56, 0x78 } };

            background.details();
        }
        {
            background_type background{ color_type{ 0x12, 0x34, 0x56, 0x78 } };

            background.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
