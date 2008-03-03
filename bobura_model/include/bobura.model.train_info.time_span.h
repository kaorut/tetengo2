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

#include <tetengo2.SizeConcept.h>

#include "bobura.model.StationConcept.h"


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The class for a time span.

        \tparam Size A size type. It must conform to
                     tetengo2::SizeConcept<Size>.
    */
    template <typename Size>
    class time_span : private boost::equality_comparable<time_span<Size> >
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Size, tetengo2, SizeConcept);


    public:
        // types

        //! The size type.
        typedef Size size_type;

        //! The time unit tag type.
        struct hour {};

        //! The time unit tag type.
        struct minute {};

        //! The time unit tag type.
        struct second {};


        // constructors and destructor

        /*!
            \brief Creates a time_span.

            When time_unit_tag is minute or second, it must be span <= 59.

            \tparam TimeUnit A time unit type. It must be
                             time_span::hour, time_span::minute or
                             time_span::second.
            
            \param span      A time span.
            \param time_unit The time unit tag of a time span.
        */
        template <typename TimeUnit>
        time_span(const size_type span, const TimeUnit& time_unit_tag)
        :
        m_seconds(calculate_seconds(span, time_unit_tag))
        {}

        /*!
            \brief Creates a time_span.

            \param hours   An hour span.
            \param minutes A minute span. It must be that minutes <= 59.
            \param seconds A second span. It must be that seconds <= 59.

            \throw std::length_error When the minutes and/or seconds are
                                     invalid.
        */
        time_span(
            const size_type hours,
            const size_type minutes,
            const size_type seconds
        )
        :
        m_seconds(
            calculate_seconds(hours, hour()) +
            calculate_seconds(minutes, minute()) +
            calculate_seconds(seconds, second())
        )
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
        size_type seconds()
        const
        {
            return m_seconds;
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
            const size_type hours = m_seconds / (60 * 60);
            const size_type minutes = m_seconds / 60 - hours * 60;
            const size_type seconds =
                m_seconds - hours * 60 * 60 - minutes * 60;

            return boost::make_tuple(hours, minutes, seconds);
        }


    private:
        // variables

        size_type m_seconds;


        // functions

        template <typename TimeUnit>
        static size_type calculate_seconds(
            const size_type span,
            const TimeUnit& time_unit_tag
        );

        template <>
        static size_type calculate_seconds(
            const size_type span,
            const hour&     time_unit_tag
        )
        {
            return span * 60 * 60;
        }

        template <>
        static size_type calculate_seconds(
            const size_type span,
            const minute&   time_unit_tag
        )
        {
            if (span >= 60)
            {
                throw std::length_error(
                    "60 or larger is specified for the minutes."
                );
            }

            return span * 60;
        }

        template <>
        static size_type calculate_seconds(
            const size_type span,
            const second&   time_unit_tag
        )
        {
            if (span >= 60)
            {
                throw std::length_error(
                    "60 or larger is specified for the seconds."
                );
            }

            return span;
        }


    };


}}}

namespace std
{
    /*!
        \brief Swaps two time_span objects.

        \tparam Size A size type. It must conform to
                     tetengo2::SizeConcept<Size>.

        \param time_span1 A time_span object #1.
        \param time_span2 A time_span object #2.
    */
    template <typename Size>
    void swap(
        bobura::model::train_info::time_span<Size>& time_span1,
        bobura::model::train_info::time_span<Size>& time_span2
    )
    throw ()
    {
        boost::function_requires<tetengo2::SizeConcept<Size> >();

        time_span1.swap(time_span2);
    }


}

#endif
