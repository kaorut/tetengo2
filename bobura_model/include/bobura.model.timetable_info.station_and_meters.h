/*! \file
    \brief The definition of bobura::model::timetable_info::station_and_meters.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_STATIONANDMETERS_H)
#define BOBURA_MODEL_TIMETABLEINFO_STATIONANDMETERS_H

#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

#include "bobura.model.StationConcept.h"


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The class for a station and meters.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
        \tparam Meters  A meters type. It must conform to
                        boost::EqualityComparableConcept<Meters> and
                        boost::LessThanComparableConcept<Meters>.
    */
    template <typename Station, typename Meters>
    class station_and_meters :
        private boost::equality_comparable<station_and_meters<Station, Meters> >
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Station, bobura::model, StationConcept);
        BOOST_CLASS_REQUIRE(Meters, boost, EqualityComparableConcept);
        BOOST_CLASS_REQUIRE(Meters, boost, LessThanComparableConcept);


    public:
        // types

        //! The station type.
        typedef Station station_type;

        //! The meters type.
        typedef Meters meters_type;


        // constructors and destructor

        /*!
            \brief Creates a station_and_meters.

            \param station A station.
            \param meters  Meters.
        */
        station_and_meters(
            const station_type& station,
            const meters_type   meters
        )
        :
        m_station(station),
        m_meters(meters)
        {}

        /*!
            \brief Creates a station_and_meters.

            \param anotherAnother station_and_meters object.
        */
        station_and_meters(const station_and_meters& another)
        :
        m_station(another.m_station),
        m_meters(another.m_meters)
        {}

        /*!
            \brief Destroys the station_and_meters.
        */
        virtual ~station_and_meters()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another station_and_meters object.

            \param another Another station_and_meters object.
        */
        void swap(station_and_meters& another)
        throw ()
        {
            m_station.swap(another.m_station);
            std::swap(m_meters, another.m_meters);
        }

        /*!
            \brief Assigns another station_and_meters object.

            \param another Another station_and_meters object.

            \return this object.
        */
        station_and_meters& operator=(
            const station_and_meters& another
        )
        {
            station_and_meters(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther
                   station_and_meters object.

            \param another Another station_and_meters object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const station_and_meters& another)
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

            \retval true  When this->meters() <= another.meters().
            \retval false Otherwise.
        */
        bool before(const station_and_meters& another)
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
        \brief Swaps two station_and_meters objects.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
        \tparam Meters  A meters type. It must conform to
                        tetengo2::MetersConcept<Meters>.

        \param station_and_meters1 A station_and_meters object #1.
        \param station_and_meters2 A station_and_meters object #2.
    */
    template <typename Station, typename Meters>
    void swap(
        bobura::model::timetable_info::station_and_meters<Station, Meters>&
        station_and_meters1,
        bobura::model::timetable_info::station_and_meters<Station, Meters>&
        station_and_meters2
    )
    throw ()
    {
        station_and_meters1.swap(station_and_meters2);
    }


}

#endif
