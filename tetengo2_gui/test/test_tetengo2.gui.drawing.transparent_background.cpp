/*! \file
    \brief Test of class tetengo2::gui::drawing::transparent_background.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using drawing_details_type = detail_type_list_type::drawing_type;

    using background_type = tetengo2::gui::drawing::transparent_background<drawing_details_type>;


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

        BOOST_REQUIRE(p_clone);
        BOOST_CHECK(dynamic_cast<background_type*>(p_clone.get()));
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
