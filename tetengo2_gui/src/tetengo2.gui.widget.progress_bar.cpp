/*! \file
    \brief The definition of tetengo2::gui::widget::progress_bar.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/detail/base/gui_impl_set.h>
#include <tetengo2/detail/base/message_handler.h>
#include <tetengo2/detail/base/widget.h>
#include <tetengo2/gui/message/child_observer_set.h>
#include <tetengo2/gui/widget/control.h>
#include <tetengo2/gui/widget/progress_bar.h>
#include <tetengo2/gui/widget/widget.h>


namespace tetengo2::gui::widget {
    class progress_bar::impl : private boost::noncopyable
    {
    public:
        // types

        using size_type = progress_bar::size_type;

        using state_type = progress_bar::state_type;


        // functions

        size_type goal(const progress_bar& self) const
        {
            return widget_details().progress_bar_goal(self);
        }

        void set_goal(const size_type goal, progress_bar& self)
        {
            widget_details().set_progress_bar_goal(self, goal);
        }

        size_type progress(const progress_bar& self) const
        {
            return widget_details().progress_bar_progress(self);
        }

        void set_progress(const size_type progress, progress_bar& self)
        {
            widget_details().set_progress_bar_progress(self, progress);
        }

        state_type state(const progress_bar& self) const
        {
            return static_cast<state_type>(widget_details().progress_bar_state(self));
        }

        void set_state(const state_type state, progress_bar& self)
        {
            widget_details().set_progress_bar_state(
                self, static_cast<widget_details_type::progress_bar_state_type>(state));
        }
    };


    progress_bar::progress_bar(widget& parent)
    :
#if BOOST_COMP_MSVC
#pragma warning(push)
#pragma warning(disable : 4355)
#endif
      control{ control::scroll_bar_style_type::none,
               detail::gui_detail_impl_set().message_handler_().make_progress_bar_message_handler_map(
                   *this,
                   message_handler_map_type{}),
               widget_details().create_progress_bar(parent) },
#if BOOST_COMP_MSVC
#pragma warning(pop)
#endif
      m_p_impl{ std::make_unique<impl>() }
    {
        control::initialize(this);

        parent.child_observer_set().created()(*this);
    }

    progress_bar::~progress_bar() noexcept
    {
        try
        {
            if (this->has_parent())
                this->parent().child_observer_set().destroying()(*this);
        }
        catch (...)
        {
        }
    }

    progress_bar::size_type progress_bar::goal() const
    {
        return m_p_impl->goal(*this);
    }

    void progress_bar::set_goal(const size_type goal)
    {
        m_p_impl->set_goal(goal, *this);
    }

    progress_bar::size_type progress_bar::progress() const
    {
        return m_p_impl->progress(*this);
    }

    void progress_bar::set_progress(const size_type progress)
    {
        m_p_impl->set_progress(progress, *this);
    }

    progress_bar::state_type progress_bar::state() const
    {
        return m_p_impl->state(*this);
    }

    void progress_bar::set_state(const state_type state)
    {
        m_p_impl->set_state(state, *this);
    }
}
