/*! \file
    \brief The definition of concept_bobura::model::timetable_info::StationLocation.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_MODEL_TIMETABLEINFO_STATIONLOCATION_H)
#define CONCEPTBOBURA_MODEL_TIMETABLEINFO_STATIONLOCATION_H //!< !! Include Guard !!

//#include <boost/concept_check.hpp>

#include <concept_tetengo2.Assignable.h>


namespace concept_bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The concept check class template for a station location.

        \tparam Type A type.
    */
    template <typename Type>
    class StationLocation :
        private concept_tetengo2::Assignable<Type>,
        private boost::EqualityComparable<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::station_type station_type;

        typedef typename Type::meterage_type meterage_type;


        // usage checks

        BOOST_CONCEPT_USAGE(StationLocation)
        {
            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const station_type& station = object.station();
            boost::ignore_unused_variable_warning(station);

            const meterage_type& meterage = object.meterage();
            boost::ignore_unused_variable_warning(meterage);

            const bool before = object.before(object);
            boost::ignore_unused_variable_warning(before);
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}}

#endif
