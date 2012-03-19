/*! \file
    \brief Test of class bobura::load_save::load_from_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if __CYGWIN__ && __GNUC__ == 4 && __GNUC_MINOR__ == 5 && __GNUC_PATCHLEVEL__ == 3
#   warning "This file does not compile with g++ 4.5.3 on Cygwin."
#else

#include <boost/test/unit_test.hpp>

#include <tetengo2.detail.stub.common_dialog.h>
#include <tetengo2.gui.common_dialog.file_open.h>

#include "bobura.type_list.h"


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
            bobura::model_type_list, bobura::type::model::writer
        >::type
        writer_type;

    typedef
        boost::mpl::at<
            bobura::locale_type_list, bobura::type::locale::message_catalog
        >::type
        message_catalog_type;

    typedef
        boost::mpl::at<
            bobura::load_save_type_list, bobura::type::load_save::save_to_file
        >::type
        save_to_file_type;

    typedef
        boost::mpl::at<
            bobura::load_save_type_list,
            bobura::type::load_save::confirm_file_save
        >::type
        confirm_file_save_type;

    typedef
        boost::mpl::at<
            bobura::model_type_list, bobura::type::model::reader
        >::type
        reader_type;

    typedef
        boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type
        window_type;

    typedef
        boost::mpl::at<
            bobura::load_save_type_list,
            bobura::type::load_save::load_from_file
        >::type
        load_from_file_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(load_save)
BOOST_AUTO_TEST_SUITE(load_from_file)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        writer_type writer;
        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, writer, message_catalog);
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        reader_type reader;
        const load_from_file_type load_from_file(
            confirm_file_save, reader, message_catalog
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        writer_type writer;
        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, writer, message_catalog);
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        reader_type reader;
        const load_from_file_type load_from_file(
            confirm_file_save, reader, message_catalog
        );

        window_type parent;
        load_from_file(model, parent);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

#endif
