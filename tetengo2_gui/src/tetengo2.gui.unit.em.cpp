/*! \file
    \brief The definition of tetengo2::gui::unit::basic_em.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/core/swap.hpp>
#include <boost/predef.h>
#include <boost/rational.hpp>

#include <tetengo2/detail/stub/unit.h> // IWYU pragma: keep
#if BOOST_OS_WINDOWS
#   include <tetengo2/detail/windows/unit.h> // IWYU pragma: keep
#endif
#include <tetengo2/gui/unit/em.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui { namespace unit
{
    template <typename Value, typename UnitDetails>
    basic_em<Value, UnitDetails>::basic_em()
    :
    m_value(0)
    {}

    template <typename Value, typename UnitDetails>
    basic_em<Value, UnitDetails>::basic_em(value_type value)
    :
    m_value(std::move(value))
    {}

    template <typename V, typename UD>
    bool operator==(const basic_em<V, UD>& one, const V& another)
    {
        return one.value() == another;
    }

    template <typename V, typename UD>
    bool operator<(const basic_em<V, UD>& one, const V& another)
    {
        return one.value() < another;
    }

    template <typename V, typename UD>
    bool operator>(const basic_em<V, UD>& one, const V& another)
    {
        return one.value() > another;
    }

    template <typename Value, typename UnitDetails>
    basic_em<Value, UnitDetails>& basic_em<Value, UnitDetails>::add(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value += another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value, typename UnitDetails>
    basic_em<Value, UnitDetails>& basic_em<Value, UnitDetails>::subtract(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value -= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value, typename UnitDetails>
    basic_em<Value, UnitDetails>& basic_em<Value, UnitDetails>::multiply(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value *= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value, typename UnitDetails>
    basic_em<Value, UnitDetails>& basic_em<Value, UnitDetails>::divide_by(const value_type& another)
    {
        basic_em temp{ *this };

        temp.m_value /= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value, typename UnitDetails>
    Value basic_em<Value, UnitDetails>::divide_by(const basic_em& another)
    const
    {
        return value() / another.value();
    }

    template <typename Value, typename UnitDetails>
    const Value& basic_em<Value, UnitDetails>::value()
    const
    {
        return m_value;
    }

    template <typename Value, typename UnitDetails>
    basic_em<Value, UnitDetails> basic_em<Value, UnitDetails>::from_pixels_impl(
        const typename value_type::int_type value
    )
    {
        return basic_em{ unit_details_type::instance().to_em(value) };
    }

    template <typename Value, typename UnitDetails>
    typename Value::int_type basic_em<Value, UnitDetails>::to_pixels_impl(const value_type& value)
    {
        return unit_details_type::instance().template em_to_pixel<typename value_type::int_type>(value);
    }


    namespace
    {
        using size_rational_type = boost::rational<type_list::size_type>;

        using difference_rational_type = boost::rational<type_list::difference_type>;

    }

    template class basic_em<size_rational_type, detail::stub::unit>;

    template class basic_em<difference_rational_type, detail::stub::unit>;

    template bool operator==(
        const basic_em<size_rational_type, detail::stub::unit>& one,
        const size_rational_type&                               another
    );

    template bool operator==(
        const basic_em<difference_rational_type, detail::stub::unit>& one,
        const difference_rational_type&                               another
    );

    template bool operator<(
        const basic_em<size_rational_type, detail::stub::unit>& one,
        const size_rational_type&                               another
    );

    template bool operator<(
        const basic_em<difference_rational_type, detail::stub::unit>& one,
        const difference_rational_type&                               another
    );

    template bool operator>(
        const basic_em<size_rational_type, detail::stub::unit>& one,
        const size_rational_type&                               another
    );

    template bool operator>(
        const basic_em<difference_rational_type, detail::stub::unit>& one, 
        const difference_rational_type&                               another
    );

#if BOOST_OS_WINDOWS
    template class basic_em<size_rational_type, detail::windows::unit>;

    template class basic_em<difference_rational_type, detail::windows::unit>;

    template bool operator==(
        const basic_em<size_rational_type, detail::windows::unit>& one,
        const size_rational_type&                                  another
    );

    template bool operator==(
        const basic_em<difference_rational_type, detail::windows::unit>& one,
        const difference_rational_type&                                  another
    );

    template bool operator<(
        const basic_em<size_rational_type, detail::windows::unit>& one,
        const size_rational_type&                                  another
    );

    template bool operator<(
        const basic_em<difference_rational_type, detail::windows::unit>& one,
        const difference_rational_type&                                  another
    );

    template bool operator>(
        const basic_em<size_rational_type, detail::windows::unit>& one,
        const size_rational_type&                                  another
    );

    template bool operator>(
        const basic_em<difference_rational_type, detail::windows::unit>& one, 
        const difference_rational_type&                                  another
    );
#endif


}}}
