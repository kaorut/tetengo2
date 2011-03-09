/*! \file
    \brief Test of class tetengo2::gui::menu.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <string>
//#include <utility>

#include <boost/test/unit_test.hpp>

#include "tetengo2.cpp0x.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.menu.h"
#include "tetengo2.encoder.h"
#include "tetengo2.encoding.locale.h"
#include "tetengo2.gui.menu_observer_set.h"
#include "tetengo2.gui.traits.menu_traits.h"

#include "tetengo2.gui.menu.h"


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
        tetengo2::gui::menu<menu_traits_type, menu_details_type> menu_type;

    class concrete_menu : public menu_type
    {
    public:
        // constructors and destructors

        concrete_menu(std::string&& text)
        :
        menu_type(
            std::forward<std::string>(text), menu_details_type::create_menu()
        )
        {}

        
    private:
        // virtual functions

        virtual const style_type& style_impl()
        const
        {
            return menu_details_type::menu_command_style();
        }


    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(menu)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_menu menu(std::string("Tetengo"));
    }

    BOOST_AUTO_TEST_CASE(text)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_menu menu(std::string("Tetengo"));

        BOOST_CHECK(menu.text() == "Tetengo");
    }

    BOOST_AUTO_TEST_CASE(style)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_menu menu(std::string("Tetengo"));

        BOOST_CHECK(
            &menu.style() == &menu_details_type::menu_command_style()
        );
    }

    BOOST_AUTO_TEST_CASE(select)
    {
        BOOST_TEST_PASSPOINT();

        concrete_menu menu(std::string("Tetengo"));

        menu.select();
    }

    BOOST_AUTO_TEST_CASE(menu_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(std::string("Tetengo"));

            menu.menu_observer_set();
        }
        {
            concrete_menu menu(std::string("Tetengo"));

            menu.menu_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(begin)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(std::string("Tetengo"));

            menu.begin();
        }
        {
            concrete_menu menu(std::string("Tetengo"));

            menu.begin();
        }
    }

    BOOST_AUTO_TEST_CASE(end)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(std::string("Tetengo"));

            menu.end();
        }
        {
            concrete_menu menu(std::string("Tetengo"));

            menu.end();
        }
    }

    BOOST_AUTO_TEST_CASE(recursive_begin)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(std::string("Tetengo"));

            menu.recursive_begin();
        }
        {
            concrete_menu menu(std::string("Tetengo"));

            menu.recursive_begin();
        }
    }

    BOOST_AUTO_TEST_CASE(recursive_end)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_menu menu(std::string("Tetengo"));

            menu.recursive_end();
        }
        {
            concrete_menu menu(std::string("Tetengo"));

            menu.recursive_end();
        }
    }

    BOOST_AUTO_TEST_CASE(insert)
    {
        BOOST_TEST_PASSPOINT();

        concrete_menu menu(std::string("Tetengo"));
        tetengo2::cpp0x::unique_ptr<menu_type>::type p_child(
            new concrete_menu(std::string("Hoge"))
        );

        // Assertion fails.
        //menu.insert(menu.begin(), std::move(p_child));
    }

    BOOST_AUTO_TEST_CASE(erase)
    {
        BOOST_TEST_PASSPOINT();

        concrete_menu menu(std::string("Tetengo"));

        // Assertion fails.
        //menu.erase(menu.begin(), menu.begin());
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
