/*! \file
    \brief The definition of bobura::model::train_info::time.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_TIME_H)
#define BOBURA_MODEL_TIMETABLEINFO_TIME_H

//#include <algorithm>

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

#include "bobura.model.StationConcept.h"


namespace bobura { namespace model { namespace train_info
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
    class time :
        private boost::equality_comparable<
            time<Station, Meters>
        >
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
            \brief Creates a time.

            \param station A station.
            \param meters  Meters.
        */
        time(
            const station_type& station,
            const meters_type   meters
        )
        :
        m_station(station),
        m_meters(meters)
        {}

        /*!
            \brief Creates a time.

            \param another Another time object.
        */
        time(const time& another)
        :
        m_station(another.m_station),
        m_meters(another.m_meters)
        {}

        /*!
            \brief Destroys the time.
        */
        virtual ~time()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another time object.

            \param another Another time object.
        */
        void swap(time& another)
        throw ()
        {
            m_station.swap(another.m_station);
            std::swap(m_meters, another.m_meters);
        }

        /*!
            \brief Assigns another time object.

            \param another Another time object.

            \return this object.
        */
        time& operator=(
            const time& another
        )
        {
            time(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther
                   time object.

            \param another Another time object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const time& another)
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
        bool before(const time& another)
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
        \brief Swaps two time objects.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
        \tparam Meters  A meters type. It must conform to
                        boost::EqualityComparableConcept<Meters> and
                        boost::ComparableConcept<Meters>.

        \param time1 A time object #1.
        \param time2 A time object #2.
    */
    template <typename Station, typename Meters>
    void swap(
        bobura::model::train_info::time<Station, Meters>&
        time1,
        bobura::model::train_info::time<Station, Meters>&
        time2
    )
    throw ()
    {
        boost::function_requires<bobura::model::StationConcept<Station> >();
        boost::function_requires<boost::EqualityComparableConcept<Meters> >();
        boost::function_requires<boost::ComparableConcept<Meters> >();

        time1.swap(time2);
    }


}

#endif
