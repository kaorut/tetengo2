/*! \file
    \brief The definition of tetengo2::detail::base::shell.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/shell.h>


namespace tetengo2::detail::base {
    class shell::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = shell::string_type;


        // functions

        bool execute(const string_type& command, const std::vector<string_type>& parameters, const shell& base) const
        {
            return base.execute_impl(command, parameters);
        }
    };


    shell::~shell() = default;

    bool shell::execute(const string_type& command, const std::vector<string_type>& parameters) const
    {
        return m_p_impl->execute(command, parameters, *this);
    }

    shell::shell() : m_p_impl{ std::make_unique<impl>() } {}
}