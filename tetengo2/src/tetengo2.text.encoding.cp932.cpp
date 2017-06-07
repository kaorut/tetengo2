/*! \file
    \brief The definition of tetengo2::text::encoding::cp932.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>

#include <tetengo2/text/encoding/cp932.h>


namespace tetengo2 { namespace text { namespace encoding
{
    class cp932::impl : boost::noncopyable
    {
    public:
        // types

        using base_type = cp932::base_type;

        using string_type = cp932::string_type;

        using encoding_details_type = cp932::encoding_details_type;


        // constructors and destructors

        explicit impl(const encoding_details_type& encoding_details)
        :
        m_encoding_details(encoding_details)
        {}


        // functions

        friend bool operator==(const impl& one, const impl& another)
        {
            boost::ignore_unused(one, another);
            return true;
        }

        string_type from_pivot(const typename base_type::pivot_type& pivot)
        const
        {
            return m_encoding_details.pivot_to_cp932(pivot);
        }

        typename base_type::pivot_type to_pivot(const string_type& string)
        const
        {
            return m_encoding_details.cp932_to_pivot(string);
        }


    private:
        // variables

        const encoding_details_type& m_encoding_details;


    };


    cp932::cp932(const encoding_details_type& encoding_details)
    :
    m_p_impl(std::make_shared<impl>(encoding_details))
    {}

    cp932::~cp932()
    = default;


    bool operator==(const cp932& one, const cp932& another)
    {
        return *one.m_p_impl == *another.m_p_impl;
    }

    cp932::string_type cp932::from_pivot(const typename base_type::pivot_type& pivot)
    const
    {
        return m_p_impl->from_pivot(pivot);
    }

    typename cp932::base_type::pivot_type cp932::to_pivot(const string_type& string)
    const
    {
        return m_p_impl->to_pivot(string);
    }


}}}
