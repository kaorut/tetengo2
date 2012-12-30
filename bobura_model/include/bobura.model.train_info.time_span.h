/*! \file
    \brief The definition of bobura::model::train_info::time_span.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIMESPAN_H)
#define BOBURA_MODEL_TRAININFO_TIMESPAN_H

#include <stdexcept>

#include <boost/operators.hpp>
#include <boost/swap.hpp>
#include <boost/throw_exception.hpp>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class template for a time span.

        \tparam TimeSpanTick A time span tick type.
    */
    template <typename TimeSpanTick>
    class time_span :
        private boost::totally_ordered<time_span<TimeSpanTick>>,
        private boost::additive<time_span<TimeSpanTick>>
    {
    public:
        // types

        //! The tick type.
        typedef TimeSpanTick tick_type;

        //! The hours-minutes-seconds type.
        class hours_minutes_seconds_type : private boost::equality_comparable<hours_minutes_seconds_type>
        {
        public:
            /*!
                \brief Creates hours-minutes-seconds.

                \param hours   Hours.
                \param minutes Minutes.
                \param seconds Seconds.
            */
            hours_minutes_seconds_type(const tick_type hours, const tick_type minutes, const tick_type seconds)
            :
            m_hours(hours),
            m_minutes(minutes),
            m_seconds(seconds)
            {}

            /*!
                \brief Checks whether one hours-minutes-seconds is equal to another.

                \param one     One hours-minutes-seconds.
                \param another Another hours-minutes-seconds.

                \retval true  When the one is equal to the other.
                \retval false Otherwise.
            */
            friend bool operator==(const hours_minutes_seconds_type& one, const hours_minutes_seconds_type& another)
            {
                return
                    one.m_hours == another.m_hours &&
                    one.m_minutes == another.m_minutes &&
                    one.m_seconds == another.m_seconds;
            }

            /*!
                \brief Returns hours.

                \return Hours.
            */
            tick_type hours()
            const
            {
                return m_hours;
            }

            /*!
                \brief Returns minutes.

                \return Minutes.
            */
            tick_type minutes()
            const
            {
                return m_minutes;
            }

            /*!
                \brief Returns seconds.

                \return Seconds.
            */
            tick_type seconds()
            const
            {
                return m_seconds;
            }


        private:
            tick_type m_hours;

            tick_type m_minutes;

            tick_type m_seconds;

        };


        // static functions

        /*!
            \brief Returns the seconds of a whole day.

            The value is 24 * 60 * 60 (= 86400).

            \return The seconds of a whole way.
        */
        static tick_type seconds_of_whole_day()
        {
            return 24 * 60 * 60;
        }


        // constructors and destructor

        /*!
            \brief Creates a time span.

            \param seconds A second span.
        */
        explicit time_span(const tick_type seconds)
        :
        m_seconds(seconds)
        {}

        /*!
            \brief Creates a time span.

            The hours, the minutes and the seconds must be 0 or must have the
            same signs.

            \param hours   An hour span.
            \param minutes A minute span. It must be that -59 <= minutes <= 59.
            \param seconds A second span. It must be that -59 <= seconds <= 59.

            \throw std::out_of_range     When the minutes and/or seconds are invalid.
            \throw std::invalid_argument When the signs of the hours and the minutes and the seconds are different.
        */
        time_span(const tick_type hours, const tick_type minutes, const tick_type seconds)
        :
        m_seconds(calculate_seconds(hours, minutes, seconds))
        {}


        // functions

        /*!
            \brief Adds another time span.

            \param another Another time span.

            \return This object.
        */
        time_span& operator+=(const time_span& another)
        {
            time_span temp(*this);

            temp.m_seconds += another.m_seconds;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Subtracts another time span.

            \param another Another time span.

            \return This object.
        */
        time_span& operator-=(const time_span& another)
        {
            time_span temp(*this);

            temp.m_seconds -= another.m_seconds;

            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Checks whether one time span is equal to another.

            \param one     One time span.
            \param another Another time span.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const time_span& one, const time_span& another)
        {
            return one.m_seconds == another.m_seconds;
        }

        /*!
            \brief Checks whether one time span is less than another.

            \param one     One time span.
            \param another Another time span.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        friend bool operator<(const time_span& one, const time_span& another)
        {
            return one.m_seconds < another.m_seconds;
        }

        /*!
            \brief Returns the seconds.

            \return The seconds.
        */
        tick_type seconds()
        const
        {
            return m_seconds;
        }

        /*!
            \brief Returns the hours, minutes and seconds.

            \return The hours, minutes and seconds.
        */
        const hours_minutes_seconds_type hours_minutes_seconds()
        const
        {
            const tick_type hours = m_seconds / (60 * 60);
            const tick_type minutes = m_seconds / 60 - hours * 60;
            const tick_type seconds = m_seconds - hours * 60 * 60 - minutes * 60;

            return hours_minutes_seconds_type(hours, minutes, seconds);
        }


    private:
        // static functions

        static tick_type calculate_seconds(const tick_type hours, const tick_type minutes, const tick_type seconds)
        {
            if (!(hours >= 0 && minutes >= 0 && seconds >= 0) && !(hours <= 0 && minutes <= 0 && seconds <= 0))
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("The signs of the hours, the minutes and the seconds are different.")
                );
            }
            else if (minutes > 59)
            {
                BOOST_THROW_EXCEPTION(std::out_of_range("60 or larger is specified for the minutes."));
            }
            else if (minutes < -59)
            {
                BOOST_THROW_EXCEPTION(std::out_of_range("-60 or smaller is specified for the minutes."));
            }
            else if (seconds > 59)
            {
                BOOST_THROW_EXCEPTION(std::out_of_range("60 or larger is specified for the seconds."));
            }
            else if (seconds < -59)
            {
                BOOST_THROW_EXCEPTION(std::out_of_range("-60 or smaller is specified for the seconds."));
            }

            return hours * 60 * 60 + minutes * 60 + seconds;
        }


        // variables

        tick_type m_seconds;


    };


}}}


#endif
