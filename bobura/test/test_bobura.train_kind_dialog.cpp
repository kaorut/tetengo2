/*! \file
    \brief Test of class bobura::train_kind_dialog.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <stdexcept>

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

    typedef train_kind_dialog_type::font_type font_type;

    typedef train_kind_dialog_type::color_type color_type;


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

    BOOST_AUTO_TEST_CASE(background)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        const train_kind_dialog_type train_kind_dialog(window, message_catalog);

        //BOOST_CHECK_THROW(train_kind_dialog.background(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(set_background)
    {
        BOOST_TEST_PASSPOINT();

        window_type window;
        const message_catalog_type message_catalog;
        train_kind_dialog_type train_kind_dialog(window, message_catalog);

        //train_kind_dialog.set_background(color_type(12, 34, 56));

        //BOOST_CHECK(train_kind_dialog.background() == color_type(12, 34, 56));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif
