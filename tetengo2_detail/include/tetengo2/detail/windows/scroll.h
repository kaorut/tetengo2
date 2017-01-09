/*! \file
    \brief The definition of tetengo2::detail::windows::scroll.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_SCROLL_H)
#define TETENGO2_DETAIL_WINDOWS_SCROLL_H

#include <cassert>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <system_error>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

//#pragma warning (push)
//#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
//#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/stdalt.h>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of a scroll.
    */
    class scroll : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = std::size_t;

        //! The range type.
        using range_type = std::pair<size_type, size_type>;

        //! The scroll bar details type.
        struct scroll_bar_details_type
        {
#if !defined(DOCUMENTATION)
            ::HWND window_handle;
            int native_style;
            bool enabled;

            scroll_bar_details_type(const ::HWND window_handle, const int native_style, const bool enabled)
            :
            window_handle(window_handle),
            native_style(native_style),
            enabled(enabled)
            {}
#endif

        };

        //! The scroll bar details pointer type.
        using scroll_bar_details_ptr_type = std::unique_ptr<scroll_bar_details_type>;

        //! The style type.
        enum class style_type
        {
            vertical,   //!< The vertical style.
            horizontal, //!< The horizontal style.
        };


        // static functions

        /*!
            \brief Creates a scroll bar.

            \tparam WidgetDetails A detail implementation type of a widget.

            \param widget_details A detail implementation of a widget.
            \param style          A style.

            \return A unique pointer to a scroll bar. 

            \throw std::system_error When a system cursor cannot be created.
        */
        template <typename WidgetDetails>
        static scroll_bar_details_ptr_type create_scroll_bar(
            const WidgetDetails& widget_details,
            const style_type     style
        )
        {
            auto p_scroll_bar_details =
                stdalt::make_unique<scroll_bar_details_type>(
                    widget_details.handle.get(), to_native_style(style), true
                );

            set_enabled(*p_scroll_bar_details, true);

            return std::move(p_scroll_bar_details);
        }

        /*!
            \brief Returns the position.

            \param details A detail implementation of a scroll bar.
            
            \return The position.

            \throw std::system_error When the scroll information cannot be obtained.
        */
        static size_type position(const scroll_bar_details_type& details)
        {
            ::SCROLLINFO info{};
            info.cbSize = sizeof(::SCROLLINFO);
            info.fMask = SIF_POS;
            
            if (::GetScrollInfo(details.window_handle, details.native_style, &info) == 0)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{
                        std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                        "Can't obtain scroll information."
                    }
                ));
            }

            return info.nPos;
        }

        /*!
            \brief Sets a position.

            \param details  A detail implementation of a scroll bar.
            \param position A position.

            \throw std::system_error When the scroll information cannot be set.
        */
        static void set_position(scroll_bar_details_type& details, const size_type position)
        {
            ::SCROLLINFO info{};
            info.cbSize = sizeof(::SCROLLINFO);
            info.fMask = SIF_POS | SIF_DISABLENOSCROLL;
            info.nPos = static_cast<int>(position);

            ::SetScrollInfo(details.window_handle, details.native_style, &info, TRUE);
        }

        /*!
            \brief Returns the range.

            \param details A detail implementation of a scroll bar.
            
            \return The range.

            \throw std::system_error When the scroll information cannot be obtained.
        */
        static range_type range(const scroll_bar_details_type& details)
        {
            ::SCROLLINFO info{};
            info.cbSize = sizeof(::SCROLLINFO);
            info.fMask = SIF_RANGE;
            
            if (::GetScrollInfo(details.window_handle, details.native_style, &info) == 0)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{
                        std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                        "Can't obtain scroll information."
                    }
                ));
            }

            return { info.nMin, info.nMax };
        }

        /*!
            \brief Sets a range.

            \param details A detail implementation of a scroll bar.
            \param range   A range.

            \throw std::system_error When the scroll information cannot be set.
        */
        static void set_range(scroll_bar_details_type& details, const range_type& range)
        {
            ::SCROLLINFO info{};
            info.cbSize = sizeof(::SCROLLINFO);
            info.fMask = SIF_RANGE | SIF_DISABLENOSCROLL;
            info.nMin = static_cast<int>(range.first);
            info.nMax = static_cast<int>(range.second);

            ::SetScrollInfo(details.window_handle, details.native_style, &info, TRUE);
        }

        /*!
            \brief Returns the page size.

            \param details A detail implementation of a scroll bar.
            
            \return The page size.

            \throw std::system_error When the scroll information cannot be obtained.
        */
        static size_type page_size(const scroll_bar_details_type& details)
        {
            ::SCROLLINFO info{};
            info.cbSize = sizeof(::SCROLLINFO);
            info.fMask = SIF_PAGE;
            
            if (::GetScrollInfo(details.window_handle, details.native_style, &info) == 0)
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{
                        std::error_code{ static_cast<int>(::GetLastError()), win32_category() },
                        "Can't obtain scroll information."
                    }
                ));
            }

            return info.nPage;
        }

        /*!
            \brief Sets a page size.

            \param details   A detail implementation of a scroll bar.
            \param page_size A page size.

            \throw std::system_error When the scroll information cannot be set.
        */
        static void set_page_size(scroll_bar_details_type& details, const size_type page_size)
        {
            ::SCROLLINFO info{};
            info.cbSize = sizeof(::SCROLLINFO);
            info.fMask = SIF_PAGE | SIF_DISABLENOSCROLL;
            info.nPage = static_cast< ::UINT>(page_size);

            ::SetScrollInfo(details.window_handle, details.native_style, &info, TRUE);
        }

        /*!
            \brief Returns the enabled status.

            \param details A detail implementation of a scroll bar.

            \retval true  When the scroll bar is enabled.
            \retval false Otherwise.
        */
        static bool enabled(const scroll_bar_details_type& details)
        {
            return details.enabled;
        }

        /*!
            \brief Sets an enabled status.

            \param details A detail implementation of a scroll bar.
            \param enabled An enable status.
        */
        static void set_enabled(scroll_bar_details_type& details, const bool enabled)
        {
            ::EnableScrollBar(
                details.window_handle, details.native_style, enabled ? ESB_ENABLE_BOTH : ESB_DISABLE_BOTH
            );
            details.enabled = enabled;
        }


    private:
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


        // forbidden operations

        scroll()
        = delete;


    };


}}}


#endif
