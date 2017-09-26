/*! \file
    \brief The definition of tetengo2::gui::unit::pixel.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/rational.hpp>
#include <boost/swap.hpp>

#include <tetengo2/gui/unit/pixel.h>
#include <tetengo2/stdalt.h>
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


    template <typename Value>
    class pixel_factory<Value>::impl : private boost::noncopyable
    {
    public:
        // types

        using value_type = typename pixel_factory::value_type;

        using unit_type = typename pixel_factory::unit_type;


        // constructors and destructor;

        impl()
        {}


        // functions

        unit_type make(value_type value)
        const
        {
            return unit_type{ std::move(value) };
        }


    };


    template <typename Value>
    pixel_factory<Value>::pixel_factory()
    :
    m_p_impl(stdalt::make_unique<impl>())
    {}

    template <typename Value>
    pixel_factory<Value>::~pixel_factory()
    = default;

    template <typename Value>
    typename pixel_factory<Value>::unit_type pixel_factory<Value>::make(value_type value)
    const
    {
        return m_p_impl->make(std::move(value));
    }


    namespace
    {
        using size_rational_type = boost::rational<type_list::size_type>;

        using difference_rational_type = boost::rational<type_list::difference_type>;

    }

    template class pixel<size_rational_type>;

    template class pixel<difference_rational_type>;

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


    template class pixel_factory<size_rational_type>;

    template class pixel_factory<difference_rational_type>;


}}}
