/*! \file
    \brief The definition of tetengo2::gui::message::keyboard_observer_set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_KEYBOARDOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_KEYBOARDOBSERVERSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>

#include <tetengo2/gui/virtual_key.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::message {
    /*!
        \brief The class for a keyboard observer set.
    */
    class keyboard_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The virtual key type.
        using virtual_key_type = gui::virtual_key;

        //! The character type.
        using char_type = tetengo2::type_list::string_type::value_type;

        /*!
            \brief The observer type of key down.

            \param virtual_key A virtual key.
            \param shift       True when shift key is pressed.
            \param control     True when control key is pressed.
            \param meta        True when meta key is pressed.
        */
        using key_down_type = void(const virtual_key_type& virtual_key, bool shift, bool control, bool meta);

        //! The signal type of key down.
        using key_down_signal_type = boost::signals2::signal<key_down_type>;

        /*!
            \brief The observer type of key up.

            \param virtual_key A virtual key.
            \param shift       True when shift key is pressed.
            \param control     True when control key is pressed.
            \param meta        True when meta key is pressed.
        */
        using key_up_type = void(const virtual_key_type& virtual_key, bool shift, bool control, bool meta);

        //! The signal type of key up.
        using key_up_signal_type = boost::signals2::signal<key_up_type>;

        /*!
            \brief The observer type of character input.

            \param character A character.
        */
        using character_input_type = void(char_type character);

        //! The signal type of character input.
        using character_input_signal_type = boost::signals2::signal<character_input_type>;


        // constructors and destructor

        /*!
            \brief Creates a keyboard observer set.
        */
        keyboard_observer_set();

        /*!
            \brief Destroys the keyboard observer set.
        */
        ~keyboard_observer_set();


        // functions

        /*!
            \brief Returns the observer called when a key is pushed down.

            \return The observer called when a key is pushed down.
        */
        const key_down_signal_type& key_down() const;

        /*!
            \brief Returns the observer called when a key is pushed down.

            \return The observer called when a key is pushed down.
        */
        key_down_signal_type& key_down();

        /*!
            \brief Returns the observer called when a key is released up.

            \return The observer called when a key is released up.
        */
        const key_up_signal_type& key_up() const;

        /*!
            \brief Returns the observer called when a key is released up.

            \return The observer called when a key is released up.
        */
        key_up_signal_type& key_up();

        /*!
            \brief Returns the observer called when a character is input.

            \return The observer called when a character is input.
        */
        const character_input_signal_type& character_input() const;

        /*!
            \brief Returns the observer called when a character is input.

            \return The observer called when a character is input.
        */
        character_input_signal_type& character_input();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
