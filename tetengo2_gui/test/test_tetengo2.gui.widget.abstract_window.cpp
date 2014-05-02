/*! \file
    \brief Test of class tetengo2::gui::widget::abstract_window.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "tetengo2.stdalt.h"
#include "tetengo2.text.h"

#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<test_tetengo2::gui::type_list, test_tetengo2::gui::type::path>::type path_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::gui_common_type_list, test_tetengo2::gui::type::gui_common::icon>::type
        icon_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::menu_type_list, test_tetengo2::gui::type::menu::menu_bar>::type
        menu_bar_type;

    typedef
        boost::mpl::at<test_tetengo2::gui::widget_type_list, test_tetengo2::gui::type::widget::abstract_window>::type
        abstract_window_type;

    class concrete_window : public abstract_window_type
    {
    public:
        concrete_window(const bool file_droppable = false)
        :
        abstract_window_type(
            abstract_window_type::scroll_bar_style_type::none, file_droppable, message_handler_map_type()
        ),
        m_p_details(tetengo2::stdalt::make_unique<details_type>())
        {
            this->initialize(this);
        }

        virtual ~concrete_window()
        TETENGO2_STDALT_NOEXCEPT = default;


    private:
        details_ptr_type m_p_details;

        virtual const details_type& details_impl()
        const override
        {
            return *m_p_details;
        }

        virtual details_type& details_impl()
        override
        {
            return *m_p_details;
        }


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

        {
            const concrete_window window(false);
        }
        {
            const concrete_window window(true);
        }
    }

    BOOST_AUTO_TEST_CASE(activate)
    {
        BOOST_TEST_PASSPOINT();

        concrete_window window;

        window.activate();
    }

    BOOST_AUTO_TEST_CASE(window_state)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_window window;

        window.window_state();
    }

    BOOST_AUTO_TEST_CASE(set_window_state)
    {
        BOOST_TEST_PASSPOINT();

        concrete_window window;

        window.set_window_state(abstract_window_type::window_state_type::normal);
    }

    BOOST_AUTO_TEST_CASE(normal_dimension)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_window window;

        window.normal_dimension();
    }

    BOOST_AUTO_TEST_CASE(has_icon)
    {
        BOOST_TEST_PASSPOINT();

        const concrete_window window;

        BOOST_CHECK(!window.has_icon());
    }

    BOOST_AUTO_TEST_CASE(icon)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_window window;

            BOOST_CHECK_THROW(window.icon(), std::logic_error);
        }
        {
            concrete_window window;

            BOOST_CHECK_THROW(window.icon(), std::logic_error);
        }
    }

    BOOST_AUTO_TEST_CASE(set_icon)
    {
        BOOST_TEST_PASSPOINT();

        concrete_window window;

        std::unique_ptr<icon_type> p_icon =
            tetengo2::stdalt::make_unique<icon_type>(path_type(TETENGO2_TEXT("hoge.ico")));
        window.set_icon(std::move(p_icon));

        BOOST_REQUIRE(window.has_icon());
        const icon_type& icon = window.icon();
        BOOST_CHECK(icon.path() == path_type(TETENGO2_TEXT("hoge.ico")));
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

            auto p_menu_bar = tetengo2::stdalt::make_unique<menu_bar_type>();
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

            auto p_menu_bar = tetengo2::stdalt::make_unique<menu_bar_type>();
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

        auto p_menu_bar = tetengo2::stdalt::make_unique<menu_bar_type>();
        window.set_menu_bar(std::move(p_menu_bar));

        auto p_menu_bar2 = tetengo2::stdalt::make_unique<menu_bar_type>();
        window.set_menu_bar(std::move(p_menu_bar2));
    }

    BOOST_AUTO_TEST_CASE(file_droppable)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_window window(false);

            BOOST_CHECK(!window.file_droppable());
        }
        {
            const concrete_window window(true);

            BOOST_CHECK(window.file_droppable());
        }
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

    BOOST_AUTO_TEST_CASE(file_drop_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            const concrete_window window;

            window.file_drop_observer_set();
        }
        {
            concrete_window window;

            window.file_drop_observer_set();
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
