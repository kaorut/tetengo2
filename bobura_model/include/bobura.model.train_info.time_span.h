/*! \file
    \brief The definition of bobura::model::train_info::time_span.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIMESPAN_H)
#define BOBURA_MODEL_TRAININFO_TIMESPAN_H

//#include <algorithm>
#include <stdexcept>

#include <boost/concept_check.hpp>
#include <boost/operators.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class for a time span.

        \tparam TimeSpanTick A time span tick type. It must conform to
                             boost::SignedInteger<TimeSpanTick>.
    */
    template <typename TimeSpanTick>
    class time_span :
        private boost::totally_ordered<time_span<TimeSpanTick> >,
        private boost::additive<time_span<TimeSpanTick> >
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((boost::SignedInteger<TimeSpanTick>));


    public:
        // types

        //! The tick type.
        typedef TimeSpanTick tick_type;


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
            \brief Creates a time_span.

            \param seconds A second span.
        */
        explicit time_span(const tick_type seconds)
        :
        m_seconds(seconds)
        {}

        /*!
            \brief Creates a time_span.

            The hours, the minutes and the seconds must be 0 or must have the
            same signs.

            \param hours   An hour span.
            \param minutes A minute span. It must be that
                           -59 <= minutes <= 59.
            \param seconds A second span. It must be that
                           -59 <= seconds <= 59.

            \throw std::out_of_range     When the minutes and/or seconds are
                                         invalid.
            \throw std::invalid_argument The signs of the hours and the
                                         minutes and the seconds are
                                         different.
        */
        time_span(
            const tick_type hours,
            const tick_type minutes,
            const tick_type seconds
        )
        :
        m_seconds(calculate_seconds(hours, minutes, seconds))
        {}

        /*!
            \brief Copies a time_span.

            \param another Another time_span object.
        */
        time_span(const time_span& another)
        :
        m_seconds(another.m_seconds)
        {}

        /*!
            \brief Destroys the time_span.
        */
        ~time_span()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another time_span object.

            \param another Another time_span object.
        */
        void swap(time_span& another)
        throw ()
        {
            std::swap(m_seconds, another.m_seconds);
        }

        /*!
            \brief Assigns another time_span object.

            \param another Another time_span object.

            \return this object.
        */
        time_span& operator=(const time_span& another)
        {
            time_span(another).swap(*this);
            return *this;
        }

        /*!
            \brief Adds another time_span object.

            \param another Another time_span object.

            \return this object.
        */
        time_span& operator+=(const time_span& another)
        {
            time_span temp(*this);

            temp.m_seconds += another.m_seconds;
            
            temp.swap(*this);
            return *this;
        }

        /*!
            \brief Subtracts another time_span object.

            \param another Another time_span object.

            \return this object.
        */
        time_span& operator-=(const time_span& another)
        {
            time_span temp(*this);

            temp.m_seconds -= another.m_seconds;
            
            temp.swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther time_span object.

            \param another Another time_span object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const time_span& another)
        const
        {
            return m_seconds == another.m_seconds;
        }

        /*!
            \brief Checks whether this is less than anther time_span object.

            \param another Another time_span object.

            \retval true  When this is less than another.
            \retval false Otherwise.
        */
        bool operator<(const time_span& another)
        const
        {
            return m_seconds < another.m_seconds;
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

            \return The hours, minutes and seconds, which are stored in a
                    boost::tuple object in this order.
        */
        const boost::tuple<tick_type, tick_type, tick_type>
        hours_minutes_seconds()
        const
        {
            const tick_type hours = m_seconds / (60 * 60);
            const tick_type minutes = m_seconds / 60 - hours * 60;
            const tick_type seconds =
                m_seconds - hours * 60 * 60 - minutes * 60;

            return boost::make_tuple(hours, minutes, seconds);
        }


    private:
        // static functions

        static tick_type calculate_seconds(
            const tick_type hours,
            const tick_type minutes,
            const tick_type seconds
        )
        {
            if (
                !(hours >= 0 && minutes >= 0 && seconds >= 0) &&
                !(hours <= 0 && minutes <= 0 && seconds <= 0)
            )
            {
                throw std::invalid_argument(
                    "The signs of the hours, the minutes and the seconds "
                    "are different."
                );
            }
            else if (minutes > 59)
            {
                throw std::out_of_range(
                    "60 or larger is specified for the minutes."
                );
            }
            else if (minutes < -59)
            {
                throw std::out_of_range(
                    "-60 or smaller is specified for the minutes."
                );
            }
            else if (seconds > 59)
            {
                throw std::out_of_range(
                    "60 or larger is specified for the seconds."
                );
            }
            else if (seconds < -59)
            {
                throw std::out_of_range(
                    "-60 or smaller is specified for the seconds."
                );
            }

            return hours * 60 * 60 + minutes * 60 + seconds;
        }


        // variables

        tick_type m_seconds;


    };


}}}

namespace std
{
    /*!
        \brief Swaps two time_span objects.

        \tparam TimeSpanTick A time span tick type. It must conform to
                             boost::SignedInteger<TimeSpanTick>.

        \param time_span1 A time_span object #1.
        \param time_span2 A time_span object #2.
    */
    template <typename TimeSpanTick>
    void swap(
        bobura::model::train_info::time_span<TimeSpanTick>& time_span1,
        bobura::model::train_info::time_span<TimeSpanTick>& time_span2
    )
    throw ()
    {
        BOOST_CONCEPT_ASSERT((boost::SignedInteger<TimeSpanTick>));

        time_span1.swap(time_span2);
    }


}

#endif
