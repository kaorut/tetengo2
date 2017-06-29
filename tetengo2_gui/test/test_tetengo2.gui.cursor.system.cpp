/*! \file
    \brief Test of class tetengo2::gui::cursor::system.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/stub/cursor.h>
#include <tetengo2/gui/cursor/system.h>


namespace
{
    // types

    using cursor_type = tetengo2::gui::cursor::system;

    using cursor_details_type = tetengo2::detail::stub::cursor;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(cursor)
BOOST_AUTO_TEST_SUITE(system)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const cursor_type cursor{ cursor_type::style_type::default_, cursor_details_type::instance() };
        }
        {
            const cursor_type cursor{ cursor_type::style_type::hand, cursor_details_type::instance() };
        }
        {
            const cursor_type cursor{ cursor_type::style_type::horizontal_resize, cursor_details_type::instance() };
        }
        {
            const cursor_type cursor{ cursor_type::style_type::vertical_resize, cursor_details_type::instance() };
        }
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        {
            const cursor_type cursor{ cursor_type::style_type::default_, cursor_details_type::instance() };

            BOOST_CHECK(cursor.style() == cursor_type::style_type::default_);
        }
        {
            const cursor_type cursor{ cursor_type::style_type::hand, cursor_details_type::instance() };

            BOOST_CHECK(cursor.style() == cursor_type::style_type::hand);
        }
        {
            const cursor_type cursor{ cursor_type::style_type::horizontal_resize, cursor_details_type::instance() };

            BOOST_CHECK(cursor.style() == cursor_type::style_type::horizontal_resize);
        }
        {
            const cursor_type cursor{ cursor_type::style_type::vertical_resize, cursor_details_type::instance() };

            BOOST_CHECK(cursor.style() == cursor_type::style_type::vertical_resize);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
