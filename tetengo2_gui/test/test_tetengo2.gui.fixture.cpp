/*! \file
    \brief Test of class tetengo2::gui::fixture.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <utility>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/stub/gui_fixture.h>
#include <tetengo2/gui/fixture.h>


namespace {
    // types

    using fixture_type = tetengo2::gui::fixture;

    using fixture_details_type = tetengo2::detail::stub::gui_fixture;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(fixture)
            // test cases

            BOOST_AUTO_TEST_CASE(construction)
            {
                BOOST_TEST_PASSPOINT();

                auto               p_fixture_details = std::make_unique<fixture_details_type>();
                const fixture_type fixture{ std::move(p_fixture_details) };
            }


        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
