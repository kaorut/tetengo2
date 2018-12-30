/*! \file
    \brief The definition of tetengo2::gui::scroll_bar.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/scroll.h>
#include <tetengo2/gui/message/scroll_bar_observer_set.h>
#include <tetengo2/gui/scroll_bar.h>

namespace tetengo2 { namespace gui { namespace widget {
    class widget;
}}}


namespace tetengo2::gui {
    class scroll_bar::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = scroll_bar::size_type;

        using range_type = scroll_bar::range_type;

        using scroll_bar_observer_set_type = scroll_bar::scroll_bar_observer_set_type;

        using style_type = scroll_bar::style_type;


        // constructors and destructor

        impl(const gui::widget::widget& widget, const style_type style)
        : m_p_details{ detail::gui_detail_impl_set().scroll_().create_scroll_bar(widget, to_details_style(style)) },
          m_scroll_bar_observer_set{}, m_tracking_position{}
        {
            set_observers();
        }


        // functions

        size_type position() const
        {
            return detail::gui_detail_impl_set().scroll_().position(*m_p_details);
        }

        void set_position(const size_type position)
        {
            const auto r = range();
            if (position < r.first || r.second < position)
                BOOST_THROW_EXCEPTION((std::out_of_range{ "The position is outside the range." }));

            detail::gui_detail_impl_set().scroll_().set_position(*m_p_details, position);
        }

        size_type tracking_position() const
        {
            return m_tracking_position;
        }

        range_type range() const
        {
            return detail::gui_detail_impl_set().scroll_().range(*m_p_details);
        }

        void set_range(range_type range)
        {
            if (range.first > range.second)
                BOOST_THROW_EXCEPTION((std::out_of_range{ "Reversed range is not allowed." }));

            detail::gui_detail_impl_set().scroll_().set_range(*m_p_details, std::move(range));
        }

        size_type page_size() const
        {
            return detail::gui_detail_impl_set().scroll_().page_size(*m_p_details);
        }

        void set_page_size(const size_type page_size)
        {
            detail::gui_detail_impl_set().scroll_().set_page_size(*m_p_details, page_size);
        }

        bool enabled() const
        {
            return detail::gui_detail_impl_set().scroll_().enabled(*m_p_details);
        }

        void set_enabled(const bool enabled)
        {
            detail::gui_detail_impl_set().scroll_().set_enabled(*m_p_details, enabled);
        }

        const scroll_bar_observer_set_type& scroll_bar_observer_set() const
        {
            return m_scroll_bar_observer_set;
        }

        scroll_bar_observer_set_type& scroll_bar_observer_set()
        {
            return m_scroll_bar_observer_set;
        }


    private:
        // types

        using details_type = detail::base::scroll;

        using scroll_bar_details_ptr_type = details_type::scroll_bar_details_ptr_type;


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


    scroll_bar::scroll_bar(const gui::widget::widget& widget, const style_type style)
    : m_p_impl{ std::make_unique<impl>(widget, style) }
    {}

    scroll_bar::~scroll_bar() = default;

    scroll_bar::size_type scroll_bar::position() const
    {
        return m_p_impl->position();
    }

    void scroll_bar::set_position(const size_type position)
    {
        m_p_impl->set_position(position);
    }

    scroll_bar::size_type scroll_bar::tracking_position() const
    {
        return m_p_impl->tracking_position();
    }

    scroll_bar::range_type scroll_bar::range() const
    {
        return m_p_impl->range();
    }

    void scroll_bar::set_range(range_type range)
    {
        m_p_impl->set_range(std::move(range));
    }

    scroll_bar::size_type scroll_bar::page_size() const
    {
        return m_p_impl->page_size();
    }

    void scroll_bar::set_page_size(const size_type page_size)
    {
        m_p_impl->set_page_size(page_size);
    }

    bool scroll_bar::enabled() const
    {
        return m_p_impl->enabled();
    }

    void scroll_bar::set_enabled(const bool enabled)
    {
        m_p_impl->set_enabled(enabled);
    }

    const scroll_bar::scroll_bar_observer_set_type& scroll_bar::scroll_bar_observer_set() const
    {
        return m_p_impl->scroll_bar_observer_set();
    }

    scroll_bar::scroll_bar_observer_set_type& scroll_bar::scroll_bar_observer_set()
    {
        return m_p_impl->scroll_bar_observer_set();
    }
}
