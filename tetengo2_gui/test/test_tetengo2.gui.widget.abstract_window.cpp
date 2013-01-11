/*! \file
    \brief Test of class tetengo2::gui::widget::abstract_window.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <memory>
//#include <stdexcept>
//#include <utility>

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.unique.h>

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::menu_bar>::type
        menu_bar_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::abstract_window>::type
        abstract_window_type;

    class concrete_window : public abstract_window_type
    {
    public:
        concrete_window()
        :
        abstract_window_type(abstract_window_type::scroll_bar_style_type::none, message_handler_map_type()),
        m_p_details(tetengo2::make_unique<details_type>())
        {
            initialize(this);
        }

        virtual ~concrete_window()
        TETENGO2_CPP11_NOEXCEPT
        {}

        virtual boost::optional<const details_type&> details_impl()
        const
        {
            return boost::make_optional<const details_type&>(*m_p_details);
        }

        virtual boost::optional<details_type&> details_impl()
        {
            return boost::make_optional<details_type&>(*m_p_details);
        }


    private:
        details_ptr_type m_p_details;


    };


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(abstract_window)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_window window;
    }

    BOOST_AUTO_TEST_CASE(activate)
    {
        BOOST_TEST_PASSPOINT();

        concrete_window window;

        window.activate();
    }

    BOOST_AUTO_TEST_CASE(has_menu_bar)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_window window;

            BOOST_CHECK(!window.has_menu_bar());
        }
        {
            concrete_window window;

            std::unique_ptr<menu_bar_type> p_menu_bar(tetengo2::make_unique<menu_bar_type>());
            window.set_menu_bar(std::move(p_menu_bar));

            BOOST_CHECK(window.has_menu_bar());
       }
    }

    BOOST_AUTO_TEST_CASE(menu_bar)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_window window;

            BOOST_CHECK_THROW(window.menu_bar(), std::logic_error);
        }
        {
            concrete_window window;

            BOOST_CHECK_THROW(window.menu_bar(), std::logic_error);
        }
        {
            concrete_window window;

            std::unique_ptr<menu_bar_type> p_menu_bar(tetengo2::make_unique<menu_bar_type>());
            window.set_menu_bar(std::move(p_menu_bar));

            window.menu_bar();

            const abstract_window_type& const_window = window;
            const_window.menu_bar();
        }
    }

    BOOST_AUTO_TEST_CASE(set_menu_bar)
    {
        BOOST_TEST_PASSPOINT();

        concrete_window window;

        std::unique_ptr<menu_bar_type> p_menu_bar(tetengo2::make_unique<menu_bar_type>());
        window.set_menu_bar(std::move(p_menu_bar));

        std::unique_ptr<menu_bar_type> p_menu_bar2(tetengo2::make_unique<menu_bar_type>());
        window.set_menu_bar(std::move(p_menu_bar2));
    }

    BOOST_AUTO_TEST_CASE(window_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_window window;

            window.window_observer_set();
        }
        {
            concrete_window window;

            window.window_observer_set();
        }
    }

    BOOST_AUTO_TEST_CASE(close)
    {
        BOOST_TEST_PASSPOINT();

        concrete_window window;

        window.close();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
