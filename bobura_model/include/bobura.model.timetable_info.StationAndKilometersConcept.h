/*! \file
    \brief The definition of bobura::model::timetable_info::StationAndKilometersConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLENINFO_STATIONANDKILOMETERSCONCEPT_H)
#define BOBURA_MODEL_TIMETABLENINFO_STATIONANDKILOMETERSCONCEPT_H

#include <boost/concept_check.hpp>


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The concept check class template for a station_and_kilometers.

        \tparam StationAndKilometers A station_and_kilometers type.
    */
    template <typename StationAndKilometers>
    class StationAndKilometersConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints on a station_and_kilometers.
        */
        void constraints()
        {
            typedef typename StationAndKilometers::station_type station_type;
            typedef typename StationAndKilometers::float_type float_type;

            const_constraints(m_station_and_kilometers);
        }

        /*!
            \brief Checks the const constraints on a station_and_kilometers.
        */
        void const_constraints(
            const StationAndKilometers& station_and_kilometers
        )
        {
            //const typename StationAndKilometers::string_type name =
            //    station_and_kilometers.name();
            //boost::ignore_unused_variable_warning(name);
        }


        // variables

        StationAndKilometers m_station_and_kilometers;


    };


}}}

#endif
