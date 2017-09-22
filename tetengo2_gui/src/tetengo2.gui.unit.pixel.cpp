/*! \file
    \brief The definition of tetengo2::gui::unit::pixel.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/rational.hpp>
#include <boost/swap.hpp>

#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui { namespace unit
{
    template <typename Value>
    pixel<Value>::pixel(const value_type& value)
    :
    m_value(value)
    {}

    template <typename V1, typename V2>
    bool operator==(const pixel<V1>& one, const V2& another)
    {
        return one.value() == another;
    }

    template <typename V1, typename V2>
    bool operator<(const pixel<V1>& one, const V2& another)
    {
        return one.value() < another;
    }

    template <typename V1, typename V2>
    bool operator>(const pixel<V1>& one, const V2& another)
    {
        return one.value() > another;
    }

    template <typename Value>
    pixel<Value>& pixel<Value>::add(const value_type& another)
    {
        pixel temp{ *this };

        temp.m_value += another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    pixel<Value>& pixel<Value>::subtract(const value_type& another)
    {
        pixel temp{ *this };

        temp.m_value -= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    pixel<Value>& pixel<Value>::multiply(const value_type& another)
    {
        pixel temp{ *this };

        temp.m_value *= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    pixel<Value>& pixel<Value>::divide_by(const value_type& another)
    {
        pixel temp{ *this };

        temp.m_value /= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    Value pixel<Value>::divide_by(const pixel& another)
    const
    {
        return value() / another.value();
    }

    template <typename Value>
    const Value& pixel<Value>::value()
    const
    {
        return m_value;
    }

    template <typename Value>
    typename Value::int_type pixel<Value>::to_pixels_impl(const value_type& value)
    {
        return boost::rational_cast<typename value_type::int_type>(value);
    }


    namespace
    {
        using size_rational_type = boost::rational<type_list::size_type>;

        using difference_rational_type = boost::rational<type_list::difference_type>;

    }

    template class pixel<size_rational_type>;

    template class pixel<difference_rational_type>;

    template type_list::size_type pixel<size_rational_type>::to_pixels_impl(const value_type& value);

    template type_list::difference_type pixel<difference_rational_type>::to_pixels_impl(const value_type& value);

    template bool operator==(const pixel<size_rational_type>& one, const size_rational_type& another);

    template bool operator==(const pixel<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator==(const pixel<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator==(
        const pixel<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );

    template bool operator<(const pixel<size_rational_type>& one, const size_rational_type& another);

    template bool operator<(const pixel<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator<(const pixel<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator<(
        const pixel<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );

    template bool operator>(const pixel<size_rational_type>& one, const size_rational_type& another);

    template bool operator>(const pixel<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator>(const pixel<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator>(
        const pixel<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );


}}}
