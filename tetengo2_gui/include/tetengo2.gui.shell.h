/*! \file
    \brief The definition of tetengo2::gui::shell.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_SHELL_H)
#define TETENGO2_GUI_SHELL_H

#include <memory>

#include <boost/noncopyable.hpp>

#include "tetengo2.stdalt.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a shell.

        \tparam ShellDetails A detail implementation type of a shell.
    */
    template <typename ShellDetails>
    class shell : private boost::noncopyable
    {
    public:
        // types

        //! The detail implementation type of a shell.
        typedef ShellDetails shell_details_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const shell& instance()
        {
            static const shell singleton;
            return singleton;
        }


        // functions


    private:
        // variables

        std::unique_ptr<shell_details_type> m_p_shell_details;


        // constructors

        shell()
        :
        m_p_shell_details(stdalt::make_unique<shell_details_type>())
        {}


    };


}}

#endif
