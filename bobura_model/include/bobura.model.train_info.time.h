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
//#include <boost/tuple/tuple.hpp>
//#include <boost/tuple/tuple_comparison.hpp>

#include <tetengo2.SizeConcept.h>

#include "bobura.model.train_info.TimeSpanConcept.h"


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class for a time.

        \tparam Size     A size type. It must conform to
                         tetengo2::SizeConcept<Size>.
        \tparam TimeSpan A time span type. It must conform to
                         bobura::model::train_info::TimeSpanConcept<TimeSpan>.
    */
    template <typename Size, typename TimeSpan>
    class time :
        private boost::totally_ordered<time<Size, TimeSpan> >,
        private boost::additive<time<Size, TimeSpan>, TimeSpan>
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


        // static functions

        /*!
            \brief Returns the seconds of a whole day.

            The value is 24 * 60 * 60 (= 86400).

            \return The seconds of a whole way.
        */
        static size_type seconds_of_whole_day()
        {
            return 24 * 60 * 60;
        }


        // constructors and destructor

        /*!
            \brief Creates a time.

            When seconds_from_midnight is greater than seconds_of_whole_day(),
            it is assumed that the result of
            seconds_from_midnight % seconds_of_whole_day() is passed.

            \param seconds_from_midnight Seconds from the midnight.
        */
        explicit time(const size_type seconds_from_midnight)
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
            \brief Copies a time.

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
            \brief Adds a time span.

            After this operation, seconds_from_midnight() must be that
            seconds_from_midnight() < seconds_of_whole_day().
            When time_span is too large or too small, the result is
            seconds_from_midnight() % seconds_from_midnight().

            \param time_span A time span.

            \return this object.
        */
        time& operator+=(const time_span_type& time_span)
        {
            time_span_type::difference_type seconds =
                m_seconds_from_midnight;
            while (seconds < -time_span.seconds())
                seconds += seconds_of_whole_day();
            seconds += time_span.seconds();
            seconds %= seconds_of_whole_day();
            assert(
                0 <= seconds &&
                seconds < static_cast<time_span_type::difference_type>(
                    seconds_of_whole_day()
                )
            );

            time(seconds).swap(*this);
            return *this;
        }

        /*!
            \brief Subtracts a time span.

            After this operation, seconds_from_midnight() must be that
            seconds_from_midnight() < seconds_of_whole_day().
            When time_span is too large or too small, the result is
            seconds_from_midnight() % seconds_from_midnight().

            \param time_span A time span.

            \return this object.
        */
        time& operator-=(const time_span_type& time_span)
        {
            time_span_type::difference_type seconds =
                m_seconds_from_midnight;
            while (seconds < time_span.seconds())
                seconds += seconds_of_whole_day();
            seconds -= time_span.seconds();
            seconds %= seconds_of_whole_day();
            assert(
                0 <= seconds &&
                seconds < static_cast<time_span_type::difference_type>(
                    seconds_of_whole_day()
                )
            );

            time(seconds).swap(*this);
            return *this;
        }

        /*!
            \brief Subtracts times.

            The result is always 0 or positive. A smaller minus a larger
            is calculated over the midnight.

            \param another Another time object.

            \return The time span.
        */
        const time_span_type operator-(const time& another)
        const
        {
            time_span_type::difference_type seconds = m_seconds_from_midnight;
            seconds -= another.m_seconds_from_midnight;
            while (seconds < 0)
                seconds += seconds_of_whole_day();

            return time_span_type(seconds);
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

        /*!
            \brief Checks whether this is less than anther time object.

            \param another Another time object.

            \retval true  When this is less than another.
            \retval false Otherwise.
        */
        bool operator<(const time& another)
        const
        {
            return m_seconds_from_midnight < another.m_seconds_from_midnight;
        }

        /*!
            \brief Returns the seconds from the midnight.

            \return The seconds from the midnight.
        */
        size_type seconds_from_midnight()
        const
        {
            return m_seconds_from_midnight;
        }

        /*!
            \brief Returns the hours, minutes and seconds.

            \return The hours, minutes and seconds, which are stored in a
                    boost::tuple object in this order.
        */
        const boost::tuple<size_type, size_type, size_type>
        hours_minutes_seconds()
        const
        {
            const size_type hours = m_seconds_from_midnight / (60 * 60);
            const size_type minutes =
                m_seconds_from_midnight / 60 - hours * 60;
            const size_type seconds =
                m_seconds_from_midnight - hours * 60 * 60 - minutes * 60;

            return boost::make_tuple(hours, minutes, seconds);
        }


    private:
        // static functions

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


        // variables

        size_type m_seconds_from_midnight;


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
