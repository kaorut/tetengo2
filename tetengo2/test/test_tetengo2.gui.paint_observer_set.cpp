/*! \file
    \brief Test of class tetengo2::gui::paint_observer_set.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>
//#include <utility>

#include <boost/test/unit_test.hpp>

#include "stub_tetengo2.gui.font.h"
#include "stub_tetengo2.gui.drawing.picture.h"
#include "stub_tetengo2.gui.drawing.widget_canvas.h"
#include "tetengo2.encoder.h"
#include "tetengo2.encoding.locale.h"
#include "tetengo2.gui.drawing.background.h"
#include "tetengo2.gui.paint_observer_set.h"


namespace
{
    // types

    typedef std::pair<std::size_t, std::size_t> dimension_type;

    typedef tetengo2::encoding::locale<std::wstring> internal_encoding_type;

    typedef tetengo2::encoding::locale<std::wstring> ui_encoding_type;

    typedef
        tetengo2::encoder<internal_encoding_type, ui_encoding_type>
        ui_encoder_type;

    typedef tetengo2::gui::drawing::background<const void*> background_type;

    typedef stub_tetengo2::gui::font<std::wstring, std::size_t> font_type;

    typedef stub_tetengo2::gui::drawing::picture<std::size_t> picture_type;

    typedef
        stub_tetengo2::gui::drawing::widget_canvas<
            const void*,
            std::size_t,
            std::wstring,
            dimension_type,
            ui_encoder_type,
            background_type,
            font_type,
            picture_type
        >
        canvas_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(paint_observer_set)
    // test cases

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
