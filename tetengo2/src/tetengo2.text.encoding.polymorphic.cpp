/*! \file
    \brief The definition of tetengo2::text::encoding::polymorphic.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/text/encoding/polymorphic.h>


namespace tetengo2::text::encoding {
    template <typename String>
    class polymorphic<String>::impl : private boost::noncopyable
    {
    public:
        // types

        using base_type = typename polymorphic::base_type;

        using pivot_type = typename polymorphic::pivot_type;

        using string_type = typename polymorphic::string_type;


        // constructors and destructors

        impl() : m_p_encoding{} {}

        explicit impl(std::unique_ptr<base_type> p_encoding) : m_p_encoding{ std::move(p_encoding) }
        {
            if (!m_p_encoding)
                BOOST_THROW_EXCEPTION(std::invalid_argument("p_encoding is nullptr."));
        }


        // functions

        const std::string& name_impl() const
        {
            if (!m_p_encoding)
                BOOST_THROW_EXCEPTION(std::logic_error("p_encoding is nullptr."));
            return m_p_encoding->name();
        }

        string_type from_pivot_impl(pivot_type pivot) const
        {
            if (!m_p_encoding)
                BOOST_THROW_EXCEPTION(std::logic_error("p_encoding is nullptr."));
            return m_p_encoding->from_pivot(std::move(pivot));
        }

        typename base_type::pivot_type to_pivot_impl(string_type string) const
        {
            if (!m_p_encoding)
                BOOST_THROW_EXCEPTION(std::logic_error("p_encoding is nullptr."));
            return m_p_encoding->to_pivot(std::move(string));
        }


    private:
        // variables

        const std::unique_ptr<base_type> m_p_encoding;
    };


    template <typename String>
    polymorphic<String>::polymorphic() : m_p_impl{ std::make_shared<impl>() }
    {}

    template <typename String>
    polymorphic<String>::polymorphic(std::unique_ptr<base_type> p_encoding)
    : m_p_impl{ std::make_shared<impl>(std::move(p_encoding)) }
    {}

    template <typename String>
    polymorphic<String>::~polymorphic() = default;

    template <typename String>
    const std::string& polymorphic<String>::name_impl() const
    {
        return m_p_impl->name_impl();
    }

    template <typename String>
    typename polymorphic<String>::string_type polymorphic<String>::from_pivot_impl(pivot_type pivot) const
    {
        return m_p_impl->from_pivot_impl(pivot);
    }

    template <typename String>
    typename polymorphic<String>::pivot_type polymorphic<String>::to_pivot_impl(string_type string) const
    {
        return m_p_impl->to_pivot_impl(string);
    }


    template class polymorphic<std::string>;

    template class polymorphic<std::wstring>;
}
