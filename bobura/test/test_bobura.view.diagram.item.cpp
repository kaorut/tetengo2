/*! \file
    \brief Test of class bobura::view::diagram::item.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <memory>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.gui.measure.h>

#include "bobura.type_list.h"

#include "bobura.view.diagram.item.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::picture_box>::type picture_box_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::canvas>::type canvas_type;

    typedef canvas_type::position_type position_type;

    typedef tetengo2::gui::position<position_type>::left_type left_type;

    typedef tetengo2::gui::position<position_type>::top_type top_type;

    typedef bobura::view::diagram::item<canvas_type> item_type;

    class concrete_item : public item_type
    {
    public:
        concrete_item()
        :
        m_selected(false)
        {}

    private:
        bool m_selected;

        virtual void draw_on_impl(canvas_type& canvas)
        const
        {}

        virtual item_type* p_item_by_position_impl(const position_type& position)
        {
            return NULL;
        }

        virtual bool selected_impl()
        const
        {
            return m_selected;
        }

        virtual void set_selected_impl(const bool selected)
        {
            m_selected = selected;
        }

    };


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(view)
BOOST_AUTO_TEST_SUITE(diagram)
BOOST_AUTO_TEST_SUITE(item)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_item item;
    }

    BOOST_AUTO_TEST_CASE(draw_on)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_item item;

        window_type window;
        const picture_box_type picture_box(window, picture_box_type::scroll_bar_style_type::both);
        const std::unique_ptr<canvas_type> p_canvas(picture_box.create_canvas());
        item.draw_on(*p_canvas);
    }

    BOOST_AUTO_TEST_CASE(p_item_by_position)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_item item;

            item.p_item_by_position(position_type(left_type(42), top_type(24)));
        }
        {
            concrete_item item;

            item.p_item_by_position(position_type(left_type(42), top_type(24)));
        }
    }

    BOOST_AUTO_TEST_CASE(selected)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_item item;

        BOOST_CHECK(!item.selected());
    }

    BOOST_AUTO_TEST_CASE(set_selected)
    {
        BOOST_TEST_PASSPOINT();

        concrete_item item;

        item.set_selected(true);

        BOOST_CHECK(item.selected());

        item.set_selected(false);

        BOOST_CHECK(!item.selected());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
