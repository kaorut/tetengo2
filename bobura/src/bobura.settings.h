/*! \file
    \brief The definition of bobura::settings.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_SETTINGS_H)
#define BOBURA_SETTINGS_H //!< !! Include Guard !!

#include <vector>

//#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>
#include <boost/program_options.hpp>

#include <concept_tetengo2.String.h>


namespace bobura
{
    /*!
        \brief The class template for settings of bobura.

        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
    */
    template <typename String>
    class settings : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));


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

            \tparam CommandLineArgumentInputIterator A input iterator type for
                                                     a command line arguments.

            \param command_line_argument_first The first iterator for a
                                               command line arguments.
            \param command_line_argument_last  The last iterator for a command
                                               line arguments.
        */
        template <typename CommandLineArgumentInputIterator>
        settings(
            CommandLineArgumentInputIterator command_line_argument_first,
            CommandLineArgumentInputIterator command_line_argument_last
        )
        :
        m_options(make_options()),
        m_option_values(
            make_option_values(
                m_options,
                std::vector<string_type>(
                    command_line_argument_first, command_line_argument_last
                )
            )
        )
        {}

        /*!
            \brief Destroys the settings.
        */
        ~settings()
        throw ()
        {}


    private:
        // variables

        const boost::program_options::options_description m_options;

        const boost::program_options::variables_map m_option_values;


        // functions

        static const boost::program_options::options_description
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

            return options;
        }

        static const boost::program_options::variables_map make_option_values(
            const boost::program_options::options_description& options,
            const std::vector<string_type>&                    command_line_arguments
        )
        {
            const boost::program_options::wparsed_options& parsed_options =
                boost::program_options::wcommand_line_parser(
                    command_line_arguments
                ).options(options).run();

            boost::program_options::variables_map option_values;
            boost::program_options::store(parsed_options, option_values);
            boost::program_options::notify(option_values);

            return option_values;
        }


    };


}

#endif
