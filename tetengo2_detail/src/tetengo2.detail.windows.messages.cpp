/*! \file
    \brief The definition of tetengo2::detail::windows::messages.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/messages.h>
#include <tetengo2/detail/windows/messages.h>
#include <tetengo2/text.h>


namespace tetengo2::detail::windows {
    class messages::impl : private boost::noncopyable
    {
    public:
        // types

        using string_type = base::messages::string_type;


        // virtual functions

        const string_type& locale_name_prefix_impl() const
        {
            static const string_type singleton{ TETENGO2_TEXT("Windows") };
            return singleton;
        }
    };


    messages::messages() : m_p_impl{ std::make_unique<impl>() } {}

    messages::~messages() {}

    const messages::string_type& messages::locale_name_prefix_impl() const
    {
        return m_p_impl->locale_name_prefix_impl();
    }
}