/*! \file
    \brief The definition of tetengo2::gui::unit::basic_em.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/core/swap.hpp>
#include <boost/predef.h>

#include <tetengo2/detail/stub/unit.h> // IWYU pragma: keep
#if BOOST_OS_WINDOWS
#include <tetengo2/detail/windows/unit.h> // IWYU pragma: keep
#endif
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::unit {
    template <typename IntValue, typename UnitDetails>
    basic_em<IntValue, UnitDetails> basic_em<IntValue, UnitDetails>::from_pixels(const int_value_type int_value)
    {
        return basic_em{ unit_details_type::instance().to_em(int_value) };
    }

    template <typename IntValue, typename UnitDetails>
    basic_em<IntValue, UnitDetails>::basic_em() : m_value{ 0 }
    {}

    template <typename IntValue, typename UnitDetails>
    basic_em<IntValue, UnitDetails>::basic_em(value_type value) : m_value{ std::move(value) }
    {}

    template <typename IV, typename UD>
    bool operator==(const basic_em<IV, UD>& one, const typename basic_em<IV, UD>::value_type& another)
    {
        return one.value() == another;
    }

    template <typename IV, typename UD>
    bool operator<(const basic_em<IV, UD>& one, const typename basic_em<IV, UD>::value_type& another)
    {
        return one.value() < another;
    }

    template <typename IV, typename UD>
    bool operator>(const basic_em<IV, UD>& one, const typename basic_em<IV, UD>::value_type& another)
    {
        return one.value() > another;
    }

    template <typename IntValue, typename UnitDetails>
    basic_em<IntValue, UnitDetails>& basic_em<IntValue, UnitDetails>::add(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value += another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue, typename UnitDetails>
    basic_em<IntValue, UnitDetails>& basic_em<IntValue, UnitDetails>::subtract(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value -= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue, typename UnitDetails>
    basic_em<IntValue, UnitDetails>& basic_em<IntValue, UnitDetails>::multiply(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value *= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue, typename UnitDetails>
    basic_em<IntValue, UnitDetails>& basic_em<IntValue, UnitDetails>::divide_by(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value /= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue, typename UnitDetails>
    typename basic_em<IntValue, UnitDetails>::value_type
    basic_em<IntValue, UnitDetails>::divide_by(const basic_em& another) const
    {
        return value() / another.value();
    }

    template <typename IntValue, typename UnitDetails>
    const typename basic_em<IntValue, UnitDetails>::value_type& basic_em<IntValue, UnitDetails>::value() const
    {
        return m_value;
    }

    template <typename IntValue, typename UnitDetails>
    typename basic_em<IntValue, UnitDetails>::int_value_type basic_em<IntValue, UnitDetails>::to_pixels() const
    {
        return unit_details_type::instance().template em_to_pixel<int_value_type>(m_value);
    }


    namespace {
        using size_type = type_list::size_type;

        using difference_type = type_list::difference_type;
    }

    template class basic_em<size_type, detail::stub::unit>;

    template class basic_em<difference_type, detail::stub::unit>;

    template bool operator==(
        const basic_em<size_type, detail::stub::unit>&                      one,
        const typename basic_em<size_type, detail::stub::unit>::value_type& another);

    template bool operator==(
        const basic_em<difference_type, detail::stub::unit>&                      one,
        const typename basic_em<difference_type, detail::stub::unit>::value_type& another);

    template bool operator<(
        const basic_em<size_type, detail::stub::unit>&                      one,
        const typename basic_em<size_type, detail::stub::unit>::value_type& another);

    template bool operator<(
        const basic_em<difference_type, detail::stub::unit>&                      one,
        const typename basic_em<difference_type, detail::stub::unit>::value_type& another);

    template bool operator>(
        const basic_em<size_type, detail::stub::unit>&                      one,
        const typename basic_em<size_type, detail::stub::unit>::value_type& another);

    template bool operator>(
        const basic_em<difference_type, detail::stub::unit>&                      one,
        const typename basic_em<difference_type, detail::stub::unit>::value_type& another);

#if BOOST_OS_WINDOWS
    template class basic_em<size_type, detail::windows::unit>;

    template class basic_em<difference_type, detail::windows::unit>;

    template bool operator==(
        const basic_em<size_type, detail::windows::unit>&                      one,
        const typename basic_em<size_type, detail::windows::unit>::value_type& another);

    template bool operator==(
        const basic_em<difference_type, detail::windows::unit>&                      one,
        const typename basic_em<difference_type, detail::windows::unit>::value_type& another);

    template bool operator<(
        const basic_em<size_type, detail::windows::unit>&                      one,
        const typename basic_em<size_type, detail::windows::unit>::value_type& another);

    template bool operator<(
        const basic_em<difference_type, detail::windows::unit>&                      one,
        const typename basic_em<difference_type, detail::windows::unit>::value_type& another);

    template bool operator>(
        const basic_em<size_type, detail::windows::unit>&                      one,
        const typename basic_em<size_type, detail::windows::unit>::value_type& another);

    template bool operator>(
        const basic_em<difference_type, detail::windows::unit>&                      one,
        const typename basic_em<difference_type, detail::windows::unit>::value_type& another);
#endif
}
