/*! \file
    \brief Test of class bobura::train_kind_dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <stdexcept>
#include <utility>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef
        boost::mpl::at<bobura::dialog_type_list, bobura::type::dialog::train_kind_dialog>::type train_kind_dialog_type;

    typedef train_kind_dialog_type::info_set_type info_set_type;

    typedef train_kind_dialog_type::int_size_type int_size_type;

    typedef train_kind_dialog_type::train_kind_type train_kind_type;


}


#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(train_kind_dialog)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const train_kind_dialog_type train_kind_dialog(window, message_catalog);
    }

    BOOST_AUTO_TEST_CASE(info_sets)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const train_kind_dialog_type train_kind_dialog(window, message_catalog);

        BOOST_CHECK(train_kind_dialog.info_sets().empty());
    }

    BOOST_AUTO_TEST_CASE(set_info_sets)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        train_kind_dialog_type train_kind_dialog(window, message_catalog);

        std::vector<info_set_type> info_sets;
        info_sets.emplace_back(
            boost::make_optional<int_size_type>(42),
            true,
            train_kind_type(
                string_type(TETENGO2_TEXT("name")),
                string_type(TETENGO2_TEXT("abbreviation")),
                train_kind_type::color_type(12, 34, 56),
                train_kind_type::weight_type::bold,
                train_kind_type::line_style_type::dotted
            )
        );
        train_kind_dialog.set_info_sets(std::move(info_sets));

        BOOST_REQUIRE_EQUAL(train_kind_dialog.info_sets().size(), 1U);
        BOOST_REQUIRE(train_kind_dialog.info_sets()[0].original_index());
        BOOST_CHECK_EQUAL(*train_kind_dialog.info_sets()[0].original_index(), 42U);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif
