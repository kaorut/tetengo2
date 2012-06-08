/*! \file
    \brief The definition of bobura::model::timetable_info::station_interval_calculator.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLEINFO_STATIONINTERVALCALCULATOR_H)
#define BOBURA_MODEL_TIMETABLEINFO_STATIONINTERVALCALCULATOR_H

#include <algorithm>
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
                return station_intervals_type(m_station_locations.size(), 3);

            const station_intervals_type down_intervals = down_station_intervals();
            const station_intervals_type up_intervals = up_station_intervals();

            station_intervals_type intervals;
            intervals.reserve(m_station_locations.size());
            std::transform(
                down_intervals.begin(),
                down_intervals.end(),
                up_intervals.begin(),
                std::back_inserter(intervals),
                select_station_interval
            );

            return intervals;
        }


    private:
        // types

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

        static station_interval_type select_station_interval(
            const station_interval_type& interval1,
            const station_interval_type& interval2
        )
        {

            const station_interval_type selected = std::min(interval1, interval2);
            return selected < whole_day() ? selected : selected - whole_day();
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

        station_intervals_type down_station_intervals()
        const
        {
            station_intervals_type intervals(m_station_locations.size(), 3 + whole_day());

            for (typename station_intervals_type::size_type from = 0; from < intervals.size(); ++from)
            {
                if (!shortest_travel_time(m_down_trains, from, from))
                    continue;

                for (typename station_intervals_type::size_type to = from + 1; to < intervals.size(); ++to)
                {
                    const boost::optional<time_span_type> travel_time = shortest_travel_time(m_down_trains, from, to);
                    if (travel_time)
                    {
                        for (typename station_intervals_type::size_type i = from; i < to; ++i)
                        {
                            intervals[i] = to_station_interval(*travel_time, to - from);
                            if (to - from > 1)
                                intervals[i] += whole_day();
                        }
                        break;
                    }
                }
            }

            return intervals;
        }

        station_intervals_type up_station_intervals()
        const
        {
            station_intervals_type intervals(m_station_locations.size(), 3 + whole_day());

            for (typename station_intervals_type::size_type from = 0; from < intervals.size(); ++from)
            {
                if (!shortest_travel_time(m_up_trains, from, from))
                    continue;

                for (typename station_intervals_type::size_type to = from + 1; to < intervals.size(); ++to)
                {
                    const boost::optional<time_span_type> travel_time = shortest_travel_time(m_up_trains, to, from);
                    if (travel_time)
                    {
                        for (typename station_intervals_type::size_type i = from; i < to; ++i)
                        {
                            intervals[i] = to_station_interval(*travel_time, to - from);
                            if (to - from > 1)
                                intervals[i] += whole_day();
                        }
                        break;
                    }
                }
            }

            return intervals;
        }

        boost::optional<time_span_type> shortest_travel_time(
            const trains_type&                               trains,
            const typename station_intervals_type::size_type from,
            const typename station_intervals_type::size_type to
        )
        const
        {
            if (trains.empty())
                return boost::none;

            boost::optional<time_span_type> travel_time = calculate_travel_time(trains[0], from, to);
            for (typename trains_type::size_type i = 1; i < trains.size(); ++i)
            {
                const boost::optional<time_span_type> new_travel_time = calculate_travel_time(trains[i], from, to);
                if (!new_travel_time)
                    continue;

                if (!travel_time || *new_travel_time < *travel_time)
                    travel_time = *new_travel_time;
            }

            return travel_time ? boost::make_optional(*travel_time) : boost::none;
        }

        boost::optional<time_span_type> calculate_travel_time(
            const train_type&                                train, 
            const typename station_intervals_type::size_type from,
            const typename station_intervals_type::size_type to
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
