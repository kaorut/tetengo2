/*! \file
    \brief The definition of bobura::model::timetable_info::TimeConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_TIMECONCEPT_H)
#define BOBURA_MODEL_TRAININFO_TIMECONCEPT_H

#include <algorithm>

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
    class TimeConcept
    {
    public:
        // constructors and destructor

        TimeConcept();


        // functions

        /*!
            \brief Checks the constraints on a time.
        */
        void constraints()
        {
            typedef typename Time::tick_type tick_type;
            typedef typename Time::time_span_type time_span_type;

            m_time.swap(m_time);
            std::swap(m_time, m_time);

            Time& assigned = m_time = m_time;
            boost::ignore_unused_variable_warning(assigned);

            Time& plus_assigned = m_time += m_time_span;
            boost::ignore_unused_variable_warning(plus_assigned);

            Time& minus_assigned = m_time -= m_time_span;
            boost::ignore_unused_variable_warning(minus_assigned);

            const typename Time::tick_type& seconds_of_whole_day =
                typename Time::seconds_of_whole_day();
            boost::ignore_unused_variable_warning(seconds_of_whole_day);

            const Time& uninitialized = typename Time::uninitialized();
            boost::ignore_unused_variable_warning(uninitialized);

            const_constraints(m_time);
        }

        /*!
            \brief Checks the const constraints on a time.

            \param time A constant object.
        */
        void const_constraints(const Time& time)
        {
            const bool equality = time == time;
            boost::ignore_unused_variable_warning(equality);

            const bool less_than = time < time;
            boost::ignore_unused_variable_warning(less_than);

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


    };


}}}

#endif
