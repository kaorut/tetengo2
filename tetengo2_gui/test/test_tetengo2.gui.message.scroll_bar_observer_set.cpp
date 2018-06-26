/*! \file
    \brief Test of class tetengo2::gui::message::scroll_bar_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/message/scroll_bar_observer_set.h>

#include "test_tetengo2.gui.detail_type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using scroll_bar_observer_set_type = tetengo2::gui::message::scroll_bar_observer_set;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(message)
            BOOST_AUTO_TEST_SUITE(scroll_bar_observer_set)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const scroll_bar_observer_set_type observer_set{};
                }

                BOOST_AUTO_TEST_CASE(scrolling)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const scroll_bar_observer_set_type observer_set{};

                        observer_set.scrolling();
                    }
                    {
                        scroll_bar_observer_set_type observer_set{};

                        observer_set.scrolling();
                    }
                }

                BOOST_AUTO_TEST_CASE(scrolled)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const scroll_bar_observer_set_type observer_set{};

                        observer_set.scrolled();
                    }
                    {
                        scroll_bar_observer_set_type observer_set{};

                        observer_set.scrolled();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
