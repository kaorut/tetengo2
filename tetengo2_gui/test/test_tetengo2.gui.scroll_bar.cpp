/*! \file
    \brief Test of class tetengo2::gui::scroll_bar.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#include <cassert>
#include <cstddef>
//#include <stdexcept>

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.scroll_bar.h"


namespace
{
    // types

    typedef tetengo2::gui::scroll_bar<std::size_t> scroll_bar_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(scroll_bar)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const scroll_bar_type scroll_bar;
    }

    BOOST_AUTO_TEST_CASE(position)
    {
        BOOST_TEST_PASSPOINT();

        const scroll_bar_type scroll_bar;

        BOOST_CHECK_EQUAL(scroll_bar.position(), 0U);
    }

    BOOST_AUTO_TEST_CASE(set_position)
    {
        BOOST_TEST_PASSPOINT();

        {
            scroll_bar_type scroll_bar;
            scroll_bar.set_range(scroll_bar_type::range_type(0, 100));

            scroll_bar.set_position(42);

            BOOST_CHECK_EQUAL(scroll_bar.position(), 42U);
        }
        {
            scroll_bar_type scroll_bar;
            scroll_bar.set_range(scroll_bar_type::range_type(0, 100));

            BOOST_CHECK_THROW(scroll_bar.set_position(128), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(range)
    {
        BOOST_TEST_PASSPOINT();

        const scroll_bar_type scroll_bar;

        BOOST_CHECK(scroll_bar.range() == scroll_bar_type::range_type(0, 0));
    }

    BOOST_AUTO_TEST_CASE(set_range)
    {
        BOOST_TEST_PASSPOINT();

        {
            scroll_bar_type scroll_bar;

            scroll_bar.set_range(scroll_bar_type::range_type(0, 42));

            BOOST_CHECK(scroll_bar.range() == scroll_bar_type::range_type(0, 42));
        }
        {
            scroll_bar_type scroll_bar;
            assert(scroll_bar.position() == 0);

            BOOST_CHECK_THROW(scroll_bar.set_range(scroll_bar_type::range_type(10, 42)), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(page_size)
    {
        BOOST_TEST_PASSPOINT();

        const scroll_bar_type scroll_bar;

        BOOST_CHECK_EQUAL(scroll_bar.page_size(), 0U);
    }

    BOOST_AUTO_TEST_CASE(set_page_size)
    {
        BOOST_TEST_PASSPOINT();

        scroll_bar_type scroll_bar;

        scroll_bar.set_page_size(42);

        BOOST_CHECK_EQUAL(scroll_bar.page_size(), 42U);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
