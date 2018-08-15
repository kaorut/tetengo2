/*! \file
    \brief The definition of tetengo2::detail::windows::scroll.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <cassert>
#include <cstddef>
#include <memory>
#include <system_error>
#include <utility>

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

#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/detail/windows/scroll.h>
#include <tetengo2/detail/windows/widget.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::detail::windows {
    class scroll::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = scroll::size_type;

        using range_type = scroll::range_type;

        using scroll_bar_details_type = scroll::scroll_bar_details_type;

        using scroll_bar_details_ptr_type = scroll::scroll_bar_details_ptr_type;

        using style_type = scroll::style_type;


        // static functions

        static const scroll& instance()
        {
            static const scroll singleton;
            return singleton;
        }


        // functions

        scroll_bar_details_ptr_type
        create_scroll_bar_impl(const gui::widget::widget& widget, const style_type style) const
        {
            auto p_scroll_bar_details = std::make_unique<windows_scroll_bar_details_type>(
                reinterpret_cast<::HWND>(
                    static_cast<const detail::windows::widget::windows_widget_details_type&>(widget.details()).handle),
                to_native_style(style),
                true);

            set_enabled_impl(*p_scroll_bar_details, true);

            return std::move(p_scroll_bar_details);
        }

        size_type position_impl(const scroll_bar_details_type& details) const
        {
            ::SCROLLINFO info{};
            info.cbSize = sizeof(::SCROLLINFO);
            info.fMask = SIF_POS;

            if (::GetScrollInfo(
                    as_windows_details(details).window_handle, as_windows_details(details).native_style, &info) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't obtain scroll information." }));
            }

            return info.nPos;
        }

        void set_position_impl(scroll_bar_details_type& details, const size_type position) const
        {
            ::SCROLLINFO info{};
            info.cbSize = sizeof(::SCROLLINFO);
            info.fMask = SIF_POS | SIF_DISABLENOSCROLL;
            info.nPos = static_cast<int>(position);

            ::SetScrollInfo(
                as_windows_details(details).window_handle, as_windows_details(details).native_style, &info, TRUE);
        }

        range_type range_impl(const scroll_bar_details_type& details) const
        {
            ::SCROLLINFO info{};
            info.cbSize = sizeof(::SCROLLINFO);
            info.fMask = SIF_RANGE;

            if (::GetScrollInfo(
                    as_windows_details(details).window_handle, as_windows_details(details).native_style, &info) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't obtain scroll information." }));
            }

            return range_type{ info.nMin, info.nMax };
        }

        void set_range_impl(scroll_bar_details_type& details, range_type range) const
        {
            ::SCROLLINFO info{};
            info.cbSize = sizeof(::SCROLLINFO);
            info.fMask = SIF_RANGE | SIF_DISABLENOSCROLL;
            info.nMin = static_cast<int>(range.first);
            info.nMax = static_cast<int>(range.second);

            ::SetScrollInfo(
                as_windows_details(details).window_handle, as_windows_details(details).native_style, &info, TRUE);
        }

        size_type page_size_impl(const scroll_bar_details_type& details) const
        {
            ::SCROLLINFO info{};
            info.cbSize = sizeof(::SCROLLINFO);
            info.fMask = SIF_PAGE;

            if (::GetScrollInfo(
                    as_windows_details(details).window_handle, as_windows_details(details).native_style, &info) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                                        "Can't obtain scroll information." }));
            }

            return info.nPage;
        }

        void set_page_size_impl(scroll_bar_details_type& details, const size_type page_size) const
        {
            ::SCROLLINFO info{};
            info.cbSize = sizeof(::SCROLLINFO);
            info.fMask = SIF_PAGE | SIF_DISABLENOSCROLL;
            info.nPage = static_cast<::UINT>(page_size);

            ::SetScrollInfo(
                as_windows_details(details).window_handle, as_windows_details(details).native_style, &info, TRUE);
        }

        bool enabled_impl(const scroll_bar_details_type& details) const
        {
            return as_windows_details(details).enabled;
        }

        void set_enabled_impl(scroll_bar_details_type& details, const bool enabled) const
        {
            ::EnableScrollBar(
                as_windows_details(details).window_handle,
                as_windows_details(details).native_style,
                enabled ? ESB_ENABLE_BOTH : ESB_DISABLE_BOTH);
            as_windows_details(details).enabled = enabled;
        }


    private:
        // types

        struct windows_scroll_bar_details_type : public scroll_bar_details_type
        {
            ::HWND window_handle;
            int    native_style;
            bool   enabled;

            windows_scroll_bar_details_type(const ::HWND window_handle, const int native_style, const bool enabled)
            : window_handle{ window_handle }, native_style{ native_style }, enabled{ enabled }
            {}

            virtual ~windows_scroll_bar_details_type() = default;
        };


        // static functions

        static int to_native_style(const style_type style)
        {
            switch (style)
            {
            case style_type::vertical:
                return SB_VERT;
            case style_type::horizontal:
                return SB_HORZ;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid style." }));
            }
        }

        static const windows_scroll_bar_details_type& as_windows_details(const scroll_bar_details_type& details)
        {
            return static_cast<const windows_scroll_bar_details_type&>(details);
        }

        static windows_scroll_bar_details_type& as_windows_details(scroll_bar_details_type& details)
        {
            return static_cast<windows_scroll_bar_details_type&>(details);
        }
    };


    const scroll& scroll::instance()
    {
        return impl::instance();
    }

    scroll::~scroll() = default;

    scroll::scroll() : m_p_impl{ std::make_unique<impl>() } {}

    scroll::scroll_bar_details_ptr_type
    scroll::create_scroll_bar_impl(const gui::widget::widget& widget, const style_type style) const
    {
        return m_p_impl->create_scroll_bar_impl(widget, style);
    }

    scroll::size_type scroll::position_impl(const scroll_bar_details_type& details) const
    {
        return m_p_impl->position_impl(details);
    }

    void scroll::set_position_impl(scroll_bar_details_type& details, const size_type position) const
    {
        m_p_impl->set_position_impl(details, position);
    }

    scroll::range_type scroll::range_impl(const scroll_bar_details_type& details) const
    {
        return m_p_impl->range_impl(details);
    }

    void scroll::set_range_impl(scroll_bar_details_type& details, range_type range) const
    {
        m_p_impl->set_range_impl(details, std::move(range));
    }

    scroll::size_type scroll::page_size_impl(const scroll_bar_details_type& details) const
    {
        return m_p_impl->page_size_impl(details);
    }

    void scroll::set_page_size_impl(scroll_bar_details_type& details, const size_type page_size) const
    {
        m_p_impl->set_page_size_impl(details, page_size);
    }

    bool scroll::enabled_impl(const scroll_bar_details_type& details) const
    {
        return m_p_impl->enabled_impl(details);
    }

    void scroll::set_enabled_impl(scroll_bar_details_type& details, const bool enabled) const
    {
        m_p_impl->set_enabled_impl(details, enabled);
    }
}
