/*! \file
    \brief The definition of tetengo2::gui::scroll_bar.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_SCROLLBAR_H)
#define TETENGO2_GUI_SCROLLBAR_H

#include <cassert>
#include <stdexcept>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/gui/message/scroll_bar_observer_set.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui {
    /*!
        \brief The class template for a scroll bar.

        \tparam ScrollDetails A detail implementation type of a scroll.
    */
    template <typename ScrollDetails>
    class scroll_bar : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = tetengo2::type_list::size_type;

        //! The range type.
        using range_type = std::pair<size_type, size_type>;

        //! The scroll details type.
        using details_type = ScrollDetails;

        //! The detail implementation pointer type of a scroll bar.
        using scroll_bar_details_ptr_type = typename details_type::scroll_bar_details_ptr_type;

        //! The scroll bar observer set type.
        using scroll_bar_observer_set_type = gui::message::scroll_bar_observer_set;

        //! The style type.
        enum class style_type
        {
            vertical, //!< The vertical style.
            horizontal, //!< The horizontal style.
        };


        // constructors and destructor

        /*!
            \brief Creates a scroll bar.

            \param widget_details A detail implementation of a widget.
            \param style          A style.
        */
        template <typename WidgetDetails>
        scroll_bar(const WidgetDetails& widget_details, const style_type style)
        : m_p_details{ details_type::create_scroll_bar(widget_details, to_details_style(style)) },
          m_scroll_bar_observer_set{}, m_tracking_position{}
        {
            set_observers();
        }


        // functions

        /*!
            \brief Returns the position.

            \return The position.
        */
        size_type position() const
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
            const auto r = range();
            if (position < r.first || r.second < position)
                BOOST_THROW_EXCEPTION((std::out_of_range{ "The position is outside the range." }));

            details_type::set_position(*m_p_details, position);
        }

        /*!
            \brief Returns the tracking position.

            \return The tracking position.
        */
        size_type tracking_position() const
        {
            return m_tracking_position;
        }

        /*!
            \brief Returns the range.

            \return The range.
        */
        const range_type range() const
        {
            return details_type::range(*m_p_details);
        }

        /*!
            \brief Sets a range

            The range.first must be smaller than the range.second, and the position must be inside the range;
            i.e., range.first <= position() <= range.second.

            \param range A range.

            \throw std::out_of_range When the position is outside the range.
        */
        void set_range(range_type range)
        {
            if (range.first > range.second)
                BOOST_THROW_EXCEPTION((std::out_of_range{ "Reversed range is not allowed." }));

            details_type::set_range(*m_p_details, std::move(range));
        }

        /*!
            \brief Returns the page size.

            \return The page size.
        */
        size_type page_size() const
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

        /*!
            \brief Returns the enabled status.

            \retval true  When the scroll bar is enabled.
            \retval false Otherwise.
        */
        bool enabled() const
        {
            return details_type::enabled(*m_p_details);
        }

        /*!
            \brief Sets an entabled status.

            \param enabled An enabled status.
        */
        void set_enabled(const bool enabled)
        {
            details_type::set_enabled(*m_p_details, enabled);
        }

        /*!
            \brief Returns the scroll bar observer set.

            \return The scroll bar observer set.
        */
        const scroll_bar_observer_set_type& scroll_bar_observer_set() const
        {
            return m_scroll_bar_observer_set;
        }

        /*!
            \brief Returns the scroll bar observer set.

            \return The scroll bar observer set.
        */
        scroll_bar_observer_set_type& scroll_bar_observer_set()
        {
            return m_scroll_bar_observer_set;
        }


    private:
        // static functions

        static typename details_type::style_type to_details_style(const style_type style)
        {
            switch (style)
            {
            case style_type::vertical:
                return details_type::style_type::vertical;
            case style_type::horizontal:
                return details_type::style_type::horizontal;
            default:
                assert(false);
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid style." }));
            }
        }


        // variables

        scroll_bar_details_ptr_type m_p_details;

        scroll_bar_observer_set_type m_scroll_bar_observer_set;

        size_type m_tracking_position;


        // functions

        void set_observers()
        {
            m_scroll_bar_observer_set.scrolling().connect(
                [this](const size_type new_position) { this->set_tracking_position(new_position); });
            m_scroll_bar_observer_set.scrolled().connect(
                [this](const size_type new_position) { this->set_tracking_position(new_position); });
        }

        void set_tracking_position(const size_type new_position)
        {
            m_tracking_position = new_position;
        }
    };
}

#endif
