/*! \file
    \brief The definition of tetengo2::gui::message::keyboard_observer_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_KEYBOARDOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_KEYBOARDOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class template for a keyboard observer set.

        \tparam Char A character type.
    */
    template <typename Char>
    class keyboard_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The character type.
        typedef Char char_type;

        /*!
            \brief The observer type of character input.
        */
        typedef void character_input_type(char_type character);

        //! The signal type of character input.
        typedef
            boost::signals2::signal<character_input_type>
            character_input_signal_type;


        // functions

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

        character_input_signal_type m_character_input;


    };


}}}


#endif
