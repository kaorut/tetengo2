/*! \file
    \brief The definition of tetengo2::detail::base::shell.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_SHELL_H)
#define TETENGO2_DETAIL_BASE_SHELL_H

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of a shell.
    */
    class shell : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = type_list::string_type;


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        virtual ~shell();


        // functions

        /*!
            \brief Executes a command.

            \param command    A command. When it is a path, the path is relative to the current directory.
            \param parameters Parameters.

            \retval true  When the command is executed successfully.
            \retval false Otherwise.
        */
        bool execute(const string_type& command, const std::vector<string_type>& parameters) const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        shell();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual bool execute_impl(const string_type& command, const std::vector<string_type>& parameters) const = 0;
    };
}


#endif
