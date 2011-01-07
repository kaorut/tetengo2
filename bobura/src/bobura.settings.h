/*! \file
    \brief The definition of bobura::settings.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(BOBURA_SETTINGS_H)
#define BOBURA_SETTINGS_H

#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/program_options.hpp>

#include <tetengo2.text.h>


namespace bobura
{
    /*!
        \brief The class template for settings of bobura.

        \tparam String A string type.
        \tparam Path   A path type.
    */
    template <typename String, typename Path>
    class settings : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The path type.
        typedef Path path_type;


        // constructors and destructor

        /*!
            \brief Creates settings.

            \tparam V A vector of string type.
            \tparam P A path type.

            \param command_line_arguments Command line arguments.
            \param base_path              A base path.
        */
        template <typename V, typename P>
        settings(V&& command_line_arguments, P&& base_path)
        :
        m_options(make_options()),
        m_option_values(
            make_option_values(
                m_options, std::forward<V>(command_line_arguments)
            )
        ),
        m_base_path(std::forward<P>(base_path))
        {}


        // functions

        const path_type& base_path()
        const
        {
            return m_base_path;
        }

        path_type message_directory_path()
        const
        {
            return m_base_path / path_string_type(TETENGO2_TEXT("messages"));
        }

        path_type image_directory_path()
        const
        {
            return m_base_path / path_string_type(TETENGO2_TEXT("images"));
        }


    private:
        // types

        typedef typename path_type::string_type path_string_type;


        // variables

        const boost::program_options::options_description m_options;

        const boost::program_options::variables_map m_option_values;

        const path_type m_base_path;


        // functions

        static boost::program_options::options_description
        make_options()
        {
            boost::program_options::options_description options(
                "bobura"
            );
            
            options.add_options()
            ("help,h", "help")
            (
                "geometry,g",
                boost::program_options::value<int>()->default_value(640),
                "geometry"
            )
            ;

            return std::move(options);
        }

        static boost::program_options::variables_map make_option_values(
            const boost::program_options::options_description& options,
            std::vector<string_type>&&                         command_line_arguments
        )
        {
            boost::program_options::wparsed_options parsed_options =
                boost::program_options::wcommand_line_parser(
                    std::forward<std::vector<string_type>>(
                        command_line_arguments
                    )
                ).options(options).run();

            boost::program_options::variables_map option_values;
            boost::program_options::store(
                std::move(parsed_options), option_values
            );
            boost::program_options::notify(option_values);

            return std::move(option_values);
        }


    };


}

#endif
