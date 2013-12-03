/*! \file
    \brief The definition of bobura::settings.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_SETTINGS_H)
#define BOBURA_SETTINGS_H

#include <cassert>
//#include <memory>
#include <string>
//#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/program_options.hpp>
#include <boost/variant.hpp>

#include <tetengo2.gui.measure.h>
#include <tetengo2.stdalt.h>
#include <tetengo2.text.h>


namespace bobura
{
    /*!
        \brief The class template for settings of bobura.

        \tparam String       A string type.
        \tparam Path         A path type.
        \tparam Position     A position type.
        \tparam Dimension    A dimension type.
        \tparam ConfigTraits A configuration traits type.
    */
    template <typename String, typename Path, typename Position, typename Dimension, typename ConfigTraits>
    class settings : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The path type.
        typedef Path path_type;

        //! The position type.
        typedef Position position_type;

        //! The left type.
        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        //! The dimension type.
        typedef Dimension dimension_type;

        //! The width type.
        typedef typename tetengo2::gui::dimension<dimension_type>::width_type width_type;

        //! The configuration traits type.
        typedef ConfigTraits config_traits_type;


        // constructors and destructor

        /*!
            \brief Creates settings.

            \param command_line_arguments Command line arguments.
        */
        explicit settings(const std::vector<string_type>& command_line_arguments)
        :
        m_base_path(),
        m_input(),
        m_p_config()
        {
            initialize(command_line_arguments);
        }


        // functions

        /*!
            \brief Returns the base path.

            \return The base path.
        */
        const path_type& base_path()
        const
        {
            return m_base_path;
        }

        /*!
            \brief Returns the input.

            \return The input.
        */
        const boost::optional<path_type>& input()
        const
        {
            return m_input;
        }

        /*!
            \brief Returns the message directory path.

            \return The message directory path.
        */
        path_type message_directory_path()
        const
        {
            return m_base_path / path_string_type(TETENGO2_TEXT("messages"));
        }

        /*!
            \brief Returns the image directory path.

            \return The image directory path.
        */
        path_type image_directory_path()
        const
        {
            return m_base_path / path_string_type(TETENGO2_TEXT("images"));
        }

        /*!
            \brief Returns the main window dimension.

            \return The main window dimension.
        */
        boost::optional<dimension_type> main_window_dimension()
        const
        {
            const auto width = m_p_config->get(string_type(TETENGO2_TEXT("MainWindow/Width")));
            if (!width || width->which() != 1)
                return boost::none;
            const auto height = m_p_config->get(string_type(TETENGO2_TEXT("MainWindow/Height")));
            if (!height || height->which() != 1)
                return boost::none;

            return
                boost::make_optional(
                    dimension_type(
                        width_type::from_pixels(boost::get<uint_type>(*width)),
                        height_type::from_pixels(boost::get<uint_type>(*height))
                    )
                );
        }

        /*!
            \brief Sets a main window dimension.

            \param dimension A dimension.
        */
        void set_main_window_dimension(const dimension_type& dimension)
        {
            const auto& width = tetengo2::gui::dimension<dimension_type>::width(dimension);
            m_p_config->set(
                string_type(TETENGO2_TEXT("MainWindow/Width")),
                config_value_type(width.template to_pixels<uint_type>())
            );

            const auto& height = tetengo2::gui::dimension<dimension_type>::height(dimension);
            m_p_config->set(
                string_type(TETENGO2_TEXT("MainWindow/Height")),
                config_value_type(height.template to_pixels<uint_type>())
            );
        }

        /*!
            \brief Returns the maximized status of the main window.

            \return The maximized status.
        */
        boost::optional<bool> main_window_maximized()
        const
        {
            const auto status = m_p_config->get(string_type(TETENGO2_TEXT("MainWindow/Maximized")));
            if (!status || status->which() != 1)
                return boost::none;

            return boost::make_optional(boost::get<uint_type>(*status) != 0);
        }

        /*!
            \brief Sets a maximized status of the main window.

            \param status A maximized status.
        */
        void set_main_window_maximized(const bool status)
        {
            m_p_config->set(string_type(TETENGO2_TEXT("MainWindow/Maximized")), config_value_type(status ? 1 : 0));
        }

        /*!
            \brief Returns the property bar width.

            \return The property bar width.
        */
        boost::optional<width_type> property_bar_width()
        const
        {
            const auto width = m_p_config->get(string_type(TETENGO2_TEXT("MainWindow/PropertyBarWidth")));
            if (!width || width->which() != 1)
                return boost::none;

            return boost::make_optional(width_type::from_pixels(boost::get<uint_type>(*width)));
        }
        
        /*!
            \brief Sets a property bar width.

            \param width A width.
        */
        void set_property_bar_width(const width_type& width)
        {
            m_p_config->set(
                string_type(TETENGO2_TEXT("MainWindow/PropertyBarWidth")),
                config_value_type(width.template to_pixels<uint_type>())
            );
        }

        /*!
            \brief Returns the minimized status of the property bar.

            \return The minimized status.
        */
        boost::optional<bool> property_bar_minimized()
        const
        {
            const auto status = m_p_config->get(string_type(TETENGO2_TEXT("MainWindow/PropertyBarMinimized")));
            if (!status || status->which() != 1)
                return boost::none;

            return boost::make_optional(boost::get<uint_type>(*status) != 0);
        }
        
        /*!
            \brief Sets a minimized status of the property bar.

            \param status A minimized status.
        */
        void set_property_bar_minimized(const bool status)
        {
            m_p_config->set(
                string_type(TETENGO2_TEXT("MainWindow/PropertyBarMinimized")), config_value_type(status ? 1 : 0)
            );
        }

        /*!
            \brief Returns the splitter bar position in the property bar.

            \return The splitter bar position.
        */
        boost::optional<left_type> property_bar_splitter_position()
        const
        {
            const auto position =
                m_p_config->get(string_type(TETENGO2_TEXT("MainWindow/PropertyBarSplitterPosition")));
            if (!position || position->which() != 1)
                return boost::none;

            return boost::make_optional(left_type::from_pixels(boost::get<uint_type>(*position)));
        }
        
        /*!
            \brief Sets a splitter bar position in the property bar.

            \param position A position.
        */
        void set_property_bar_splitter_position(const left_type& position)
        {
            m_p_config->set(
                string_type(TETENGO2_TEXT("MainWindow/PropertyBarSplitterPosition")),
                config_value_type(position.template to_pixels<uint_type>())
            );
        }


    private:
        // types

        typedef typename path_type::string_type path_string_type;

        typedef typename tetengo2::gui::dimension<dimension_type>::height_type height_type;

        typedef typename config_traits_type::uint_type uint_type;

        typedef typename config_traits_type::config_base_type config_base_type;

        typedef typename config_base_type::value_type config_value_type;

        typedef typename config_traits_type::config_list_type config_list_type;

        typedef typename config_traits_type::cached_config_type cached_config_type;

        typedef typename config_traits_type::temporary_config_type temporary_config_type;

        typedef typename config_traits_type::persistent_config_type persistent_config_type;

        template <typename T, typename Str>
        struct value_impl;

        template <typename T>
        struct value_impl<T, std::string>
        {
            boost::program_options::typed_value<T, char>* operator()()
            const
            {
                return boost::program_options::value<T>();
            }

        };

        template <typename T>
        struct value_impl<T, std::wstring>
        {
            boost::program_options::typed_value<T, wchar_t>* operator()()
            const
            {
                return boost::program_options::wvalue<T>();
            }

        };


        // static functions

        static boost::program_options::variables_map parse_command_line_arguments(
            const std::vector<string_type>& command_line_arguments
        )
        {
            boost::program_options::options_description visible_options;
            visible_options.add_options()
            ("dimension,d", value<string_type, string_type>());

            boost::program_options::options_description hidden_options;
            hidden_options.add_options()
            ("exe", value<string_type, string_type>())
            ("input", value<std::vector<string_type>, string_type>());

            boost::program_options::options_description options;
            options.add(visible_options).add(hidden_options);

            boost::program_options::positional_options_description positional_options;
            positional_options.add("exe", 1);
            positional_options.add("input", -1);

            boost::program_options::variables_map option_values;
            try
            {
                typedef
                    boost::program_options::basic_command_line_parser<typename string_type::value_type>
                    command_line_parser_type;
                const auto parsed_options =
                    command_line_parser_type(
                        command_line_arguments
                    ).options(std::move(options)).positional(std::move(positional_options)).run();
                boost::program_options::store(parsed_options, option_values);
            }
            catch (const boost::program_options::error&)
            {}
            boost::program_options::notify(option_values);

            return option_values;
        }

        template <typename T, typename Str>
        static boost::program_options::typed_value<T, typename Str::value_type>* value()
        {
            return value_impl<T, Str>()();
        }

        static std::unique_ptr<config_base_type> create_config(const boost::program_options::variables_map& options)
        {
            std::vector<std::unique_ptr<config_base_type>> p_configs;
            p_configs.push_back(create_temporary_config(options));
            p_configs.push_back(create_persistent_config());

            return tetengo2::stdalt::make_unique<config_list_type>(std::move(p_configs));
        }

        static std::unique_ptr<config_base_type> create_temporary_config(
            const boost::program_options::variables_map& options
        )
        {
            std::vector<std::pair<string_type, config_value_type>> values;
            {
                const auto main_window_dimension_ = main_window_dimension_in_command_line(options);
                if (main_window_dimension_)
                {
                    values.emplace_back(
                        string_type(TETENGO2_TEXT("MainWindow/Width")),
                        config_value_type(main_window_dimension_->first)
                    );
                    values.emplace_back(
                        string_type(TETENGO2_TEXT("MainWindow/Height")),
                        config_value_type(main_window_dimension_->second)
                    );
                }
            }

            return tetengo2::stdalt::make_unique<temporary_config_type>(values.begin(), values.end());
        }

        static boost::optional<std::pair<uint_type, uint_type>> main_window_dimension_in_command_line(
            const boost::program_options::variables_map& options
        )
        {
            const auto found = options.find("dimension");
            if (found == options.end())
                return boost::none;

            const auto width_and_height = parse_dimension(found->second.as<string_type>());
            if (!width_and_height)
                return boost::none;

            return width_and_height;
        }

        static boost::optional<std::pair<uint_type, uint_type>> parse_dimension(const string_type& dimension_string)
        {
            std::vector<string_type> result;
            typedef typename string_type::value_type char_type;
            boost::split(
                result,
                dimension_string,
                [](const char_type character) { return character == char_type(TETENGO2_TEXT('x')); }
            );
            if (result.size() < 2)
                return boost::none;

            try
            {
                return
                    std::make_pair(
                        boost::lexical_cast<uint_type>(result[0]), boost::lexical_cast<uint_type>(result[1])
                    );
            }
            catch (const boost::bad_lexical_cast&)
            {
                return boost::none;
            }
        }

        static std::unique_ptr<config_base_type> create_persistent_config()
        {
            return
                tetengo2::stdalt::make_unique<cached_config_type>(
                    tetengo2::stdalt::make_unique<persistent_config_type>(string_type(TETENGO2_TEXT("bobura")))
                );
        }


        // variables

        path_type m_base_path;

        boost::optional<path_type> m_input;

        std::unique_ptr<config_base_type> m_p_config;


        // functions

        void initialize(const std::vector<string_type>& command_line_arguments)
        {
            const auto options = parse_command_line_arguments(command_line_arguments);

            assert(options.find("exe") != options.end());
            m_base_path = boost::filesystem::path(options["exe"].template as<string_type>()).parent_path();

            if (options.find("input") != options.end())
            {
                const auto& input_values = options["input"].template as<std::vector<string_type>>();
                if (!input_values.empty())
                    m_input = boost::make_optional<string_type>(input_values[0]);
            }

            m_p_config = create_config(options);
        }


    };


}


#endif
