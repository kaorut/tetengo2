/*! \file
    \brief The definition of bobura::model::timetable_info::TimeConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIMECONCEPT_H)
#define BOBURA_MODEL_TRAININFO_TIMECONCEPT_H

#include <boost/concept_check.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The concept check class template for a time.

        \tparam Time A time type.
    */
    template <typename Time>
    class TimeConcept :
        private boost::CopyConstructible<Time>,
        private boost::Assignable<Time>,
        private boost::EqualityComparable<Time>,
        private boost::LessThanComparable<Time>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Time::tick_type tick_type;

        typedef typename Time::time_span_type time_span_type;


        // usage checks

        BOOST_CONCEPT_USAGE(TimeConcept)
        {
            Time& plus_assigned = m_time += m_time_span;
            boost::ignore_unused_variable_warning(plus_assigned);

            Time& minus_assigned = m_time -= m_time_span;
            boost::ignore_unused_variable_warning(minus_assigned);

            const Time& uninitialized = typename Time::uninitialized();
            boost::ignore_unused_variable_warning(uninitialized);

            const_constraints(m_time);
        }

        void const_constraints(const Time& time)
        {
            const bool less_than_or_equal = time <= time;
            boost::ignore_unused_variable_warning(less_than_or_equal);

            const bool greater_than = time > time;
            boost::ignore_unused_variable_warning(greater_than);

            const bool greater_than_or_equal = time >= time;
            boost::ignore_unused_variable_warning(greater_than_or_equal);

            const Time plused = time + m_time_span;
            boost::ignore_unused_variable_warning(plused);

            const Time minused = time - m_time_span;
            boost::ignore_unused_variable_warning(minused);

            const typename Time::time_span_type minused2 = time - time;
            boost::ignore_unused_variable_warning(minused2);

            const typename Time::tick_type& seconds_from_midnight =
                time.seconds_from_midnight();
            boost::ignore_unused_variable_warning(seconds_from_midnight);

            const boost::tuple<
                typename Time::tick_type,
                typename Time::tick_type,
                typename Time::tick_type
            > hours_minutes_seconds = time.hours_minutes_seconds();
            boost::ignore_unused_variable_warning(hours_minutes_seconds);
        }

        
    private:
        // variables

        Time m_time;

        const typename Time::time_span_type m_time_span;


#endif
    };


}}}

#endif
