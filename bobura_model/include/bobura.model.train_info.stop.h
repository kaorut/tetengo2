/*! \file
    \brief The definition of bobura::model::train_info::stop.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_STOP_H)
#define BOBURA_MODEL_TRAININFO_STOP_H

#include <boost/operators.hpp>
#include <boost/swap.hpp>

#include <tetengo2.assignable.h>
#include <tetengo2.cpp0x_keyword.h>
#include <tetengo2.swappable.h>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class for a train stop.

        \tparam Time     A time type.
        \tparam Platform A string type.
    */
    template <typename Time, typename Platform>
    class stop :
        public tetengo2::assignable<stop<Time, Platform>>,
        private tetengo2::swappable<stop<Time, Platform>>,
        private boost::equality_comparable<stop<Time, Platform>>
    {
    public:
        // types

        //! \return The time type.
        typedef Time time_type;

        //! \return The platform type.
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

            \param another Another stop.
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
        TETENGO2_NOEXCEPT
        {}


        // functions

        /*!
            \brief Swaps the members with another stop.

            \param another Another stop.
        */
        void swap(stop& another)
        TETENGO2_NOEXCEPT
        {
            boost::swap(m_arrival, another.m_arrival);
            boost::swap(m_departure, another.m_departure);
            boost::swap(m_platform, another.m_platform);
        }

        /*!
            \brief Assigns another stop.

            \param another Another stop.

            \return This object.
        */
        stop& operator=(const stop& another)
        {
            return assign(another);
        }

        /*!
            \brief Checks whether one stop is equal to anther.

            \param one     One stop.
            \param another Another stop.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const stop& one, const stop& another)
        {
            return one.m_arrival == another.m_arrival &&
                one.m_departure == another.m_departure &&
                one.m_platform == another.m_platform;
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


#endif
