/*! \file
    \brief The definition of tetengo2::gui::message::menu_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <tetengo2/gui/message/menu_observer_set.h>


namespace tetengo2::gui::message {
    class menu_observer_set::impl : private boost::noncopyable
    {
    public:
        // types

        using selected_type = void();

        using selected_signal_type = boost::signals2::signal<selected_type>;


        // functions

        const selected_signal_type& selected() const
        {
            return m_selected;
        }

        selected_signal_type& selected()
        {
            return m_selected;
        }


    private:
        // variables

        selected_signal_type m_selected;
    };


    menu_observer_set::menu_observer_set() : m_p_impl{ std::make_unique<impl>() } {}

    menu_observer_set::~menu_observer_set() = default;

    const menu_observer_set::selected_signal_type& menu_observer_set::selected() const
    {
        return m_p_impl->selected();
    }

    menu_observer_set::selected_signal_type& menu_observer_set::selected()
    {
        return m_p_impl->selected();
    }
}