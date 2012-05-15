/*! \file
    \brief The definition of tetengo2::detail::stub::scroll.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_SCROLL_H)
#define TETENGO2_DETAIL_STUB_SCROLL_H

#include <memory>
#include <tuple>
#include <utility>

#include <boost/noncopyable.hpp>

#include "tetengo2.unique.h"


namespace tetengo2 { namespace detail { namespace stub
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
        typedef std::tuple<size_type, std::pair<size_type, size_type>, size_type> scroll_bar_details_type;

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
        static scroll_bar_details_ptr_type create_scroll_bar(WidgetDetails& widget_details)
        {
            return tetengo2::make_unique<scroll_bar_details_type>(0, std::make_pair(0, 100), 10);
        }

        /*!
            \brief Returns the position.

            \param details A detail implementation of a scroll bar.
            
            \return The position.
        */
        static size_type position(const scroll_bar_details_type& details)
        {
            return std::get<0>(details);
        }

        /*!
            \brief Sets a position.

            \param details  A detail implementation of a scroll bar.
            \param position A position.
        */
        static void set_position(scroll_bar_details_type& details, const size_type position)
        {
            std::get<0>(details) = position;
        }

        /*!
            \brief Returns the range.

            \param details A detail implementation of a scroll bar.
            
            \return The range.
        */
        static const range_type& range(const scroll_bar_details_type& details)
        {
            return std::get<1>(details);
        }

        /*!
            \brief Sets a range.

            \tparam R A range type.

            \param details A detail implementation of a scroll bar.
            \param range   A range.
        */
        template <typename R>
        static void set_range(scroll_bar_details_type& details, R&& range)
        {
            std::get<1>(details) = std::forward<R>(range);
        }

        /*!
            \brief Returns the page size.

            \param details A detail implementation of a scroll bar.
            
            \return The page size.
        */
        static size_type page_size(const scroll_bar_details_type& details)
        {
            return std::get<2>(details);
        }

        /*!
            \brief Sets a page size.

            \param details   A detail implementation of a scroll bar.
            \param page_size A page size.
        */
        static void set_page_size(scroll_bar_details_type& details, const size_type page_size)
        {
            std::get<2>(details) = page_size;
        }


    private:
        // static functions


        // forbidden operations

        scroll();


    };


}}}


#endif
