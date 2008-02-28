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
        \tparam Meterage  A meterage type. It must conform to
                        boost::EqualityComparableConcept<Meterage> and
                        boost::ComparableConcept<Meterage>.
    */
    template <typename Station, typename Meterage>
    class time :
        private boost::equality_comparable<
            time<Station, Meterage>
        >
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Station, bobura::model, StationConcept);
        BOOST_CLASS_REQUIRE(Meterage, boost, EqualityComparableConcept);
        BOOST_CLASS_REQUIRE(Meterage, boost, ComparableConcept);


    public:
        // types

        //! The station type.
        typedef Station station_type;

        //! The meterage type.
        typedef Meterage meterage_type;


        // constructors and destructor

        /*!
            \brief Creates a time.

            \param station A station.
            \param meterage  Meterage.
        */
        time(
            const station_type& station,
            const meterage_type   meterage
        )
        :
        m_station(station),
        m_meterage(meterage)
        {}

        /*!
            \brief Creates a time.

            \param another Another time object.
        */
        time(const time& another)
        :
        m_station(another.m_station),
        m_meterage(another.m_meterage)
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
            std::swap(m_meterage, another.m_meterage);
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

            \param another Another sation_and_meterage object.

            \retval true  When this->meterage() <= another.meterage().
            \retval false Otherwise.
        */
        bool before(const time& another)
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
        \brief Swaps two time objects.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
        \tparam Meterage  A meterage type. It must conform to
                        boost::EqualityComparableConcept<Meterage> and
                        boost::ComparableConcept<Meterage>.

        \param time1 A time object #1.
        \param time2 A time object #2.
    */
    template <typename Station, typename Meterage>
    void swap(
        bobura::model::train_info::time<Station, Meterage>&
        time1,
        bobura::model::train_info::time<Station, Meterage>&
        time2
    )
    throw ()
    {
        boost::function_requires<bobura::model::StationConcept<Station> >();
        boost::function_requires<boost::EqualityComparableConcept<Meterage> >();
        boost::function_requires<boost::ComparableConcept<Meterage> >();

        time1.swap(time2);
    }


}

#endif
