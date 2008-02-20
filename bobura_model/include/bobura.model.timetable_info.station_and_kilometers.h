/*! \file
    \brief The definition of bobura::model::timetable_info::station_and_kilometers.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_STATIONANDKILOMETERS_H)
#define BOBURA_MODEL_TIMETABLEINFO_STATIONANDKILOMETERS_H

#include <boost/concept_check.hpp>

#include <tetengo2.SizeConcept.h>

#include "bobura.model.StationConcept.h"


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The class for a station and kilometers.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
        \tparam Size    A size type. It must conform to
                        tetengo2::SizeConcept<Size>.
    */
    template <typename Station, typename Size>
    class station_and_kilometers
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
            \brief Creates a station_and_kilometers.

            \param station    A station.
            \param kilometers Kilometers.
        */
        station_and_kilometers(
            const station_type& station,
            const size_type     kilometers
        )
        :
        m_station(station),
        m_kilometers(kilometers)
        {}

        /*!
            \brief Creates a station_and_kilometers.

            \param anotherAnother station_and_kilometers object.
        */
        station_and_kilometers(const station_and_kilometers& another)
        :
        m_station(another.m_station),
        m_kilometers(another.m_kilometers)
        {}

        /*!
            \brief Destroys the station_and_kilometers.
        */
        virtual ~station_and_kilometers()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another station_and_kilometers
                   object.

            \param another Another station_and_kilometers object.
        */
        void swap(station_and_kilometers& another)
        throw ()
        {
            m_station.swap(another.m_station);
            std::swap(m_kilometers, another.m_kilometers);
        }

        /*!
            \brief Assigns another station_and_kilometers object.

            \param another Another station_and_kilometers object.

            \return this object.
        */
        station_and_kilometers& operator=(
            const station_and_kilometers& another
        )
        {
            station_and_kilometers(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther
                   station_and_kilometers object.

            \param another Another station_and_kilometers object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const station_and_kilometers& another)
        const
        {
            return m_station == another.m_station &&
                   m_kilometers == another.m_kilometers;
        }

        /*!
            \brief Checks whether this is not equal to anther
                   station_and_kilometers object.

            \param another Another station_and_kilometers object.

            \retval true  When this is not equal to another.
            \retval false Otherwise.
        */
        bool operator!=(const station_and_kilometers& another)
        const
        {
            return !(*this == another);
        }


    private:
        // variables

        station_type m_station;

        size_type m_kilometers;


    };


}}}

#endif
