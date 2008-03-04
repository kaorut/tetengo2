/*! \file
    \brief The definition of bobura::model::train_info::time_span.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIMESPAN_H)
#define BOBURA_MODEL_TRAININFO_TIMESPAN_H

//#include <algorithm>
#include <stdexcept>

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <tetengo2.DifferenceConcept.h>

#include "bobura.model.StationConcept.h"


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class for a time span.

        \tparam Difference A difference type. It must conform to
                           tetengo2::DifferenceConcept<Difference>.
    */
    template <typename Difference>
    class time_span :
        private boost::equality_comparable<time_span<Difference> >
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Difference, tetengo2, DifferenceConcept);


    public:
        // types

        //! The difference type.
        typedef Difference difference_type;

        //! The hour time unit tag type.
        struct hour {};

        //! The minute time unit tag type.
        struct minute {};

        //! The second time unit tag type.
        struct second {};


        // constructors and destructor

        /*!
            \brief Creates a time_span.

            When time_unit_tag is minute or second, it must be
            -59 <= span <= 59.

            \tparam TimeUnit A time unit type. It must be
                             time_span::hour, time_span::minute or
                             time_span::second.
            
            \param span      A time span.
            \param time_unit The time unit tag of a time span.

            \throw std::length_error When the span is invalid.
        */
        template <typename TimeUnit>
        time_span(const difference_type span, const TimeUnit& time_unit_tag)
        :
        m_seconds(calculate_seconds(span, time_unit_tag))
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

            \throw std::length_error When the minutes and/or seconds are
                                     invalid.
            \throw std::invalid_argument The signs of the hours and the
                                         minutes and the seconds are
                                         different.
        */
        time_span(
            const difference_type hours,
            const difference_type minutes,
            const difference_type seconds
        )
        :
        m_seconds(calculate_seconds(hours, minutes, seconds))
        {}

        /*!
            \brief Creates a time_span.

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
            \brief Checks whether this is equal to anther
                   time_span object.

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
            \brief Returns the seconds.

            \return The seconds.
        */
        difference_type seconds()
        const
        {
            return m_seconds;
        }

        /*!
            \brief Returns the hours, minutes and seconds.

            \return The hours, minutes and seconds, which are stored in a
                    boost::tuple object in this order.
        */
        const boost::tuple<difference_type, difference_type, difference_type>
        hours_minutes_seconds()
        const
        {
            const difference_type hours = m_seconds / (60 * 60);
            const difference_type minutes = m_seconds / 60 - hours * 60;
            const difference_type seconds =
                m_seconds - hours * 60 * 60 - minutes * 60;

            return boost::make_tuple(hours, minutes, seconds);
        }


    private:
        // variables

        difference_type m_seconds;


        // functions

        template <typename TimeUnit>
        static difference_type calculate_seconds(
            const difference_type span,
            const TimeUnit&       time_unit_tag
        );

        template <>
        static difference_type calculate_seconds(
            const difference_type span,
            const hour&           time_unit_tag
        )
        {
            return span * 60 * 60;
        }

        template <>
        static difference_type calculate_seconds(
            const difference_type span,
            const minute&         time_unit_tag
        )
        {
            if (span > 59)
            {
                throw std::length_error(
                    "60 or larger is specified for the minutes."
                );
            }
            else if (span < -59)
            {
                throw std::length_error(
                    "-60 or smaller is specified for the minutes."
                );
            }

            return span * 60;
        }

        template <>
        static difference_type calculate_seconds(
            const difference_type span,
            const second&         time_unit_tag
        )
        {
            if (span > 59)
            {
                throw std::length_error(
                    "60 or larger is specified for the seconds."
                );
            }
            else if (span < -59)
            {
                throw std::length_error(
                    "-60 or smaller is specified for the seconds."
                );
            }

            return span;
        }

        static difference_type calculate_seconds(
            const difference_type hours,
            const difference_type minutes,
            const difference_type seconds
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

            return calculate_seconds(hours, hour()) +
                calculate_seconds(minutes, minute()) +
                calculate_seconds(seconds, second());
        }


    };


}}}

namespace std
{
    /*!
        \brief Swaps two time_span objects.

        \tparam Difference A difference type. It must conform to
                           tetengo2::DifferenceConcept<Difference>.

        \param time_span1 A time_span object #1.
        \param time_span2 A time_span object #2.
    */
    template <typename Difference>
    void swap(
        bobura::model::train_info::time_span<Difference>& time_span1,
        bobura::model::train_info::time_span<Difference>& time_span2
    )
    throw ()
    {
        boost::function_requires<tetengo2::DifferenceConcept<Difference> >();

        time_span1.swap(time_span2);
    }


}

#endif
