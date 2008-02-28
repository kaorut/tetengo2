/*! \file
    \brief The definition of bobura::model::timetable_info::StationLocationConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLENINFO_STATIONLOCATIONCONCEPT_H)
#define BOBURA_MODEL_TIMETABLENINFO_STATIONLOCATIONCONCEPT_H

#include <algorithm>

#include <boost/concept_check.hpp>


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The concept check class template for a station_location.

        \tparam StationLocation A station_location type.
    */
    template <typename StationLocation>
    class StationLocationConcept
    {
    public:
        // constructors and destructor

        StationLocationConcept();


        // functions

        /*!
            \brief Checks the constraints on a station_location.
        */
        void constraints()
        {
            typedef typename StationLocation::station_type station_type;
            typedef typename StationLocation::meterage_type meterage_type;

            m_station_location.swap(m_station_location);
            std::swap(m_station_location, m_station_location);

            StationLocation& station_location =
                m_station_location = m_station_location;
            boost::ignore_unused_variable_warning(station_location);

            const_constraints(m_station_location);
        }

        /*!
            \brief Checks the const constraints on a station_location.

            \param station_location A constant object.
        */
        void const_constraints(const StationLocation& station_location)
        {
            const typename StationLocation::station_type& station =
                station_location.station();
            boost::ignore_unused_variable_warning(station);

            const typename StationLocation::meterage_type& meterage =
                station_location.meterage();
            boost::ignore_unused_variable_warning(meterage);

            const bool before = station_location.before(station_location);
            boost::ignore_unused_variable_warning(before);
        }


    private:
        // variables

        StationLocation m_station_location;


    };


}}}

#endif
