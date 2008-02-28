/*! \file
    \brief The definition of bobura::model::train.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAIN_H)
#define BOBURA_MODEL_TRAIN_H

//#include <algorithm>

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

#include "bobura.model.StationConcept.h"


namespace bobura { namespace model
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
    class train :
        private boost::equality_comparable<
            train<Station, Meters>
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
            \brief Creates a train.

            \param station A station.
            \param meters  Meters.
        */
        train(
            const station_type& station,
            const meters_type   meters
        )
        :
        m_station(station),
        m_meters(meters)
        {}

        /*!
            \brief Creates a train.

            \param another Another train object.
        */
        train(const train& another)
        :
        m_station(another.m_station),
        m_meters(another.m_meters)
        {}

        /*!
            \brief Destroys the train.
        */
        virtual ~train()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another train object.

            \param another Another train object.
        */
        void swap(train& another)
        throw ()
        {
            m_station.swap(another.m_station);
            std::swap(m_meters, another.m_meters);
        }

        /*!
            \brief Assigns another train object.

            \param another Another train object.

            \return this object.
        */
        train& operator=(
            const train& another
        )
        {
            train(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther
                   train object.

            \param another Another train object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const train& another)
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
        bool before(const train& another)
        const
        {
            return m_meters <= another.m_meters;
        }


    private:
        // variables

        station_type m_station;

        meters_type m_meters;


    };


}}

namespace std
{
    /*!
        \brief Swaps two train objects.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
        \tparam Meters  A meters type. It must conform to
                        boost::EqualityComparableConcept<Meters> and
                        boost::ComparableConcept<Meters>.

        \param train1 A train object #1.
        \param train2 A train object #2.
    */
    template <typename Station, typename Meters>
    void swap(
        bobura::model::train<Station, Meters>&
        train1,
        bobura::model::train<Station, Meters>&
        train2
    )
    throw ()
    {
        boost::function_requires<bobura::model::StationConcept<Station> >();
        boost::function_requires<boost::EqualityComparableConcept<Meters> >();
        boost::function_requires<boost::ComparableConcept<Meters> >();

        train1.swap(train2);
    }


}

#endif
