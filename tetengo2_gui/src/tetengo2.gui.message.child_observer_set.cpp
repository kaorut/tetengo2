/*! \file
    \brief The definition of tetengo2::gui::message::child_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/message/child_observer_set.h>


namespace tetengo2::gui::message {
    class child_observer_set::impl : private boost::noncopyable
    {
    public:
        // types

        using widget_type = child_observer_set::widget_type;

        using created_signal_type = child_observer_set::created_signal_type;

        using destroying_signal_type = child_observer_set::destroying_signal_type;


        // functions

        const created_signal_type& created() const
        {
            return m_created;
        }

        created_signal_type& created()
        {
            return m_created;
        }

        const destroying_signal_type& destroying() const
        {
            return m_destroying;
        }

        destroying_signal_type& destroying()
        {
            return m_destroying;
        }


    private:
        // variables

        created_signal_type m_created;

        destroying_signal_type m_destroying;
    };


    child_observer_set::child_observer_set() : m_p_impl{ std::make_unique<impl>() } {}

    child_observer_set::~child_observer_set() = default;

    const child_observer_set::created_signal_type& child_observer_set::created() const
    {
        return m_p_impl->created();
    }

    child_observer_set::created_signal_type& child_observer_set::created()
    {
        return m_p_impl->created();
    }

    const child_observer_set::destroying_signal_type& child_observer_set::destroying() const
    {
        return m_p_impl->destroying();
    }

    child_observer_set::destroying_signal_type& child_observer_set::destroying()
    {
        return m_p_impl->destroying();
    }
}
