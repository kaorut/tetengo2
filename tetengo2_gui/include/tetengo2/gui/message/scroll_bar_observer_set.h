/*! \file
    \brief The definition of tetengo2::gui::message::scroll_bar_observer_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_SCROLLBAROBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_SCROLLBAROBSERVERSET_H

#include <memory>

#include <boost/core/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include <tetengo2/type_list.h>


namespace tetengo2::gui::message {
    /*!
        \brief The class for a scroll bar observer set.
    */
    class scroll_bar_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = tetengo2::type_list::size_type;

        /*!
            \brief The observer type of scrolling.

            \param new_position A new position.
        */
        using scrolling_type = void(typename scroll_bar_observer_set::size_type new_position);

        //! The signal type of scrolling.
        using scrolling_signal_type = boost::signals2::signal<scrolling_type>;

        /*!
            \brief The observer type of scrolled.

            \param new_position A new position.
        */
        using scrolled_type = void(typename scroll_bar_observer_set::size_type new_position);

        //! The signal type of scrolled.
        using scrolled_signal_type = boost::signals2::signal<scrolled_type>;


        // constructors and destructor

        /*!
            \brief Creates a scroll bar observer set.
        */
        scroll_bar_observer_set();

        /*!
            \brief Destroys the scroll bar_observer set.
        */
        ~scroll_bar_observer_set();


        // functions

        /*!
            \brief Returns the observer called when a scroll bar is being scrolled.

            \return The observer called when a scroll bar is being scrolled.
        */
        const scrolled_signal_type& scrolling() const;

        /*!
            \brief Returns the observer called when a scroll bar is being scrolled.

            \return The observer called when a scroll bar is being scrolled.
        */
        scrolled_signal_type& scrolling();

        /*!
            \brief Returns the observer called when a scroll bar is scrolled.

            \return The observer called when a scroll bar is scrolled.
        */
        const scrolled_signal_type& scrolled() const;

        /*!
            \brief Returns the observer called when a scroll bar is scrolled.

            \return The observer called when a scroll bar is scrolled.
        */
        scrolled_signal_type& scrolled();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;
    };
}


#endif
