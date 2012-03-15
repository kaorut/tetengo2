/*! \file
    \brief Test of class bobura::command::file_property.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"

#include "bobura.command.file_property.h"


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
            bobura::dialog_type_list,
            bobura::type::dialog::file_property_dialog
        >::type
        file_property_dialog_type;

    typedef
        boost::mpl::at<
            bobura::locale_type_list, bobura::type::locale::message_catalog
        >::type
        message_catalog_type;

    typedef
        boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type
        window_type;

    typedef
        bobura::command::file_property<
            model_type, abstract_window_type, file_property_dialog_type
        >
        file_property_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(command)
BOOST_AUTO_TEST_SUITE(file_property)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog;
        const file_property_type file_property(message_catalog);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const message_catalog_type message_catalog;
        const file_property_type file_property(message_catalog);

        model_type model;
        window_type parent;
        file_property(model, parent);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
