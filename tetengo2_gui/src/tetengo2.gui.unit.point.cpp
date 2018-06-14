/*! \file
    \brief The definition of tetengo2::gui::unit::basic_point.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/core/swap.hpp> // IWYU pragma: keep

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/unit.h> // IWYU pragma: keep
#include <tetengo2/gui/unit/point.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::unit {
    template <typename IntValue>
    basic_point<IntValue> basic_point<IntValue>::from_pixels(const int_value_type value)
    {
        return basic_point{ detail::gui_detail_impl_set().unit_().to_point(value) };
    }

    template <typename IntValue>
    basic_point<IntValue>::basic_point() : m_value{ 0 }
    {}

    template <typename IntValue>
    basic_point<IntValue>::basic_point(value_type value) : m_value{ std::move(value) }
    {}

    template <typename IV>
    bool operator==(const basic_point<IV>& one, const typename basic_point<IV>::value_type& another)
    {
        return one.value() == another;
    }

    template <typename IV>
    bool operator<(const basic_point<IV>& one, const typename basic_point<IV>::value_type& another)
    {
        return one.value() < another;
    }

    template <typename IV>
    bool operator>(const basic_point<IV>& one, const typename basic_point<IV>::value_type& another)
    {
        return one.value() > another;
    }

    template <typename IntValue>
    basic_point<IntValue>& basic_point<IntValue>::add(const value_type& another)
    {
        basic_point temp{ *this };

        temp.m_value += another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue>
    basic_point<IntValue>& basic_point<IntValue>::subtract(const value_type& another)
    {
        basic_point temp{ *this };

        temp.m_value -= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue>
    basic_point<IntValue>& basic_point<IntValue>::multiply(const value_type& another)
    {
        basic_point temp{ *this };

        temp.m_value *= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue>
    basic_point<IntValue>& basic_point<IntValue>::divide_by(const value_type& another)
    {
        basic_point temp{ *this };

        temp.m_value /= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue>
    typename basic_point<IntValue>::value_type basic_point<IntValue>::divide_by(const basic_point& another) const
    {
        return value() / another.value();
    }

    template <typename IntValue>
    const typename basic_point<IntValue>::value_type& basic_point<IntValue>::value() const
    {
        return m_value;
    }

    template <typename IntValue>
    typename basic_point<IntValue>::int_value_type basic_point<IntValue>::to_pixels() const
    {
        return detail::gui_detail_impl_set().unit_().template point_to_pixel<int_value_type>(m_value);
    }


    namespace {
        using size_type = type_list::size_type;

        using difference_type = type_list::difference_type;
    }

    template class basic_point<size_type>;

    template class basic_point<difference_type>;

    template bool
    operator==(const basic_point<size_type>& one, const typename basic_point<size_type>::value_type& another);

    template bool operator==(
        const basic_point<difference_type>&                      one,
        const typename basic_point<difference_type>::value_type& another);

    template bool
    operator<(const basic_point<size_type>& one, const typename basic_point<size_type>::value_type& another);

    template bool operator<(
        const basic_point<difference_type>&                      one,
        const typename basic_point<difference_type>::value_type& another);

    template bool
    operator>(const basic_point<size_type>& one, const typename basic_point<size_type>::value_type& another);

    template bool operator>(
        const basic_point<difference_type>&                      one,
        const typename basic_point<difference_type>::value_type& another);
}
