/*! \file
    \brief The definition of bobura::model::train_info::stop.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_STOP_H)
#define BOBURA_MODEL_TRAININFO_STOP_H

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

#include <concept_tetengo2.String.h>
#include <tetengo2.assignable.h>

#include "concept_bobura.model.train_info.Time.h"


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class for a train stop.

        \tparam Time     A time type. It must conform to
                         concept_bobura::model::train_info::Time<Time>.
        \tparam Platform A string type. It must conform to
                         concept_tetengo2::String<Platform>.
    */
    template <typename Time, typename Platform>
    class stop :
        public tetengo2::assignable<stop<Time, Platform> >,
        private boost::equality_comparable<stop<Time, Platform> >
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_bobura::model::train_info::Time<Time>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<Platform>));


    public:
        // types

        //! The time type.
        typedef Time time_type;

        //! The platform type.
        typedef Platform platform_type;


        // constructors and destructor

        /*!
            \brief Creates a stop.

            \param arrival   An arrival time.
            \param departure A departure time.
            \param platform  A platform.
        */
        stop(
            const time_type&     arrival,
            const time_type&     departure,
            const platform_type& platform
        )
        :
        m_arrival(arrival),
        m_departure(departure),
        m_platform(platform)
        {}

        /*!
            \brief Copies a stop.

            \param another Another stop object.
        */
        stop(const stop& another)
        :
        m_arrival(another.m_arrival),
        m_departure(another.m_departure),
        m_platform(another.m_platform)
        {}

        /*!
            \brief Destroys the stop.
        */
        ~stop()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another stop object.

            \param another Another stop object.
        */
        void swap(stop& another)
        throw ()
        {
            m_arrival.swap(another.m_arrival);
            m_departure.swap(another.m_departure);
            m_platform.swap(another.m_platform);
        }

        /*!
            \brief Assigns another stop object.

            \param another Another stop object.

            \return this object.
        */
        stop& operator=(const stop& another)
        {
            return assign(another);
        }

        /*!
            \brief Checks whether this is equal to anther stop object.

            \param another Another stop object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const stop& another)
        const
        {
            return m_arrival == another.m_arrival &&
                m_departure == another.m_departure &&
                m_platform == another.m_platform;
        }

        /*!
            \brief Returns the arrival time.

            \return The arrival time.
        */
        const time_type& arrival()
        const
        {
            return m_arrival;
        }

        /*!
            \brief Returns the departure time.

            \return The departure time.
        */
        const time_type& departure()
        const
        {
            return m_departure;
        }

        /*!
            \brief Returns the platform.

            \return The platform.
        */
        const platform_type& platform()
        const
        {
            return m_platform;
        }


    private:
        // variables

        time_type m_arrival;

        time_type m_departure;

        platform_type m_platform;


    };


}}}

namespace std
{
    /*!
        \brief Swaps two stop objects.

        \tparam Time     A time type. It must conform to
                         concept_bobura::model::train_info::Time<Time>.
        \tparam Platform A platform type. It must conform to
                         concept_tetengo2::String<Platform>.

        \param stop1 A stop object #1.
        \param stop2 A stop object #2.
    */
    template <typename Time, typename Platform>
    void swap(
        bobura::model::train_info::stop<Time, Platform>& stop1,
        bobura::model::train_info::stop<Time, Platform>& stop2
    )
    throw ()
    {
        BOOST_CONCEPT_ASSERT((concept_bobura::model::train_info::Time<Time>));
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<Platform>));

        stop1.swap(stop2);
    }


}

#endif
