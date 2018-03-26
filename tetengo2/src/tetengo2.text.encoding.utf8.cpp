/*! \file
    \brief The definition of tetengo2::text::encoding::utf8.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <string>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/text/encoding/encoding.h>
#include <tetengo2/text/encoding/utf8.h>


namespace tetengo2::text::encoding {
    class utf8::impl : private boost::noncopyable
    {
    public:
        // types

        using base_type = utf8::base_type;

        using pivot_type = utf8::pivot_type;

        using string_type = utf8::string_type;


        // functions

        const std::string& name_impl() const
        {
            static const std::string singleton{ "UTF-8" };
            return singleton;
        }

        string_type from_pivot_impl(pivot_type pivot) const
        {
            return utf8::details().pivot_to_utf8(std::move(pivot));
        }

        typename base_type::pivot_type to_pivot_impl(const string_type& string) const
        {
            return utf8::details().utf8_to_pivot(std::move(string));
        }
    };


    utf8::utf8() : m_p_impl{ std::make_shared<impl>() } {}

    utf8::~utf8() = default;

    const std::string& utf8::name_impl() const
    {
        return m_p_impl->name_impl();
    }

    utf8::string_type utf8::from_pivot_impl(pivot_type pivot) const
    {
        return m_p_impl->from_pivot_impl(pivot);
    }

    typename utf8::base_type::pivot_type utf8::to_pivot_impl(string_type string) const
    {
        return m_p_impl->to_pivot_impl(string);
    }
}
