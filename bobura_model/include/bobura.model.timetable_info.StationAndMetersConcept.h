/*! \file
    \brief The definition of bobura::model::timetable_info::StationAndMetersConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLENINFO_STATIONANDMETERSCONCEPT_H)
#define BOBURA_MODEL_TIMETABLENINFO_STATIONANDMETERSCONCEPT_H

#include <boost/concept_check.hpp>


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The concept check class template for a station_and_meters.

        \tparam StationAndMeters A station_and_meters type.
    */
    template <typename StationAndMeters>
    class StationAndMetersConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints on a station_and_meters.
        */
        void constraints()
        {
            typedef typename StationAndMeters::station_type station_type;
            typedef typename StationAndMeters::size_type size_type;

            const_constraints(m_station_and_meters);
        }

        /*!
            \brief Checks the const constraints on a station_and_meters.
        */
        void const_constraints(const StationAndMeters& station_and_meters)
        {
            //const typename StationAndMeters::string_type name =
            //    station_and_meters.name();
            //boost::ignore_unused_variable_warning(name);
        }


        // variables

        StationAndMeters m_station_and_meters;


    };


}}}

#endif
