/*! \file
    \brief The definition of tetengo2::text::encoding::cp932.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>
#include <string>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/text/encoding/cp932.h>


namespace tetengo2 { namespace text { namespace encoding
{
    class cp932::impl : private boost::noncopyable
    {
    public:
        // types

        using base_type = cp932::base_type;

        using pivot_type = cp932::pivot_type;

        using string_type = cp932::string_type;


        // functions

        const std::string& name_impl()
        const
        {
            static const std::string singleton{ "CP932" };
            return singleton;
        }

        string_type from_pivot_impl(pivot_type pivot, const cp932& base)
        const
        {
            return base.details().pivot_to_cp932(std::move(pivot));
        }

        typename base_type::pivot_type to_pivot_impl(const string_type& string, const cp932& base)
        const
        {
            return base.details().cp932_to_pivot(std::move(string));
        }


    };


    cp932::cp932()
    :
    m_p_impl(std::make_shared<impl>())
    {}

    cp932::~cp932()
    = default;

    const std::string& cp932::name_impl()
    const
    {
        return m_p_impl->name_impl();
    }

    cp932::string_type cp932::from_pivot_impl(pivot_type pivot)
    const
    {
        return m_p_impl->from_pivot_impl(pivot, *this);
    }

    typename cp932::base_type::pivot_type cp932::to_pivot_impl(string_type string)
    const
    {
        return m_p_impl->to_pivot_impl(string, *this);
    }


}}}
