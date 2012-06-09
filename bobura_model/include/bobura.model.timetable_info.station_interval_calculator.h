/*! \file
    \brief The definition of bobura::model::timetable_info::station_interval_calculator.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_STATIONINTERVALCALCULATOR_H)
#define BOBURA_MODEL_TIMETABLEINFO_STATIONINTERVALCALCULATOR_H

#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

#include <boost/optional.hpp>


namespace bobura { namespace model { namespace timetable_info
{
    /*!
        \brief The class template for a station interval calculator.

        \tparam StationLocation A station location type.
        \tparam Train           A train type.
        \tparam StationInterval A station interval type.
    */
    template <typename StationLocation, typename Train, typename StationInterval>
    class station_interval_calculator
    {
    public:
        // types

        //! The station location type.
        typedef StationLocation station_location_type;

        //! The station locations type.
        typedef std::vector<station_location_type> station_locations_type;

        //! The train type.
        typedef Train train_type;

        //! The trains type.
        typedef std::vector<train_type> trains_type;

        //! The station interval type.
        typedef StationInterval station_interval_type;

        //! The station intervals type.
        typedef std::vector<station_interval_type> station_intervals_type;


        // static functions

        static const station_interval_type& default_interval()
        {
            static const station_interval_type singleton(3);
            return singleton;
        }


        // constructors and destructor

        /*!
            \brief Creates a station interval calculator.

            \param station_locations Station locations.
            \param down_trains       Down trains.
            \param up_trains         Up trains.
        */
        station_interval_calculator(
            const station_locations_type& station_locations,
            const trains_type&            down_trains,
            const trains_type&            up_trains
        )
        :
        m_station_locations(station_locations),
        m_down_trains(down_trains),
        m_up_trains(up_trains)
        {}

        // functions

        /*!
            \brief Calculates station intervals.

            \return Station intervals.
        */
        station_intervals_type calculate()
        const
        {
            if (m_station_locations.empty())
                return station_intervals_type(m_station_locations.size(), default_interval());

            station_intervals_type intervals(m_station_locations.size(), default_interval() + whole_day2());

            BOOST_FOREACH (const train_type& train, m_down_trains)
            {
                const station_intervals_type intervals_by_train = calculate_by_train(train, true);
                assert(intervals.size() == intervals_by_train.size());
                std::transform(
                    intervals.begin(), intervals.end(), intervals_by_train.begin(), intervals.begin(), select
                );
            }
            BOOST_FOREACH (const train_type& train, m_up_trains)
            {
                const station_intervals_type intervals_by_train = calculate_by_train(train, false);
                assert(intervals.size() == intervals_by_train.size());
                std::transform(
                    intervals.begin(), intervals.end(), intervals_by_train.begin(), intervals.begin(), select
                );
            }

            std::for_each(intervals.begin(), intervals.end(), normalize);
            return intervals;
        }


    private:
        // types

        typedef typename train_type::stops_type::size_type stop_index_type;

        typedef typename train_type::stop_type stop_type;

        typedef typename stop_type::time_type time_type;

        typedef typename time_type::time_span_type time_span_type;


        // static functions

        static const station_interval_type& whole_day()
        {
            static const station_interval_type singleton =
                to_station_interval(time_span_type(time_span_type::seconds_of_whole_day()));
            return singleton;
        }

        static const station_interval_type& whole_day2()
        {
            static const station_interval_type singleton = whole_day() * 2;
            return singleton;
        }

        static void normalize(station_interval_type& interval)
        {
            if      (interval >= whole_day2())
                interval -= whole_day2();
            else if (interval >= whole_day())
                interval -= whole_day();
        }

        static const station_interval_type& select(
            const station_interval_type& interval1,
            const station_interval_type& interval2
        )
        {
            return std::min<station_interval_type>(interval1, interval2);
        }

        static station_interval_type to_station_interval(
            const time_span_type&                            time_span,
            const typename station_intervals_type::size_type denominator = 1
        )
        {
            station_interval_type interval(time_span.seconds());
            interval /= 60 * denominator;
            return interval;
        }


        // variables

        const station_locations_type& m_station_locations;

        const trains_type& m_down_trains;

        const trains_type& m_up_trains;


        // functions

        station_intervals_type calculate_by_train(const train_type& train, const bool down)
        const
        {
            station_intervals_type intervals(train.stops().size(), default_interval() + whole_day2());

            for (stop_index_type from = 0; from < train.stops().size() - 1; )
            {
                if (!calculate_travel_time(train, from, from))
                {
                    ++from;
                    continue;
                }

                stop_index_type to = from + 1;
                for (; to < train.stops().size(); ++to)
                {
                    const stop_index_type departure = down ? from : to;
                    const stop_index_type arrival = down ? to : from;
                    const boost::optional<time_span_type> travel_time =
                        calculate_travel_time(train, departure, arrival);
                    if (travel_time)
                    {
                        station_interval_type interval = to_station_interval(*travel_time, to - from);
                        if (to - from > 1)
                            interval += whole_day();
                        for (stop_index_type i = from; i < to; ++i)
                            intervals[i] = std::move(interval);
                        break;
                    }
                }

                from = to;
            }

            return intervals;
        }

        boost::optional<time_span_type> calculate_travel_time(
            const train_type&     train, 
            const stop_index_type from,
            const stop_index_type to
        )
        const
        {
            const stop_type& from_stop = train.stops()[from];
            const time_type from_time =
                from_stop.departure() != time_type::uninitialized() ? from_stop.departure() : from_stop.arrival();
            if (from_time == time_type::uninitialized())
                return boost::none;

            const stop_type& to_stop = train.stops()[to];
            const time_type to_time =
                to_stop.arrival() != time_type::uninitialized() ? to_stop.arrival() : to_stop.departure();
            if (to_time == time_type::uninitialized())
                return boost::none;

            return boost::make_optional(to_time - from_time);
        }


    };


}}}


#endif
