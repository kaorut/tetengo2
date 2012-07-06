/*! \file
    \brief The definition of bobura::model::train_info::stop.

    Copyright (C) 2007-2012 kaoru

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

            \tparam AT A time type.
            \tparam S  A string type.

            \param arrival   An arrival time.
            \param departure A departure time.
            \param platform  A platform.
        */
        template <typename AT, typename DT, typename S>
        stop(AT&& arrival, DT&& departure, S&& platform)
        :
        m_arrival(std::forward<AT>(arrival)),
        m_departure(std::forward<DT>(departure)),
        m_platform(std::forward<S>(platform))
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
        const string_type& platform()
        const
        {
            return m_platform;
        }


    private:
        // variables

        time_type m_arrival;

        time_type m_departure;

        string_type m_platform;


    };


}}}


#endif
