/*! \file
    \brief Test of class tetengo2::gui::paint_observer_set.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>

#include <boost/test/unit_test.hpp>

#include "stub_tetengo2.gui.font.h"
#include "stub_tetengo2.gui.canvas.h"
#include "tetengo2.encoder.h"
#include "tetengo2.encoding.locale.h"
#include "tetengo2.gui.paint_observer_set.h"


namespace
{
    // types

    typedef tetengo2::encoding::locale<std::wstring> internal_encoding_type;

    typedef tetengo2::encoding::locale<std::wstring> ui_encoding_type;

    typedef
        tetengo2::encoder<internal_encoding_type, ui_encoding_type>
        ui_encoder_type;

    typedef stub_tetengo2::gui::font<std::wstring, std::size_t> font_type;

    typedef
        stub_tetengo2::gui::canvas<
            const void*,
            std::size_t,
            std::wstring,
            ui_encoder_type,
            const void*,
            font_type
        >
        canvas_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(paint_observer_set)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const tetengo2::gui::paint_observer_set<canvas_type> observer_set;
    }

    BOOST_AUTO_TEST_CASE(destroyed)
    {
        BOOST_TEST_PASSPOINT();

        {
            const tetengo2::gui::paint_observer_set<canvas_type> observer_set;

            observer_set.paint();
        }
        {
            tetengo2::gui::paint_observer_set<canvas_type> observer_set;

            observer_set.paint();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
