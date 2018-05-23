/*! \file
    \brief The definition of tetengo2::gui::shell.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_SHELL_H)
#define TETENGO2_GUI_SHELL_H

#include <vector>

#include <boost/core/noncopyable.hpp>


namespace tetengo2::gui {
    /*!
        \brief The class template for a shell.

        \tparam String       A string type.
        \tparam Encoder      An encoder type.
        \tparam ShellDetails A detail implementation type of a shell.
    */
    template <typename String, typename Encoder, typename ShellDetails>
    class shell : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = String;

        //! The encoder type.
        using encoder_type = Encoder;

        //! The shell details type.
        using shell_details_type = ShellDetails;


        // constructors

        /*!
            \brief Creates a shell.

            \param shell_details A detail implementation of a shell.
        */
        explicit shell(const shell_details_type& shell_details) : m_shell_details{ shell_details } {}


        // functions

        /*!
            \brief Executes a command.

            \param command A command. When it is a path, the path is relative to the current directory.

            \retval true  When the command is executed successfully.
            \retval false Otherwise.
        */
        bool execute(const string_type& command) const
        {
            static const std::vector<string_type> empty_parameters;
            return execute(command, empty_parameters.begin(), empty_parameters.end());
        }

        /*!
            \brief Executes a command.

            \tparam InputIterator An input iterator type.

            \param command         A command. When it is a path, the path is relative to the current directory.
            \param parameter_first The first iterator to parameters.
            \param parameter_last  The last iterator to parameters.

            \retval true  When the command is executed successfully.
            \retval false Otherwise.
        */
        template <typename InputIterator>
        bool
        execute(const string_type& command, const InputIterator parameter_first, const InputIterator parameter_last)
            const
        {
            static const encoder_type      encoder{};
            const std::vector<string_type> parameters{ parameter_first, parameter_last };
            return m_shell_details.execute(command, parameters);
        }


    private:
        // variables

        const shell_details_type& m_shell_details;
    };
}

#endif
