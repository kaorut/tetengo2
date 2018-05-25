/*! \file
    \brief The definition of tetengo2::detail::windows::shell.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_SHELL_H)
#define TETENGO2_DETAIL_WINDOWS_SHELL_H

#include <memory>
#include <vector>

#include <tetengo2/detail/base/shell.h>


namespace tetengo2::detail::windows {
    /*!
        \brief The class for a detail implementation of a shell.
    */
    class shell : public base::shell
    {
    public:
        // types

        //! The string type.
        using string_type = base::shell::string_type;


        // static functions

        static const shell& instance();


        // constructors and destructor

        /*!
            \brief Destroys the detail implementation.
        */
        ~shell();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        shell();


        // virtual functions

        virtual bool
        execute_impl(const string_type& command, const std::vector<string_type>& parameters) const override;
    };
}


#endif
