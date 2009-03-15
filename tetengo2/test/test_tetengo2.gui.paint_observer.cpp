/*! \file
    \brief Test of class tetengo2::gui::paint_observer.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#include <cstddef>
//#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.paint_observer.h"

#include "stub_tetengo2.encode.h"
#include "stub_tetengo2.gui.canvas.h"


namespace
{
    // types

    typedef
        stub_tetengo2::gui::canvas<
            const void*,
            std::size_t,
            std::wstring,
            stub_tetengo2::encode,
            const void*
        >
        canvas_type;

    typedef tetengo2::gui::paint_observer<canvas_type> paint_observer_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(paint_observer)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_CHECKPOINT("");

        paint_observer_type();
    }

    BOOST_AUTO_TEST_CASE(paint)
    {
        BOOST_CHECKPOINT("");

        paint_observer_type paint_observer;
        canvas_type canvas(NULL, true);

        paint_observer.paint(&canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
