/*! \file
    \brief The definition of tetengo2::gui::shell.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/shell.h>


namespace tetengo2::gui {
    class shell::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = shell::string_type;

        using shell_details_type = shell::shell_details_type;


        // constructors

        explicit impl(const shell_details_type& shell_details) : m_shell_details{ shell_details } {}


        // functions

        bool execute(const string_type& command, const std::vector<string_type>& parameters) const
        {
            return m_shell_details.execute(command, parameters);
        }


    private:
        // variables

        const shell_details_type& m_shell_details;
    };


    shell::shell(const shell_details_type& shell_details) : m_p_impl{ std::make_unique<impl>(shell_details) } {}

    shell::~shell() = default;

    bool shell::execute(const string_type& command, const std::vector<string_type>& parameters /*= {}*/) const
    {
        return m_p_impl->execute(command, parameters);
    }
}
