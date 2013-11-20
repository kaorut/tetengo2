/*! \file
    \brief The definition of bobura::model::train_info::stop.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_STOP_H)
#define BOBURA_MODEL_TRAININFO_STOP_H

#include <utility>

#include <boost/operators.hpp>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class template for a train stop.

        \tparam Time   A time type.
        \tparam String A string type.
    */
    template <typename Time, typename String>
    class stop : private boost::equality_comparable<stop<Time, String>>
    {
    public:
        // types

        //! The time type.
        typedef Time time_type;

        //! The string type.
        typedef String string_type;


        // constructors and destructor

        /*!
            \brief Creates a stop.

            \param arrival     An arrival time.
            \param departure   A departure time.
            \param operational Set true for an operational stop.
            \param platform    A platform.
        */
        stop(time_type arrival, time_type departure, const bool operational, string_type platform)
        :
        m_arrival(std::move(arrival)),
        m_departure(std::move(departure)),
        m_operational(operational),
        m_platform(std::move(platform))
        {}


        // functions

        /*!
            \brief Checks whether one stop is equal to another.

            \param one     One stop.
            \param another Another stop.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const stop& one, const stop& another)
        {
            return
                one.m_arrival == another.m_arrival &&
                one.m_departure == another.m_departure &&
                one.m_operational == another.m_operational &&
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
            \brief Checks whether the stop is passing.

            \retval true  When the stop is passing.
            \retval false Otherwise.
        */
        bool passing()
        const
        {
            return m_arrival == time_type::uninitialized() && m_departure == time_type::uninitialized();
        }

        /*!
            \brief Checks whether the stop is operational.

            \retval true  When the stop is operational.
            \retval false Otherwise.
        */
        bool operational()
        const
        {
            return m_operational;
        }

        /*!
            \brief Returns the platform.

            \return The platform.
        */
        const string_type& platform()
        const
        {
            return m_platform;
        }


    private:
        // variables

        time_type m_arrival;

        time_type m_departure;

        bool m_operational;

        string_type m_platform;


    };


}}}


#endif
