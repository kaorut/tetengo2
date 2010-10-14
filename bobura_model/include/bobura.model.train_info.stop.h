/*! \file
    \brief The definition of bobura::model::train_info::stop.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_STOP_H)
#define BOBURA_MODEL_TRAININFO_STOP_H

#include <boost/operators.hpp>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class for a train stop.

        \tparam Time     A time type.
        \tparam Platform A string type.
    */
    template <typename Time, typename Platform>
    class stop :
        private boost::equality_comparable<stop<Time, Platform>>
    {
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


        // functions

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
