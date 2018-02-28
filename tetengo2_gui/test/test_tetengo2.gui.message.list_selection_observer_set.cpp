/*! \file
    \brief Test of class tetengo2::gui::message::list_selection_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/message/list_selection_observer_set.h>


namespace {
// types

using list_selection_observer_set_type = tetengo2::gui::message::list_selection_observer_set;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(message)
            BOOST_AUTO_TEST_SUITE(list_selection_observer_set)
                // test cases

                BOOST_AUTO_TEST_CASE(selection_changed)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const list_selection_observer_set_type observer_set{};

                        observer_set.selection_changed();
                    }
                    {
                        list_selection_observer_set_type observer_set{};

                        observer_set.selection_changed();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
