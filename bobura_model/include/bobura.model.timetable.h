/*! \file
    \brief The definition of bobura::model::timetable.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLE_H)
#define BOBURA_MODEL_TIMETABLE_H

#include <stdexcept>
#include <vector>

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>
#include <boost/utility.hpp>

#include "concept_bobura.model.Train.h"
#include "concept_bobura.model.timetable_info.StationLocation.h"


namespace bobura { namespace model
{
    /*!
        \brief The class template for a timetable.

        \tparam StationLocation A station location type. It must conform to
                                concept_bobura::model::timetable_info::StationLocation<StationLocation>.
        \tparam Train           A train type. It must conform to
                                concept_bobura::model::Train<Train>.
    */
    template <typename StationLocation, typename Train>
    class timetable :
        private boost::equality_comparable<timetable<StationLocation, Train> >
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((
            concept_bobura::model::timetable_info::StationLocation<
                StationLocation
            >
        ));
        BOOST_CONCEPT_ASSERT((concept_bobura::model::Train<Train>));


    public:
        // types

        //! The station location type.
        typedef StationLocation station_location_type;

        //! The station locations type.
        typedef std::vector<station_location_type> station_locations_type;

        //! The train type.
        typedef Train train_type;

        //! The trains type.
        typedef std::vector<train_type> trains_type;


        // constructors and destructor

        /*!
            \brief Creates a timetalble.
        */
        timetable()
        :
        m_station_locations(),
        m_trains()
        {}

        /*!
            \brief Copies a timetable.

            \param another Another timetable object.
        */
        timetable(const timetable& another)
        :
        m_station_locations(another.m_station_locations),
        m_trains(another.m_trains)
        {}

        /*!
            \brief Destroys the timetable.
        */
        ~timetable()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another timetable object.

            \param another Another timetable object.
        */
        void swap(timetable& another)
        throw ()
        {
            m_station_locations.swap(another.m_station_locations);
            m_trains.swap(another.m_trains);
        }

        /*!
            \brief Assigns another timetable object.

            \param another Another timetable object.

            \return this object.
        */
        timetable& operator=(const timetable& another)
        {
            timetable(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther timetable object.

            \param another Another timetable object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const timetable& another)
        const
        {
            return m_station_locations == another.m_station_locations &&
                m_trains == another.m_trains;
        }

        /*!
            \brief Returns the station locations.

            \return The station locations.
        */
        const station_locations_type& station_locations()
        const
        {
            return m_station_locations;
        }

        /*!
            \brief Inserts a station location.

            After the insertion, the station locations must be sequenced in
            ascending order.

            \param position         A position where a station location is
                                    inserted.
            \param station_location A station location.

            \throw std::invalid_argument When the station locations are not
                                         sequenced in ascending order after
                                         the insertion.
        */
        void insert_station_location(
            const typename station_locations_type::const_iterator
                                         position,
            const station_location_type& station_location
        )
        {
            if (!can_insert_to(position, station_location))
            {
                throw std::invalid_argument(
                    "The insertion position is invalid."
                );
            }

            m_station_locations.insert(position, station_location);
        }

        /*!
            \brief Erases the station locations.

            \param first A first iterator among the erased station locations.
            \param last  A last iterator among the erased station locations.
        */
        void erase_station_locations(
            const typename station_locations_type::const_iterator first,
            const typename station_locations_type::const_iterator last
        )
        {
            m_station_locations.erase(first, last);
        }

        /*!
            \brief Returns the trains.

            \return The trains
        */
        const trains_type& trains()
        const
        {
            return m_trains;
        }

        /*!
            \brief Inserts a train.

            \param position  A position where a train is inserted.
            \param train     A train.
        */
        void insert_train(
            const typename trains_type::const_iterator position,
            const train_type&                          train
        )
        {
            m_trains.insert(position, train);
        }

        /*!
            \brief Erases the trains.

            \param first A first iterator among the erased trains.
            \param last  A last iterator among the erased trains.
        */
        void erase_trains(
            const typename trains_type::const_iterator first,
            const typename trains_type::const_iterator last
        )
        {
            m_trains.erase(first, last);
        }


    private:
        // variables

        station_locations_type m_station_locations;

        trains_type m_trains;


        // functions

        bool can_insert_to(
            const typename station_locations_type::const_iterator
                                         position,
            const station_location_type& station_location
        )
        const
        {
            if (
                position != m_station_locations.begin() &&
                !boost::prior(position)->before(station_location)
            )
            {
                return false;
            }
            
            if (
                position != m_station_locations.end() &&
                !station_location.before(*position)
            )
            {
                return false;
            }

            return true;
        }


    };


}}

namespace std
{
    /*!
        \brief Swaps two timetable objects.

        \tparam StationLocation A station location type. It must conform to
                                concept_bobura::model::timetable_info::StationLocation<StationLocation>.
        \tparam Train           A train type. It must conform to
                                concept_bobura::model::Train<Train>.

        \param timetable1 A timetable object #1.
        \param timetable2 A timetable object #2.
    */
    template <typename StationLocation, typename Train>
    void swap(
        bobura::model::timetable<StationLocation, Train>& timetable1,
        bobura::model::timetable<StationLocation, Train>& timetable2
    )
    throw ()
    {
        BOOST_CONCEPT_ASSERT((
            concept_bobura::model::timetable_info::StationLocation<
                StationLocation
            >
        ));
        BOOST_CONCEPT_ASSERT((concept_bobura::model::Train<Train>));

        timetable1.swap(timetable2);
    }


}


#endif
