/*! \file
    \brief The definition of tetengo2::detail::stub::shell.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/shell.h>
#include <tetengo2/detail/stub/shell.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>


namespace tetengo2::detail::stub {
    class shell::impl : private boost::noncopyable
    {
    public:
        // types

        //! The string type.
        using string_type = base::shell::string_type;


        // static functions

        static const shell& instance()
        {
            static const shell singleton;
            return singleton;
        }


        // functions

        bool execute_impl(
            const string_type&                 command,
            TETENGO2_STDALT_MAYBE_UNUSED const std::vector<string_type>& parameters) const
        {
            return command.find(TETENGO2_TEXT("fail")) == string_type::npos;
        }
    };


    const shell& shell::instance()
    {
        return impl::instance();
    }

    shell::~shell() = default;

    shell::shell() : m_p_impl{ std::make_unique<impl>() } {}

    bool shell::execute_impl(const string_type& command, const std::vector<string_type>& parameters) const
    {
        return m_p_impl->execute_impl(command, parameters);
    }
}