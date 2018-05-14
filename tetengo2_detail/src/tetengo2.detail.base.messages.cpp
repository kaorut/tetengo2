/*! \file
    \brief The definition of tetengo2::detail::base::messages.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/messages.h>


namespace tetengo2::detail::base {
    class messages::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = messages::string_type;


        // functions

        const string_type& locale_name_prefix(const messages& self) const
        {
            return self.locale_name_prefix_impl();
        }
    };


    messages::~messages() {}

    const messages::string_type& messages::locale_name_prefix() const
    {
        return m_p_impl->locale_name_prefix(*this);
    }

    messages::messages() : m_p_impl{ std::make_unique<impl>() } {}
}
