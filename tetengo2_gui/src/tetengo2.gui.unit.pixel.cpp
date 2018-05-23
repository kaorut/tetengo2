/*! \file
    \brief The definition of tetengo2::gui::unit::basic_pixel.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/core/swap.hpp>
#include <boost/rational.hpp>

#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::unit {
    template <typename IntValue>
    basic_pixel<IntValue> basic_pixel<IntValue>::from_pixels(const int_value_type int_value)
    {
        return basic_pixel{ int_value };
    }

    template <typename IntValue>
    basic_pixel<IntValue>::basic_pixel() : m_value{ 0 }
    {}

    template <typename IntValue>
    basic_pixel<IntValue>::basic_pixel(value_type value) : m_value{ std::move(value) }
    {}

    template <typename IV>
    bool operator==(const basic_pixel<IV>& one, const typename basic_pixel<IV>::value_type& another)
    {
        return one.value() == another;
    }

    template <typename IV>
    bool operator<(const basic_pixel<IV>& one, const typename basic_pixel<IV>::value_type& another)
    {
        return one.value() < another;
    }

    template <typename IV>
    bool operator>(const basic_pixel<IV>& one, const typename basic_pixel<IV>::value_type& another)
    {
        return one.value() > another;
    }

    template <typename IntValue>
    basic_pixel<IntValue>& basic_pixel<IntValue>::add(const value_type& another)
    {
        basic_pixel temp{ *this };

        temp.m_value += another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue>
    basic_pixel<IntValue>& basic_pixel<IntValue>::subtract(const value_type& another)
    {
        basic_pixel temp{ *this };

        temp.m_value -= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue>
    basic_pixel<IntValue>& basic_pixel<IntValue>::multiply(const value_type& another)
    {
        basic_pixel temp{ *this };

        temp.m_value *= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue>
    basic_pixel<IntValue>& basic_pixel<IntValue>::divide_by(const value_type& another)
    {
        basic_pixel temp{ *this };

        temp.m_value /= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue>
    typename basic_pixel<IntValue>::value_type basic_pixel<IntValue>::divide_by(const basic_pixel& another) const
    {
        return value() / another.value();
    }

    template <typename IntValue>
    const typename basic_pixel<IntValue>::value_type& basic_pixel<IntValue>::value() const
    {
        return m_value;
    }

    template <typename IntValue>
    typename basic_pixel<IntValue>::int_value_type basic_pixel<IntValue>::to_pixels() const
    {
        return boost::rational_cast<int_value_type>(m_value);
    }


    namespace {
        using size_type = type_list::size_type;

        using difference_type = type_list::difference_type;
    }

    template class basic_pixel<size_type>;

    template class basic_pixel<difference_type>;

    template bool
    operator==(const basic_pixel<size_type>& one, const typename basic_pixel<size_type>::value_type& another);

    template bool operator==(
        const basic_pixel<difference_type>&                      one,
        const typename basic_pixel<difference_type>::value_type& another);

    template bool
    operator<(const basic_pixel<size_type>& one, const typename basic_pixel<size_type>::value_type& another);

    template bool operator<(
        const basic_pixel<difference_type>&                      one,
        const typename basic_pixel<difference_type>::value_type& another);

    template bool
    operator>(const basic_pixel<size_type>& one, const typename basic_pixel<size_type>::value_type& another);

    template bool operator>(
        const basic_pixel<difference_type>&                      one,
        const typename basic_pixel<difference_type>::value_type& another);
}
