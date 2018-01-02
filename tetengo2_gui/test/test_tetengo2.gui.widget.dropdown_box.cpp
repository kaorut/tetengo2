/*! \file
    \brief Test of class tetengo2::gui::widget::dropdown_box.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <stdexcept>
#include <string>

#include <boost/optional.hpp>
#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2/gui/menu/abstract_popup.h>
#include <tetengo2/gui/menu/menu_bar.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/dropdown_box.h>
#include <tetengo2/gui/widget/window.h>
#include <tetengo2/text.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::type_list::detail_for_test;

    using common_type_list_type = test_tetengo2::gui::type_list::common<detail_type_list_type>;

    using string_type = common_type_list_type::string_type;

    using widget_traits_type = common_type_list_type::widget_traits_type;

    using widget_details_traits_type = common_type_list_type::widget_details_traits_type;

    using menu_details_type = detail_type_list_type::menu_type;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using dropdown_box_type = tetengo2::gui::widget::dropdown_box<widget_traits_type, widget_details_traits_type>;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(widget)
BOOST_AUTO_TEST_SUITE(dropdown_box)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const dropdown_box_type dropdown_box{ parent };
    }

    BOOST_AUTO_TEST_CASE(value_count)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const dropdown_box_type dropdown_box{ parent };

            BOOST_TEST(dropdown_box.value_count() == 0U);
        }
        {
            window_type parent{};
            dropdown_box_type dropdown_box{ parent };
            dropdown_box.insert_value(0, string_type{ TETENGO2_TEXT("hoge") });

            BOOST_TEST(dropdown_box.value_count() == 1U);
        }
    }

    BOOST_AUTO_TEST_CASE(value)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            dropdown_box_type dropdown_box{ parent };
            dropdown_box.insert_value(0, string_type{ TETENGO2_TEXT("hoge") });

            BOOST_CHECK(dropdown_box.value(0) == string_type{ TETENGO2_TEXT("hoge") });
        }
        {
            window_type parent{};
            const dropdown_box_type dropdown_box{ parent };

            BOOST_CHECK_THROW(dropdown_box.value(0), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(set_value)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            dropdown_box_type dropdown_box{ parent };
            dropdown_box.insert_value(0, string_type{ TETENGO2_TEXT("hoge") });

            dropdown_box.set_value(0, string_type{ TETENGO2_TEXT("fuga") });

            BOOST_CHECK(dropdown_box.value(0) == string_type{ TETENGO2_TEXT("fuga") });
        }
        {
            window_type parent{};
            dropdown_box_type dropdown_box{ parent };

            BOOST_CHECK_THROW(dropdown_box.set_value(0, string_type{ TETENGO2_TEXT("fuga") }), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(insert_value)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            dropdown_box_type dropdown_box{ parent };

            dropdown_box.insert_value(0, string_type{ TETENGO2_TEXT("hoge") });
            dropdown_box.insert_value(1, string_type{ TETENGO2_TEXT("fuga") });
            dropdown_box.insert_value(0, string_type{ TETENGO2_TEXT("piyo") });
            dropdown_box.insert_value(2, string_type{ TETENGO2_TEXT("piyoyo") });

            BOOST_TEST(dropdown_box.value_count() == 4U);
            BOOST_CHECK(dropdown_box.value(0) == string_type{ TETENGO2_TEXT("piyo") });
            BOOST_CHECK(dropdown_box.value(1) == string_type{ TETENGO2_TEXT("hoge") });
            BOOST_CHECK(dropdown_box.value(2) == string_type{ TETENGO2_TEXT("piyoyo") });
            BOOST_CHECK(dropdown_box.value(3) == string_type{ TETENGO2_TEXT("fuga") });
        }
        {
            window_type parent{};
            dropdown_box_type dropdown_box{ parent };

            BOOST_CHECK_THROW(dropdown_box.insert_value(1, string_type{ TETENGO2_TEXT("fuga") }), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(erase_value)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            dropdown_box_type dropdown_box{ parent };
            dropdown_box.insert_value(0, string_type{ TETENGO2_TEXT("hoge") });

            dropdown_box.erase_value(0);

            BOOST_TEST(dropdown_box.value_count() == 0U);
        }
        {
            window_type parent{};
            dropdown_box_type dropdown_box{ parent };

            BOOST_CHECK_THROW(dropdown_box.erase_value(0), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(clear)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        dropdown_box_type dropdown_box{ parent };
        dropdown_box.insert_value(0, string_type{ TETENGO2_TEXT("hoge") });
        dropdown_box.insert_value(1, string_type{ TETENGO2_TEXT("fuga") });

        dropdown_box.clear();

        BOOST_TEST(dropdown_box.value_count() == 0U);
    }

    BOOST_AUTO_TEST_CASE(selected_value_index)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        const dropdown_box_type dropdown_box{ parent };

        BOOST_TEST(!dropdown_box.selected_value_index());
    }

    BOOST_AUTO_TEST_CASE(select_value)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            dropdown_box_type dropdown_box{ parent };
            dropdown_box.insert_value(0, string_type{ TETENGO2_TEXT("hoge") });

            dropdown_box.select_value(0);

            BOOST_TEST_REQUIRE(dropdown_box.selected_value_index().is_initialized());
            BOOST_TEST(*dropdown_box.selected_value_index() == 0U);
        }
        {
            window_type parent{};
            dropdown_box_type dropdown_box{ parent };

            BOOST_CHECK_THROW(dropdown_box.select_value(0), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE(list_selection_observer_set)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const dropdown_box_type dropdown_box{ parent };

            dropdown_box.list_selection_observer_set();
        }
        {
            window_type parent{};
            dropdown_box_type dropdown_box{ parent };

            dropdown_box.list_selection_observer_set();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
