/*! \file
    \brief Test of class tetengo2::gui::paint_observer.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#include <cstddef>
//#include <string>

#include <boost/test/unit_test.hpp>

#include "stub_tetengo2.gui.canvas.h"
#include "stub_tetengo2.gui.font.h"
#include "tetengo2.encoder.h"
#include "tetengo2.encoding.locale.h"

#include "tetengo2.gui.paint_observer.h"


namespace
{
    // types

    typedef
        tetengo2::encoder<
            tetengo2::encoding::locale<std::wstring>,
            tetengo2::encoding::locale<std::wstring>
        >
        encoder_type;

    typedef
        stub_tetengo2::gui::canvas<
            const void*,
            std::size_t,
            std::wstring,
            encoder_type,
            const void*,
            stub_tetengo2::gui::font<std::wstring, std::size_t>
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
        BOOST_TEST_PASSPOINT();

        paint_observer_type();
    }

    BOOST_AUTO_TEST_CASE(paint)
    {
        BOOST_TEST_PASSPOINT();

        paint_observer_type paint_observer;
        canvas_type canvas(NULL, true);

        paint_observer.paint(&canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
