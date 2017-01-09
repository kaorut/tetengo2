/*! \file
    \brief The definition of tetengo2::gui::message::keyboard_observer_set.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_KEYBOARDOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_KEYBOARDOBSERVERSET_H

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class template for a keyboard observer set.

        \tparam VirtualKey A virtual key type.
        \tparam Char       A character type.
    */
    template <typename VirtualKey, typename Char>
    class keyboard_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The virtual key type.
        using virtual_key_type = VirtualKey;

        //! The character type.
        using char_type = Char;

        /*!
            \brief The observer type of key down.

            \param virtual_key A virtual key.
            \param shift       True when shift key is pressed.
            \param control     True when control key is pressed.
            \param meta        True when meta key is pressed.
        */
        using key_down_type = void (const virtual_key_type& virtual_key, bool shift, bool control, bool meta);

        //! The signal type of key down.
        using key_down_signal_type = boost::signals2::signal<key_down_type>;

        /*!
            \brief The observer type of key up.

            \param virtual_key A virtual key.
            \param shift       True when shift key is pressed.
            \param control     True when control key is pressed.
            \param meta        True when meta key is pressed.
        */
        using key_up_type = void (const virtual_key_type& virtual_key, bool shift, bool control, bool meta);

        //! The signal type of key up.
        using key_up_signal_type = boost::signals2::signal<key_up_type>;

        /*!
            \brief The observer type of character input.

            \param character A character.
        */
        using character_input_type = void (typename keyboard_observer_set::char_type character);

        //! The signal type of character input.
        using character_input_signal_type = boost::signals2::signal<character_input_type>;


        // functions

        /*!
            \brief Returns the observer called when a key is pushed down.

            \return The observer called when a key is pushed down.
        */
        const key_down_signal_type& key_down()
        const
        {
            return m_key_down;
        }

        /*!
            \brief Returns the observer called when a key is pushed down.

            \return The observer called when a key is pushed down.
        */
        key_down_signal_type& key_down()
        {
            return m_key_down;
        }

        /*!
            \brief Returns the observer called when a key is released up.

            \return The observer called when a key is released up.
        */
        const key_up_signal_type& key_up()
        const
        {
            return m_key_up;
        }

        /*!
            \brief Returns the observer called when a key is released up.

            \return The observer called when a key is released up.
        */
        key_up_signal_type& key_up()
        {
            return m_key_up;
        }

        /*!
            \brief Returns the observer called when a character is input.

            \return The observer called when a character is input.
        */
        const character_input_signal_type& character_input()
        const
        {
            return m_character_input;
        }

        /*!
            \brief Returns the observer called when a character is input.

            \return The observer called when a character is input.
        */
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


}}}


#endif
