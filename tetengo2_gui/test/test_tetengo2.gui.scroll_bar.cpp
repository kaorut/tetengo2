/*! \file
    \brief Test of class tetengo2::gui::scroll_bar.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

//#include <stdexcept>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::gui::scroll_type_list, test_tetengo2::gui::type::scroll::scroll_bar>::type
        scroll_bar_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(scroll_bar)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const scroll_bar_type scroll_bar(0, scroll_bar_type::style_type::vertical);
        }
        {
            const scroll_bar_type scroll_bar(0, scroll_bar_type::style_type::horizontal);
        }
    }

    BOOST_AUTO_TEST_CASE(position)
    {
        BOOST_TEST_PASSPOINT();

        const scroll_bar_type scroll_bar(0, scroll_bar_type::style_type::vertical);

        scroll_bar.position();
    }

    BOOST_AUTO_TEST_CASE(set_position)
    {
        BOOST_TEST_PASSPOINT();

        {
            scroll_bar_type scroll_bar(0, scroll_bar_type::style_type::vertical);
            scroll_bar.set_range(scroll_bar_type::range_type(0, 100));

            scroll_bar.set_position(42);

            BOOST_CHECK_EQUAL(scroll_bar.position(), 42U);
        }
        {
            scroll_bar_type scroll_bar(0, scroll_bar_type::style_type::vertical);
            scroll_bar.set_range(scroll_bar_type::range_type(0, 100));

            BOOST_CHECK_THROW(scroll_bar.set_position(128), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(tracking_position)
    {
        BOOST_TEST_PASSPOINT();

        scroll_bar_type scroll_bar(0, scroll_bar_type::style_type::vertical);

        scroll_bar.tracking_position();
    }

    BOOST_AUTO_TEST_CASE(range)
    {
        BOOST_TEST_PASSPOINT();

        const scroll_bar_type scroll_bar(0, scroll_bar_type::style_type::vertical);

        scroll_bar.range();
    }

    BOOST_AUTO_TEST_CASE(set_range)
    {
        BOOST_TEST_PASSPOINT();

        {
            scroll_bar_type scroll_bar(0, scroll_bar_type::style_type::vertical);

            scroll_bar.set_range(scroll_bar_type::range_type(0, 42));

            BOOST_CHECK(scroll_bar.range() == scroll_bar_type::range_type(0, 42));
        }
        {
            scroll_bar_type scroll_bar(0, scroll_bar_type::style_type::vertical);

            BOOST_CHECK_THROW(scroll_bar.set_range(scroll_bar_type::range_type(42, 10)), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(page_size)
    {
        BOOST_TEST_PASSPOINT();

        const scroll_bar_type scroll_bar(0, scroll_bar_type::style_type::vertical);

        scroll_bar.page_size();
    }

    BOOST_AUTO_TEST_CASE(set_page_size)
    {
        BOOST_TEST_PASSPOINT();

        scroll_bar_type scroll_bar(0, scroll_bar_type::style_type::vertical);

        scroll_bar.set_page_size(42);

        BOOST_CHECK_EQUAL(scroll_bar.page_size(), 42U);
    }

    BOOST_AUTO_TEST_CASE(enabled)
    {
        BOOST_TEST_PASSPOINT();

        const scroll_bar_type scroll_bar(0, scroll_bar_type::style_type::vertical);

        scroll_bar.enabled();
    }

    BOOST_AUTO_TEST_CASE(set_enabled)
    {
        BOOST_TEST_PASSPOINT();

        scroll_bar_type scroll_bar(0, scroll_bar_type::style_type::vertical);

        scroll_bar.set_enabled(true);

        BOOST_CHECK(scroll_bar.enabled());

        scroll_bar.set_enabled(false);

        BOOST_CHECK(!scroll_bar.enabled());
    }

    BOOST_AUTO_TEST_CASE(scroll_bar_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        scroll_bar_type scroll_bar(0, scroll_bar_type::style_type::vertical);

        scroll_bar.scroll_bar_observer_set();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
