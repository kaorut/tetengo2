/*! \file
    \brief The definition of tetengo2::gui::unit::point.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/rational.hpp>
#include <boost/swap.hpp>

#include <tetengo2/gui/unit/point.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui { namespace unit
{
    template <typename Value>
    point<Value>::point(const value_type& value, const unit_details_type& unit_details)
    :
    m_value(value),
    m_p_details(&unit_details)
    {}

    template <typename V1, typename V2>
    bool operator==(const point<V1>& one, const V2& another)
    {
        return one.value() == another;
    }

    template <typename V1, typename V2>
    bool operator<(const point<V1>& one, const V2& another)
    {
        return one.value() < another;
    }

    template <typename V1, typename V2>
    bool operator>(const point<V1>& one, const V2& another)
    {
        return one.value() > another;
    }

    template <typename Value>
    point<Value>& point<Value>::add(const value_type& another)
    {
        point temp{ *this };

        temp.m_value += another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    point<Value>& point<Value>::subtract(const value_type& another)
    {
        point temp{ *this };

        temp.m_value -= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    point<Value>& point<Value>::multiply(const value_type& another)
    {
        point temp{ *this };

        temp.m_value *= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    point<Value>& point<Value>::divide_by(const value_type& another)
    {
        point temp{ *this };

        temp.m_value /= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    Value point<Value>::divide_by(const point& another)
    const
    {
        return value() / another.value();
    }

    template <typename Value>
    const Value& point<Value>::value()
    const
    {
        return m_value;
    }

    template <typename Value>
    const typename point<Value>::unit_details_type& point<Value>::details()
    const
    {
        return *m_p_details;
    }

    template <typename Value>
    point<Value> point<Value>::from_pixels_impl(
        const typename value_type::int_type value,
        const unit_details_type&            unit_details
    )
    {
        return point{ unit_details.to_point(value), unit_details };
    }

    template <typename Value>
    typename Value::int_type point<Value>::to_pixels_impl(
        const value_type&        value,
        const unit_details_type& unit_details
    )
    {
        return unit_details.template point_to_pixel<typename value_type::int_type>(value);
    }


    namespace
    {
        using size_rational_type = boost::rational<type_list::size_type>;

        using difference_rational_type = boost::rational<type_list::difference_type>;

    }

    template class point<size_rational_type>;

    template class point<difference_rational_type>;

    template bool operator==(const point<size_rational_type>& one, const size_rational_type& another);

    template bool operator==(const point<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator==(const point<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator==(
        const point<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );

    template bool operator<(const point<size_rational_type>& one, const size_rational_type& another);

    template bool operator<(const point<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator<(const point<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator<(
        const point<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );

    template bool operator>(const point<size_rational_type>& one, const size_rational_type& another);

    template bool operator>(const point<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator>(const point<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator>(
        const point<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );


}}}
