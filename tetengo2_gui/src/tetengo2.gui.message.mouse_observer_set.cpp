/*! \file
    \brief The definition of tetengo2::gui::message::mouse_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/message/mouse_observer_set.h>


namespace tetengo2::gui::message {
    class mouse_observer_set::impl : private boost::noncopyable
    {
    public:
        // types

        using position_type = mouse_observer_set::position_type;

        using difference_type = mouse_observer_set::difference_type;

        using clicked_type = mouse_observer_set::clicked_type;

        using clicked_signal_type = mouse_observer_set::clicked_signal_type;

        using doubleclicked_type = mouse_observer_set::doubleclicked_type;

        using doubleclicked_signal_type = mouse_observer_set::doubleclicked_signal_type;

        using mouse_button_type = mouse_observer_set::mouse_button_type;

        using pressed_type = mouse_observer_set::pressed_type;

        using pressed_signal_type = mouse_observer_set::pressed_signal_type;

        using released_type = mouse_observer_set::released_type;

        using released_signal_type = mouse_observer_set::released_signal_type;

        using delta_type = mouse_observer_set::delta_type;

        using direction_type = mouse_observer_set::direction_type;

        using moved_type = mouse_observer_set::moved_type;

        using moved_signal_type = mouse_observer_set::moved_signal_type;

        using wheeled_type = mouse_observer_set::wheeled_type;

        using wheeled_signal_type = mouse_observer_set::wheeled_signal_type;


        // functions

        const clicked_signal_type& clicked() const
        {
            return m_clicked;
        }

        clicked_signal_type& clicked()
        {
            return m_clicked;
        }

        const doubleclicked_signal_type& doubleclicked() const
        {
            return m_doubleclicked;
        }

        doubleclicked_signal_type& doubleclicked()
        {
            return m_doubleclicked;
        }

        const pressed_signal_type& pressed() const
        {
            return m_pressed;
        }

        pressed_signal_type& pressed()
        {
            return m_pressed;
        }

        const released_signal_type& released() const
        {
            return m_released;
        }

        released_signal_type& released()
        {
            return m_released;
        }

        const moved_signal_type& moved() const
        {
            return m_moved;
        }

        moved_signal_type& moved()
        {
            return m_moved;
        }

        const wheeled_signal_type& wheeled() const
        {
            return m_wheeled;
        }

        wheeled_signal_type& wheeled()
        {
            return m_wheeled;
        }


    private:
        // variables

        clicked_signal_type m_clicked;

        doubleclicked_signal_type m_doubleclicked;

        pressed_signal_type m_pressed;

        moved_signal_type m_moved;

        released_signal_type m_released;

        wheeled_signal_type m_wheeled;
    };


    mouse_observer_set::mouse_observer_set() : m_p_impl{ std::make_unique<impl>() } {}

    mouse_observer_set::~mouse_observer_set() = default;

    const mouse_observer_set::clicked_signal_type& mouse_observer_set::clicked() const
    {
        return m_p_impl->clicked();
    }

    mouse_observer_set::clicked_signal_type& mouse_observer_set::clicked()
    {
        return m_p_impl->clicked();
    }

    const mouse_observer_set::doubleclicked_signal_type& mouse_observer_set::doubleclicked() const
    {
        return m_p_impl->doubleclicked();
    }

    mouse_observer_set::doubleclicked_signal_type& mouse_observer_set::doubleclicked()
    {
        return m_p_impl->doubleclicked();
    }

    const mouse_observer_set::pressed_signal_type& mouse_observer_set::pressed() const
    {
        return m_p_impl->pressed();
    }

    mouse_observer_set::pressed_signal_type& mouse_observer_set::pressed()
    {
        return m_p_impl->pressed();
    }

    const mouse_observer_set::released_signal_type& mouse_observer_set::released() const
    {
        return m_p_impl->released();
    }

    mouse_observer_set::released_signal_type& mouse_observer_set::released()
    {
        return m_p_impl->released();
    }

    const mouse_observer_set::moved_signal_type& mouse_observer_set::moved() const
    {
        return m_p_impl->moved();
    }

    mouse_observer_set::moved_signal_type& mouse_observer_set::moved()
    {
        return m_p_impl->moved();
    }

    const mouse_observer_set::wheeled_signal_type& mouse_observer_set::wheeled() const
    {
        return m_p_impl->wheeled();
    }

    mouse_observer_set::wheeled_signal_type& mouse_observer_set::wheeled()
    {
        return m_p_impl->wheeled();
    }
}
