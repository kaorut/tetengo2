/*! \file
    \brief The definition of test_bobura::model::type_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TESTBOBURA_MODEL_TYPELIST_H)
#define TESTBOBURA_MODEL_TYPELIST_H

//#include <cstddef>
#include <string>

#include <boost/mpl/at.hpp>
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
    /**** Common *************************************************************/

    namespace type
    {
        struct size;           //!< The size type.
        struct difference;     //!< The difference type.
        struct string;         //!< The string type.
    }

    //! The common type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::size, std::size_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::difference, std::ptrdiff_t>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::string, std::string>,
        tetengo2::meta::assoc_list_end
        >>>
        type_list;


    /**** Serialization *****************************************************/

    namespace type { namespace serialization
    {
        struct string;         //!< The string type.
    }}

    //! The serialization type list.
    //typedef
    //    tetengo2::meta::assoc_list<
    //        boost::mpl::pair<type::string, detail::string_type>,
    //    tetengo2::meta::assoc_list_end
    //    >
    //    serialization_type_list;


    /**** Model *************************************************************/

    namespace type { namespace model
    {
        struct grade_type_set; //!< The station grade type set type.
        struct station;        //!< The station type.
        struct station_location; //!< The station location type.
        struct time;           //!< The time type.
        struct stop;           //!< The stop type.
        struct train;          //!< The train type.
        struct timetable;      //!< The timetable type.
    }}

#if !defined(DOCUMENTATION)
    namespace detail
    {
        typedef
            bobura::model::station_info::grade_type_set<
                boost::mpl::at<type_list, type::string>::type
            >
            grade_type_set_type;
        typedef grade_type_set_type::grade_type grade_type;
        typedef
            bobura::model::station<
                boost::mpl::at<type_list, type::string>::type, grade_type
            >
            station_type;
        typedef
            bobura::model::timetable_info::station_location<
                station_type, boost::mpl::at<type_list, type::size>::type
            >
            station_location_type;
        typedef
            bobura::model::train_info::time<
                boost::mpl::at<type_list, type::size>::type,
                bobura::model::train_info::time_span<
                    boost::mpl::at<type_list, type::difference>::type
                >
            >
            time_type;
        typedef
            bobura::model::train_info::stop<
                detail::time_type,
                boost::mpl::at<type_list, type::string>::type
            >
            stop_type;
        typedef
            bobura::model::train<
                boost::mpl::at<type_list, type::string>::type,
                boost::mpl::at<type_list, type::string>::type,
                stop_type
            >
            train_type;
    }
#endif

    //! The model type list.
    typedef
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::grade_type_set, detail::grade_type_set_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::model::station, detail::station_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::station_location, detail::station_location_type
            >,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::model::time, detail::time_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::model::stop, detail::stop_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<type::model::train, detail::train_type>,
        tetengo2::meta::assoc_list<
            boost::mpl::pair<
                type::model::timetable,
                bobura::model::timetable<
                    boost::mpl::at<type_list, type::string>::type,
                    detail::station_location_type,
                    detail::train_type,
                    bobura::model::message::timetable_observer_set
                >
            >,
        tetengo2::meta::assoc_list_end
        >>>>>>>
        model_type_list;


}}


#endif
