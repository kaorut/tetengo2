/*! \file
    \brief The definition of tetengo2::gui::drawing::color.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>
#include <stdexcept>

#include <boost/throw_exception.hpp>

#include <tetengo2/gui/drawing/color.h>


namespace tetengo2::gui::drawing {
    template <typename Value>
    class basic_color<Value>::impl
    {
    public:
        // types

        using value_type = basic_color::value_type;


        // constructors and destructor

        impl(const value_type red, const value_type green, const value_type blue, const value_type alpha)
        : m_red{ red }, m_green{ green }, m_blue{ blue }, m_alpha{ alpha }
        {}


        // functions

        basic_color& operator_assign(const basic_color& another, basic_color& self)
        {
            m_red = another.m_p_impl->m_red;
            m_green = another.m_p_impl->m_green;
            m_blue = another.m_p_impl->m_blue;
            m_alpha = another.m_p_impl->m_alpha;

            return self;
        }

        basic_color& operator_assign(basic_color&& another, basic_color& self)
        {
            m_red = another.m_p_impl->m_red;
            m_green = another.m_p_impl->m_green;
            m_blue = another.m_p_impl->m_blue;
            m_alpha = another.m_p_impl->m_alpha;

            return self;
        }

        value_type red() const
        {
            return m_red;
        }

        value_type green() const
        {
            return m_green;
        }

        value_type blue() const
        {
            return m_blue;
        }

        value_type alpha() const
        {
            return m_alpha;
        }

        basic_color mix(const basic_color& another, const double weight) const
        {
            if (weight < 0 || 1.0 < weight)
                BOOST_THROW_EXCEPTION(std::invalid_argument{ "Invalid weight value." });

            const auto mixed_red = static_cast<unsigned char>(
                static_cast<double>(m_red) * (1.0 - weight) + static_cast<double>(another.m_p_impl->m_red) * weight);
            const auto mixed_green = static_cast<unsigned char>(
                static_cast<double>(m_green) * (1.0 - weight) +
                static_cast<double>(another.m_p_impl->m_green) * weight);
            const auto mixed_blue = static_cast<unsigned char>(
                static_cast<double>(m_blue) * (1.0 - weight) + static_cast<double>(another.m_p_impl->m_blue) * weight);
            const auto mixed_alpha = static_cast<unsigned char>(
                static_cast<double>(m_alpha) * (1.0 - weight) +
                static_cast<double>(another.m_p_impl->m_alpha) * weight);
            return basic_color{ mixed_red, mixed_green, mixed_blue, mixed_alpha };
        }


    private:
        // variables

        value_type m_red;

        value_type m_green;

        value_type m_blue;

        value_type m_alpha;
    };


    template <typename Value>
    basic_color<Value>::basic_color(
        const value_type red,
        const value_type green,
        const value_type blue,
        const value_type alpha /*= std::numeric_limits<value_type>::max()*/)
    : m_p_impl{ std::make_unique<impl>(red, green, blue, alpha) }
    {}

    template <typename Value>
    basic_color<Value>::basic_color(const basic_color& another) : m_p_impl{ std::make_unique<impl>(*another.m_p_impl) }
    {}

    template <typename Value>
    basic_color<Value>::basic_color(basic_color&& another) : m_p_impl{ std::move(another.m_p_impl) }
    {}

    template <typename Value>
    basic_color<Value>::~basic_color() = default;

    template <typename Value>
    bool operator==(const basic_color<Value>& one, const basic_color<Value>& another)
    {
        return one.red() == another.red() && one.green() == another.green() && one.blue() == another.blue() &&
               one.alpha() == another.alpha();
    }

    template <typename Value>
    basic_color<Value>& basic_color<Value>::operator=(const basic_color& another)
    {
        return m_p_impl->operator_assign(another, *this);
    }

    template <typename Value>
    basic_color<Value>& basic_color<Value>::operator=(basic_color&& another)
    {
        return m_p_impl->operator_assign(std::move(another), *this);
    }

    template <typename Value>
    typename basic_color<Value>::value_type basic_color<Value>::red() const
    {
        return m_p_impl->red();
    }

    template <typename Value>
    typename basic_color<Value>::value_type basic_color<Value>::green() const
    {
        return m_p_impl->green();
    }

    template <typename Value>
    typename basic_color<Value>::value_type basic_color<Value>::blue() const
    {
        return m_p_impl->blue();
    }

    template <typename Value>
    typename basic_color<Value>::value_type basic_color<Value>::alpha() const
    {
        return m_p_impl->alpha();
    }

    template <typename Value>
    basic_color<Value> basic_color<Value>::mix(const basic_color& another, const double weight) const
    {
        return m_p_impl->mix(another, weight);
    }


    template class basic_color<unsigned char>;

    template bool operator==(const basic_color<unsigned char>& one, const basic_color<unsigned char>& another);
}
