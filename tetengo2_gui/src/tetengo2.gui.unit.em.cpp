/*! \file
    \brief The definition of tetengo2::gui::unit::basic_em.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <boost/core/swap.hpp> // IWYU pragma: keep

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/unit.h> // IWYU pragma: keep
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::unit {
    template <typename IntValue>
    basic_em<IntValue> basic_em<IntValue>::from_pixels(const int_value_type int_value)
    {
        return basic_em{ detail::gui_detail_impl_set().unit_().to_em(int_value) };
    }

    template <typename IntValue>
    basic_em<IntValue>::basic_em() : m_value{ 0 }
    {}

    template <typename IntValue>
    basic_em<IntValue>::basic_em(value_type value) : m_value{ std::move(value) }
    {}

    template <typename IV>
    bool operator==(const basic_em<IV>& one, const typename basic_em<IV>::value_type& another)
    {
        return one.value() == another;
    }

    template <typename IV>
    bool operator<(const basic_em<IV>& one, const typename basic_em<IV>::value_type& another)
    {
        return one.value() < another;
    }

    template <typename IV>
    bool operator>(const basic_em<IV>& one, const typename basic_em<IV>::value_type& another)
    {
        return one.value() > another;
    }

    template <typename IntValue>
    basic_em<IntValue>& basic_em<IntValue>::add(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value += another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue>
    basic_em<IntValue>& basic_em<IntValue>::subtract(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value -= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue>
    basic_em<IntValue>& basic_em<IntValue>::multiply(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value *= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue>
    basic_em<IntValue>& basic_em<IntValue>::divide_by(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value /= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue>
    typename basic_em<IntValue>::value_type basic_em<IntValue>::divide_by(const basic_em& another) const
    {
        return value() / another.value();
    }

    template <typename IntValue>
    const typename basic_em<IntValue>::value_type& basic_em<IntValue>::value() const
    {
        return m_value;
    }

    template <typename IntValue>
    typename basic_em<IntValue>::int_value_type basic_em<IntValue>::to_pixels() const
    {
        return detail::gui_detail_impl_set().unit_().template em_to_pixel<int_value_type>(m_value);
    }


    namespace {
        using size_type = type_list::size_type;

        using difference_type = type_list::difference_type;
    }

    template class basic_em<size_type>;

    template class basic_em<difference_type>;

    template bool operator==(const basic_em<size_type>& one, const typename basic_em<size_type>::value_type& another);

    template bool
    operator==(const basic_em<difference_type>& one, const typename basic_em<difference_type>::value_type& another);

    template bool operator<(const basic_em<size_type>& one, const typename basic_em<size_type>::value_type& another);

    template bool
    operator<(const basic_em<difference_type>& one, const typename basic_em<difference_type>::value_type& another);

    template bool operator>(const basic_em<size_type>& one, const typename basic_em<size_type>::value_type& another);

    template bool
    operator>(const basic_em<difference_type>& one, const typename basic_em<difference_type>::value_type& another);
}
