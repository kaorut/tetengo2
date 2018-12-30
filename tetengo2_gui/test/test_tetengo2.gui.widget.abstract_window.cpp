/*! \file
    \brief Test of class tetengo2::gui::widget::abstract_window.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <sstream>
#include <stdexcept>
#include <utility>

#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/base/widget.h>
#include <tetengo2/detail/stub/widget.h>
#include <tetengo2/gui/icon.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/widget/abstract_window.h>
#include <tetengo2/gui/widget/widget.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using icon_type = tetengo2::gui::icon;

    using string_type = common_type_list_type::string_type;

    using menu_bar_type = tetengo2::gui::menu::menu_bar;

    using abstract_window_type = tetengo2::gui::widget::abstract_window;

    class concrete_window : public abstract_window_type
    {
    public:
        concrete_window(const bool file_droppable = false)
        : abstract_window_type{ abstract_window_type::scroll_bar_style_type::none,
                                file_droppable,
                                message_handler_map_type{} },
          m_p_details{ std::make_unique<tetengo2::detail::stub::widget::widget_details_type>() }
        {
            abstract_window_type::initialize(this);
        }

        virtual ~concrete_window() = default;


    private:
        typename widget_details_type::widget_details_ptr_type m_p_details;

        virtual const details_type& details_impl() const override
        {
            return *static_cast<const details_type*>(m_p_details.get());
        }

        virtual details_type& details_impl() override
        {
            return *static_cast<details_type*>(m_p_details.get());
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
                        const concrete_window window{ false };
                    }
                    {
                        const concrete_window window{ true };
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

                    BOOST_TEST(!window.has_icon());
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

                    using path_type = tetengo2::stdalt::filesystem::path;
                    using path_string_type = path_type::string_type;

                    std::unique_ptr<icon_type> p_icon =
                        std::make_unique<icon_type>(path_type{ path_string_type{ TETENGO2_TEXT("hoge.ico") } });
                    window.set_icon(std::move(p_icon));

                    BOOST_TEST_REQUIRE(window.has_icon());
                    const icon_type& icon = window.icon();
                    BOOST_CHECK(icon.path() == path_type{ path_string_type{ TETENGO2_TEXT("hoge.ico") } });
                }

                BOOST_AUTO_TEST_CASE(has_menu_bar)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const concrete_window window;

                        BOOST_TEST(!window.has_menu_bar());
                    }
                    {
                        concrete_window window;

                        auto p_menu_bar = std::make_unique<menu_bar_type>();
                        window.set_menu_bar(std::move(p_menu_bar));

                        BOOST_TEST(window.has_menu_bar());
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

                        auto p_menu_bar = std::make_unique<menu_bar_type>();
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

                    auto p_menu_bar = std::make_unique<menu_bar_type>();
                    window.set_menu_bar(std::move(p_menu_bar));

                    auto p_menu_bar2 = std::make_unique<menu_bar_type>();
                    window.set_menu_bar(std::move(p_menu_bar2));
                }

                BOOST_AUTO_TEST_CASE(file_droppable)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const concrete_window window{ false };

                        BOOST_TEST(!window.file_droppable());
                    }
                    {
                        const concrete_window window{ true };

                        BOOST_TEST(window.file_droppable());
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
