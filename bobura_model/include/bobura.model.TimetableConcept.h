/*! \file
    \brief The definition of bobura::model::TimetableConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLECONCEPT_H)
#define BOBURA_MODEL_TIMETABLECONCEPT_H

#include <boost/concept_check.hpp>


namespace bobura { namespace model
{
    /*!
        \brief The concept check class template for timetables.

        \tparam Timetable A timetable type.
    */
    template <typename Timetable>
    class TimetableConcept :
        private boost::CopyConstructible<StationLocation>,
        private boost::Assignable<StationLocation>,
        private boost::EqualityComparable<StationLocation>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef
            typename Timetable::station_location_type station_locatoin_type;

        typedef
            typename Timetable::station_locations_type station_lcoations_type;


        // usage checks

        BOOST_CONCEPT_USAGE(TimetableConcept)
        {
            m_timetable.insert_station_location(
                m_timetable.station_locations().begin(), m_station_location
            );

            m_timetable.erase_station_locations(
                m_timetable.station_locations().begin(),
                m_timetable.station_locations().end()
            );

            const_constraints(m_timetable);
        }

        void const_constraints(const StationLocation& station_location)
        {
            const station_locations_type& station_locations =
                m_timetable.station_locations();
            boost::ignore_unused_variable_warning(station_locations);
        }

        
    private:
        // variables

        TimeTable m_timetable;

        station_location_type m_station_location;


#endif
    };


}}

#endif
