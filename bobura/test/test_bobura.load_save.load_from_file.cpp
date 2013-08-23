/*! \file
    \brief Test of class bobura::load_save::load_from_file.

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

#include "bobura.model.serializer.select_oudia_diagram.h"
#include "bobura.type_list.h"

#include "bobura.load_save.load_from_file.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::model_type_list, bobura::type::model::model>::type model_type;

    typedef model_type::timetable_type timetable_type;

    typedef boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

    typedef boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::save_to_file>::type save_to_file_type;

    typedef
        boost::mpl::at<bobura::load_save_type_list, bobura::type::load_save::confirm_file_save>::type
        confirm_file_save_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::window>::type window_type;

    struct oudia_diagram_dialog_type : public boost::mpl::at<bobura::ui_type_list, bobura::type::ui::dialog>::type
    {
        typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::dialog>::type base_type;

        typedef window_type::base_type abstract_window_type;

        typedef abstract_window_type::string_type string_type;

        typedef
            boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type message_catalog_type;

        typedef boost::mpl::at<bobura::common_type_list, bobura::type::size>::type int_size_type;

        oudia_diagram_dialog_type(abstract_window_type& parent, const message_catalog_type& message_catalog)
        :
        base_type(parent)
        {
            tetengo2::suppress_unused_variable_warning(message_catalog);
        }

        virtual ~oudia_diagram_dialog_type()
        TETENGO2_STDALT_NOEXCEPT
        {}

        const string_type& file_name()
        const
        {
            static const string_type singleton;
            return singleton;
        }

        void set_file_name(string_type file_name)
        {
            tetengo2::suppress_unused_variable_warning(file_name);
        }

        const std::vector<string_type>& names()
        const
        {
            static const std::vector<string_type> singleton;
            return singleton;
        }

        void set_names(std::vector<string_type> names)
        {
            tetengo2::suppress_unused_variable_warning(names);
        }

        const boost::optional<int_size_type>& selected_index()
        const
        {
            static const boost::optional<int_size_type> singleton;
            return singleton;
        }

        void set_selected_index(const int_size_type index)
        {
            tetengo2::suppress_unused_variable_warning(index);
        }

    };

    typedef
        bobura::model::serializer::reader_set<
            boost::mpl::at<bobura::common_type_list, bobura::type::input_stream_iterator>::type,
            timetable_type,
            boost::mpl::at<bobura::common_type_list, bobura::type::pull_parser>::type,
            boost::mpl::at<bobura::model_type_list, bobura::type::model::station_grade_type_set>::type,
            bobura::model::serializer::select_oudia_diagram<oudia_diagram_dialog_type>,
            boost::mpl::at<bobura::locale_type_list, bobura::type::locale::timetable_file_encoder>::type,
            boost::mpl::at<bobura::locale_type_list, bobura::type::locale::windia_file_encoder>::type
        >
        reader_set_type;

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::path>::type path_type;

    typedef
        bobura::load_save::load_from_file<
            model_type,
            boost::mpl::at<bobura::ui_type_list, bobura::type::ui::abstract_window>::type,
            boost::mpl::at<bobura::common_dialog_type_list, bobura::type::common_dialog::message_box>::type,
            boost::mpl::at<bobura::common_dialog_type_list, bobura::type::common_dialog::file_open_dialog>::type,
            confirm_file_save_type,
            boost::mpl::at<bobura::model_type_list, bobura::type::model::reader_selector>::type,
            reader_set_type,
            boost::mpl::at<bobura::locale_type_list, bobura::type::locale::message_catalog>::type
        >
        load_from_file_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(load_save)
BOOST_AUTO_TEST_SUITE(load_from_file)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        {
            model_type model;
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(false, message_catalog);
            const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
            const load_from_file_type load_from_file(false, confirm_file_save, message_catalog);
        }
        {
            model_type model;
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(false, message_catalog);
            const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
            const load_from_file_type load_from_file(true, confirm_file_save, message_catalog);
        }
    }

    BOOST_AUTO_TEST_CASE(reloadable)
    {
        BOOST_TEST_PASSPOINT();
    
        {
            model_type model;
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(false, message_catalog);
            const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
            const load_from_file_type load_from_file(false, confirm_file_save, message_catalog);

            const boost::optional<path_type> path;

            BOOST_CHECK(!load_from_file.reloadable(model, path));
        }
        {
            model_type model;
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(false, message_catalog);
            const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
            const load_from_file_type load_from_file(true, confirm_file_save, message_catalog);

            const boost::optional<path_type> path;

            BOOST_CHECK(load_from_file.reloadable(model, path));
        }
        {
            model_type model;
            model.set_path(path_type(TETENGO2_TEXT("file_path")));
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(false, message_catalog);
            const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
            const load_from_file_type load_from_file(false, confirm_file_save, message_catalog);

            const boost::optional<path_type> path;
            BOOST_CHECK(load_from_file.reloadable(model, path));
        }
        {
            model_type model;
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(false, message_catalog);
            const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
            const load_from_file_type load_from_file(false, confirm_file_save, message_catalog);

            const boost::optional<path_type> path(path_type(TETENGO2_TEXT("file_path")));
            BOOST_CHECK(load_from_file.reloadable(model, path));
        }
    }

    BOOST_AUTO_TEST_CASE(operator_paren)
    {
        BOOST_TEST_PASSPOINT();

        {
            model_type model;
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(false, message_catalog);
            const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
            const load_from_file_type load_from_file(false, confirm_file_save, message_catalog);

            const boost::optional<path_type> path;
            window_type parent;
            load_from_file(model, path, parent);
        }
        {
            model_type model;
            const message_catalog_type message_catalog;
            const save_to_file_type save_to_file(false, message_catalog);
            const confirm_file_save_type confirm_file_save(model, save_to_file, message_catalog);
            const load_from_file_type load_from_file(true, confirm_file_save, message_catalog);

            const boost::optional<path_type> path;
            window_type parent;
            load_from_file(model, path, parent);
        }
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
