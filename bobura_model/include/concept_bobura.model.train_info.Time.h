/*! \file
    \brief The definition of concept_bobura::model::timetable_info::Time.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_MODEL_TRAININFO_TIME_H)
#define CONCEPTBOBURA_MODEL_TRAININFO_TIME_H

#include <boost/concept_check.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>


namespace concept_bobura { namespace model { namespace train_info
{
    /*!
        \brief The concept check class template for a time.

        \tparam Type A type.
    */
    template <typename Type>
    class Time :
        private boost::CopyConstructible<Type>,
        private boost::Assignable<Type>,
        private boost::EqualityComparable<Type>,
        private boost::LessThanComparable<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::tick_type tick_type;

        typedef typename Type::time_span_type time_span_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Time)
        {
            Type& plus_assigned = m_object += m_time_span;
            boost::ignore_unused_variable_warning(plus_assigned);

            Type& minus_assigned = m_object -= m_time_span;
            boost::ignore_unused_variable_warning(minus_assigned);

            const Type& uninitialized = typename Type::uninitialized();
            boost::ignore_unused_variable_warning(uninitialized);

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const bool less_than_or_equal = object <= object;
            boost::ignore_unused_variable_warning(less_than_or_equal);

            const bool greater_than = object > object;
            boost::ignore_unused_variable_warning(greater_than);

            const bool greater_than_or_equal = object >= object;
            boost::ignore_unused_variable_warning(greater_than_or_equal);

            const Type plused = object + m_time_span;
            boost::ignore_unused_variable_warning(plused);

            const Type minused = object - m_time_span;
            boost::ignore_unused_variable_warning(minused);

            const typename Type::time_span_type minused2 = object - object;
            boost::ignore_unused_variable_warning(minused2);

            const typename Type::tick_type& seconds_from_midnight =
                object.seconds_from_midnight();
            boost::ignore_unused_variable_warning(seconds_from_midnight);

            const boost::tuple<
                typename Type::tick_type,
                typename Type::tick_type,
                typename Type::tick_type
            > hours_minutes_seconds = object.hours_minutes_seconds();
            boost::ignore_unused_variable_warning(hours_minutes_seconds);
        }

        
    private:
        // variables

        Type m_object;

        time_span_type m_time_span;


#endif
    };


}}}

#endif
