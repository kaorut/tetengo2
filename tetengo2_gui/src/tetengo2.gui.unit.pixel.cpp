/*! \file
    \brief The definition of tetengo2::gui::unit::basic_pixel.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <boost/rational.hpp>
#include <boost/swap.hpp>

#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui { namespace unit
{
    template <typename Value>
    basic_pixel<Value>::basic_pixel()
    :
    m_value(0)
    {}

    template <typename Value>
    basic_pixel<Value>::basic_pixel(value_type value)
    :
    m_value(std::move(value))
    {}

    template <typename V1, typename V2>
    bool operator==(const basic_pixel<V1>& one, const V2& another)
    {
        return one.value() == another;
    }

    template <typename V1, typename V2>
    bool operator<(const basic_pixel<V1>& one, const V2& another)
    {
        return one.value() < another;
    }

    template <typename V1, typename V2>
    bool operator>(const basic_pixel<V1>& one, const V2& another)
    {
        return one.value() > another;
    }

    template <typename Value>
    basic_pixel<Value>& basic_pixel<Value>::add(const value_type& another)
    {
        basic_pixel temp{ *this };

        temp.m_value += another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    basic_pixel<Value>& basic_pixel<Value>::subtract(const value_type& another)
    {
        basic_pixel temp{ *this };

        temp.m_value -= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    basic_pixel<Value>& basic_pixel<Value>::multiply(const value_type& another)
    {
        basic_pixel temp{ *this };

        temp.m_value *= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    basic_pixel<Value>& basic_pixel<Value>::divide_by(const value_type& another)
    {
        basic_pixel temp{ *this };

        temp.m_value /= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    Value basic_pixel<Value>::divide_by(const basic_pixel& another)
    const
    {
        return value() / another.value();
    }

    template <typename Value>
    const Value& basic_pixel<Value>::value()
    const
    {
        return m_value;
    }

    template <typename Value>
    typename Value::int_type basic_pixel<Value>::to_pixels_impl(const value_type& value)
    {
        return boost::rational_cast<typename value_type::int_type>(value);
    }


    namespace
    {
        using size_rational_type = boost::rational<type_list::size_type>;

        using difference_rational_type = boost::rational<type_list::difference_type>;

    }

    template class basic_pixel<size_rational_type>;

    template class basic_pixel<difference_rational_type>;

    template bool operator==(const basic_pixel<size_rational_type>& one, const size_rational_type& another);

    template bool operator==(const basic_pixel<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator==(const basic_pixel<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator==(
        const basic_pixel<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );

    template bool operator<(const basic_pixel<size_rational_type>& one, const size_rational_type& another);

    template bool operator<(const basic_pixel<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator<(const basic_pixel<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator<(
        const basic_pixel<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );

    template bool operator>(const basic_pixel<size_rational_type>& one, const size_rational_type& another);

    template bool operator>(const basic_pixel<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator>(const basic_pixel<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator>(
        const basic_pixel<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );


}}}
