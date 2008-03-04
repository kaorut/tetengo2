/*! \file
    \brief The definition of bobura::model::train_info::time.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIME_H)
#define BOBURA_MODEL_TRAININFO_TIME_H

//#include <algorithm>
#include <cassert>
#include <stdexcept>

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>

#include <tetengo2.SizeConcept.h>

#include "bobura.model.train_info.TimeSpanConcept.h"


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class for a station location.

        \tparam Size     A size type. It must conform to
                         tetengo2::SizeConcept<Size>.
        \tparam TimeSpan A time span type. It must conform to
                         bobura::model::train_info::TimeSpanConcept<TimeSpan>.
    */
    template <typename Size, typename TimeSpan>
    class time : private boost::equality_comparable<time<Size, TimeSpan> >
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Size, tetengo2, SizeConcept);
        BOOST_CLASS_REQUIRE(
            TimeSpan, bobura::model::train_info, TimeSpanConcept
        );


    public:
        // types

        //! The time_span type.
        typedef TimeSpan time_span_type;

        //! The size type.
        typedef Size size_type;


        // constructors and destructor

        /*!
            \brief Creates a time.

            When seconds_from_midnight is greater than seconds_of_whole_day(),
            it is assumed that the result of
            seconds_from_midnight % seconds_of_whole_day() is passed.

            \param seconds_from_midnight Seconds from the midnight.
        */
        time(const size_type seconds_from_midnight)
        :
        m_seconds_from_midnight(
            seconds_from_midnight % seconds_of_whole_day()
        )
        {}

        /*!
            \brief Creates a time.

            \param hours   Hours. It must be that 0 <= hours <= 23.
            \param minutes Minutes. It must be that 0 <= minutes <= 59.
            \param seconds Seconds. It must be that 0 <= seconds <= 59.

            \throw std::length_error When hours, minutes and/or seconds
                                     are invalid.
        */
        time(
            const size_type hours,
            const size_type minutes,
            const size_type seconds
        )
        :
        m_seconds_from_midnight(
            calculate_seconds_from_midnight(hours, minutes, seconds)
        )
        {}

        /*!
            \brief Creates a time.

            \param another Another time object.
        */
        time(const time& another)
        :
        m_seconds_from_midnight(another.m_seconds_from_midnight)
        {}

        /*!
            \brief Destroys the time.
        */
        ~time()
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
            std::swap(
                m_seconds_from_midnight, another.m_seconds_from_midnight
            );
        }

        /*!
            \brief Assigns another time object.

            \param another Another time object.

            \return this object.
        */
        time& operator=(const time& another)
        {
            time(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther time object.

            \param another Another time object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const time& another)
        const
        {
            return m_seconds_from_midnight == another.m_seconds_from_midnight;
        }

        static size_type seconds_of_whole_day()
        {
            return 24 * 60 * 60;
        }

        size_type seconds_from_midnight()
        const
        {
            return m_seconds_from_midnight;
        }


    private:
        // variables

        size_type m_seconds_from_midnight;


        // functions

        static size_type calculate_seconds_from_midnight(
            const size_type hours,
            const size_type minutes,
            const size_type seconds
        )
        {
            if (hours > 23)
            {
                throw std::length_error(
                    "24 or greater is specified for the hours."
                );
            }
            else if (minutes > 59)
            {
                throw std::length_error(
                    "60 or greater is specified for the minutes."
                );
            }
            else if (seconds > 59)
            {
                throw std::length_error(
                    "60 or greater is specified for the minutes."
                );
            }

            const size_type seconds_from_midnight =
                hours * 60 * 60 + minutes * 60 + seconds;
            assert(seconds_from_midnight < seconds_of_whole_day());

            return seconds_from_midnight;
        }


    };


}}}

namespace std
{
    /*!
        \brief Swaps two time objects.

        \tparam Size     A size type. It must conform to
                         tetengo2::SizeConcept<Size>.
        \tparam TimeSpan A time span type. It must conform to
                         bobura::model::train_info::TimeSpanConcept<TimeSpan>.

        \param time1 A time object #1.
        \param time2 A time object #2.
    */
    template <typename TimeSpan, typename Size>
    void swap(
        bobura::model::train_info::time<Size, TimeSpan>& time1,
        bobura::model::train_info::time<Size, TimeSpan>& time2
    )
    throw ()
    {
        boost::function_requires<tetengo2::SizeConcept<Size> >();
        boost::function_requires<
            bobura::model::train_info::TimeSpanConcept<TimeSpan>
        >();

        time1.swap(time2);
    }


}

#endif
