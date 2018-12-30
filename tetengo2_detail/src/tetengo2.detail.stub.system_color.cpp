/*! \file
    \brief The definition of tetengo2::detail::stub::system_color.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/stub/system_color.h>


namespace tetengo2::detail::stub {
    class system_color::impl : boost::noncopyable
    {
    public:
        // types

        using color_type = system_color::color_type;

        using index_type = system_color::index_type;


        // static functions

        static const system_color& instance()
        {
            static const system_color singleton{};
            return singleton;
        }


        // functions

        color_type get_system_color_impl(const index_type index) const
        {
            switch (index)
            {
            case index_type::title_bar_text:
                return { 255, 255, 255 };
            case index_type::title_bar_background:
                return { 0, 0, 128 };
            case index_type::dialog_background:
                return { 192, 192, 192 };
            case index_type::control_background:
                return { 255, 255, 255 };
            case index_type::control_text:
                return { 0, 0, 0 };
            case index_type::selected_background:
                return { 0, 0, 128 };
            case index_type::selected_text:
                return { 255, 255, 255 };
            case index_type::hyperlink_text:
                return { 0, 0, 255 };
            default:
                assert(false);
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid system color index." }));
            }
        }
    };


    const system_color& system_color::instance()
    {
        return impl::instance();
    }

    system_color::~system_color() = default;

    system_color::system_color() : m_p_impl{ std::make_unique<impl>() } {}

    system_color::color_type system_color::get_system_color_impl(const index_type index) const
    {
        return m_p_impl->get_system_color_impl(index);
    }
}
