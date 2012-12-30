/*! \file
    \brief Test of class bobura::diagram_view.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <memory>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.unique.h>

#include "bobura.type_list.h"

#include "bobura.diagram_view.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::view_type_list, bobura::type::view::diagram_header>::type header_type;

    typedef
        boost::mpl::at<bobura::view_type_list, bobura::type::view::diagram_time_line_list>::type time_line_list_type;

    typedef
        boost::mpl::at<bobura::view_type_list, bobura::type::view::diagram_station_line_list>::type
        station_line_list_type;

    typedef
        boost::mpl::at<bobura::view_type_list, bobura::type::view::diagram_train_line_list>::type train_line_list_type;

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::picture_box>::type picture_box_type;

    typedef picture_box_type::position_type position_type;

    typedef tetengo2::gui::position<position_type>::left_type left_type;

    typedef tetengo2::gui::position<position_type>::top_type top_type;

    typedef picture_box_type::dimension_type dimension_type;

    typedef tetengo2::gui::dimension<dimension_type>::width_type width_type;

    typedef tetengo2::gui::dimension<dimension_type>::height_type height_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::canvas>::type canvas_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::solid_background>::type solid_background_type;

    typedef
        boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

    typedef
        bobura::diagram_view<
            header_type,
            time_line_list_type,
            station_line_list_type,
            train_line_list_type,
            model_type,
            canvas_type,
            solid_background_type,
            message_catalog_type
        >
        view_type;

    typedef view_type::horizontal_scale_type horizontal_scale_type;

    typedef view_type::vertical_scale_type vertical_scale_type;


}


#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(diagram_view)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        const view_type view(model, message_catalog);
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);

        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const std::unique_ptr<canvas_type> p_canvas(picture_box.create_canvas());
        view.draw_on(
            *p_canvas, dimension_type(width_type(42), height_type(24)), position_type(left_type(2), top_type(3))
        );
    }

    BOOST_AUTO_TEST_CASE(horizontal_scale)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        const view_type view(model, message_catalog);

        view.horizontal_scale();
    }

    BOOST_AUTO_TEST_CASE(set_horizontal_scale)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);

        view.set_horizontal_scale(42);

        BOOST_CHECK(view.horizontal_scale() == horizontal_scale_type(42));

        view.set_horizontal_scale(24);

        BOOST_CHECK(view.horizontal_scale() == horizontal_scale_type(24));
    }

    BOOST_AUTO_TEST_CASE(vertical_scale)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        const view_type view(model, message_catalog);

        view.vertical_scale();
    }

    BOOST_AUTO_TEST_CASE(set_vertical_scale)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);

        view.set_vertical_scale(42);

        BOOST_CHECK(view.vertical_scale() == vertical_scale_type(42));

        view.set_vertical_scale(24);

        BOOST_CHECK(view.vertical_scale() == vertical_scale_type(24));
    }

    BOOST_AUTO_TEST_CASE(dimension)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        const view_type view(model, message_catalog);

        view.dimension();
    }

    BOOST_AUTO_TEST_CASE(update_dimension)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);

        view.update_dimension();
    }

    BOOST_AUTO_TEST_CASE(page_size)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        const view_type view(model, message_catalog);

        view.page_size(dimension_type(width_type(42), height_type(24)));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif
