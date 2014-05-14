/*! \file
    \brief Test of class tetengo2::gui::menu::recursive_iterator.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using menu_base_type =
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::menu_base>::type;

    using popup_menu_type =
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::popup>::type;

    using string_type = boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type;

    using iterator_type =
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::recursive_iterator>::type;


    // functions

    std::unique_ptr<menu_base_type> create_menu()
    {
        auto p_menu = tetengo2::stdalt::make_unique<popup_menu_type>(string_type(TETENGO2_TEXT("0")));

        p_menu->insert(p_menu->end(), tetengo2::stdalt::make_unique<popup_menu_type>(string_type(TETENGO2_TEXT("1"))));
        p_menu->begin()->insert(
            p_menu->begin()->end(), tetengo2::stdalt::make_unique<popup_menu_type>(string_type(TETENGO2_TEXT("2")))
        );
        p_menu->insert(p_menu->end(), tetengo2::stdalt::make_unique<popup_menu_type>(string_type(TETENGO2_TEXT("3"))));

        return std::move(p_menu);
    }


}

BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
BOOST_AUTO_TEST_SUITE(recursive_iterator)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            const iterator_type iterator;
        }
        {
            const auto p_menu = create_menu();
            const iterator_type iterator(p_menu.get());
        }
    }

    BOOST_AUTO_TEST_CASE(dereference)
    {
        BOOST_TEST_PASSPOINT();

        const auto p_menu = create_menu();
        const iterator_type iterator(p_menu.get());

        *iterator;
    }

    BOOST_AUTO_TEST_CASE(equal)
    {
        BOOST_TEST_PASSPOINT();

        {
            const iterator_type iterator1;
            const iterator_type iterator2;

            BOOST_CHECK(iterator1 == iterator2);
        }
        {
            const auto p_menu = create_menu();
            const iterator_type iterator1(p_menu.get());
            const iterator_type iterator2(p_menu.get());

            BOOST_CHECK(iterator1 == iterator2);
        }
        {
            const auto p_menu = create_menu();
            const iterator_type iterator1(p_menu.get());
            const iterator_type iterator2;

            BOOST_CHECK(iterator1 != iterator2);
        }
    }

    BOOST_AUTO_TEST_CASE(increment)
    {
        BOOST_TEST_PASSPOINT();

        {
            const auto p_menu = create_menu();
            iterator_type iterator(p_menu.get());

            BOOST_CHECK(iterator->text() == string_type(TETENGO2_TEXT("0")));
            ++iterator;
            BOOST_CHECK(iterator->text() == string_type(TETENGO2_TEXT("1")));
            ++iterator;
            BOOST_CHECK(iterator->text() == string_type(TETENGO2_TEXT("2")));
            ++iterator;
            BOOST_CHECK(iterator->text() == string_type(TETENGO2_TEXT("3")));
            ++iterator;
            BOOST_CHECK(iterator == iterator_type());
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
