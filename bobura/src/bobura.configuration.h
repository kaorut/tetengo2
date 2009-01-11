/*! \file
    \brief The definition of bobura::configuration.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_CONFIGURATION_H)
#define BOBURA_CONFIGURATION_H

//#include <cstddef>
//#include <memory>
//#include <string>

#include <boost/function.hpp>
//#include <boost/noncopyable.hpp>
#include <boost/program_options.hpp>

#include <tetengo2.gui.win32.gui_type_list.h>

#include "bobura.bobura.h"


namespace bobura
{
    /*!
        \brief The class for a configuration of bobura.
    */
    class configuration : private boost::noncopyable
    {
    public:
        // types

        //! The type list type to create platform specific GUI components.
        typedef
            tetengo2::gui::win32::gui_type_list<std::size_t, std::wstring>
            gui_type_list_type;

        //! The GUI initialization and finalization manager type.
        typedef
            gui_type_list_type::gui_initializer_finalizer_type
            gui_initializer_finalizer_type;

        //! The binary functor type of the alert.
        typedef gui_type_list_type::alert_type alert_type;

        //! The Bobura application type.
        typedef
            bobura<gui_type_list_type, boost::function<void ()> >
            bobura_type;


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
            \brief Creates a configuration.

            \param option_values The option values for the application.
        */
        explicit configuration(
            const boost::program_options::variables_map& option_values
        )
        :
        m_option_values(option_values)
        {}

        /*!
            \brief Destroys the configuration.
        */
        ~configuration()
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
