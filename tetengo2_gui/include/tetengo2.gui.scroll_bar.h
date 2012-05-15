/*! \file
    \brief The definition of tetengo2::gui::scroll_bar.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_SCROLLBAR_H)
#define TETENGO2_GUI_SCROLLBAR_H

#include <stdexcept>
#include <utility>

#include <boost/throw_exception.hpp>

#include "tetengo2.unique.h"


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a scroll bar.

        \tparam Size          A size type.
        \tparam ScrollDetails A detail implementation type of a scroll.
    */
    template <typename Size, typename ScrollDetails>
    class scroll_bar
    {
    public:
        // types

        //! The size type.
        typedef Size size_type;

        //! The range type.
        typedef std::pair<size_type, size_type> range_type;

        //! The detail implementation type of a scroll.
        typedef ScrollDetails details_type;

        //! The detail implementation type of a scroll bar.
        typedef typename details_type::scroll_bar_details_type scroll_bar_details_type;

        //! The detail implementation pointer type of a scroll bar.
        typedef typename details_type::scroll_bar_details_ptr_type scroll_bar_details_ptr_type;


        // constructors and destructor

        /*!
            \brief Creates a scroll bar.
        */
        template <typename WidgetDetails>
        scroll_bar(const WidgetDetails& widget_details)
        :
        m_p_details(details_type::create_scroll_bar(widget_details))
        {}


        // functions

        /*!
            \brief Returns the position.

            \return The position.
        */
        size_type position()
        const
        {
            return details_type::position(*m_p_details);
        }

        /*!
            \brief Sets a position

            The position must be inside the range; i.e., range().first <= position < range().second.

            \param position A position.

            \throw std::out_of_range When the position is outside the range.
        */
        void set_position(const size_type position)
        {
            const range_type r = range();
            if (position < r.first || r.second < position)
                BOOST_THROW_EXCEPTION(std::out_of_range("The position is outside the range."));

            details_type::set_position(*m_p_details, position);
        }

        /*!
            \brief Returns the range.

            \return The range.
        */
        const range_type range()
        const
        {
            return details_type::range(*m_p_details);
        }

        /*!
            \brief Sets a range

            The range.first must be smaller than the range.second, and the position must be inside the range;
            i.e., range.first <= position() <= range.second.

            \tparam R A range type.

            \param range A range.

            \throw std::out_of_range When the position is outside the range.
        */
        template <typename R>
        void set_range(R&& range)
        {
            if (range.first > range.second)
                BOOST_THROW_EXCEPTION(std::out_of_range("Reversed range is not allowed."));
            const size_type p = position();
            if (p < range.first || range.second <= p)
                BOOST_THROW_EXCEPTION(std::out_of_range("The position is outside the range."));

            details_type::set_range(*m_p_details, std::forward<R>(range));
        }

        /*!
            \brief Returns the page size.

            \return The page size.
        */
        size_type page_size()
        const
        {
            return details_type::page_size(*m_p_details);
        }

        /*!
            \brief Sets a page size

            The page size may be larger than the size of the range.

            \param page_size A page size.
        */
        void set_page_size(const size_type page_size)
        {
            details_type::set_page_size(*m_p_details, page_size);
        }


    private:
        // variables

        scroll_bar_details_ptr_type m_p_details;

        size_type m_position;

        range_type m_range;

        size_type m_page_size;


    };


}}

#endif
