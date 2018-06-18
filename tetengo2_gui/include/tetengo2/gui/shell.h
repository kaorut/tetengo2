/*! \file
    \brief The definition of tetengo2::gui::shell.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_SHELL_H)
#define TETENGO2_GUI_SHELL_H

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2::gui {
    /*!
        \brief The class for a shell.
    */
    class shell : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::string_type;


        // constructors

        /*!
            \brief Creates a shell.
        */
        shell();

        /*!
            \brief Destroys the shell.
        */
        ~shell();


        // functions

        /*!
            \brief Executes a command.

            \param command    A command. When it is a path, the path is relative to the current directory.
            \param parameters Parameters.

            \retval true  When the command is executed successfully.
            \retval false Otherwise.
        */
        bool execute(const string_type& command, const std::vector<string_type>& parameters = {}) const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}

#endif
