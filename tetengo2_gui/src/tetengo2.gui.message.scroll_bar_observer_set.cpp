/*! \file
    \brief The definition of tetengo2::gui::message::scroll_bar_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/message/scroll_bar_observer_set.h>


namespace tetengo2::gui::message {
    class scroll_bar_observer_set::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = scroll_bar_observer_set::size_type;

        using scrolling_type = scroll_bar_observer_set::scrolling_type;

        using scrolling_signal_type = scroll_bar_observer_set::scrolling_signal_type;

        using scrolled_type = scroll_bar_observer_set::scrolled_type;

        using scrolled_signal_type = scroll_bar_observer_set::scrolled_signal_type;


        // functions

        const scrolled_signal_type& scrolling() const
        {
            return m_scrolling;
        }

        scrolled_signal_type& scrolling()
        {
            return m_scrolling;
        }

        const scrolled_signal_type& scrolled() const
        {
            return m_scrolled;
        }

        scrolled_signal_type& scrolled()
        {
            return m_scrolled;
        }


    private:
        // variables

        scrolling_signal_type m_scrolling;

        scrolled_signal_type m_scrolled;
    };


    scroll_bar_observer_set::scroll_bar_observer_set() : m_p_impl{ std::make_unique<impl>() } {}

    scroll_bar_observer_set::~scroll_bar_observer_set() = default;

    const scroll_bar_observer_set::scrolled_signal_type& scroll_bar_observer_set::scrolling() const
    {
        return m_p_impl->scrolling();
    }

    scroll_bar_observer_set::scrolled_signal_type& scroll_bar_observer_set::scrolling()
    {
        return m_p_impl->scrolling();
    }

    const scroll_bar_observer_set::scrolled_signal_type& scroll_bar_observer_set::scrolled() const
    {
        return m_p_impl->scrolled();
    }

    scroll_bar_observer_set::scrolled_signal_type& scroll_bar_observer_set::scrolled()
    {
        return m_p_impl->scrolled();
    }
}
