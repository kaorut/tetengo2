/*! \file
    \brief The definition of tetengo2::gui::message::list_selection_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/message/list_selection_observer_set.h>


namespace tetengo2::gui::message {
    class list_selection_observer_set::impl : private boost::noncopyable
    {
    public:
        // types

        using selection_changed_type = list_selection_observer_set::selection_changed_type;

        using selection_changed_signal_type = list_selection_observer_set::selection_changed_signal_type;


        // functions

        const selection_changed_signal_type& selection_changed() const
        {
            return m_selection_changed;
        }

        selection_changed_signal_type& selection_changed()
        {
            return m_selection_changed;
        }


    private:
        // variables

        selection_changed_signal_type m_selection_changed;
    };


    list_selection_observer_set::list_selection_observer_set() : m_p_impl{ std::make_unique<impl>() } {}

    list_selection_observer_set::~list_selection_observer_set() = default;

    const list_selection_observer_set::selection_changed_signal_type&
    list_selection_observer_set::selection_changed() const
    {
        return m_p_impl->selection_changed();
    }

    list_selection_observer_set::selection_changed_signal_type& list_selection_observer_set::selection_changed()
    {
        return m_p_impl->selection_changed();
    }
}
