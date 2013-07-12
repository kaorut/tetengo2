/*! \file
    \brief Test of class tetengo2::gui::widget::list_box.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <stdexcept>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.text.h"

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::window>::type
        window_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::list_box>::type
        list_box_type;

    typedef list_box_type::string_type string_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(list_box)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);
        }
        {
            window_type parent;
            const list_box_type list_box(parent, list_box_type::scroll_bar_style_type::both);
        }
    }

    BOOST_AUTO_TEST_CASE(item_count)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);

            BOOST_CHECK_EQUAL(list_box.item_count(), 0U);
        }
        {
            window_type parent;
            list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);
            list_box.insert_item(0, string_type(TETENGO2_TEXT("hoge")));

            BOOST_CHECK_EQUAL(list_box.item_count(), 1U);
        }
    }

    BOOST_AUTO_TEST_CASE(item)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);
            list_box.insert_item(0, string_type(TETENGO2_TEXT("hoge")));

            BOOST_CHECK(list_box.item(0) == string_type(TETENGO2_TEXT("hoge")));
        }
        {
            window_type parent;
            const list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);

            BOOST_CHECK_THROW(list_box.item(0), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(set_item)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);
            list_box.insert_item(0, string_type(TETENGO2_TEXT("hoge")));

            list_box.set_item(0, string_type(TETENGO2_TEXT("fuga")));

            BOOST_CHECK(list_box.item(0) == string_type(TETENGO2_TEXT("fuga")));
        }
        {
            window_type parent;
            list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);

            BOOST_CHECK_THROW(list_box.set_item(0, string_type(TETENGO2_TEXT("fuga"))), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(insert_item)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);

            list_box.insert_item(0, string_type(TETENGO2_TEXT("hoge")));
            list_box.insert_item(1, string_type(TETENGO2_TEXT("fuga")));
            list_box.insert_item(0, string_type(TETENGO2_TEXT("piyo")));
            list_box.insert_item(2, string_type(TETENGO2_TEXT("piyoyo")));

            BOOST_CHECK_EQUAL(list_box.item_count(), 4U);
            BOOST_CHECK(list_box.item(0) == string_type(TETENGO2_TEXT("piyo")));
            BOOST_CHECK(list_box.item(1) == string_type(TETENGO2_TEXT("hoge")));
            BOOST_CHECK(list_box.item(2) == string_type(TETENGO2_TEXT("piyoyo")));
            BOOST_CHECK(list_box.item(3) == string_type(TETENGO2_TEXT("fuga")));
        }
        {
            window_type parent;
            list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);

            BOOST_CHECK_THROW(list_box.insert_item(1, string_type(TETENGO2_TEXT("fuga"))), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(erase_item)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);
            list_box.insert_item(0, string_type(TETENGO2_TEXT("hoge")));

            list_box.erase_item(0);

            BOOST_CHECK_EQUAL(list_box.item_count(), 0U);
        }
        {
            window_type parent;
            list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);

            BOOST_CHECK_THROW(list_box.erase_item(0), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(clear)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);
        list_box.insert_item(0, string_type(TETENGO2_TEXT("hoge")));
        list_box.insert_item(1, string_type(TETENGO2_TEXT("fuga")));

        list_box.clear();

        BOOST_CHECK_EQUAL(list_box.item_count(), 0U);
    }

    BOOST_AUTO_TEST_CASE(selected_item_index)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);

        BOOST_CHECK(!list_box.selected_item_index());
    }

    BOOST_AUTO_TEST_CASE(select_item)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);
            list_box.insert_item(0, string_type(TETENGO2_TEXT("hoge")));

            list_box.select_item(0);

            BOOST_CHECK(list_box.selected_item_index());
            BOOST_CHECK_EQUAL(*list_box.selected_item_index(), 0U);
        }
        {
            window_type parent;
            list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);

            BOOST_CHECK_THROW(list_box.select_item(0), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(list_box_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent;
            const list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);

            list_box.list_box_observer_set();
        }
        {
            window_type parent;
            list_box_type list_box(parent, list_box_type::scroll_bar_style_type::none);

            list_box.list_box_observer_set();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()