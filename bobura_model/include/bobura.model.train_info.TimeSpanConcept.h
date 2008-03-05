/*! \file
    \brief The definition of bobura::model::time spantable_info::TimeSpanConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIMESPANCONCEPT_H)
#define BOBURA_MODEL_TRAININFO_TIMESPANCONCEPT_H

#include <algorithm>

#include <boost/concept_check.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>


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

            TimeSpan& assigned = m_time_span = m_time_span;
            boost::ignore_unused_variable_warning(assigned);

            TimeSpan& plus_assigned = m_time_span += m_time_span;
            boost::ignore_unused_variable_warning(plus_assigned);

            TimeSpan& minus_assigned = m_time_span -= m_time_span;
            boost::ignore_unused_variable_warning(minus_assigned);

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

            const bool less_than = time_span < time_span;
            boost::ignore_unused_variable_warning(less_than);

            const bool less_than_or_equal = time_span <= time_span;
            boost::ignore_unused_variable_warning(less_than_or_equal);

            const bool greater_than = time_span < time_span;
            boost::ignore_unused_variable_warning(greater_than);

            const bool greater_than_or_equal = time_span >= time_span;
            boost::ignore_unused_variable_warning(greater_than_or_equal);

            const TimeSpan plused = time_span + time_span;
            boost::ignore_unused_variable_warning(plused);

            const TimeSpan minused = time_span - time_span;
            boost::ignore_unused_variable_warning(minused);

            const typename TimeSpan::difference_type& seconds =
                time_span.seconds();
            boost::ignore_unused_variable_warning(seconds);

            const boost::tuple<
                typename TimeSpan::difference_type,
                typename TimeSpan::difference_type,
                typename TimeSpan::difference_type
            > hours_minutes_seconds = time_span.hours_minutes_seconds();
            boost::ignore_unused_variable_warning(hours_minutes_seconds);
        }


    private:
        // variables

        TimeSpan m_time_span;


    };


}}}

#endif
