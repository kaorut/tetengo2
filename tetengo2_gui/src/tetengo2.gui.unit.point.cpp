/*! \file
    \brief The definition of tetengo2::gui::unit::basic_point.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/core/swap.hpp>
#include <boost/predef.h>

#include <tetengo2/detail/stub/unit.h> // IWYU pragma: keep
#if BOOST_OS_WINDOWS
#include <tetengo2/detail/windows/unit.h> // IWYU pragma: keep
#endif
#include <tetengo2/gui/unit/point.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::unit {
    template <typename IntValue, typename UnitDetails>
    basic_point<IntValue, UnitDetails> basic_point<IntValue, UnitDetails>::from_pixels(const int_value_type value)
    {
        return basic_point{ unit_details_type::instance().to_point(value) };
    }

    template <typename IntValue, typename UnitDetails>
    basic_point<IntValue, UnitDetails>::basic_point() : m_value{ 0 }
    {}

    template <typename IntValue, typename UnitDetails>
    basic_point<IntValue, UnitDetails>::basic_point(value_type value) : m_value{ std::move(value) }
    {}

    template <typename IV, typename UD>
    bool operator==(const basic_point<IV, UD>& one, const typename basic_point<IV, UD>::value_type& another)
    {
        return one.value() == another;
    }

    template <typename IV, typename UD>
    bool operator<(const basic_point<IV, UD>& one, const typename basic_point<IV, UD>::value_type& another)
    {
        return one.value() < another;
    }

    template <typename IV, typename UD>
    bool operator>(const basic_point<IV, UD>& one, const typename basic_point<IV, UD>::value_type& another)
    {
        return one.value() > another;
    }

    template <typename IntValue, typename UnitDetails>
    basic_point<IntValue, UnitDetails>& basic_point<IntValue, UnitDetails>::add(const value_type& another)
    {
        basic_point temp{ *this };

        temp.m_value += another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue, typename UnitDetails>
    basic_point<IntValue, UnitDetails>& basic_point<IntValue, UnitDetails>::subtract(const value_type& another)
    {
        basic_point temp{ *this };

        temp.m_value -= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue, typename UnitDetails>
    basic_point<IntValue, UnitDetails>& basic_point<IntValue, UnitDetails>::multiply(const value_type& another)
    {
        basic_point temp{ *this };

        temp.m_value *= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue, typename UnitDetails>
    basic_point<IntValue, UnitDetails>& basic_point<IntValue, UnitDetails>::divide_by(const value_type& another)
    {
        basic_point temp{ *this };

        temp.m_value /= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename IntValue, typename UnitDetails>
    typename basic_point<IntValue, UnitDetails>::value_type
    basic_point<IntValue, UnitDetails>::divide_by(const basic_point& another) const
    {
        return value() / another.value();
    }

    template <typename IntValue, typename UnitDetails>
    const typename basic_point<IntValue, UnitDetails>::value_type& basic_point<IntValue, UnitDetails>::value() const
    {
        return m_value;
    }

    template <typename IntValue, typename UnitDetails>
    typename basic_point<IntValue, UnitDetails>::int_value_type basic_point<IntValue, UnitDetails>::to_pixels() const
    {
        return unit_details_type::instance().template point_to_pixel<int_value_type>(m_value);
    }


    namespace {
        using size_type = type_list::size_type;

        using difference_type = type_list::difference_type;
    }

    template class basic_point<size_type, detail::stub::unit>;

    template class basic_point<difference_type, detail::stub::unit>;

    template bool operator==(
        const basic_point<size_type, detail::stub::unit>&                      one,
        const typename basic_point<size_type, detail::stub::unit>::value_type& another);

    template bool operator==(
        const basic_point<difference_type, detail::stub::unit>&                      one,
        const typename basic_point<difference_type, detail::stub::unit>::value_type& another);

    template bool operator<(
        const basic_point<size_type, detail::stub::unit>&                      one,
        const typename basic_point<size_type, detail::stub::unit>::value_type& another);

    template bool operator<(
        const basic_point<difference_type, detail::stub::unit>&                      one,
        const typename basic_point<difference_type, detail::stub::unit>::value_type& another);

    template bool operator>(
        const basic_point<size_type, detail::stub::unit>&                      one,
        const typename basic_point<size_type, detail::stub::unit>::value_type& another);

    template bool operator>(
        const basic_point<difference_type, detail::stub::unit>&                      one,
        const typename basic_point<difference_type, detail::stub::unit>::value_type& another);

#if BOOST_OS_WINDOWS
    template class basic_point<size_type, detail::windows::unit>;

    template class basic_point<difference_type, detail::windows::unit>;

    template bool operator==(
        const basic_point<size_type, detail::windows::unit>&                      one,
        const typename basic_point<size_type, detail::windows::unit>::value_type& another);

    template bool operator==(
        const basic_point<difference_type, detail::windows::unit>&                      one,
        const typename basic_point<difference_type, detail::windows::unit>::value_type& another);

    template bool operator<(
        const basic_point<size_type, detail::windows::unit>&                      one,
        const typename basic_point<size_type, detail::windows::unit>::value_type& another);

    template bool operator<(
        const basic_point<difference_type, detail::windows::unit>&                      one,
        const typename basic_point<difference_type, detail::windows::unit>::value_type& another);

    template bool operator>(
        const basic_point<size_type, detail::windows::unit>&                      one,
        const typename basic_point<size_type, detail::windows::unit>::value_type& another);

    template bool operator>(
        const basic_point<difference_type, detail::windows::unit>&                      one,
        const typename basic_point<difference_type, detail::windows::unit>::value_type& another);
#endif
}
