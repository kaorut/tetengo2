/*! \file
    \brief The definition of tetengo2::gui::message::keyboard_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/gui/message/keyboard_observer_set.h>


namespace tetengo2::gui::message {
    class keyboard_observer_set::impl : private boost::noncopyable
    {
    public:
        // types

        using virtual_key_type = keyboard_observer_set::virtual_key_type;

        using char_type = keyboard_observer_set::char_type;

        using key_down_type = keyboard_observer_set::key_down_type;

        using key_down_signal_type = keyboard_observer_set::key_down_signal_type;

        using key_up_type = keyboard_observer_set::key_up_type;

        using key_up_signal_type = keyboard_observer_set::key_up_signal_type;

        using character_input_type = keyboard_observer_set::character_input_type;

        using character_input_signal_type = keyboard_observer_set::character_input_signal_type;


        // functions

        const key_down_signal_type& key_down() const
        {
            return m_key_down;
        }

        key_down_signal_type& key_down()
        {
            return m_key_down;
        }

        const key_up_signal_type& key_up() const
        {
            return m_key_up;
        }

        key_up_signal_type& key_up()
        {
            return m_key_up;
        }

        const character_input_signal_type& character_input() const
        {
            return m_character_input;
        }

        character_input_signal_type& character_input()
        {
            return m_character_input;
        }


    private:
        // variables

        key_down_signal_type m_key_down;

        key_up_signal_type m_key_up;

        character_input_signal_type m_character_input;
    };


    keyboard_observer_set::keyboard_observer_set() : m_p_impl{ std::make_unique<impl>() } {}

    keyboard_observer_set::~keyboard_observer_set() = default;

    const keyboard_observer_set::key_down_signal_type& keyboard_observer_set::key_down() const
    {
        return m_p_impl->key_down();
    }

    keyboard_observer_set::key_down_signal_type& keyboard_observer_set::key_down()
    {
        return m_p_impl->key_down();
    }

    const keyboard_observer_set::key_up_signal_type& keyboard_observer_set::key_up() const
    {
        return m_p_impl->key_up();
    }

    keyboard_observer_set::key_up_signal_type& keyboard_observer_set::key_up()
    {
        return m_p_impl->key_up();
    }

    const keyboard_observer_set::character_input_signal_type& keyboard_observer_set::character_input() const
    {
        return m_p_impl->character_input();
    }

    keyboard_observer_set::character_input_signal_type& keyboard_observer_set::character_input()
    {
        return m_p_impl->character_input();
    }
}