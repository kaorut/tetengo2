/*! \file
    \brief The definition of tetengo2::detail::windows::system_color.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h> // IWYU pragma: keep
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/system_color.h>


namespace tetengo2::detail::windows {
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
                return get_system_color_impl(COLOR_CAPTIONTEXT);
            case index_type::title_bar_background:
                return get_system_color_impl(COLOR_ACTIVECAPTION);
            case index_type::dialog_background:
                return get_system_color_impl(COLOR_3DFACE);
            case index_type::control_background:
                return get_system_color_impl(COLOR_WINDOW);
            case index_type::control_text:
                return get_system_color_impl(COLOR_WINDOWTEXT);
            case index_type::selected_background:
                return get_system_color_impl(COLOR_HIGHLIGHT);
            case index_type::selected_text:
                return get_system_color_impl(COLOR_HIGHLIGHTTEXT);
            case index_type::hyperlink_text:
                return get_system_color_impl(COLOR_HOTLIGHT);
            default:
                assert(false);
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid system color index." }));
            }
        }


    private:
        // static functions

        static color_type get_system_color_impl(const int index)
        {
            const auto color_ref = ::GetSysColor(index);
            return { GetRValue(color_ref), GetGValue(color_ref), GetBValue(color_ref) };
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
