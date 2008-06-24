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
#include "bobura.model.timetable_info.MeterageConcept.h"


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The class for a station location.

        \tparam Station  A station type. It must conform to
                         bobura::model::StationConcept<Station>.
        \tparam Meterage A meterage type. It must conform to
                         bobura::model::timetable_info::MeterageConcept<Meterage>.
    */
    template <typename Station, typename Meterage>
    class station_location :
        private boost::equality_comparable<station_location<Station, Meterage> >
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Station, bobura::model, StationConcept);
        BOOST_CLASS_REQUIRE(
            Meterage, bobura::model::timetable_info, MeterageConcept
        );


    public:
        // types

        //! The station type.
        typedef Station station_type;

        //! The meterage type.
        typedef Meterage meterage_type;


        // constructors and destructor

        /*!
            \brief Creates a station_location.

            \param station  A station.
            \param meterage A meterage.
        */
        station_location(
            const station_type& station,
            const meterage_type meterage
        )
        :
        m_station(station),
        m_meterage(meterage)
        {}

        /*!
            \brief Copies a station_location.

            \param another Another station_location object.
        */
        station_location(const station_location& another)
        :
        m_station(another.m_station),
        m_meterage(another.m_meterage)
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
            std::swap(m_meterage, another.m_meterage);
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
                   m_meterage == another.m_meterage;
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
            \brief Returns the meterage.

            \return The meterage.
        */
        meterage_type meterage()
        const
        {
            return m_meterage;
        }

        /*!
            \brief Checks this station is located before another.

            \param another Another sation_location object.

            \retval true  When this->meterage() <= another.meterage().
            \retval false Otherwise.
        */
        bool before(const station_location& another)
        const
        {
            return m_meterage <= another.m_meterage;
        }


    private:
        // variables

        station_type m_station;

        meterage_type m_meterage;


    };


}}}

namespace std
{
    /*!
        \brief Swaps two station_location objects.

        \tparam Station  A station type. It must conform to
                         bobura::model::StationConcept<Station>.
        \tparam Meterage A meterage type. It must conform to
                         bobura::model::timetable_info::MeterageConcept<Meterage>.

        \param station_location1 A station_location object #1.
        \param station_location2 A station_location object #2.
    */
    template <typename Station, typename Meterage>
    void swap(
        bobura::model::timetable_info::station_location<Station, Meterage>&
        station_location1,
        bobura::model::timetable_info::station_location<Station, Meterage>&
        station_location2
    )
    throw ()
    {
        BOOST_CONCEPT_ASSERT((bobura::model::StationConcept<Station>));
        BOOST_CONCEPT_ASSERT((
            bobura::model::timetable_info::MeterageConcept<Meterage>
        ));

        station_location1.swap(station_location2);
    }


}

#endif
