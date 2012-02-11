/*! \file
    \brief Test of class bobura::confirm_file_save.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <string>

//#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "test_bobura.types.h"


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(confirm_file_save)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const confirm_file_save_type confirm_file_save(model);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const confirm_file_save_type confirm_file_save(model);

        const message_catalog_type message_catalog;
        std::vector<std::wstring> arguments;
        boost::filesystem::path path;
        const settings_type settings(std::move(arguments), std::move(path));
        main_window_type main_window(message_catalog, settings);
        confirm_file_save(main_window);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
