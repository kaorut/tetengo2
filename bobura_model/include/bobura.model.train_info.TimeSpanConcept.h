/*! \file
    \brief The definition of bobura::model::time spantable_info::TimeSpanConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIMESPANCONCEPT_H)
#define BOBURA_MODEL_TRAININFO_TIMESPANCONCEPT_H

#include <algorithm>

#include <boost/concept_check.hpp>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The concept check class template for a time span.

        \tparam TimeSpan A time span type.
    */
    template <typename TimeSpan>
    class TimeSpanConcept
    {
    public:
        // constructors and destructor

        TimeSpanConcept();


        // functions

        /*!
            \brief Checks the constraints on a time span.
        */
        void constraints()
        {
            typedef typename TimeSpan::difference_type difference_type;

            m_time_span.swap(m_time_span);
            std::swap(m_time_span, m_time_span);

            TimeSpan& time span = m_time_span = m_time_span;
            boost::ignore_unused_variable_warning(time span);

            const_constraints(m_time_span);
        }

        /*!
            \brief Checks the const constraints on a time_span.

            \param time_span A constant object.
        */
        void const_constraints(const TimeSpan& time_span)
        {
            const bool equality = time_span == time_span;
            boost::ignore_unused_variable_warning(equality);

            const typename TimeSpan::difference_type& seconds =
                time span.seconds();
            boost::ignore_unused_variable_warning(seconds);

            const typename TimeSpan::difference_type& hours_minutes_seconds =
                time span.hours_minutes_seconds();
            boost::ignore_unused_variable_warning(hours_minutes_seconds);
        }


    private:
        // variables

        TimeSpan m_time_span;


    };


}}}

#endif
