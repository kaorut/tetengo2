/*! \file
    \brief The definition of bobura::model::train_info::time_span.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIMESPAN_H)
#define BOBURA_MODEL_TRAININFO_TIMESPAN_H //!< !! Include Guard !!

#include <stdexcept>

#include <boost/concept_check.hpp>
#include <boost/operators.hpp>
#include <boost/swap.hpp>
#include <boost/throw_exception.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <tetengo2.assignable.h>
#include <tetengo2.swappable.h>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class for a time span.

        \tparam TimeSpanTick A time span tick type. It must conform to
                             boost::SignedInteger<TimeSpanTick>.
    */
    template <typename TimeSpanTick>
    class time_span :
        public tetengo2::assignable<time_span<TimeSpanTick> >,
        private tetengo2::swappable<time_span<TimeSpanTick> >,
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
            \brief Copies a time span.

            \param another Another time span.
        */
        time_span(const time_span& another)
        :
        m_seconds(another.m_seconds)
        {}

        /*!
            \brief Destroys the time span.
        */
        ~time_span()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another time span.

            \param another Another time span.
        */
        void swap(time_span& another)
        throw ()
        {
            boost::swap(m_seconds, another.m_seconds);
        }

        /*!
            \brief Assigns another time span.

            \param another Another time span.

            \return this object.
        */
        time_span& operator=(const time_span& another)
        {
            return assign(another);
        }

        /*!
            \brief Adds another time span.

            \param another Another time span.

            \return this object.
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

            \return this object.
        */
        time_span& operator-=(const time_span& another)
        {
            time_span temp(*this);

            temp.m_seconds -= another.m_seconds;
            
            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Checks whether one time span is equal to anther.

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
            \brief Checks whether one time span is less than anther.

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
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument(
                        "The signs of the hours, the minutes and the seconds "
                        "are different."
                    )
                );
            }
            else if (minutes > 59)
            {
                BOOST_THROW_EXCEPTION(
                    std::out_of_range(
                        "60 or larger is specified for the minutes."
                    )
                );
            }
            else if (minutes < -59)
            {
                BOOST_THROW_EXCEPTION(
                    std::out_of_range(
                        "-60 or smaller is specified for the minutes."
                    )
                );
            }
            else if (seconds > 59)
            {
                BOOST_THROW_EXCEPTION(
                    std::out_of_range(
                        "60 or larger is specified for the seconds."
                    )
                );
            }
            else if (seconds < -59)
            {
                BOOST_THROW_EXCEPTION(
                    std::out_of_range(
                        "-60 or smaller is specified for the seconds."
                    )
                );
            }

            return hours * 60 * 60 + minutes * 60 + seconds;
        }


        // variables

        tick_type m_seconds;


    };


}}}


#endif
