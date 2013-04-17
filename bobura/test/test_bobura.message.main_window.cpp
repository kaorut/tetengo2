/*! \file
    \brief Test of class bobura::message::main_window.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <utility>
//#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.text.h>
#include <tetengo2.utility.h>

#include "bobura.type_list.h"

#include "bobura.message.main_window.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::popup_menu>::type popup_menu_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::abstract_window>::type abstract_window_type;

    struct command_type
    {
    public:
        enum class state_type
        {
            default_,
            checked,
            selected,
        };

        command_type()
        {}

        virtual bool enabled(const model_type& model)
        const
        {
            tetengo2::suppress_unused_variable_warning(model);

            return true;
        }

        virtual state_type state()
        const
        {
            return state_type::default_;
        }

        virtual void execute(model_type& model, abstract_window_type& parent)
        const
        {
            tetengo2::suppress_unused_variable_warning(model, parent);
        }

    };

    typedef boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

    typedef boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::save_to_file>::type save_to_file_type;

    typedef
        boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::confirm_file_save>::type
        confirm_file_save_type;

    typedef boost::mpl::at<bobura::setting_type_list, bobura::type::setting::settings>::type settings_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    typedef boost::mpl::at<bobura::view_type_list, bobura::type::view::view>::type view_type;

    typedef
        boost::mpl::at<bobura::main_window_type_list, bobura::type::main_window::diagram_picture_box>::type
        diagram_picture_box_type;

    typedef
        boost::mpl::at<bobura::main_window_type_list, bobura::type::main_window::property_bar>::type property_bar_type;

    typedef
        bobura::message::main_window::popup_menu_selected<popup_menu_type, command_type, model_type>
        popup_menu_selected_type;

    typedef
        bobura::message::main_window::menu_command_selected<command_type, model_type, abstract_window_type>
        menu_command_selected_type;

    typedef
        bobura::message::main_window::window_resized<
            view_type, abstract_window_type, diagram_picture_box_type, property_bar_type
        >
        window_resized_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(main_window)
BOOST_AUTO_TEST_SUITE(popup_menu_selected)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        popup_menu_type popup_menu(string_type(TETENGO2_TEXT("popup")));
        std::vector<const command_type*> commands;
        const model_type model;
        const popup_menu_selected_type observer(popup_menu, std::move(commands), model);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        popup_menu_type popup_menu(string_type(TETENGO2_TEXT("popup")));
        std::vector<const command_type*> commands;
        const model_type model;
        const popup_menu_selected_type observer(popup_menu, std::move(commands), model);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(menu_command_selected)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const command_type command;
        model_type model;
        window_type window;
        const menu_command_selected_type menu(command, model, window);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const command_type command;
        model_type model;
        window_type window;
        const menu_command_selected_type observer(command, model, window);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(window_resized)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        window_type window;
        diagram_picture_box_type diagram_picture_box(window);
        property_bar_type property_bar(window);
        const window_resized_type observer(view, window, diagram_picture_box, property_bar);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        const model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        window_type window;
        diagram_picture_box_type diagram_picture_box(window);
        property_bar_type property_bar(window);
        const window_resized_type observer(view, window, diagram_picture_box, property_bar);

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(window_closing)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        model_type model;
        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, message_catalog);
        const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
        const std::vector<string_type> command_line_arguments(1, string_type(TETENGO2_TEXT("path/to/exe")));
        settings_type settings(command_line_arguments);
        const bobura::message::main_window::window_closing<abstract_window_type, confirm_file_save_type, settings_type>
        observer(parent, confirm_file_save, settings);
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        model_type model;
        const message_catalog_type message_catalog;
        const save_to_file_type save_to_file(false, message_catalog);
        const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
        const std::vector<string_type> command_line_arguments(1, string_type(TETENGO2_TEXT("path/to/exe")));
        settings_type settings(command_line_arguments);
        const bobura::message::main_window::window_closing<abstract_window_type, confirm_file_save_type, settings_type>
        observer(parent, confirm_file_save, settings);

        auto cancel = false;
        observer(cancel);

        BOOST_CHECK(!cancel);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
