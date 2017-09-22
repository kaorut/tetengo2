/*! \file
    \brief The definition of tetengo2::gui::unit::em.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <boost/rational.hpp>
#include <boost/swap.hpp>

#include <tetengo2/gui/unit/em.h>
#include <tetengo2/type_list.h>


namespace tetengo2 { namespace gui { namespace unit
{
    template <typename Value>
    em<Value>::em(const value_type& value, const unit_details_type& unit_details)
    :
    m_value(value),
    m_p_details(&unit_details)
    {}

    template <typename V1, typename V2>
    bool operator==(const em<V1>& one, const V2& another)
    {
        return one.value() == another;
    }

    template <typename V1, typename V2>
    bool operator<(const em<V1>& one, const V2& another)
    {
        return one.value() < another;
    }

    template <typename V1, typename V2>
    bool operator>(const em<V1>& one, const V2& another)
    {
        return one.value() > another;
    }

    template <typename Value>
    em<Value>& em<Value>::add(const value_type& another)
    {
        em temp{ *this };

        temp.m_value += another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    em<Value>& em<Value>::subtract(const value_type& another)
    {
        em temp{ *this };

        temp.m_value -= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    em<Value>& em<Value>::multiply(const value_type& another)
    {
        em temp{ *this };

        temp.m_value *= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    em<Value>& em<Value>::divide_by(const value_type& another)
    {
        em temp{ *this };

        temp.m_value /= another;

        boost::swap(temp, *this);
        return *this;
    }

    template <typename Value>
    Value em<Value>::divide_by(const em& another)
    const
    {
        return value() / another.value();
    }

    template <typename Value>
    const Value& em<Value>::value()
    const
    {
        return m_value;
    }

    template <typename Value>
    const typename em<Value>::unit_details_type& em<Value>::details()
    const
    {
        return *m_p_details;
    }


    namespace
    {
        using size_rational_type = boost::rational<type_list::size_type>;

        using difference_rational_type = boost::rational<type_list::difference_type>;

    }

    template class em<size_rational_type>;

    template class em<difference_rational_type>;

    //template type_list::size_type em<size_rational_type>::to_ems_impl(const value_type& value);

    //template type_list::difference_type em<difference_rational_type>::to_ems_impl(const value_type& value);

    template bool operator==(const em<size_rational_type>& one, const size_rational_type& another);

    template bool operator==(const em<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator==(const em<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator==(
        const em<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );

    template bool operator<(const em<size_rational_type>& one, const size_rational_type& another);

    template bool operator<(const em<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator<(const em<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator<(
        const em<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );

    template bool operator>(const em<size_rational_type>& one, const size_rational_type& another);

    template bool operator>(const em<size_rational_type>& one, const size_rational_type::int_type& another);

    template bool operator>(const em<difference_rational_type>& one, const difference_rational_type& another);

    template bool operator>(
        const em<difference_rational_type>&    one,
        const difference_rational_type::int_type& another
    );

}}}
