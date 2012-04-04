/*! \file
    \brief Test of class bobura::command::about.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"

#include "bobura.command.about.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            bobura::model_type_list, bobura::type::model::model
        >::type
        model_type;

    typedef
        boost::mpl::at<
            bobura::ui_type_list, bobura::type::ui::abstract_window
        >::type
        abstract_window_type;

    typedef
        boost::mpl::at<
            bobura::dialog_type_list, bobura::type::dialog::about_dialog
        >::type
        about_dialog_type;

    typedef
        boost::mpl::at<
            bobura::locale_type_list, bobura::type::locale::message_catalog
        >::type
        message_catalog_type;

    typedef
        boost::mpl::at<bobura::common_type_list, bobura::type::string>::type
        string_type;

    typedef
        boost::mpl::at<bobura::common_type_list, bobura::type::path>::type
        path_type;

    typedef
        boost::mpl::at<bobura::common_type_list, bobura::type::settings>::type
        settings_type;

    typedef
        boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type
        window_type;

    typedef
        bobura::command::about<
            model_type, abstract_window_type, about_dialog_type
        >
        about_type;


}


#if defined(__GNUC__) && defined(SKIP_COMPILATION)
#   warning Skipped the compilation to avoid errors.
#else
BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(about)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog;
        std::vector<string_type> arguments;
        path_type path;
        const settings_type settings(std::move(arguments), std::move(path));
        const about_type about(message_catalog, settings);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog;
        std::vector<string_type> arguments;
        path_type path;
        const settings_type settings(std::move(arguments), std::move(path));
        const about_type about(message_catalog, settings);

        model_type model;
        window_type parent;
        about(model, parent);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
#endif
