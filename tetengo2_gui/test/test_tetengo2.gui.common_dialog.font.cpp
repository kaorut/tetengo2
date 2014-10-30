/*! \file
    \brief Test of class tetengo2::gui::common_dialog::font.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#include <boost/mpl/at.hpp>
#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include "test_tetengo2.gui.detail_type_list.h"
#include "test_tetengo2.gui.type_list.h"


namespace
{
    // types

    using detail_type_list_type = test_tetengo2::gui::detail_type_list_for_test;

    using type_list_type = test_tetengo2::gui::type_list<detail_type_list_type>;

    using size_type = boost::mpl::at<type_list_type, test_tetengo2::gui::type::size>::type;

    using string_type = boost::mpl::at<type_list_type, test_tetengo2::gui::type::string>::type;

    using widget_traits_type = boost::mpl::at<type_list_type, test_tetengo2::gui::type::widget_traits>::type;

    using widget_details_traits_type =
        boost::mpl::at<type_list_type, test_tetengo2::gui::type::widget_details_traits>::type;

    using menu_details_type = boost::mpl::at<detail_type_list_type, test_tetengo2::gui::type::detail::menu>::type;

    using window_type =
        tetengo2::gui::widget::window<widget_traits_type, widget_details_traits_type, menu_details_type>;

    using drawing_details_type =
        boost::mpl::at<detail_type_list_type, test_tetengo2::gui::type::detail::drawing>::type;

    using font_type = tetengo2::gui::drawing::font<string_type, size_type, drawing_details_type>;

    using common_dialog_details_type =
        boost::mpl::at<detail_type_list_type, test_tetengo2::gui::type::detail::common_dialog>::type;

    using font_dialog_type =
        tetengo2::gui::common_dialog::font<
            font_type, widget_traits_type, common_dialog_details_type, widget_details_traits_type, menu_details_type
        >;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(common_dialog)
BOOST_AUTO_TEST_SUITE(font)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const font_dialog_type font{ boost::none, parent };
        }
        {
            window_type parent{};
            const font_dialog_type font{
                boost::make_optional(font_type{ string_type{ TETENGO2_TEXT("fuga") }, 42, false, true, false, true }),
                parent
            };
        }
    }

    BOOST_AUTO_TEST_CASE(result)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const font_dialog_type font{ boost::none, parent };

            BOOST_CHECK(font.result() == font_type::dialog_font());
        }
        {
            window_type parent{};
            font_dialog_type font{ boost::none, parent };

            font.do_modal();

            BOOST_CHECK(font.result() != font_type::dialog_font());
        }
    }

    BOOST_AUTO_TEST_CASE(do_modal)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent{};
        font_dialog_type font{ boost::none, parent };

        font.do_modal();
    }

    BOOST_AUTO_TEST_CASE(details)
    {
        BOOST_TEST_PASSPOINT();

        {
            window_type parent{};
            const font_dialog_type font{ boost::none, parent };

            font.details();
        }
        {
            window_type parent{};
            font_dialog_type font{ boost::none, parent };

            font.details();
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
