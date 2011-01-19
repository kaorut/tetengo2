/*! \file
    \brief Test of class tetengo2::gui::drawing::background.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.drawing.background.h"


namespace
{
    // types

    typedef tetengo2::gui::drawing::background<int> background_type;

    struct concrete_background : public background_type
    {
        concrete_background(const int handle)
        :
        background_type(handle)
        {}


    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(drawing)
BOOST_AUTO_TEST_SUITE(background)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        const concrete_background background(42);
    }

    BOOST_AUTO_TEST_CASE(handle)
    {
        const concrete_background background(42);

        BOOST_CHECK_EQUAL(background.handle(), 42);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
