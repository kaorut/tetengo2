/*! \file
    \brief The definition of tetengo2::gui::unit::em.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/rational.hpp>
#include <boost/swap.hpp>

#include <tetengo2/gui/unit/em.h>
#include <tetengo2/stdalt.h>
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

    template <typename Value>
    em<Value> em<Value>::from_pixels_impl(
        const typename value_type::int_type value,
        const unit_details_type&            unit_details
    )
    {
        return em{ unit_details.to_em(value), unit_details };
    }

    template <typename Value>
    typename Value::int_type em<Value>::to_pixels_impl(
        const value_type&        value,
        const unit_details_type& unit_details
    )
    {
        return unit_details.template em_to_pixel<typename value_type::int_type>(value);
    }


    template <typename Value>
    class em_factory<Value>::impl : private boost::noncopyable
    {
    public:
        // types

        using value_type = typename em_factory::value_type;

        using unit_type = typename em_factory::unit_type;

        using unit_details_type = typename em_factory::unit_details_type;


        // constructors and destructor;

        explicit impl(const unit_details_type& unit_details)
        :
        m_unit_details(unit_details)
        {}


        // functions

        unit_type make(value_type value)
        const
        {
            return unit_type{ std::move(value), m_unit_details };
        }


    private:
        // variables

        const unit_details_type& m_unit_details;


    };


    template <typename Value>
    em_factory<Value>::em_factory(const unit_details_type& unit_details)
    :
    m_p_impl(stdalt::make_unique<impl>(unit_details))
    {}

    template <typename Value>
    em_factory<Value>::~em_factory()
    = default;

    template <typename Value>
    typename em_factory<Value>::unit_type em_factory<Value>::make(value_type value)
    const
    {
        return m_p_impl->make(std::move(value));
    }


    namespace
    {
        using size_rational_type = boost::rational<type_list::size_type>;

        using difference_rational_type = boost::rational<type_list::difference_type>;

    }

    template class em<size_rational_type>;

    template class em<difference_rational_type>;

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

    template class em_factory<size_rational_type>;

    template class em_factory<difference_rational_type>;


}}}
