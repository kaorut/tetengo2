/*! \file
    \brief The definition of bobura::model::timetable_info::StationLocationConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_STATIONLOCATIONCONCEPT_H)
#define BOBURA_MODEL_TIMETABLEINFO_STATIONLOCATIONCONCEPT_H

#include <boost/concept_check.hpp>


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The concept check class template for a station_location.

        \tparam StationLocation A station_location type.
    */
    template <typename StationLocation>
    class StationLocationConcept :
        private boost::CopyConstructible<StationLocation>,
        private boost::Assignable<StationLocation>,
        private boost::EqualityComparable<StationLocation>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename StationLocation::station_type station_type;

        typedef typename StationLocation::meterage_type meterage_type;


        // usage checks

        BOOST_CONCEPT_USAGE(StationLocationConcept)
        {
            const_constraints(m_station_location);
        }

        void const_constraints(const StationLocation& station_location)
        {
            const station_type& station = station_location.station();
            boost::ignore_unused_variable_warning(station);

            const meterage_type& meterage = station_location.meterage();
            boost::ignore_unused_variable_warning(meterage);

            const bool before = station_location.before(station_location);
            boost::ignore_unused_variable_warning(before);
        }

        
    private:
        // variables

        StationLocation m_station_location;


#endif
    };


}}}

#endif
