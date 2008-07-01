/*! \file
    \brief The definition of concept_bobura::model::Timetable.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_MODEL_TIMETABLE_H)
#define CONCEPTBOBURA_MODEL_TIMETABLE_H

#include <boost/concept_check.hpp>


namespace concept_bobura { namespace model
{
    /*!
        \brief The concept check class template for a timetable.

        \tparam Type A type.
    */
    template <typename Type>
    class Timetable :
        private boost::CopyConstructible<Type>,
        private boost::Assignable<Type>,
        private boost::EqualityComparable<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef
            typename Type::station_location_type station_locatoin_type;

        typedef
            typename Type::station_locations_type station_lcoations_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Timetable)
        {
            m_object.insert_station_location(
                m_station_locations.begin(), m_station_location
            );

            m_object.erase_station_locations(
                m_station_locations.begin(), m_station_locations.end()
            );

            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            const station_locations_type& station_locations =
                object.station_locations();
            boost::ignore_unused_variable_warning(station_locations);
        }

        
    private:
        // variables

        Type m_object;

        station_location_type m_station_location;

        station_locations_type m_station_locations;


#endif
    };


}}

#endif
