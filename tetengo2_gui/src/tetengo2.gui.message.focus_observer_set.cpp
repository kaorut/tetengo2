/*! \file
    \brief The definition of tetengo2::gui::message::focus_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <tetengo2/gui/message/focus_observer_set.h>


namespace tetengo2::gui::message {
    class focus_observer_set::impl : private boost::noncopyable
    {
    public:
        // types

        using got_focus_type = void();

        using got_focus_signal_type = boost::signals2::signal<got_focus_type>;

        using lost_focus_type = void();

        using lost_focus_signal_type = boost::signals2::signal<lost_focus_type>;


        // functions

        const got_focus_signal_type& got_focus() const
        {
            return m_got_focus;
        }

        got_focus_signal_type& got_focus()
        {
            return m_got_focus;
        }

        const lost_focus_signal_type& lost_focus() const
        {
            return m_lost_focus;
        }

        lost_focus_signal_type& lost_focus()
        {
            return m_lost_focus;
        }


    private:
        // variables

        got_focus_signal_type m_got_focus;

        lost_focus_signal_type m_lost_focus;
    };


    focus_observer_set::focus_observer_set() : m_p_impl{ std::make_unique<impl>() } {}

    focus_observer_set::~focus_observer_set() = default;

    const focus_observer_set::got_focus_signal_type& focus_observer_set::got_focus() const
    {
        return m_p_impl->got_focus();
    }

    focus_observer_set::got_focus_signal_type& focus_observer_set::got_focus()
    {
        return m_p_impl->got_focus();
    }

    const focus_observer_set::lost_focus_signal_type& focus_observer_set::lost_focus() const
    {
        return m_p_impl->lost_focus();
    }

    focus_observer_set::lost_focus_signal_type& focus_observer_set::lost_focus()
    {
        return m_p_impl->lost_focus();
    }
}
