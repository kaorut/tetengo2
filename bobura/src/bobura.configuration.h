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
#include <tetengo2.gui.win32.message_loop.h>
#include <tetengo2.gui.win32.quit_message_loop.h>

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

        //! The type list type to create platform specific GUI
        //! components.
        typedef
            tetengo2::gui::win32::gui_type_list<std::size_t, std::wstring>
            gui_type_list_type;

        //! The binary functor type of the alert.
        typedef
            tetengo2::gui::win32::alert<
                typename gui_type_list_type::window_type::handle_type,
                tetengo2::win32::encode
            >
            alert_type;

        //! The GUI initialization and finalization manager type.
        typedef
            gui_type_list_type::gui_initializer_finalizer_type
            gui_initializer_finalizer_type;

        //! The generator type for the message loop.
        typedef tetengo2::gui::win32::message_loop message_loop_type;

        //! The unary functor type for quitting the message loop.
        typedef
            tetengo2::gui::win32::quit_message_loop quit_message_loop_type;

        //! The Bobura application type.
        typedef
            bobura<
                gui_type_list_type,
                message_loop_type,
                quit_message_loop_type,
                boost::function<void ()>
            >
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

        /*!
            \brief Returns a unary functor for an alert.

            \return A unary functor for an alert.
        */
        static const alert_type alert()
        {
            return alert_type();
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


        // functions

        /*!
            \brief Creates a Bobura application.

            \return An auto pointer to a Bobura application.
        */
        std::auto_ptr<bobura_type> create_bobura()
        const
        {
            return std::auto_ptr<bobura_type>(new bobura_type());
        }


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
