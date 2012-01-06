/*! \file
    \brief Test of class tetengo2::gui::cursor::system_cursor.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.detail.stub.cursor.h"

#include "tetengo2.gui.cursor.system_cursor.h"


namespace
{
    // types

    typedef
        tetengo2::gui::cursor::system_cursor<tetengo2::detail::stub::cursor>
        cursor_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(cursor)
BOOST_AUTO_TEST_SUITE(system_cursor)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const cursor_type cursor(cursor_type::style_default);
        }
        {
            const cursor_type cursor(cursor_type::style_hand);
        }
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        {
            const cursor_type cursor(cursor_type::style_default);

            BOOST_CHECK(cursor.style() == cursor_type::style_default);
        }
        {
            const cursor_type cursor(cursor_type::style_hand);

            BOOST_CHECK(cursor.style() == cursor_type::style_hand);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
