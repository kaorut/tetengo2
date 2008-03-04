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

#include "bobura.model.timetable_info.StationLocationConcept.h"


namespace bobura { namespace model
{
    /*!
        \brief The class template for a timetable.

        \tparam StationLocation A station location type. It must conform to
                                bobura::model::timetable_info::StationLocationConcept<StationLocation>.
    */
    template <typename StationLocation>
    class timetable :
        private boost::equality_comparable<timetable<StationLocation> >
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(
            StationLocation,
            bobura::model::timetable_info,
            StationLocationConcept
        );


    public:
        // types

        //! The station location type.
        typedef StationLocation station_location_type;

        //! The station locations type.
        typedef std::vector<station_location_type> station_locations_type;


        // constructors and destructor

        /*!
            \brief Creates a timetalble.
        */
        timetable()
        :
        m_station_locations()
        {}

        /*!
            \brief Copies a timetable.

            \param another Another timetable object.
        */
        timetable(const timetable& another)
        :
        m_station_locations(another.m_station_locations)
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
            return m_station_locations == another.m_station_locations;
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

            \param begin A begin position where the station locations are
                         removed.
            \param end   A end position where the station locations are
                         removed.
        */
        void erase_station_locations(
            const typename station_locations_type::const_iterator begin,
            const typename station_locations_type::const_iterator end
        )
        {
            m_station_locations.erase(begin, end);
        }


    private:
        // variables

        station_locations_type m_station_locations;


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
                                bobura::model::timetable_info::StationLocationConcept<StationLocation>.

        \param timetable1 A timetable object #1.
        \param timetable2 A timetable object #2.
    */
    template <typename StationLocation>
    void swap(
        bobura::model::timetable<StationLocation>& timetable1,
        bobura::model::timetable<StationLocation>& timetable2
    )
    throw ()
    {
        boost::function_requires<
            bobura::model::timetable_info::StationLocationConcept<
                StationLocation
            >
        >();

        timetable1.swap(timetable2);
    }


}


#endif
