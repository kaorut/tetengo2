/*! \file
    \brief The definition of bobura::message::diagram_selection_observer_set.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGE_DIAGRAMSELECTIONOBSERVERSET_H)
#define TETENGO2_MESSAGE_DIAGRAMSELECTIONOBSERVERSET_H

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/signals2.hpp>


namespace bobura { namespace message
{
    /*!
        \brief The class template for a diagram selection observer set.

        \tparam Station A station type.
        \tparam Train   A train type.
    */
    template <typename Station, typename Train>
    class diagram_selection_observer_set : private boost::noncopyable
    {
    public:
        // types

        //! The station type.
        typedef Station station_type;

        //! The train type.
        typedef Train train_type;

        //! The stop index type.
        typedef typename train_type::stops_type::size_type stop_index_type;

        /*!
            \brief The observer type of station selection.

            \param station A station.
        */
        typedef void station_selected_type(const station_type& station);

        //! The signal type of station selection.
        typedef boost::signals2::signal<station_selected_type> station_selected_signal_type;

        /*!
            \brief The observer type of train selection.

            \param train                A train.
            \param departure_stop_index A departure stop index. Or boost::none when a whole train is selected.
        */
        typedef void train_selected_type(
            const train_type&                       train,
            const boost::optional<stop_index_type>& departure_stop_index
        );

        //! The signal type of train selection.
        typedef boost::signals2::signal<train_selected_type> train_selected_signal_type;

        /*!
            \brief The observer type of unselection.
        */
        typedef void unselected_all_type();

        //! The signal type of unselection.
        typedef boost::signals2::signal<unselected_all_type> unselected_all_signal_type;


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

        /*!
            \brief Returns the observer called when a train is selected.

            \return The observer called when a train is selected.
        */
        const train_selected_signal_type& train_selected()
        const
        {
            return m_train_selected;
        }

        /*!
            \brief Returns the observer called when a train is selected.

            \return The observer called when a train is selected.
        */
        train_selected_signal_type& train_selected()
        {
            return m_train_selected;
        }

        /*!
            \brief Returns the observer called when all the items are unselected.

            \return The observer called when all the items are unselected.
        */
        const unselected_all_signal_type& unselected_all()
        const
        {
            return m_unselected_all;
        }

        /*!
            \brief Returns the observer called when all the items are unselected.

            \return The observer called when all the items are unselected.
        */
        unselected_all_signal_type& unselected_all()
        {
            return m_unselected_all;
        }


    private:
        // variables

        station_selected_signal_type m_station_selected;

        train_selected_signal_type m_train_selected;

        unselected_all_signal_type m_unselected_all;


    };


}}


#endif
