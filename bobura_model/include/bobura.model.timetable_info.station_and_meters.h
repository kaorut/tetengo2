/*! \file
    \brief The definition of bobura::model::timetable_info::station_and_meters.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_STATIONANDMETERS_H)
#define BOBURA_MODEL_TIMETABLEINFO_STATIONANDMETERS_H

#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

#include <tetengo2.SizeConcept.h>

#include "bobura.model.StationConcept.h"


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The class for a station and meters.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
        \tparam Size    A size type. It must conform to
                        tetengo2::SizeConcept<Size>.
    */
    template <typename Station, typename Size>
    class station_and_meters :
        private boost::equality_comparable<station_and_meters<Station, Size> >
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Station, bobura::model, StationConcept);
        BOOST_CLASS_REQUIRE(Size, tetengo2, SizeConcept);


    public:
        // types

        //! The station type.
        typedef Station station_type;

        //! The size type.
        typedef Size size_type;


        // constructors and destructor

        /*!
            \brief Creates a station_and_meters.

            \param station A station.
            \param meters  Meters.
        */
        station_and_meters(
            const station_type& station,
            const size_type     meters
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

        const station_type& station()
        const
        {
            return m_station;
        }

        station_type& station()
        {
            return m_station;
        }

        size_type meters()
        const
        {
            return m_meters;
        }


    private:
        // variables

        station_type m_station;

        size_type m_meters;


    };


}}}

namespace std
{
    /*!
        \brief Swaps two station_and_meters objects.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
        \tparam Size    A size type. It must conform to
                        tetengo2::SizeConcept<Size>.

        \param station_and_meters1 A station_and_meters object #1.
        \param station_and_meters2 A station_and_meters object #2.
    */
    template <typename Station, typename Size>
    void swap(
        bobura::model::timetable_info::station_and_meters<Station, Size>&
        station_and_meters1,
        bobura::model::timetable_info::station_and_meters<Station, Size>&
        station_and_meters2
    )
    throw ()
    {
        station_and_meters1.swap(station_and_meters2);
    }


}

#endif
