/*! \file
    \brief Test of class tetengo2::gui::paint_observer.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#include <cstddef>
//#include <string>

#include <boost/test/unit_test.hpp>

#include "tetengo2.gui.paint_observer.h"

#include "stub_tetengo2.encode.h"
#include "stub_tetengo2.gui.canvas.h"

#include "test_tetengo2.gui.paint_observer.h"


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

namespace test_tetengo2 { namespace gui
{
    // functions

    boost::unit_test::test_suite* paint_observer::suite()
    {
        boost::unit_test::test_suite* const p_suite =
            BOOST_TEST_SUITE("test_tetengo2::gui::paint_observer");

        p_suite->add(BOOST_TEST_CASE(construction));
        p_suite->add(BOOST_TEST_CASE(paint));

        return p_suite;
    }

    void paint_observer::construction()
    {
        BOOST_CHECKPOINT("");

        paint_observer_type();
    }

    void paint_observer::paint()
    {
        BOOST_CHECKPOINT("");

        paint_observer_type paint_observer;
        canvas_type canvas(NULL);

        paint_observer.paint(&canvas);
    }


}}
