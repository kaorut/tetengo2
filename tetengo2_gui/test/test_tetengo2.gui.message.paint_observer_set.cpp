/*! \file
    \brief Test of class tetengo2::gui::message::paint_observer_set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <sstream>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/message/paint_observer_set.h>


namespace {
    // types

    using paint_observer_set_type = tetengo2::gui::message::paint_observer_set;
}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
    BOOST_AUTO_TEST_SUITE(gui)
        BOOST_AUTO_TEST_SUITE(message)
            BOOST_AUTO_TEST_SUITE(paint_observer_set)
                // test cases

                BOOST_AUTO_TEST_CASE(construction)
                {
                    BOOST_TEST_PASSPOINT();

                    const paint_observer_set_type observer_set{};
                }

                BOOST_AUTO_TEST_CASE(paint_background)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const paint_observer_set_type observer_set{};

                        observer_set.paint_background();
                    }
                    {
                        paint_observer_set_type observer_set{};

                        observer_set.paint_background();
                    }
                }

                BOOST_AUTO_TEST_CASE(paint)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const paint_observer_set_type observer_set{};

                        observer_set.paint();
                    }
                    {
                        paint_observer_set_type observer_set{};

                        observer_set.paint();
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
