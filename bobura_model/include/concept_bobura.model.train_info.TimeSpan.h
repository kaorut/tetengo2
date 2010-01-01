/*! \file
    \brief The definition of concept_bobura::model::time spantable_info::TimeSpan.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_MODEL_TRAININFO_TIMESPAN_H)
#define CONCEPTBOBURA_MODEL_TRAININFO_TIMESPAN_H

#include <boost/concept_check.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>


namespace concept_bobura { namespace model { namespace train_info
{
    /*!
        \brief The concept check class template for a time span.

        \tparam Type A type.
    */
    template <typename Type>
    class TimeSpan :
        private boost::CopyConstructible<Type>,
        private boost::Assignable<Type>,
        private boost::EqualityComparable<Type>,
        private boost::LessThanComparable<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::tick_type tick_type;


        // usage checks

        BOOST_CONCEPT_USAGE(TimeSpan)
        {
            Type& plus_assigned = m_object += m_object;
            boost::ignore_unused_variable_warning(plus_assigned);

            Type& minus_assigned = m_object -= m_object;
            boost::ignore_unused_variable_warning(minus_assigned);

            const typename Type::tick_type& seconds_of_whole_day =
                typename Type::seconds_of_whole_day();
            boost::ignore_unused_variable_warning(seconds_of_whole_day);

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const bool less_than_or_equal = object <= object;
            boost::ignore_unused_variable_warning(less_than_or_equal);

            const bool greater_than = object < object;
            boost::ignore_unused_variable_warning(greater_than);

            const bool greater_than_or_equal = object >= object;
            boost::ignore_unused_variable_warning(greater_than_or_equal);

            const Type plused = object + object;
            boost::ignore_unused_variable_warning(plused);

            const Type minused = object - object;
            boost::ignore_unused_variable_warning(minused);

            const typename Type::tick_type& seconds =
                object.seconds();
            boost::ignore_unused_variable_warning(seconds);

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


#endif
    };


}}}

#endif
