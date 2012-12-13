/*! \file
    \brief Test of class bobura::message::diagram_picture_box.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"

#include "bobura.message.diagram_picture_box.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::canvas>::type canvas_type;

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef
        boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

    typedef boost::mpl::at<bobura::view_type_list, bobura::type::view::view>::type view_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::position>::type position_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::picture_reader>::type picture_reader_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::picture_box>::type picture_box_type;

    typedef picture_box_type::mouse_observer_set_type mouse_observer_set_type;

    struct dummy_view_zoom_type
    {
    public:
        dummy_view_zoom_type(picture_box_type& picture_box, view_type& diagram_view)
        {}

        void horizontally_zoom_in(bool snap_to_scale_list)
        {}

        void horizontally_zoom_out(bool snap_to_scale_list)
        {}

        void vertically_zoom_in(bool snap_to_scale_list)
        {}

        void vertically_zoom_out(bool snap_to_scale_list)
        {}

    };

    typedef
        bobura::message::diagram_picture_box::mouse_wheeled<picture_box_type, view_type, dummy_view_zoom_type>
        mouse_wheeled_type;

    typedef picture_box_type::keyboard_observer_set_type::virtual_key_type virtual_key_type;

    typedef bobura::message::diagram_picture_box::keyboard_key_down<picture_box_type> keyboard_key_down_type;

    typedef
        bobura::message::diagram_picture_box::paint_paint<canvas_type, picture_box_type, view_type> paint_paint_type;

    typedef
        bobura::message::diagram_picture_box::scroll_bar_scrolled<picture_box_type, view_type>
        scroll_bar_scrolled_type;


    // functions

    void call_update_scroll_bars(view_type& view)
    {}


}


#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(diagram_picture_box)
BOOST_AUTO_TEST_SUITE(mouse_wheeled)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::vertical);
        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const mouse_wheeled_type mouse_wheeled(picture_box, view);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::vertical);
        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const mouse_wheeled_type mouse_wheeled(picture_box, view);

        mouse_wheeled(42, mouse_observer_set_type::direction_type::vertical, false, false, false);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(keyboard_key_down)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::none);
        const keyboard_key_down_type keyboard_key_down(picture_box);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::none);
        const keyboard_key_down_type keyboard_key_down(picture_box);

        keyboard_key_down(virtual_key_type::char_a(), false, false, false);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(paint_paint)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::none);
        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const paint_paint_type paint(picture_box, view, call_update_scroll_bars);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const paint_paint_type paint(picture_box, view, call_update_scroll_bars);

        std::unique_ptr<canvas_type> p_canvas(picture_box.create_canvas());
        paint(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(scroll_bar_scrolled)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const scroll_bar_scrolled_type scrolled(picture_box, view);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        const scroll_bar_scrolled_type scrolled(picture_box, view);

        scrolled(42);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif
