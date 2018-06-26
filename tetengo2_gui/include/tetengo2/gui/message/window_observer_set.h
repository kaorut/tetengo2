/*! \file
    \brief The definition of tetengo2::gui::message::window_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_WINDOWOBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_WINDOWOBSERVERSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>


namespace tetengo2::gui::message {
    /*!
        \brief The class for a window observer set.
    */
    class window_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of closing.

            \param cancel Set true to cancel the window closing.
        */
        using closing_type = void(bool& cancel);

        //! The signal type of closing.
        using closing_signal_type = boost::signals2::signal<closing_type>;

        /*!
            \brief The observer type of destroyed.
        */
        using destroyed_type = void();

        //! The signal type of destroyed.
        using destroyed_signal_type = boost::signals2::signal<destroyed_type>;


        // constructors and destructor

        /*!
            \brief Creates a window observer set.
        */
        window_observer_set();

        /*!
            \brief Destroys the window observer set.
        */
        ~window_observer_set();


        // functions

        /*!
            \brief Returns the observer called when a window is closing.

            \return The observer called when a window is closing.
        */
        const closing_signal_type& closing() const;

        /*!
            \brief Returns the observer called when a window is closing.

            \return The observer called when a window is closing.
        */
        closing_signal_type& closing();

        /*!
            \brief Returns the observer called when a window is destroyed.

            \return The observer called when a window is destroyed.
        */
        const destroyed_signal_type& destroyed() const;

        /*!
            \brief Returns the observer called when a window is destroyed.

            \return The observer called when a window is destroyed.
        */
        destroyed_signal_type& destroyed();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
