/*! \file
    \brief The definition of tetengo2::detail::windows::scroll.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_SCROLL_H)
#define TETENGO2_DETAIL_WINDOWS_SCROLL_H

#include <memory>
#include <system_error>
#include <tuple>
#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>

#include "tetengo2.detail.windows.error_category.h"
#include "tetengo2.unique.h"


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
        typedef std::size_t size_type;

        //! The range type.
        typedef std::pair<size_type, size_type> range_type;

        //! The scroll bar details type.
        typedef ::HWND scroll_bar_details_type;

        //! The scroll bar details pointer type.
        typedef std::unique_ptr<scroll_bar_details_type> scroll_bar_details_ptr_type;


        // static functions

        /*!
            \brief Creates a scroll bar.

            \tparam WidgetDetails A detail implementation type of a widget.

            \param widget_details A detail implementation of a widget.

            \return A unique pointer to a scroll bar. 

            \throw std::system_error When a system cursor cannot be created.
        */
        template <typename WidgetDetails>
        static scroll_bar_details_ptr_type create_scroll_bar(const WidgetDetails& widget_details)
        {
            return tetengo2::make_unique<scroll_bar_details_type>(std::get<0>(widget_details).get());
        }

        /*!
            \brief Returns the position.

            \param details A detail implementation of a scroll bar.
            
            \return The position.

            \throw std::system_error When the scroll information cannot be obtained.
        */
        static size_type position(const scroll_bar_details_type& details)
        {
            ::SCROLLINFO info = {};
            info.cbSize = sizeof(::SCROLLINFO);
            info.fMask = SIF_POS;
            
            if (::GetScrollInfo(details, SB_VERT, &info) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(
                        std::error_code(::GetLastError(), win32_category()), "Can't obtain scroll information."
                    )
                );
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

        }

        /*!
            \brief Returns the range.

            \param details A detail implementation of a scroll bar.
            
            \return The range.

            \throw std::system_error When the scroll information cannot be obtained.
        */
        static range_type range(const scroll_bar_details_type& details)
        {
            return std::make_pair(0, 100);
        }

        /*!
            \brief Sets a range.

            \tparam R A range type.

            \param details A detail implementation of a scroll bar.
            \param range   A range.

            \throw std::system_error When the scroll information cannot be set.
        */
        template <typename R>
        static void set_range(scroll_bar_details_type& details, R&& range)
        {

        }

        /*!
            \brief Returns the page size.

            \param details A detail implementation of a scroll bar.
            
            \return The page size.

            \throw std::system_error When the scroll information cannot be obtained.
        */
        static size_type page_size(const scroll_bar_details_type& details)
        {
            return 0;
        }

        /*!
            \brief Sets a page size.

            \param details   A detail implementation of a scroll bar.
            \param page_size A page size.

            \throw std::system_error When the scroll information cannot be set.
        */
        static void set_page_size(scroll_bar_details_type& details, const size_type page_size)
        {

        }


    private:
        // static functions


        // forbidden operations

        scroll();


    };


}}}


#endif
