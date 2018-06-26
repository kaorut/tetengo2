/*! \file
    \brief The definition of tetengo2::gui::message::size_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <tetengo2/gui/message/size_observer_set.h>


namespace tetengo2::gui::message {
    class size_observer_set::impl : private boost::noncopyable
    {
    public:
        // types

        using resized_type = size_observer_set::resized_type;

        using resized_signal_type = size_observer_set::resized_signal_type;


        // functions

        const resized_signal_type& resized() const
        {
            return m_resized;
        }

        resized_signal_type& resized()
        {
            return m_resized;
        }


    private:
        // variables

        resized_signal_type m_resized;
    };


    size_observer_set::size_observer_set() : m_p_impl{ std::make_unique<impl>() } {}

    size_observer_set::~size_observer_set() = default;

    const size_observer_set::resized_signal_type& size_observer_set::resized() const
    {
        return m_p_impl->resized();
    }

    size_observer_set::resized_signal_type& size_observer_set::resized()
    {
        return m_p_impl->resized();
    }
}
