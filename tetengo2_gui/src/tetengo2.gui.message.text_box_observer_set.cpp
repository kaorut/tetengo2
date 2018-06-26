/*! \file
    \brief The definition of tetengo2::gui::message::text_box_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <tetengo2/gui/message/text_box_observer_set.h>


namespace tetengo2::gui::message {
    class text_box_observer_set::impl : private boost::noncopyable
    {
    public:
        // types

        using changed_type = text_box_observer_set::changed_type;

        using changed_signal_type = text_box_observer_set::changed_signal_type;


        // functions

        const changed_signal_type& changed() const
        {
            return m_changed;
        }

        changed_signal_type& changed()
        {
            return m_changed;
        }


    private:
        // variables

        changed_signal_type m_changed;
    };


    text_box_observer_set::text_box_observer_set() : m_p_impl{ std::unique_ptr<impl>() } {}

    text_box_observer_set::~text_box_observer_set() = default;

    const text_box_observer_set::changed_signal_type& text_box_observer_set::changed() const
    {
        return m_p_impl->changed();
    }

    text_box_observer_set::changed_signal_type& text_box_observer_set::changed()
    {
        return m_p_impl->changed();
    }
}
