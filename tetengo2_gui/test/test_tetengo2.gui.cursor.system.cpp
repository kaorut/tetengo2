/*! \file
    \brief Test of class tetengo2::gui::cursor::system.

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

    using cursor_type = tetengo2::gui::cursor::system<detail_type_list_type::cursor_type>;


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
            const cursor_type cursor{ cursor_type::style_type::default_ };
        }
        {
            const cursor_type cursor{ cursor_type::style_type::hand };
        }
        {
            const cursor_type cursor{ cursor_type::style_type::horizontal_resize };
        }
        {
            const cursor_type cursor{ cursor_type::style_type::vertical_resize };
        }
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        {
            const cursor_type cursor{ cursor_type::style_type::default_ };

            BOOST_CHECK(cursor.style() == cursor_type::style_type::default_);
        }
        {
            const cursor_type cursor{ cursor_type::style_type::hand };

            BOOST_CHECK(cursor.style() == cursor_type::style_type::hand);
        }
        {
            const cursor_type cursor{ cursor_type::style_type::horizontal_resize };

            BOOST_CHECK(cursor.style() == cursor_type::style_type::horizontal_resize);
        }
        {
            const cursor_type cursor{ cursor_type::style_type::vertical_resize };

            BOOST_CHECK(cursor.style() == cursor_type::style_type::vertical_resize);
        }
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        BOOST_WARN_MESSAGE(false, "Not implemented yet.");
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
