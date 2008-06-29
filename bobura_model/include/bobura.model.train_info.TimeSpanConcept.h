/*! \file
    \brief The definition of bobura::model::time spantable_info::TimeSpanConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIMESPANCONCEPT_H)
#define BOBURA_MODEL_TRAININFO_TIMESPANCONCEPT_H

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
    class TimeSpanConcept :
        private boost::CopyConstructible<TimeSpan>,
        private boost::Assignable<TimeSpan>,
        private boost::EqualityComparable<TimeSpan>,
        private boost::LessThanComparable<TimeSpan>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename TimeSpan::tick_type tick_type;


        // usage checks

        BOOST_CONCEPT_USAGE(TimeSpanConcept)
        {
            TimeSpan& plus_assigned = m_time_span += m_time_span;
            boost::ignore_unused_variable_warning(plus_assigned);

            TimeSpan& minus_assigned = m_time_span -= m_time_span;
            boost::ignore_unused_variable_warning(minus_assigned);

            const typename TimeSpan::tick_type& seconds_of_whole_day =
                typename TimeSpan::seconds_of_whole_day();
            boost::ignore_unused_variable_warning(seconds_of_whole_day);

            const_constraints(m_time_span);
        }

        void const_constraints(const TimeSpan& time_span)
        {
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

            const typename TimeSpan::tick_type& seconds =
                time_span.seconds();
            boost::ignore_unused_variable_warning(seconds);

            const boost::tuple<
                typename TimeSpan::tick_type,
                typename TimeSpan::tick_type,
                typename TimeSpan::tick_type
            > hours_minutes_seconds = time_span.hours_minutes_seconds();
            boost::ignore_unused_variable_warning(hours_minutes_seconds);
        }

        
    private:
        // variables

        TimeSpan m_time_span;


#endif
    };


}}}

#endif
