/*! \file
    \brief The definition of tetengo2::gui::message::mouse_observer_set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_MOUSEOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_MOUSEOBSERVERSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/rational.hpp>
#include <boost/signals2.hpp>

#include <tetengo2/gui/type_list.h>
#include <tetengo2/type_list.h>


namespace tetengo2::gui::message {
    /*!
        \brief The class for a mouse observer set.
    */
    class mouse_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The position type.
        using position_type = gui::type_list::position_type;

        //! The difference type.
        using difference_type = tetengo2::type_list::difference_type;

        /*!
            \brief The observer type of clicked.
        */
        using clicked_type = void();

        //! The signal type of clicked.
        using clicked_signal_type = boost::signals2::signal<clicked_type>;

        /*!
            \brief The observer type of double-clicked.
        */
        using doubleclicked_type = void();

        //! The signal type of double-clicked.
        using doubleclicked_signal_type = boost::signals2::signal<doubleclicked_type>;

        //! The mouse button kind type.
        enum class mouse_button_type
        {
            left, //!< Left button.
            right, //!< Right button.
        };

        /*!
            \brief The observer type of pressed.

            \param button   A button kind.
            \param position A position.
            \param shift    True when shift key is pressed.
            \param control  True when control key is pressed.
            \param meta     True when meta key is pressed.
        */
        using pressed_type = void(
            typename mouse_observer_set::mouse_button_type button,
            const position_type&                           position,
            bool                                           shift,
            bool                                           control,
            bool                                           meta);

        //! The signal type of pressed.
        using pressed_signal_type = boost::signals2::signal<pressed_type>;

        /*!
            \brief The observer type of released.

            \param button   A button kind.
            \param position A position.
            \param shift    True when shift key is pressed.
            \param control  True when control key is pressed.
            \param meta     True when meta key is pressed.
        */
        using released_type = void(
            typename mouse_observer_set::mouse_button_type button,
            const position_type&                           position,
            bool                                           shift,
            bool                                           control,
            bool                                           meta);

        //! The signal type of pressed.
        using released_signal_type = boost::signals2::signal<released_type>;

        //! The mouse wheel delta type.
        using delta_type = boost::rational<difference_type>;

        //! The mouse wheel direction type.
        enum class direction_type
        {
            vertical, //!< Vertical.
            horizontal, //!< Horizontal.
        };

        /*!
            \brief The observer type of moved.

            \param position A position.
            \param shift    True when shift key is pressed.
            \param control  True when control key is pressed.
            \param meta     True when meta key is pressed.
        */
        using moved_type = void(const position_type& position, bool shift, bool control, bool meta);

        //! The signal type of pressed.
        using moved_signal_type = boost::signals2::signal<moved_type>;

        /*!
            \brief The observer type of wheeled.

            \param delta     A delta.
            \param direction A direction.
            \param shift     True when shift key is pressed.
            \param control   True when control key is pressed.
            \param meta      True when meta key is pressed.
        */
        using wheeled_type =
            void(const delta_type& delta, direction_type direction, bool shift, bool control, bool meta);

        //! The signal type of wheeled.
        using wheeled_signal_type = boost::signals2::signal<wheeled_type>;


        // constructors and destructor

        /*!
            \brief Creates a mouse observer set.
        */
        mouse_observer_set();

        /*!
            \brief Destroys the mouse observer set.
        */
        ~mouse_observer_set();


        // functions

        /*!
            \brief Returns the observer called when a mouse button is clicked.

            \return The observer called when a mouse button is clicked.
        */
        const clicked_signal_type& clicked() const;

        /*!
            \brief Returns the observer called when a mouse button is clicked.

            \return The observer called when a mouse button is clicked.
        */
        clicked_signal_type& clicked();

        /*!
            \brief Returns the observer called when a mouse button is double-clicked.

            \return The observer called when a mouse button is double-clicked.
        */
        const doubleclicked_signal_type& doubleclicked() const;

        /*!
            \brief Returns the observer called when a mouse button is double-clicked.

            \return The observer called when a mouse button is double-clicked.
        */
        doubleclicked_signal_type& doubleclicked();

        /*!
            \brief Returns the observer called when a mouse button is pressed.

            \return The observer called when a mouse button is pressed.
        */
        const pressed_signal_type& pressed() const;

        /*!
            \brief Returns the observer called when a mouse button is pressed.

            \return The observer called when a mouse button is pressed.
        */
        pressed_signal_type& pressed();

        /*!
            \brief Returns the observer called when a mouse button is released.

            \return The observer called when a mouse button is released.
        */
        const released_signal_type& released() const;

        /*!
            \brief Returns the observer called when a mouse button is released.

            \return The observer called when a mouse button is released.
        */
        released_signal_type& released();

        /*!
            \brief Returns the observer called when a mouse is moved.

            \return The observer called when a mouse is moved.
        */
        const moved_signal_type& moved() const;

        /*!
            \brief Returns the observer called when a mouse is moved.

            \return The observer called when a mouse is moved.
        */
        moved_signal_type& moved();

        /*!
            \brief Returns the observer called when a mouse wheel is wheeled.

            \return The observer called when a mouse wheel is wheeled.
        */
        const wheeled_signal_type& wheeled() const;

        /*!
            \brief Returns the observer called when a mouse wheel is wheeled.

            \return The observer called when a mouse wheel is wheeled.
        */
        wheeled_signal_type& wheeled();


    private:
        // types

        class impl;


        // variables


        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
