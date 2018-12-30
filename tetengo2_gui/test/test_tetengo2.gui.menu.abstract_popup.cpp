/*! \file
    \brief Test of class tetengo2::gui::menu::abstract_popup.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include <boost/iterator/indirect_iterator.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/preprocessor.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/menu.h>
#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_base.h>
#include <tetengo2/gui/menu/recursive_iterator.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace {
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using menu_base_type = tetengo2::gui::menu::menu_base;

    using abstract_popup_menu_type = tetengo2::gui::menu::abstract_popup;

    class concrete_popup_menu : public abstract_popup_menu_type
    {
    public:
        // constructors and destructor

        concrete_popup_menu(string_type text)
        : abstract_popup_menu_type{ std::move(text),
                                    tetengo2::detail::gui_detail_impl_set().menu_().create_popup_menu() }
        {}


    private:
        // virtual functions

        virtual const style_type& style_impl() const override
        {
            return tetengo2::detail::gui_detail_impl_set().menu_().popup_menu_style();
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

                    const concrete_popup_menu popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };
                }

                BOOST_AUTO_TEST_CASE(insert_impl)
                {
                    BOOST_TEST_PASSPOINT();

                    concrete_popup_menu popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };
                    auto p_child1 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Hoge") });
                    auto p_child2 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Fuga") });

                    popup_menu.insert(popup_menu.end(), std::move(p_child1));
                    BOOST_TEST(std::distance(popup_menu.begin(), popup_menu.end()) == 1);
                    popup_menu.insert(popup_menu.begin(), std::move(p_child2));
                    BOOST_TEST(std::distance(popup_menu.begin(), popup_menu.end()) == 2);

                    BOOST_CHECK(popup_menu.begin()->text() == string_type{ TETENGO2_TEXT("Fuga") });
                    BOOST_CHECK(std::next(popup_menu.begin())->text() == string_type{ TETENGO2_TEXT("Hoge") });
                }

                BOOST_AUTO_TEST_CASE(erase_impl)
                {
                    BOOST_TEST_PASSPOINT();

                    concrete_popup_menu popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };
                    auto p_child1 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Hoge") });
                    auto p_child2 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Fuga") });
                    popup_menu.insert(popup_menu.end(), std::move(p_child1));
                    popup_menu.insert(popup_menu.begin(), std::move(p_child2));

                    popup_menu.erase(popup_menu.begin(), popup_menu.begin());
                    BOOST_TEST(std::distance(popup_menu.begin(), popup_menu.end()) == 2);

                    popup_menu.erase(popup_menu.begin(), std::next(popup_menu.begin()));
                    BOOST_TEST(std::distance(popup_menu.begin(), popup_menu.end()) == 1);
                    BOOST_CHECK(popup_menu.begin()->text() == string_type{ TETENGO2_TEXT("Hoge") });

                    popup_menu.erase(popup_menu.begin(), popup_menu.end());
                    BOOST_TEST(std::distance(popup_menu.begin(), popup_menu.end()) == 0);
                }

                BOOST_AUTO_TEST_CASE(begin_impl)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const concrete_popup_menu popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };

                        popup_menu.begin();
                    }
                    {
                        concrete_popup_menu popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };

                        popup_menu.begin();
                    }
                }

                BOOST_AUTO_TEST_CASE(end_impl)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        concrete_popup_menu popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };
                        auto p_child1 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Hoge") });
                        auto p_child2 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Fuga") });
                        auto p_child3 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Piyo") });
                        popup_menu.insert(popup_menu.end(), std::move(p_child1));
                        popup_menu.begin()->insert(popup_menu.begin()->end(), std::move(p_child2));
                        popup_menu.insert(popup_menu.end(), std::move(p_child3));

                        const abstract_popup_menu_type& const_popup_menu = popup_menu;

                        BOOST_TEST_REQUIRE(std::distance(const_popup_menu.begin(), const_popup_menu.end()) == 2);
                        BOOST_CHECK(const_popup_menu.begin()->text() == string_type{ TETENGO2_TEXT("Hoge") });
                        BOOST_CHECK(
                            std::next(const_popup_menu.begin())->text() == string_type{ TETENGO2_TEXT("Piyo") });
                    }
                    {
                        concrete_popup_menu popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };
                        auto p_child1 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Hoge") });
                        auto p_child2 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Fuga") });
                        auto p_child3 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Piyo") });
                        popup_menu.insert(popup_menu.end(), std::move(p_child1));
                        popup_menu.begin()->insert(popup_menu.begin()->end(), std::move(p_child2));
                        popup_menu.insert(popup_menu.end(), std::move(p_child3));

                        BOOST_TEST_REQUIRE(std::distance(popup_menu.begin(), popup_menu.end()) == 2);
                        BOOST_CHECK(popup_menu.begin()->text() == string_type{ TETENGO2_TEXT("Hoge") });
                        BOOST_CHECK(std::next(popup_menu.begin())->text() == string_type{ TETENGO2_TEXT("Piyo") });
                    }
                }

                BOOST_AUTO_TEST_CASE(recursive_begin_impl)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        const concrete_popup_menu popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };

                        popup_menu.recursive_begin();
                    }
                    {
                        concrete_popup_menu popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };

                        popup_menu.recursive_begin();
                    }
                }

                BOOST_AUTO_TEST_CASE(recursive_end_impl)
                {
                    BOOST_TEST_PASSPOINT();

                    {
                        concrete_popup_menu popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };
                        auto p_child1 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Hoge") });
                        auto p_child2 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Fuga") });
                        auto p_child3 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Piyo") });
                        popup_menu.insert(popup_menu.end(), std::move(p_child1));
                        popup_menu.begin()->insert(popup_menu.begin()->end(), std::move(p_child2));
                        popup_menu.insert(popup_menu.end(), std::move(p_child3));

                        const abstract_popup_menu_type& const_popup_menu = popup_menu;

                        BOOST_TEST_REQUIRE(
                            std::distance(const_popup_menu.recursive_begin(), const_popup_menu.recursive_end()) == 4);
                        BOOST_CHECK(
                            const_popup_menu.recursive_begin()->text() == string_type{ TETENGO2_TEXT("Tetengo") });
                        BOOST_CHECK(
                            std::next(const_popup_menu.recursive_begin(), 1)->text() ==
                            string_type{ TETENGO2_TEXT("Hoge") });
                        BOOST_CHECK(
                            std::next(const_popup_menu.recursive_begin(), 2)->text() ==
                            string_type{ TETENGO2_TEXT("Fuga") });
                        BOOST_CHECK(
                            std::next(const_popup_menu.recursive_begin(), 3)->text() ==
                            string_type{ TETENGO2_TEXT("Piyo") });
                    }
                    {
                        concrete_popup_menu popup_menu{ string_type{ TETENGO2_TEXT("Tetengo") } };
                        auto p_child1 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Hoge") });
                        auto p_child2 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Fuga") });
                        auto p_child3 = std::make_unique<concrete_popup_menu>(string_type{ TETENGO2_TEXT("Piyo") });
                        popup_menu.insert(popup_menu.end(), std::move(p_child1));
                        popup_menu.begin()->insert(popup_menu.begin()->end(), std::move(p_child2));
                        popup_menu.insert(popup_menu.end(), std::move(p_child3));

                        BOOST_TEST_REQUIRE(
                            std::distance(popup_menu.recursive_begin(), popup_menu.recursive_end()) == 4);
                        BOOST_CHECK(popup_menu.recursive_begin()->text() == string_type{ TETENGO2_TEXT("Tetengo") });
                        BOOST_CHECK(
                            std::next(popup_menu.recursive_begin(), 1)->text() == string_type{ TETENGO2_TEXT("Hoge") });
                        BOOST_CHECK(
                            std::next(popup_menu.recursive_begin(), 2)->text() == string_type{ TETENGO2_TEXT("Fuga") });
                        BOOST_CHECK(
                            std::next(popup_menu.recursive_begin(), 3)->text() == string_type{ TETENGO2_TEXT("Piyo") });
                    }
                }


            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
