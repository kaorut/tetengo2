/*! \file
    \brief The definition of bobura::model::timetable_info::station_and_kilometers.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_STATIONANDKILOMETERS_H)
#define BOBURA_MODEL_TIMETABLEINFO_STATIONANDKILOMETERS_H

#include <boost/concept_check.hpp>

#include "bobura.model.StationConcept.h"


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The class for a station and kilometers.

        \tparam Station A station type. It must conform to
                        bobura::model::StationConcept<Station>.
        \tparam Float   A float-point number type. It must conform to
                        boost::LessThanComparableConcept<Float>.
    */
    template <typename Station, typename Float>
    class station_and_kilometers : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(Station, bobura::model, StationConcept);
        BOOST_CLASS_REQUIRE(Float, boost, LessThanComparableConcept);


    public:
        // types

        //! The station type.
        typedef Station station_type;

        //! The float type.
        typedef Float float_type;


        // constructors and destructor

        /*!
            \brief Creates a station_and_kilometers.
        */
        station_and_kilometers()
        {}

        /*!
            \brief Destroys the station_and_kilometers.
        */
        virtual ~station_and_kilometers()
        throw ()
        {}


        // functions


    private:
        // variables


    };


}}}

#endif
