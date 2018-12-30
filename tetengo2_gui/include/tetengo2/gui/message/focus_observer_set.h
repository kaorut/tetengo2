/*! \file
    \brief The definition of tetengo2::gui::message::focus_observer_set.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_FOCUSOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_FOCUSOBSERVERSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2::gui::message {
    /*!
        \brief The class for a focus observer set.
    */
    class focus_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of got-focus.
        */
        using got_focus_type = void();

        //! The signal type of got-focus.
        using got_focus_signal_type = boost::signals2::signal<got_focus_type>;

        /*!
            \brief The observer type of lost-focus.
        */
        using lost_focus_type = void();

        //! The signal type of lost-focus.
        using lost_focus_signal_type = boost::signals2::signal<lost_focus_type>;


        // constructors and destructor

        /*!
            \brief Creates a focus observer set.
        */
        focus_observer_set();

        /*!
            \brief Destroys the focus observer set.
        */
        ~focus_observer_set();


        // functions

        /*!
            \brief Returns the observer called when a widget got a focus.

            \return The observer called when a widget got a focus.
        */
        const got_focus_signal_type& got_focus() const;

        /*!
            \brief Returns the observer called when a widget got a focus.

            \return The observer called when a widget got a focus.
        */
        got_focus_signal_type& got_focus();

        /*!
            \brief Returns the observer called when a widget lost a focus.

            \return The observer called when a widget lost a focus.
        */
        const lost_focus_signal_type& lost_focus() const;

        /*!
            \brief Returns the observer called when a widget lost a focus.

            \return The observer called when a widget lost a focus.
        */
        lost_focus_signal_type& lost_focus();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
