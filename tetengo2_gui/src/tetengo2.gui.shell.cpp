/*! \file
    \brief The definition of tetengo2::gui::shell.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/shell.h>
#include <tetengo2/gui/shell.h>


namespace tetengo2::gui {
    class shell::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = shell::string_type;


        // functions

        bool execute(const string_type& command, const std::vector<string_type>& parameters) const
        {
            return detail::gui_detail_impl_set().shell_().execute(command, parameters);
        }
    };


    shell::shell() : m_p_impl{ std::make_unique<impl>() } {}

    shell::~shell() = default;

    bool shell::execute(const string_type& command, const std::vector<string_type>& parameters /*= {}*/) const
    {
        return m_p_impl->execute(command, parameters);
    }
}
