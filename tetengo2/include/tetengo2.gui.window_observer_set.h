/*! \file
    \brief The definition of tetengo2::gui::window_observer_set.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WINDOWOBSERVERSET_H)
#define TETENGO2_GUI_WINDOWOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace tetengo2 { namespace gui
{
    /*!
        \brief The class for a window observer set.
    */
    class window_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of destroyed.
        */
        typedef void destroyed_type();

        //! The signal type of destroyed.
        typedef boost::signals2::signal<destroyed_type> destroyed_signal_type;


        // functions

        /*!
            \brief Returns the observer called when a window is destroyed.

            \return The observer called when a window is destroyed.
        */
        const destroyed_signal_type& destroyed()
        const
        {
            return m_destroyed;
        }

        /*!
            \brief Returns the observer called when a window is destroyed.

            \return The observer called when a window is destroyed.
        */
        destroyed_signal_type& destroyed()
        {
            return m_destroyed;
        }


    private:
        // variables

        destroyed_signal_type m_destroyed;


    };


}}

#endif
