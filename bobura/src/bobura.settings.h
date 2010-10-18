/*! \file
    \brief The definition of bobura::settings.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_SETTINGS_H)
#define BOBURA_SETTINGS_H

#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/program_options.hpp>


namespace bobura
{
    /*!
        \brief The class template for settings of bobura.

        \tparam String A string type.
    */
    template <typename String>
    class settings : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        typedef String string_type;


        // constructors and destructor

        /*!
            \brief Creates empty settings.
        */
        settings()
        :
        m_options(make_options()),
        m_option_values()
        {}

        /*!
            \brief Creates settings.

            \param command_line_arguments A command line arguments.
        */
        settings(std::vector<string_type>&& command_line_arguments)
        :
        m_options(make_options()),
        m_option_values(
            make_option_values(
                m_options,
                std::forward<std::vector<string_type>>(command_line_arguments)
            )
        )
        {}


    private:
        // variables

        const boost::program_options::options_description m_options;

        const boost::program_options::variables_map m_option_values;


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
