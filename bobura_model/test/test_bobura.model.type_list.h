/*! \file
    \brief The definition of test_bobura::model::type_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TYPELIST_H)
#define TESTBOBURA_MODEL_TYPELIST_H

#include <string>

#include <boost/mpl/pair.hpp>

#include <tetengo2.meta.assoc_list.h>

#include "bobura.model.message.timetable_observer_set.h"
#include "bobura.model.station_info.grade.h"
#include "bobura.model.station.h"
#include "bobura.model.timetable.h"
#include "bobura.model.timetable_info.station_location.h"
#include "bobura.model.train.h"
#include "bobura.model.train_info.stop.h"
#include "bobura.model.train_info.time.h"
#include "bobura.model.train_info.time_span.h"


namespace test_bobura { namespace model
{
    namespace type
    {
        struct string;         //!< The string type.
        struct grade_type_set; //!< The station grade type set type.
        struct station;        //!< The station type.
        struct station_location; //!< The station location type.
        struct time;           //!< The time type.
        struct stop;           //!< The stop type.
        struct train;          //!< The train type.
        struct timetable;      //!< The timetable type.
    }

#if !defined(DOCUMENTATION)
    namespace detail
    {
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::string string_type;
        typedef
            bobura::model::station_info::grade_type_set<string_type>
            grade_type_set_type;
        typedef grade_type_set_type::grade_type grade_type;
        typedef bobura::model::station<string_type, grade_type> station_type;
        typedef
            bobura::model::timetable_info::station_location<
                station_type, size_type
            >
            station_location_type;
        typedef
            bobura::model::train_info::time<
                size_type,
                bobura::model::train_info::time_span<difference_type>
            >
            time_type;
        typedef
            bobura::model::train_info::stop<
                detail::time_type, detail::string_type
            >
            stop_type;
        typedef
            bobura::model::train<string_type, string_type, stop_type>
            train_type;
    }
#endif

    //! The type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::string, detail::string_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::grade_type_set, detail::grade_type_set_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::station, detail::station_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::station_location, detail::station_location_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::time, detail::time_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::stop, detail::stop_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::train, detail::train_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::timetable,
                bobura::model::timetable<
                    detail::string_type,
                    detail::station_location_type,
                    detail::train_type,
                    bobura::model::message::timetable_observer_set
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>>
        type_list;


}}


#endif
