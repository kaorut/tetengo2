/*! \file
    \brief Test of class bobura::message::main_window.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

//#include <memory>

//#include <boost/filesystem.hpp>
//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include "bobura.type_list.h"

#include "bobura.message.main_window.h"


namespace
{
    // types

    typedef
        boost::mpl::at<
            bobura::command_type_list_type_list,
            bobura::type::command_type_list::command_type_list
        >::type
        command_type_list_type;

    typedef
        boost::mpl::at<
            command_type_list_type, bobura::command::type::nop
        >::type
        nop_command_type;

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
            bobura::locale_type_list, bobura::type::locale::message_catalog
        >::type
        message_catalog_type;

    typedef
        boost::mpl::at<bobura::ui_type_list, bobura::type::ui::canvas>::type
        canvas_type;

    typedef
        boost::mpl::at<bobura::ui_type_list, bobura::type::ui::position>::type
        position_type;

    typedef
        boost::mpl::at<
            bobura::ui_type_list, bobura::type::ui::picture_reader
        >::type
        picture_reader_type;

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
        boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type
        window_type;

    typedef
        bobura::message::main_window::menu_selected<
            nop_command_type, model_type, abstract_window_type
        >
        menu_selected_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(main_window)
BOOST_AUTO_TEST_SUITE(menu_selected)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const nop_command_type command = nop_command_type();
        model_type model;
        window_type window;
        const menu_selected_type menu(command, model, window);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const nop_command_type command = nop_command_type();
        model_type model;
        window_type window;
        const menu_selected_type menu(command, model, window);

        menu();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(paint_paint)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::main_window::paint_paint<
            canvas_type, position_type, picture_reader_type
        > paint(boost::filesystem::path("image_path"));
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const bobura::message::main_window::paint_paint<
            canvas_type, position_type, picture_reader_type
        > paint(boost::filesystem::path("image_path"));

        const window_type window;
        std::unique_ptr<canvas_type> p_canvas(window.create_canvas());
        paint(*p_canvas);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(window)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        model_type model;
        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, message_catalog);
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        const bobura::message::main_window::window_closing<
            abstract_window_type, confirm_file_save_type
        > window(parent, confirm_file_save);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        model_type model;
        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, message_catalog);
        const confirm_file_save_type confirm_file_save(
            model, save_to_file, message_catalog
        );
        const bobura::message::main_window::window_closing<
            abstract_window_type, confirm_file_save_type
        > window(parent, confirm_file_save);

        bool cancel = false;
        window(cancel);

        BOOST_CHECK(!cancel);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
