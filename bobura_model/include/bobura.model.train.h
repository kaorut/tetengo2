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
        \tparam Meterage  A meterage type. It must conform to
                        boost::EqualityComparableConcept<Meterage> and
                        boost::ComparableConcept<Meterage>.
    */
    template <typename Station, typename Meterage>
    class train :
        private boost::equality_comparable<
            train<Station, Meterage>
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
            \brief Creates a train.

            \param station A station.
            \param meterage  Meterage.
        */
        train(
            const station_type& station,
            const meterage_type   meterage
        )
        :
        m_station(station),
        m_meterage(meterage)
        {}

        /*!
            \brief Creates a train.

            \param another Another train object.
        */
        train(const train& another)
        :
        m_station(another.m_station),
        m_meterage(another.m_meterage)
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
            std::swap(m_meterage, another.m_meterage);
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
        bool before(const train& another)
        const
        {
            return m_meterage <= another.m_meterage;
        }


    private:
        // variables

        station_type m_station;

        meterage_type m_meterage;


    };


}}

namespace std
{
    /*!
        \brief Swaps two train objects.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
        \tparam Meterage  A meterage type. It must conform to
                        boost::EqualityComparableConcept<Meterage> and
                        boost::ComparableConcept<Meterage>.

        \param train1 A train object #1.
        \param train2 A train object #2.
    */
    template <typename Station, typename Meterage>
    void swap(
        bobura::model::train<Station, Meterage>&
        train1,
        bobura::model::train<Station, Meterage>&
        train2
    )
    throw ()
    {
        boost::function_requires<bobura::model::StationConcept<Station> >();
        boost::function_requires<boost::EqualityComparableConcept<Meterage> >();
        boost::function_requires<boost::ComparableConcept<Meterage> >();

        train1.swap(train2);
    }


}

#endif
