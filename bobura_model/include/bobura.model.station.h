/*! \file
    \brief The definition of bobura::model::station.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATION_H)
#define BOBURA_MODEL_STATION_H

#include <utility>

#include <boost/operators.hpp>

#include <tetengo2.cpp11.h>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a station.

        \tparam String A string type.
        \tparam Grade  A grade type.
    */
    template <typename String, typename Grade>
    class station : private boost::equality_comparable<station<String, Grade>>
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The grade type.
        typedef Grade grade_type;


        // constructors and destructor

        /*!
            \brief Creates a station.

            \tparam S A string type.

            \param name                     A name.
            \param grade                    A grade.
            \param shows_down_arrival_times True when the arrival times of down trains are shown.
            \param shows_up_arrival_times   True when the arrival times of up trains are shown.
        */
        template <typename S>
        station(
            S&& name,
            const grade_type& grade,
            const bool shows_down_arrival_times,
            const bool shows_up_arrival_times
        )
        :
        m_name(std::forward<S>(name)),
        m_grade(grade),
        m_shows_down_arrival_times(shows_down_arrival_times),
        m_shows_up_arrival_times(shows_up_arrival_times)
        {}


        // functions

        /*!
            \brief Checks whether one station is equal to another.

            \param one     One station.
            \param another Another station.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const station& one, const station& another)
        {
            return
                one.m_name == another.m_name &&
                &one.m_grade.get() == &another.m_grade.get() &&
                one.m_shows_down_arrival_times == another.m_shows_down_arrival_times &&
                one.m_shows_up_arrival_times == another.m_shows_up_arrival_times;
        }

        /*!
            \brief Returns the name.

            \return The name.
        */
        const string_type& name()
        const
        {
            return m_name;
        }

        /*!
            \brief Returns the grade.

            \return The grade.
        */
        const grade_type& grade()
        const
        {
            return m_grade;
        }

        /*!
            \brief Returns whether the arrival times of down trains are shown.

            \retval true  When the arrival times of down trains are shown.
            \retval false Otherwise.
        */
        bool shows_down_arrival_times()
        const
        {
            return m_shows_down_arrival_times;
        }

        /*!
            \brief Returns whether the arrival times of up trains are shown.

            \retval true  When the arrival times of up trains are shown.
            \retval false Otherwise.
        */
        bool shows_up_arrival_times()
        const
        {
            return m_shows_up_arrival_times;
        }


    private:
        // variables

        string_type m_name;

        typename tetengo2::cpp11::reference_wrapper<const grade_type>::type m_grade;

        bool m_shows_down_arrival_times;

        bool m_shows_up_arrival_times;


    };


}}


#endif
