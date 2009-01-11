/*! \file
    \brief The definition of bobura::settings.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_SETTINGS_H)
#define BOBURA_SETTINGS_H

//#include <boost/noncopyable.hpp>
#include <boost/program_options.hpp>

#include <tetengo2.gui.win32.gui_type_list.h>

#include "bobura.bobura.h"


namespace bobura
{
    /*!
        \brief The class for settings of bobura.
    */
    class settings : private boost::noncopyable
    {
    public:
        // static functions

        /*!
            \brief Returns the option description of the application.

            \return The options description.
        */
        static const boost::program_options::options_description& options()
        {
            static const boost::program_options::options_description&
            singleton = make_options();

            return singleton;
        }


        // constructors and destructor

        /*!
            \brief Creates settings.

            \param option_values The option values for the application.
        */
        explicit settings(
            const boost::program_options::variables_map& option_values
        )
        :
        m_option_values(option_values)
        {}

        /*!
            \brief Destroys the settings.
        */
        ~settings()
        throw ()
        {}


    private:
        // variables

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


    };


}

#endif
