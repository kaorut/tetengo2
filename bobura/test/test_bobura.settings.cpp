/*! \file
    \brief Test of class bobura::settings.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <cstddef>
//#include <vector>

//#include <boost/mpl/at.hpp>
#include <boost/test/unit_test.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.text.h>

#include "bobura.type_list.h"


namespace
{
    // types

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::path>::type path_type;

    typedef boost::mpl::at<bobura::common_type_list, bobura::type::string>::type string_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::position>::type position_type;

    typedef tetengo2::gui::position<position_type>::left_type left_type;

    typedef boost::mpl::at<bobura::ui_type_list, bobura::type::ui::dimension>::type dimension_type;

    typedef tetengo2::gui::dimension<dimension_type>::width_type width_type;

    typedef tetengo2::gui::dimension<dimension_type>::height_type height_type;

    typedef boost::mpl::at<bobura::setting_type_list, bobura::type::setting::settings>::type settings_type;


}


BOOST_AUTO_TEST_SUITE(test_bobura)
BOOST_AUTO_TEST_SUITE(settings)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        const settings_type settings(arguments);
    }

    BOOST_AUTO_TEST_CASE(base_path)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        const settings_type settings(arguments);

        BOOST_CHECK(settings.base_path() == path_type(string_type(TETENGO2_TEXT("path/to"))));
    }

    BOOST_AUTO_TEST_CASE(input)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<string_type> arguments;
            arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
            const settings_type settings(arguments);

            BOOST_CHECK(!settings.input());
        }
        {
            std::vector<string_type> arguments;
            arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
            arguments.push_back(string_type(TETENGO2_TEXT("input_file")));
            const settings_type settings(arguments);

            BOOST_REQUIRE(settings.input());
            BOOST_CHECK(*settings.input() == path_type(string_type(TETENGO2_TEXT("input_file"))));
        }
    }

    BOOST_AUTO_TEST_CASE(message_directory_path)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        const settings_type settings(arguments);

        BOOST_CHECK(settings.message_directory_path() == path_type(string_type(TETENGO2_TEXT("path/to/messages"))));
    }

    BOOST_AUTO_TEST_CASE(image_directory_path)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        const settings_type settings(arguments);

        BOOST_CHECK(settings.image_directory_path() == path_type(string_type(TETENGO2_TEXT("path/to/images"))));
    }

    BOOST_AUTO_TEST_CASE(main_window_dimension)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<string_type> arguments;
            arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
            const settings_type settings(arguments);

            const auto dimension = settings.main_window_dimension();

            BOOST_REQUIRE(!dimension);
        }
        {
            std::vector<string_type> arguments;
            arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
            arguments.push_back(string_type(TETENGO2_TEXT("--dimension=240x120")));
            const settings_type settings(arguments);

            const auto dimension = settings.main_window_dimension();

            BOOST_REQUIRE(dimension);
            BOOST_CHECK_EQUAL(
                tetengo2::gui::dimension<dimension_type>::width(*dimension).to_pixels<std::size_t>(), 240U
            );
            BOOST_CHECK_EQUAL(
                tetengo2::gui::dimension<dimension_type>::height(*dimension).to_pixels<std::size_t>(), 120U
            );
        }
        {
            std::vector<string_type> arguments;
            arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
            arguments.push_back(string_type(TETENGO2_TEXT("-d")));
            arguments.push_back(string_type(TETENGO2_TEXT("240x120")));
            const settings_type settings(arguments);

            const auto dimension = settings.main_window_dimension();

            BOOST_REQUIRE(dimension);
            BOOST_CHECK_EQUAL(
                tetengo2::gui::dimension<dimension_type>::width(*dimension).to_pixels<std::size_t>(), 240U
            );
            BOOST_CHECK_EQUAL(
                tetengo2::gui::dimension<dimension_type>::height(*dimension).to_pixels<std::size_t>(), 120U
            );
        }
    }

    BOOST_AUTO_TEST_CASE(set_main_window_dimension)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        settings_type settings(arguments);

        settings.set_main_window_dimension(dimension_type(width_type(42), height_type(24)));

        const auto dimension = settings.main_window_dimension();

        BOOST_REQUIRE(dimension);
        BOOST_CHECK(tetengo2::gui::dimension<dimension_type>::width(*dimension) == width_type(42));
        BOOST_CHECK(tetengo2::gui::dimension<dimension_type>::height(*dimension) == height_type(24));
    }

    BOOST_AUTO_TEST_CASE(main_window_maximized)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        const settings_type settings(arguments);

        const auto maximized = settings.main_window_maximized();

        BOOST_REQUIRE(!maximized);
    }

    BOOST_AUTO_TEST_CASE(set_main_window_maximized)
    {
        BOOST_TEST_PASSPOINT();

        {
            std::vector<string_type> arguments;
            arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
            settings_type settings(arguments);

            settings.set_main_window_maximized(false);

            const auto maximized = settings.main_window_maximized();

            BOOST_REQUIRE(maximized);
            BOOST_CHECK(!*maximized);
        }
        {
            std::vector<string_type> arguments;
            arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
            settings_type settings(arguments);

            settings.set_main_window_maximized(true);

            const auto maximized = settings.main_window_maximized();

            BOOST_REQUIRE(maximized);
            BOOST_CHECK(*maximized);
        }
    }

    BOOST_AUTO_TEST_CASE(property_bar_width)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        const settings_type settings(arguments);

        const auto width = settings.property_bar_width();

        BOOST_REQUIRE(!width);
    }

    BOOST_AUTO_TEST_CASE(set_property_bar_width)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        settings_type settings(arguments);

        settings.set_property_bar_width(width_type(42));

        const auto width = settings.property_bar_width();

        BOOST_REQUIRE(width);
        BOOST_CHECK(*width == width_type(42));
    }

    BOOST_AUTO_TEST_CASE(property_bar_splitter_position)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        const settings_type settings(arguments);

        const auto position = settings.property_bar_splitter_position();

        BOOST_REQUIRE(!position);
    }

    BOOST_AUTO_TEST_CASE(set_property_bar_splitter_position)
    {
        BOOST_TEST_PASSPOINT();

        std::vector<string_type> arguments;
        arguments.push_back(string_type(TETENGO2_TEXT("path/to/exe")));
        settings_type settings(arguments);

        settings.set_property_bar_splitter_position(left_type(42));

        const auto position = settings.property_bar_splitter_position();

        BOOST_REQUIRE(position);
        BOOST_CHECK(*position == left_type(42));
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
