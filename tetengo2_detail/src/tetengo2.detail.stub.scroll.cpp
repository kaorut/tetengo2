/*! \file
    \brief The definition of tetengo2::detail::stub::scroll.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>
#include <utility>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/stub/scroll.h>
#include <tetengo2/stdalt.h>

namespace tetengo2 { namespace gui { namespace widget {
    class widget;
}}}


namespace tetengo2::detail::stub {
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

        scroll_bar_details_ptr_type create_scroll_bar_impl(
            TETENGO2_STDALT_MAYBE_UNUSED const gui::widget::widget& widget,
            TETENGO2_STDALT_MAYBE_UNUSED const style_type style) const
        {
            return std::make_unique<stub_scroll_bar_details_type>(0, std::make_pair(0, 100), 10, true);
        }

        size_type position_impl(const scroll_bar_details_type& details) const
        {
            return static_cast<const stub_scroll_bar_details_type&>(details).position;
        }

        void set_position_impl(scroll_bar_details_type& details, const size_type position) const
        {
            static_cast<stub_scroll_bar_details_type&>(details).position = position;
        }

        range_type range_impl(const scroll_bar_details_type& details) const
        {
            return static_cast<const stub_scroll_bar_details_type&>(details).range;
        }

        void set_range_impl(scroll_bar_details_type& details, range_type range) const
        {
            static_cast<stub_scroll_bar_details_type&>(details).range = std::move(range);
        }

        size_type page_size_impl(const scroll_bar_details_type& details) const
        {
            return static_cast<const stub_scroll_bar_details_type&>(details).page_size;
        }

        void set_page_size_impl(scroll_bar_details_type& details, const size_type page_size) const
        {
            static_cast<stub_scroll_bar_details_type&>(details).page_size = page_size;
        }

        bool enabled_impl(const scroll_bar_details_type& details) const
        {
            return static_cast<const stub_scroll_bar_details_type&>(details).enabled;
        }

        void set_enabled_impl(scroll_bar_details_type& details, const bool enabled) const
        {
            static_cast<stub_scroll_bar_details_type&>(details).enabled = enabled;
        }


    private:
        // types

        struct stub_scroll_bar_details_type : public scroll_bar_details_type
        {
            size_type                       position;
            std::pair<size_type, size_type> range;
            size_type                       page_size;
            bool                            enabled;

            stub_scroll_bar_details_type(
                const size_type                   position,
                std::pair<size_type, size_type>&& range,
                const size_type                   page_size,
                const bool                        enabled)
            : position{ position }, range{ std::forward<std::pair<size_type, size_type>>(range) },
              page_size{ page_size }, enabled{ enabled }
            {}

            virtual ~stub_scroll_bar_details_type() = default;
        };
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
