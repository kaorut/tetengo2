/*! \file
    \brief The definition of tetengo2::gui::unit::basic_em.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <boost/rational.hpp>
#include <boost/swap.hpp>

#include <tetengo2/gui/unit/em.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui { namespace unit
{
    template <typename Value>
    basic_em<Value>::basic_em(value_type value, const unit_details_type& unit_details)
    :
    m_value(std::move(value)),
    m_p_details(&unit_details)
    {}

    template <typename V1, typename V2>
    bool operator==(const basic_em<V1>& one, const V2& another)
    {
        return one.value() == another;
    }

    template <typename V1, typename V2>
    bool operator<(const basic_em<V1>& one, const V2& another)
    {
        return one.value() < another;
    }

    template <typename V1, typename V2>
    bool operator>(const basic_em<V1>& one, const V2& another)
    {
        return one.value() > another;
    }

    template <typename Value>
    basic_em<Value>& basic_em<Value>::add(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value += another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    basic_em<Value>& basic_em<Value>::subtract(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value -= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    basic_em<Value>& basic_em<Value>::multiply(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value *= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    basic_em<Value>& basic_em<Value>::divide_by(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value /= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    Value basic_em<Value>::divide_by(const basic_em& another)
    const
    {
        return value() / another.value();
    }

    template <typename Value>
    const Value& basic_em<Value>::value()
    const
    {
        return m_value;
    }

    template <typename Value>
    const typename basic_em<Value>::unit_details_type& basic_em<Value>::details()
    const
    {
        return *m_p_details;
    }

    template <typename Value>
    basic_em<Value> basic_em<Value>::from_pixels_impl(
        const typename value_type::int_type value,
        const unit_details_type&            unit_details
    )
    {
        return basic_em{ unit_details.to_em(value), unit_details };
    }

    template <typename Value>
    typename Value::int_type basic_em<Value>::to_pixels_impl(
        const value_type&        value,
        const unit_details_type& unit_details
    )
    {
        return unit_details.template em_to_pixel<typename value_type::int_type>(value);
    }


    namespace
    {
        using size_rational_type = boost::rational<type_list::size_type>;

        using difference_rational_type = boost::rational<type_list::difference_type>;

    }

    template class basic_em<size_rational_type>;

    template class basic_em<difference_rational_type>;

    template bool operator==(const basic_em<size_rational_type>& one, const size_rational_type& another);

    template bool operator==(const basic_em<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator==(const basic_em<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator==(
        const basic_em<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );

    template bool operator<(const basic_em<size_rational_type>& one, const size_rational_type& another);

    template bool operator<(const basic_em<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator<(const basic_em<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator<(
        const basic_em<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );

    template bool operator>(const basic_em<size_rational_type>& one, const size_rational_type& another);

    template bool operator>(const basic_em<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator>(const basic_em<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator>(
        const basic_em<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );


}}}
