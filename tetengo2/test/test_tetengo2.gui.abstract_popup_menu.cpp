/*! \file
    \brief Test of class tetengo2::gui::abstract_popup_menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#include <iterator>
#include <string>
#include <utility>

#include <boost/test/unit_test.hpp>
#include <boost/utility.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.menu.h"
#include "tetengo2.encoder.h"
#include "tetengo2.encoding.locale.h"
#include "tetengo2.gui.menu_observer_set.h"
#include "tetengo2.gui.traits.menu_traits.h"

#include "tetengo2.gui.abstract_popup_menu.h"


namespace
{
    // types

    typedef
        tetengo2::encoding::locale<
            std::string, tetengo2::detail::stub::encoding
        >
        encoding_type;

    typedef tetengo2::encoder<encoding_type, encoding_type> encoder_type;

    typedef
        tetengo2::gui::traits::menu_traits<
            std::string, encoder_type, tetengo2::gui::menu_observer_set
        >
        menu_traits_type;

    typedef tetengo2::detail::stub::menu menu_details_type;

    typedef
        tetengo2::gui::abstract_popup_menu<
            menu_traits_type, menu_details_type
        >
        abstract_popup_menu_type;

    typedef abstract_popup_menu_type::base_type menu_type;

    class concrete_popup_menu : public abstract_popup_menu_type
    {
    public:
        // constructors and destructors

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
BOOST_AUTO_TEST_SUITE(abstract_popup_menu)
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
        tetengo2::cpp0x::unique_ptr<menu_type>::type p_child1(
            new concrete_popup_menu(std::string("Hoge"))
        );
        tetengo2::cpp0x::unique_ptr<menu_type>::type p_child2(
            new concrete_popup_menu(std::string("Fuga"))
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
        tetengo2::cpp0x::unique_ptr<menu_type>::type p_child1(
            new concrete_popup_menu(std::string("Hoge"))
        );
        tetengo2::cpp0x::unique_ptr<menu_type>::type p_child2(
            new concrete_popup_menu(std::string("Fuga"))
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
