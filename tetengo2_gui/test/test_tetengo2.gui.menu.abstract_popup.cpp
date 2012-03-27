/*! \file
    \brief Test of class tetengo2::gui::menu::abstract_popup.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <iterator>
//#include <memory>
//#include <string>
//#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>
//#include <boost/utility.hpp>

#include "tetengo2.unique.h"

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            test_tetengo2::gui::menu_type_list,
            test_tetengo2::gui::type::menu::abstract_popup
        >::type
        abstract_popup_menu_type;

    typedef abstract_popup_menu_type::base_type menu_base_type;

    class concrete_popup_menu : public abstract_popup_menu_type
    {
    public:
        // constructors and destructor

        concrete_popup_menu(std::string&& text)
        :
        abstract_popup_menu_type(
            std::forward<std::string>(text),
            menu_details_type::create_popup_menu()
        )
        {}


    private:
        // virtual functions

        virtual const style_type& style_impl()
        const
        {
            return menu_details_type::popup_menu_style();
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

        const concrete_popup_menu popup_menu(std::string("Tetengo"));
    }

    BOOST_AUTO_TEST_CASE(insert)
    {
        BOOST_TEST_PASSPOINT();

        concrete_popup_menu popup_menu(std::string("Tetengo"));
        std::unique_ptr<menu_base_type> p_child1(
            tetengo2::make_unique<concrete_popup_menu>(std::string("Hoge"))
        );
        std::unique_ptr<menu_base_type> p_child2(
            tetengo2::make_unique<concrete_popup_menu>(std::string("Fuga"))
        );

        popup_menu.insert(popup_menu.end(), std::move(p_child1));
        BOOST_CHECK_EQUAL(
            std::distance(popup_menu.begin(), popup_menu.end()), 1
        );
        popup_menu.insert(popup_menu.begin(), std::move(p_child2));
        BOOST_CHECK_EQUAL(
            std::distance(popup_menu.begin(), popup_menu.end()), 2
        );

        BOOST_CHECK(popup_menu.begin()->text() == "Fuga");
        BOOST_CHECK(boost::next(popup_menu.begin())->text() == "Hoge");
    }

    BOOST_AUTO_TEST_CASE(erase)
    {
        BOOST_TEST_PASSPOINT();

        concrete_popup_menu popup_menu(std::string("Tetengo"));
        std::unique_ptr<menu_base_type> p_child1(
            tetengo2::make_unique<concrete_popup_menu>(std::string("Hoge"))
        );
        std::unique_ptr<menu_base_type> p_child2(
            tetengo2::make_unique<concrete_popup_menu>(std::string("Fuga"))
        );
        popup_menu.insert(popup_menu.end(), std::move(p_child1));
        popup_menu.insert(popup_menu.begin(), std::move(p_child2));

        popup_menu.erase(popup_menu.begin(), popup_menu.begin());
        BOOST_CHECK_EQUAL(
            std::distance(popup_menu.begin(), popup_menu.end()), 2
        );

        popup_menu.erase(popup_menu.begin(), boost::next(popup_menu.begin()));
        BOOST_CHECK_EQUAL(
            std::distance(popup_menu.begin(), popup_menu.end()), 1
        );
        BOOST_CHECK(popup_menu.begin()->text() == "Hoge");

        popup_menu.erase(popup_menu.begin(), popup_menu.end());
        BOOST_CHECK_EQUAL(
            std::distance(popup_menu.begin(), popup_menu.end()), 0
        );
    }



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
