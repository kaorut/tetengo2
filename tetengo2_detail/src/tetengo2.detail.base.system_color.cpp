/*! \file
    \brief The definition of tetengo2::detail::base::system_color.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/system_color.h>


namespace tetengo2::detail::base {
    class system_color::impl : private boost::noncopyable
    {
    public:
        // types

        using color_type = system_color::color_type;

        using index_type = system_color::index_type;


        // functions

        color_type get_system_color(const index_type index, const system_color& base) const
        {
            return base.get_system_color_impl(index);
        }
    };


    system_color::~system_color() = default;

    system_color::color_type system_color::get_system_color(const index_type index) const
    {
        return m_p_impl->get_system_color(index, *this);
    }

    system_color::system_color() : m_p_impl{ std::make_unique<impl>() } {}
}