/*! \file
    \brief The definition of tetengo2::gui::message::paint_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/message/paint_observer_set.h>


namespace tetengo2::gui::message {
    class paint_observer_set::impl : private boost::noncopyable
    {
    public:
        // types

        using canvas_type = gui::drawing::canvas;

        using paint_background_signal_type = paint_observer_set::paint_background_signal_type;

        using paint_signal_type = paint_observer_set::paint_signal_type;


        // functions

        const paint_background_signal_type& paint_background() const
        {
            return m_paint_background;
        }

        paint_background_signal_type& paint_background()
        {
            return m_paint_background;
        }

        const paint_signal_type& paint() const
        {
            return m_paint;
        }

        paint_signal_type& paint()
        {
            return m_paint;
        }


    private:
        // variables

        paint_background_signal_type m_paint_background;

        paint_signal_type m_paint;
    };


    paint_observer_set::paint_observer_set() : m_p_impl{ std::make_unique<impl>() } {}

    paint_observer_set::~paint_observer_set() = default;

    const paint_observer_set::paint_background_signal_type& paint_observer_set::paint_background() const
    {
        return m_p_impl->paint_background();
    }

    paint_observer_set::paint_background_signal_type& paint_observer_set::paint_background()
    {
        return m_p_impl->paint_background();
    }

    const paint_observer_set::paint_signal_type& paint_observer_set::paint() const
    {
        return m_p_impl->paint();
    }

    paint_observer_set::paint_signal_type& paint_observer_set::paint()
    {
        return m_p_impl->paint();
    }


    bool paint_observer_set::logical_or_combiner::is_true(const bool b)
    {
        return b;
    }
}
