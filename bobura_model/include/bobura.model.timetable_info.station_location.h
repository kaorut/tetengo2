/*! \file
    \brief The definition of bobura::model::timetable_info::station_location.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_STATIONLOCATION_H)
#define BOBURA_MODEL_TIMETABLEINFO_STATIONLOCATION_H

//#include <algorithm>

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

#include "bobura.model.StationConcept.h"


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The class for a station location.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
        \tparam Meters  A meters type. It must conform to
                        boost::EqualityComparableConcept<Meters> and
                        boost::ComparableConcept<Meters>.
    */
    template <typename Station, typename Meters>
    class station_location :
        private boost::equality_comparable<station_location<Station, Meters> >
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Station, bobura::model, StationConcept);
        BOOST_CLASS_REQUIRE(Meters, boost, EqualityComparableConcept);
        BOOST_CLASS_REQUIRE(Meters, boost, ComparableConcept);


    public:
        // types

        //! The station type.
        typedef Station station_type;

        //! The meters type.
        typedef Meters meters_type;


        // constructors and destructor

        /*!
            \brief Creates a station_location.

            \param station A station.
            \param meters  Meters.
        */
        station_location(
            const station_type& station,
            const meters_type   meters
        )
        :
        m_station(station),
        m_meters(meters)
        {}

        /*!
            \brief Creates a station_location.

            \param another Another station_location object.
        */
        station_location(const station_location& another)
        :
        m_station(another.m_station),
        m_meters(another.m_meters)
        {}

        /*!
            \brief Destroys the station_location.
        */
        ~station_location()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another station_location object.

            \param another Another station_location object.
        */
        void swap(station_location& another)
        throw ()
        {
            m_station.swap(another.m_station);
            std::swap(m_meters, another.m_meters);
        }

        /*!
            \brief Assigns another station_location object.

            \param another Another station_location object.

            \return this object.
        */
        station_location& operator=(const station_location& another)
        {
            station_location(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther
                   station_location object.

            \param another Another station_location object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const station_location& another)
        const
        {
            return m_station == another.m_station &&
                   m_meters == another.m_meters;
        }

        /*!
            \brief Returns the station.

            \return The station.
        */
        const station_type& station()
        const
        {
            return m_station;
        }

        /*!
            \brief Returns the meters.

            \return The meters.
        */
        meters_type meters()
        const
        {
            return m_meters;
        }

        /*!
            \brief Checks this station is located before another.

            \param another Another sation_and_meters object.

            \retval true  When this->meters() <= another.meters().
            \retval false Otherwise.
        */
        bool before(const station_location& another)
        const
        {
            return m_meters <= another.m_meters;
        }


    private:
        // variables

        station_type m_station;

        meters_type m_meters;


    };


}}}

namespace std
{
    /*!
        \brief Swaps two station_location objects.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
        \tparam Meters  A meters type. It must conform to
                        boost::EqualityComparableConcept<Meters> and
                        boost::ComparableConcept<Meters>.

        \param station_location1 A station_location object #1.
        \param station_location2 A station_location object #2.
    */
    template <typename Station, typename Meters>
    void swap(
        bobura::model::timetable_info::station_location<Station, Meters>&
        station_location1,
        bobura::model::timetable_info::station_location<Station, Meters>&
        station_location2
    )
    throw ()
    {
        boost::function_requires<bobura::model::StationConcept<Station> >();
        boost::function_requires<boost::EqualityComparableConcept<Meters> >();
        boost::function_requires<boost::ComparableConcept<Meters> >();

        station_location1.swap(station_location2);
    }


}

#endif
