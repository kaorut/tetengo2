/*! \file
    \brief Test of class tetengo2::gui::menu::abstract_popup.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <iterator>
#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/utility.hpp>

#include "tetengo2.stdalt.h"
#include "tetengo2.text.h"

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::menu_base>::type
        menu_base_type;

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::string>::type string_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::abstract_popup>::type
        abstract_popup_menu_type;

    class concrete_popup_menu : public abstract_popup_menu_type
    {
    public:
        // constructors and destructor

        concrete_popup_menu(string_type text)
        :
        abstract_popup_menu_type(std::move(text), menu_details_type::create_popup_menu())
        {}


    private:
        // virtual functions

        virtual const style_type& style_impl()
        const override
        {
            return menu_details_type::popup_menu_style<menu_base_type>();
        }


    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
BOOST_AUTO_TEST_SUITE(abstract_popup)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_popup_menu popup_menu(string_type(TETENGO2_TEXT("Tetengo")));
    }

    BOOST_AUTO_TEST_CASE(insert)
    {
        BOOST_TEST_PASSPOINT();

        concrete_popup_menu popup_menu(string_type(TETENGO2_TEXT("Tetengo")));
        auto p_child1 = tetengo2::stdalt::make_unique<concrete_popup_menu>(string_type(TETENGO2_TEXT("Hoge")));
        auto p_child2 = tetengo2::stdalt::make_unique<concrete_popup_menu>(string_type(TETENGO2_TEXT("Fuga")));

        popup_menu.insert(popup_menu.end(), std::move(p_child1));
        BOOST_CHECK_EQUAL(std::distance(popup_menu.begin(), popup_menu.end()), 1);
        popup_menu.insert(popup_menu.begin(), std::move(p_child2));
        BOOST_CHECK_EQUAL(std::distance(popup_menu.begin(), popup_menu.end()), 2);

        BOOST_CHECK(popup_menu.begin()->text() == string_type(TETENGO2_TEXT("Fuga")));
        BOOST_CHECK(boost::next(popup_menu.begin())->text() == string_type(TETENGO2_TEXT("Hoge")));
    }

    BOOST_AUTO_TEST_CASE(erase)
    {
        BOOST_TEST_PASSPOINT();

        concrete_popup_menu popup_menu(string_type(TETENGO2_TEXT("Tetengo")));
        auto p_child1 = tetengo2::stdalt::make_unique<concrete_popup_menu>(string_type(TETENGO2_TEXT("Hoge")));
        auto p_child2 = tetengo2::stdalt::make_unique<concrete_popup_menu>(string_type(TETENGO2_TEXT("Fuga")));
        popup_menu.insert(popup_menu.end(), std::move(p_child1));
        popup_menu.insert(popup_menu.begin(), std::move(p_child2));

        popup_menu.erase(popup_menu.begin(), popup_menu.begin());
        BOOST_CHECK_EQUAL(std::distance(popup_menu.begin(), popup_menu.end()), 2);

        popup_menu.erase(popup_menu.begin(), boost::next(popup_menu.begin()));
        BOOST_CHECK_EQUAL(std::distance(popup_menu.begin(), popup_menu.end()), 1);
        BOOST_CHECK(popup_menu.begin()->text() == string_type(TETENGO2_TEXT("Hoge")));

        popup_menu.erase(popup_menu.begin(), popup_menu.end());
        BOOST_CHECK_EQUAL(std::distance(popup_menu.begin(), popup_menu.end()), 0);
    }



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
