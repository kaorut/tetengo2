/*! \file
    \brief The definition of tetengo2::text::encoding::cp932.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>

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
#include <tetengo2/text/encoding/cp932.h>


namespace tetengo2 { namespace text { namespace encoding
{
    class cp932::impl : private boost::noncopyable
    {
    public:
        // types

        using base_type = cp932::base_type;

        using string_type = cp932::string_type;

        using encoding_details_type = cp932::encoding_details_type;


        // constructors and destructors

        impl()
        :
#if BOOST_OS_WINDOWS
        m_encoding_details(tetengo2::detail::windows::encoding::instance())
#elif BOOST_OS_LINUX
        m_encoding_details(tetengo2::detail::unixos::encoding::instance())
#else
#   error Unsupported platform.
#endif
        {}


        // functions

        string_type from_pivot_impl(const typename base_type::pivot_type& pivot)
        const
        {
            return m_encoding_details.pivot_to_cp932(pivot);
        }

        typename base_type::pivot_type to_pivot_impl(const string_type& string)
        const
        {
            return m_encoding_details.cp932_to_pivot(string);
        }


    private:
        // variables

        const encoding_details_type& m_encoding_details;


    };


    cp932::cp932()
    :
    m_p_impl(std::make_shared<impl>())
    {}

    cp932::~cp932()
    = default;


    cp932::string_type cp932::from_pivot_impl(const typename base_type::pivot_type& pivot)
    const
    {
        return m_p_impl->from_pivot_impl(pivot);
    }

    typename cp932::base_type::pivot_type cp932::to_pivot_impl(const string_type& string)
    const
    {
        return m_p_impl->to_pivot_impl(string);
    }


}}}
