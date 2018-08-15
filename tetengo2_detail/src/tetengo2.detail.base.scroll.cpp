/*! \file
    \brief The definition of tetengo2::detail::base::scroll.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <algorithm>
#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/scroll.h>

namespace tetengo2 { namespace gui { namespace widget {
    class widget;
}}}


namespace tetengo2::detail::base {
    class scroll::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = scroll::size_type;

        using range_type = scroll::range_type;

        using scroll_bar_details_type = scroll::scroll_bar_details_type;

        using scroll_bar_details_ptr_type = scroll::scroll_bar_details_ptr_type;

        using style_type = scroll::style_type;


        // functions

        scroll_bar_details_ptr_type
        create_scroll_bar(const gui::widget::widget& widget, style_type style, const scroll& self) const
        {
            return self.create_scroll_bar_impl(widget, style);
        }

        size_type position(const scroll_bar_details_type& details, const scroll& self) const
        {
            return self.position_impl(details);
        }

        void set_position(scroll_bar_details_type& details, const size_type position, const scroll& self) const
        {
            self.set_position_impl(details, position);
        }

        range_type range(const scroll_bar_details_type& details, const scroll& self) const
        {
            return self.range_impl(details);
        }

        void set_range(scroll_bar_details_type& details, range_type range, const scroll& self) const
        {
            self.set_range_impl(details, std::move(range));
        }

        size_type page_size(const scroll_bar_details_type& details, const scroll& self) const
        {
            return self.page_size(details);
        }

        void set_page_size(scroll_bar_details_type& details, const size_type page_size, const scroll& self) const
        {
            self.set_page_size(details, page_size);
        }

        bool enabled(const scroll_bar_details_type& details, const scroll& self) const
        {
            return self.enabled(details);
        }

        void set_enabled(scroll_bar_details_type& details, const bool enabled, const scroll& self) const
        {
            self.set_enabled(details, enabled);
        }
    };


    scroll::scroll_bar_details_type::~scroll_bar_details_type() = default;

    scroll::~scroll() = default;

    scroll::scroll_bar_details_ptr_type
    scroll::create_scroll_bar(const gui::widget::widget& widget, const style_type style) const
    {
        return m_p_impl->create_scroll_bar(widget, style, *this);
    }

    scroll::size_type scroll::position(const scroll_bar_details_type& details) const
    {
        return m_p_impl->position(details, *this);
    }

    void scroll::set_position(scroll_bar_details_type& details, const size_type position) const
    {
        m_p_impl->set_position(details, position, *this);
    }

    scroll::range_type scroll::range(const scroll_bar_details_type& details) const
    {
        return m_p_impl->range(details, *this);
    }

    void scroll::set_range(scroll_bar_details_type& details, range_type range) const
    {
        m_p_impl->set_range(details, std::move(range), *this);
    }

    scroll::size_type scroll::page_size(const scroll_bar_details_type& details) const
    {
        return m_p_impl->page_size(details, *this);
    }

    void scroll::set_page_size(scroll_bar_details_type& details, const size_type page_size) const
    {
        m_p_impl->set_page_size(details, page_size, *this);
    }

    bool scroll::enabled(const scroll_bar_details_type& details) const
    {
        return m_p_impl->enabled(details, *this);
    }

    void scroll::set_enabled(scroll_bar_details_type& details, const bool enabled) const
    {
        m_p_impl->set_enabled(details, enabled, *this);
    }

    scroll::scroll() : m_p_impl{ std::make_unique<impl>() } {}
}
