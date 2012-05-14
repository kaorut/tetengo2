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


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class template for a scroll bar.

        \tparam Size A size type.
    */
    template <typename Size>
    class scroll_bar
    {
    public:
        // types

        //! The size type.
        typedef Size size_type;

        //! The range type.
        typedef std::pair<size_type, size_type> range_type;


        // constructors and destructor

        /*!
            \brief Creates a scroll bar.

            The position, the range and the page size are initialized to 0.
        */
        scroll_bar()
        :
        m_position(0),
        m_range(0, 0),
        m_page_size(0)
        {}


        // functions

        /*!
            \brief Returns the position.

            \return The position.
        */
        size_type position()
        const
        {
            return m_position;
        }

        /*!
            \brief Sets a position

            The position must be inside the range; i.e., range().first <= position < range().second.

            \param position A position.

            \throw std::out_of_range When the position is outside the range.
        */
        void set_position(const size_type position)
        {
            if (position < m_range.first || m_range.second < position)
                BOOST_THROW_EXCEPTION(std::out_of_range("The position is outside the range."));

            m_position = position;
        }

        /*!
            \brief Returns the range.

            \return The range.
        */
        const range_type& range()
        const
        {
            return m_range;
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
            if (m_position < range.first || range.second <= m_position)
                BOOST_THROW_EXCEPTION(std::out_of_range("The position is outside the range."));

            m_range = std::forward<R>(range);
        }

        /*!
            \brief Returns the page size.

            \return The page size.
        */
        size_type page_size()
        const
        {
            return m_page_size;
        }

        /*!
            \brief Sets a page size

            The page size may be larger than the size of the range.

            \param page_size A page size.
        */
        void set_page_size(const size_type page_size)
        {
            m_page_size = page_size;
        }


    private:
        // variables

        size_type m_position;

        range_type m_range;

        size_type m_page_size;


    };


}}

#endif
