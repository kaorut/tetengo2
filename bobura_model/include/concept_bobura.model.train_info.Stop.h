/*! \file
    \brief The definition of concept_bobura::model::stoptable_info::Stop.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_MODEL_TRAININFO_STOP_H)
#define CONCEPTBOBURA_MODEL_TRAININFO_STOP_H

#include <boost/concept_check.hpp>


namespace concept_bobura { namespace model { namespace train_info
{
    /*!
        \brief The concept check class template for a stop.

        \tparam Type A type.
    */
    template <typename Type>
    class Stop :
        private boost::CopyConstructible<Type>,
        private boost::Assignable<Type>,
        private boost::EqualityComparable<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::time_type time_type;

        typedef typename Type::platform_type platform_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Stop)
        {
            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const time_type& arrival = object.arrival();
            boost::ignore_unused_variable_warning(arrival);

            const time_type& departure = object.departure();
            boost::ignore_unused_variable_warning(departure);

            const platform_type& platform = object.platform();
            boost::ignore_unused_variable_warning(platform);
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}}

#endif
