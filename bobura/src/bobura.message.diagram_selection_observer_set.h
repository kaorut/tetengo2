/*! \file
    \brief The definition of bobura::message::diagram_selection_observer_set.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGE_DIAGRAMSELECTIONOBSERVERSET_H)
#define TETENGO2_MESSAGE_DIAGRAMSELECTIONOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>


namespace bobura { namespace message
{
    /*!
        \brief The class for a diagram selection observer set.
    */
    class diagram_selection_observer_set : private boost::noncopyable
    {
    public:
        // types

        /*!
            \brief The observer type of reset.
        */
        typedef void station_selected_type();

        //! The signal type of reset.
        typedef boost::signals2::signal<station_selected_type> station_selected_signal_type;


        // functions

        /*!
            \brief Returns the observer called when a station is selected.

            \return The observer called when a station is selected.
        */
        const station_selected_signal_type& station_selected()
        const
        {
            return m_station_selected;
        }

        /*!
            \brief Returns the observer called when station is selected.

            \return The observer called when a station is selected.
        */
        station_selected_signal_type& station_selected()
        {
            return m_station_selected;
        }


    private:
        // variables

        station_selected_signal_type m_station_selected;


    };


}}


#endif
