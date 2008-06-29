/*! \file
    \brief The definition of bobura::model::stoptable_info::StopConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAININFO_STOPCONCEPT_H)
#define BOBURA_MODEL_TRAININFO_STOPCONCEPT_H

#include <boost/concept_check.hpp>


namespace bobura { namespace model { namespace train_info
{
    /*!
        \brief The concept check class template for a stop.

        \tparam Stop A stop type.
    */
    template <typename Stop>
    class StopConcept :
        private boost::CopyConstructible<Stop>,
        private boost::Assignable<Stop>,
        private boost::EqualityComparable<Stop>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Stop::time_type time_type;

        typedef typename Stop::platform_type platform_type;


        // usage checks

        BOOST_CONCEPT_USAGE(StopConcept)
        {
            const_constraints(m_station_location);
        }

        void const_constraints(const Stop& stop)
        {
            const time_type& arrival = stop.arrival();
            boost::ignore_unused_variable_warning(arrival);

            const time_type& departure = stop.departure();
            boost::ignore_unused_variable_warning(departure);

            const platform_type& platform = stop.platform();
            boost::ignore_unused_variable_warning(platform);
        }

        
    private:
        // variables

        Stop m_stop;


#endif
    };


}}}

#endif
