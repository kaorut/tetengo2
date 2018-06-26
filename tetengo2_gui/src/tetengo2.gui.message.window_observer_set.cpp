/*! \file
    \brief The definition of tetengo2::gui::message::window_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/message/window_observer_set.h>


namespace tetengo2::gui::message {
    class window_observer_set::impl : private boost::noncopyable
    {
    public:
        // types

        using closing_type = window_observer_set::closing_type;

        using closing_signal_type = window_observer_set::closing_signal_type;

        using destroyed_type = window_observer_set::destroyed_type;

        using destroyed_signal_type = window_observer_set::destroyed_signal_type;


        // functions

        const closing_signal_type& closing() const
        {
            return m_closing;
        }

        closing_signal_type& closing()
        {
            return m_closing;
        }

        const destroyed_signal_type& destroyed() const
        {
            return m_destroyed;
        }

        destroyed_signal_type& destroyed()
        {
            return m_destroyed;
        }


    private:
        // variables

        closing_signal_type m_closing;

        destroyed_signal_type m_destroyed;
    };


    window_observer_set::window_observer_set() : m_p_impl{ std::make_unique<impl>() } {}

    window_observer_set::~window_observer_set() = default;

    const window_observer_set::closing_signal_type& window_observer_set::closing() const
    {
        return m_p_impl->closing();
    }

    window_observer_set::closing_signal_type& window_observer_set::closing()
    {
        return m_p_impl->closing();
    }

    const window_observer_set::destroyed_signal_type& window_observer_set::destroyed() const
    {
        return m_p_impl->destroyed();
    }

    window_observer_set::destroyed_signal_type& window_observer_set::destroyed()
    {
        return m_p_impl->destroyed();
    }
}
