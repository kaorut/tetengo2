/*! \file
    \brief The definition of tetengo2::text::encoding::encoding.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>
#include <string>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#if BOOST_OS_WINDOWS
#   include <tetengo2/detail/windows/encoding.h>
#elif BOOST_OS_LINUX
#   include <tetengo2/detail/unixos/encoding.h>
#else
#   error Unsupported platform.
#endif
#include <tetengo2/text/encoding/encoding.h>


namespace tetengo2 { namespace text { namespace encoding
{
    template <typename String>
    class encoding<String>::impl : private boost::noncopyable
    {
    public:
        // types

        using pivot_type = typename encoding::pivot_type;

        using string_type = typename encoding::string_type;


        // constructors and destructor

        impl()
        :
#if BOOST_OS_WINDOWS
        m_encoding_details(detail::windows::encoding::instance())
#elif BOOST_OS_LINUX
        m_encoding_details(detail::unixos::encoding::instance())
#else
#   error Unsupported platform.
#endif
        {}


        // functions

        const encoding_details_type& details()
        const
        {
            return m_encoding_details;
        }

        string_type from_pivot(const pivot_type& pivot, const encoding<String>& base)
        const
        {
            return base.from_pivot_impl(pivot);
        }

        pivot_type to_pivot(const string_type& string, const encoding<String>& base)
        const
        {
            return base.to_pivot_impl(string);
        }


    private:
        // variables

        const encoding_details_type& m_encoding_details;


    };


    template <typename String>
    encoding<String>::~encoding()
    = default;

    template <typename S>
    bool operator==(const encoding<S>& one, const encoding<S>& another)
    {
        boost::ignore_unused(one, another);
        return true;
    }

    template <typename String>
    encoding<String>::encoding()
    :
    m_p_impl(std::make_shared<impl>())
    {}

    template <typename String>
    const typename encoding<String>::encoding_details_type& encoding<String>::details()
    const
    {
        return m_p_impl->details();
    }

    template <typename String>
    typename encoding<String>::string_type encoding<String>::from_pivot(const pivot_type& pivot)
    const
    {
        return m_p_impl->from_pivot(pivot, *this);
    }

    template <typename String>
    typename encoding<String>::pivot_type encoding<String>::to_pivot(const string_type& string)
    const
    {
        return m_p_impl->to_pivot(string, *this);
    }


    template class encoding<std::string>;

    template class encoding<std::wstring>;

    template bool operator==(const encoding<std::string>& one, const encoding<std::string>& another);

    template bool operator==(const encoding<std::wstring>& one, const encoding<std::wstring>& another);


}}}
