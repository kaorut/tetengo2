/*! \file
    \brief Test of class bobura::message::timetable_model.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <vector>

//#include <boost/mpl/at.hpp>
//#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.stdalt.h>
#include <tetengo2.text.h>
#include <tetengo2.utility.h>

#include "bobura.type_list.h"

#include "bobura.message.timetable_model.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef boost::mpl::at<bobura::view_type_list, bobura::type::view::view>::type view_type;

    typedef boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

    typedef boost::mpl::at<bobura::setting_type_list, bobura::type::setting::settings>::type settings_type;

    typedef boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::save_to_file>::type save_to_file_type;

    typedef
        boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::confirm_file_save>::type
        confirm_file_save_type;

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    class main_window_type : public boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type
    {
    public:
        typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type base_type;

        typedef
            boost::mpl::at<bobura::main_window_type_list, bobura::type::main_window::diagram_picture_box>::type
            diagram_picture_box_type;

        main_window_type(
            const message_catalog_type&   message_catalog,
            const settings_type&          settings,
            const confirm_file_save_type& confirm_file_save
        )
        :
        base_type(),
        m_diagram_picture_box(*this)
        {
            tetengo2::suppress_unused_variable_warning(message_catalog, settings, confirm_file_save);
        }

        virtual ~main_window_type()
        TETENGO2_STDALT_NOEXCEPT
        {}

        void set_title(const boost::optional<string_type>& document_name, const bool changed)
        {
            tetengo2::suppress_unused_variable_warning(document_name, changed);
        }

        const diagram_picture_box_type& diagram_picture_box()
        const
        {
            return m_diagram_picture_box;
        }

        diagram_picture_box_type& diagram_picture_box()
        {
            return m_diagram_picture_box;
        }

    private:
        diagram_picture_box_type m_diagram_picture_box;

    };


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(message)
BOOST_AUTO_TEST_SUITE(timetable_model)
BOOST_AUTO_TEST_SUITE(reset)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        const settings_type settings(arguments);
        const save_to_file_type save_to_file(false, message_catalog);
        const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
        main_window_type main_window(message_catalog, settings, confirm_file_save);
        const bobura::message::timetable_model::reset<model_type, view_type, main_window_type> observer(
            model, view, main_window
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        const settings_type settings(arguments);
        const save_to_file_type save_to_file(false, message_catalog);
        const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
        main_window_type main_window(message_catalog, settings, confirm_file_save);
        const bobura::message::timetable_model::reset<model_type, view_type, main_window_type> observer(
            model, view, main_window
        );

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(changed)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        const settings_type settings(arguments);
        const save_to_file_type save_to_file(false, message_catalog);
        const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
        main_window_type main_window(message_catalog, settings, confirm_file_save);
        const bobura::message::timetable_model::changed<model_type, view_type, main_window_type> observer(
            model, view, main_window
        );
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        model_type model;
        const message_catalog_type message_catalog;
        view_type view(model, message_catalog);
        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        const settings_type settings(arguments);
        const save_to_file_type save_to_file(false, message_catalog);
        const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
        main_window_type main_window(message_catalog, settings, confirm_file_save);
        const bobura::message::timetable_model::changed<model_type, view_type, main_window_type> observer(
            model, view, main_window
        );

        observer();
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
