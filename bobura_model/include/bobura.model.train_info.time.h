/*! \file
    \brief The definition of bobura::model::train_info::time.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIME_H)
#define BOBURA_MODEL_TRAININFO_TIME_H

#include <cassert>
#include <limits>
#include <stdexcept>

#include <boost/operators.hpp>
#include <boost/swap.hpp>
#include <boost/throw_exception.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <tetengo2.assignable.h>
#include <tetengo2.cpp0x_keyword.h>
#include <tetengo2.swappable.h>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class for a time.

        \tparam TimeTick A time tick type.
        \tparam TimeSpan A time span type.
    */
    template <typename TimeTick, typename TimeSpan>
    class time :
        public tetengo2::assignable<time<TimeTick, TimeSpan>>,
        private tetengo2::swappable<time<TimeTick, TimeSpan>>,
        private boost::totally_ordered<time<TimeTick, TimeSpan>>,
        private boost::additive<time<TimeTick, TimeSpan>, TimeSpan>
    {
    public:
        // types

        //! \return The tick type.
        typedef TimeTick tick_type;

        //! \return The time span type.
        typedef TimeSpan time_span_type;


        // static functions

        /*!
            \brief Returns the uninitialized time.

            The uninitialized time is not equal to any other time, and it is
            larger than any other time. Addition and subtraction to the
            uninitialized time always returns the uninitialized time itself.
            The seconds (and also hours, minutes) cannot be obtained.

            \return The uninitialized time.
        */
        static const time& uninitialized()
        {
            static const time singleton;

            return singleton;
        }


        // constructors and destructor

        /*!
            \brief Creates a time.

            When seconds_from_midnight is greater than
            time_span_type::seconds_of_whole_day(), it is assumed that the
            result of
            seconds_from_midnight % time_span_type::seconds_of_whole_day() is
            passed.

            \param seconds_from_midnight Seconds from the midnight.
        */
        explicit time(const tick_type seconds_from_midnight)
        :
        m_seconds_from_midnight(
            seconds_from_midnight % time_span_type::seconds_of_whole_day()
        )
        {}

        /*!
            \brief Creates a time.

            \param hours   Hours. It must be that 0 <= hours <= 23.
            \param minutes Minutes. It must be that 0 <= minutes <= 59.
            \param seconds Seconds. It must be that 0 <= seconds <= 59.

            \throw std::out_of_range When hours, minutes and/or seconds
                                     are invalid.
        */
        time(
            const tick_type hours,
            const tick_type minutes,
            const tick_type seconds
        )
        :
        m_seconds_from_midnight(
            calculate_seconds_from_midnight(hours, minutes, seconds)
        )
        {}

        /*!
            \brief Copies a time.

            \param another Another time.
        */
        time(const time& another)
        :
        m_seconds_from_midnight(another.m_seconds_from_midnight)
        {}

        /*!
            \brief Destroys the time.
        */
        ~time()
        TETENGO2_NOEXCEPT
        {}


        // functions

        /*!
            \brief Swaps the members with another time.

            \param another Another time.
        */
        void swap(time& another)
        TETENGO2_NOEXCEPT
        {
            boost::swap(
                m_seconds_from_midnight, another.m_seconds_from_midnight
            );
        }

        /*!
            \brief Assigns another time.

            \param another Another time.

            \return This object.
        */
        time& operator=(const time& another)
        {
            return assign(another);
        }

        /*!
            \brief Adds a time span.

            After this operation, seconds_from_midnight() must be that
            seconds_from_midnight() < seconds_of_whole_day().
            When time_span is too large or too small, the result is
            seconds_from_midnight() % seconds_from_midnight().

            When this is uninitialized, the result is also uninitialized.

            \param time_span A time span.

            \return This object.
        */
        time& operator+=(const time_span_type& time_span)
        {
            if (*this == uninitialized()) return *this;

            typename time_span_type::tick_type seconds =
                m_seconds_from_midnight;
            while (seconds < -time_span.seconds())
                seconds += time_span_type::seconds_of_whole_day();
            seconds += time_span.seconds();
            seconds %= time_span_type::seconds_of_whole_day();
            assert(
                0 <= seconds &&
                seconds < time_span_type::seconds_of_whole_day()
            );

            time temp(seconds);
            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Subtracts a time span.

            After this operation, seconds_from_midnight() must be that
            seconds_from_midnight() < seconds_of_whole_day().
            When time_span is too large or too small, the result is
            seconds_from_midnight() % seconds_from_midnight().

            When this is uninitialized, the result is also uninitialized.

            \param time_span A time span.

            \return This object.
        */
        time& operator-=(const time_span_type& time_span)
        {
            if (*this == uninitialized()) return *this;

            typename time_span_type::tick_type seconds =
                m_seconds_from_midnight;
            while (seconds < time_span.seconds())
                seconds += time_span_type::seconds_of_whole_day();
            seconds -= time_span.seconds();
            seconds %= time_span_type::seconds_of_whole_day();
            assert(
                0 <= seconds &&
                seconds < time_span_type::seconds_of_whole_day()
            );

            time temp(seconds);
            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Subtracts times.

            The result is always 0 or positive. A smaller minus a larger
            is calculated over the midnight.

            \param another Another time.

            \return The time span.

            \throw std::logic_error When this or another is uninitialized.
        */
        time_span_type operator-(const time& another)
        const
        {
            if (*this == uninitialized() || another == uninitialized())
            {
                BOOST_THROW_EXCEPTION(
                    std::logic_error("The time object is uninitialized.")
                );
            }

            typename time_span_type::tick_type seconds =
                m_seconds_from_midnight;
            seconds -= another.m_seconds_from_midnight;
            while (seconds < 0)
                seconds += time_span_type::seconds_of_whole_day();

            return time_span_type(seconds);
        }

        /*!
            \brief Checks whether one time is equal to anther.

            \param one     One time.
            \param another Another time.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const time& one, const time& another)
        {
            return one.m_seconds_from_midnight ==
                another.m_seconds_from_midnight;
        }

        /*!
            \brief Checks whether one time is less than anther.

            \param one     One time.
            \param another Another time.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        friend bool operator<(const time& one, const time& another)
        {
            return one.m_seconds_from_midnight <
                another.m_seconds_from_midnight;
        }

        /*!
            \brief Returns the seconds from the midnight.

            \return The seconds from the midnight.

            \throw std::logic_error When this is uninitialized.
        */
        tick_type seconds_from_midnight()
        const
        {
            if (*this == uninitialized())
            {
                BOOST_THROW_EXCEPTION(
                    std::logic_error("The time object is uninitialized.")
                );
            }

            return m_seconds_from_midnight;
        }

        /*!
            \brief Returns the hours, minutes and seconds.

            \return The hours, minutes and seconds, which are stored in a
                    boost::tuple object in this order.

            \throw std::logic_error When this is uninitialized.
        */
        const boost::tuple<tick_type, tick_type, tick_type>
        hours_minutes_seconds()
        const
        {
            if (*this == uninitialized())
            {
                BOOST_THROW_EXCEPTION(
                    std::logic_error("The time object is uninitialized.")
                );
            }

            const tick_type hours = m_seconds_from_midnight / (60 * 60);
            const tick_type minutes =
                m_seconds_from_midnight / 60 - hours * 60;
            const tick_type seconds =
                m_seconds_from_midnight - hours * 60 * 60 - minutes * 60;

            return boost::make_tuple(hours, minutes, seconds);
        }


    private:
        // static functions

        static tick_type calculate_seconds_from_midnight(
            const tick_type hours,
            const tick_type minutes,
            const tick_type seconds
        )
        {
            if (hours > 23)
            {
                BOOST_THROW_EXCEPTION(
                    std::out_of_range(
                        "24 or greater is specified for the hours."
                    )
                );
            }
            else if (minutes > 59)
            {
                BOOST_THROW_EXCEPTION(
                    std::out_of_range(
                        "60 or greater is specified for the minutes."
                    )
                );
            }
            else if (seconds > 59)
            {
                BOOST_THROW_EXCEPTION(
                    std::out_of_range(
                        "60 or greater is specified for the seconds."
                    )
                );
            }

            const tick_type seconds_from_midnight =
                hours * 60 * 60 + minutes * 60 + seconds;
            assert(
                seconds_from_midnight <
                static_cast<tick_type>(time_span_type::seconds_of_whole_day())
            );

            return seconds_from_midnight;
        }


        // constructors

        time()
        :
        m_seconds_from_midnight(std::numeric_limits<tick_type>::max())
        {}


        // variables

        tick_type m_seconds_from_midnight;


    };


}}}


#endif
