/*! \file
    \brief Test of class tetengo2::gui::message::paint_observer_set.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/drawing/canvas.h>
#include <tetengo2/gui/drawing/canvas_traits.h>
#include <tetengo2/gui/message/paint_observer_set.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using size_type = common_type_list_type::size_type;

    using canvas_traits_type =
        tetengo2::gui::drawing::canvas_traits<
            size_type,
            common_type_list_type::string_type,
            common_type_list_type::position_type,
            common_type_list_type::dimension_type,
            common_type_list_type::ui_encoder_type
        >;

    using drawing_details_type =
        detail_type_list_type::drawing_type;

    using canvas_type =
        tetengo2::gui::drawing::canvas<canvas_traits_type, drawing_details_type, detail_type_list_type::icon_type>;

    using paint_observer_set_type = tetengo2::gui::message::paint_observer_set<canvas_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(paint_observer_set)
    // test cases

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
