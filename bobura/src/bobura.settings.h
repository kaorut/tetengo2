/*! \file
    \brief The definition of bobura::settings.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_SETTINGS_H)
#define BOBURA_SETTINGS_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <boost/filesystem/path.hpp>
#include <boost/noncopyable.hpp>
#include <boost/program_options.hpp>

#include <tetengo2.text.h>
#include <tetengo2.unique.h>


namespace bobura
{
    /*!
        \brief The class template for settings of bobura.

        \tparam String       A string type.
        \tparam Path         A path type.
        \tparam ConfigTraits A configuration traits type.
    */
    template <typename String, typename Path, typename ConfigTraits>
    class settings : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The path type.
        typedef Path path_type;

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


    private:
        // types

        typedef typename path_type::string_type path_string_type;

        typedef typename config_traits_type::uint_type uint_type;

        typedef typename config_traits_type::config_base_type config_base_type;

        typedef typename config_traits_type::config_list_type config_list_type;

        typedef typename config_traits_type::cached_config_type cached_config_type;

        typedef typename config_traits_type::temporary_config_type temporary_config_type;

        typedef typename config_traits_type::persistent_config_type persistent_config_type;


        // static functions

        static boost::program_options::variables_map parse_command_line_arguments(
            const std::vector<string_type>& command_line_arguments
        )
        {
            boost::program_options::options_description visible_options;
            visible_options.add_options()
            ("dimension,d", boost::program_options::value<std::string>(), "Set a dimension of the main window.")
            ("help", "Shows a help message.");

            boost::program_options::options_description hidden_options;
            hidden_options.add_options()
            ("exe", boost::program_options::value<std::string>())
            ("input", boost::program_options::value<std::vector<std::string>>());

            boost::program_options::options_description options;
            options.add(visible_options).add(hidden_options);

            boost::program_options::positional_options_description positional_options;
            positional_options.add("exe", 1);
            positional_options.add("input", -1);

            boost::program_options::variables_map option_values;
            try
            {
                typedef
                    boost::program_options::basic_parsed_options<typename string_type::value_type> parsed_options_type;
                typedef
                    boost::program_options::basic_command_line_parser<typename string_type::value_type>
                    command_line_parser_type;
                const parsed_options_type parsed_options =
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

        static std::unique_ptr<config_base_type> create_config(const boost::program_options::variables_map& options)
        {
            std::vector<std::unique_ptr<config_base_type>> p_configs;
            p_configs.push_back(create_temporary_config(options));
            p_configs.push_back(create_persistent_config());

            return tetengo2::make_unique<config_list_type>(std::move(p_configs));
        }

        static std::unique_ptr<config_base_type> create_temporary_config(
            const boost::program_options::variables_map& options
        )
        {
            std::vector<std::pair<string_type, uint_type>> values;

            return tetengo2::make_unique<temporary_config_type>(values.begin(), values.end());
        }

        static std::unique_ptr<config_base_type> create_persistent_config()
        {
            return
                tetengo2::make_unique<cached_config_type>(
                    tetengo2::make_unique<persistent_config_type>(string_type(TETENGO2_TEXT("bobura")))
                );
        }


        // variables

        path_type m_base_path;

        std::unique_ptr<config_base_type> m_p_config;


        // functions

        void initialize(const std::vector<string_type>& command_line_arguments)
        {
            const boost::program_options::variables_map options = parse_command_line_arguments(command_line_arguments);

            assert(options.find("exe") != options.end());
            m_base_path = boost::filesystem::path(options["exe"].as<std::string>()).parent_path();

            m_p_config = create_config(options);
        }


    };


}


#endif
