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

#include "bobura.model.timetable_info.StationAndMetersConcept.h"


namespace bobura { namespace model
{
    /*!
        \brief The class template for a timetable.

        \tparam StationAndMeters A station and meters type. It must conform to
                                 bobura::model::timetable_info::StationAndMetersConcept<StationAndMeters>.
    */
    template <typename StationAndMeters>
    class timetable
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(
            StationAndMeters,
            bobura::model::timetable_info,
            StationAndMetersConcept
        );


    public:
        // types

        //! The station and meters type.
        typedef StationAndMeters station_and_meters_type;

        //! The stations and meters type.
        typedef std::vector<station_and_meters_type> stations_and_meters_type;


        // constructors and destructor

        /*!
            \brief Creates a timetalble.
        */
        timetable()
        :
        m_stations_and_meters()
        {}

        /*!
            \brief Copies a timetable.

            \param another Another timetable object.
        */
        timetable(const timetable& another)
        :
        m_stations_and_meters(another.m_stations_and_meters)
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
            return m_stations_and_meters == another.m_stations_and_meters;
        }

        const stations_and_meters_type& stations_and_meters()
        const
        {
            return m_stations_and_meters;
        }

        void insert_station_and_meters(
            const typename stations_and_meters_type::const_iterator
                                           position,
            const station_and_meters_type& station_and_meters
        )
        {
            if (
                (
                    position != m_stations_and_meters.begin() &&
                    !(position - 1)->before(station_and_meters)
                ) ||
                (
                    position != m_stations_and_meters.end() &&
                    !station_and_meters.before(*position)
                )
            )
            {
                throw std::invalid_argument("");
            }

            m_stations_and_meters.insert(position, station_and_meters);
        }


    private:
        // variables

        stations_and_meters_type m_stations_and_meters;

    };


}}

namespace std
{
    /*!
        \brief Swaps two timetable objects.

        \tparam StationAndMeters A station and meters type. It must conform to
                                 bobura::model::timetable_info::StationAndMetersConcept<StationAndMeters>.

        \param timetable1 A timetable object #1.
        \param timetable2 A timetable object #2.
    */
    template <typename StationAndMeters>
    void swap(
        bobura::model::timetable<StationAndMeters>& timetable1,
        bobura::model::timetable<StationAndMeters>& timetable2
    )
    throw ()
    {
        boost::function_requires<
            bobura::model::timetable_info::StationAndMetersConcept<
                StationAndMeters
            >
        >();

        timetable1.swap(timetable2);
    }


}


#endif
