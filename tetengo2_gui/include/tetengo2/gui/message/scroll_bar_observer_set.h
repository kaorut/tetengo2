/*! \file
    \brief The definition of tetengo2::gui::message::scroll_bar_observer_set.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MESSAGE_SCROLLBAROBSERVERSET_H)
#define TETENGO2_GUI_MESSAGE_SCROLLBAROBSERVERSET_H

#include <boost/core/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui { namespace message
{
    /*!
        \brief The class template for a scroll bar observer set.

        \tparam Size A size type.
    */
    template <typename Size>
    class scroll_bar_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        /*!
            \brief The observer type of scrolling.

            \param new_position A new position.
        */
        using scrolling_type = void (typename scroll_bar_observer_set::size_type new_position);

        //! The signal type of scrolling.
        using scrolling_signal_type = boost::signals2::signal<scrolling_type>;

        /*!
            \brief The observer type of scrolled.

            \param new_position A new position.
        */
        using scrolled_type = void (typename scroll_bar_observer_set::size_type new_position);

        //! The signal type of scrolled.
        using scrolled_signal_type = boost::signals2::signal<scrolled_type>;


        // functions

        /*!
            \brief Returns the observer called when a scroll bar is being scrolled.

            \return The observer called when a scroll bar is being scrolled.
        */
        const scrolled_signal_type& scrolling()
        const
        {
            return m_scrolling;
        }

        /*!
            \brief Returns the observer called when a scroll bar is being scrolled.

            \return The observer called when a scroll bar is being scrolled.
        */
        scrolled_signal_type& scrolling()
        {
            return m_scrolling;
        }

        /*!
            \brief Returns the observer called when a scroll bar is scrolled.

            \return The observer called when a scroll bar is scrolled.
        */
        const scrolled_signal_type& scrolled()
        const
        {
            return m_scrolled;
        }

        /*!
            \brief Returns the observer called when a scroll bar is scrolled.

            \return The observer called when a scroll bar is scrolled.
        */
        scrolled_signal_type& scrolled()
        {
            return m_scrolled;
        }


    private:
        // variables

        scrolling_signal_type m_scrolling;

        scrolled_signal_type m_scrolled;


    };


}}}


#endif
