/*! \file
    \brief The definition of bobura::view::diagram::utility.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_UTILITY_H)
#define BOBURA_VIEW_DIAGRAM_UTILITY_H


namespace bobura { namespace view { namespace diagram
{
    /*!
        \brief Calculates a horizontal position by a time.

        \tparam Left     A left type.
        \tparam Time     A time type.
        \tparam TimeSpan A time span type.

        \param time                           A time.
        \param time_offset                    A time offset
        \param previous_or_next_day           Set -1 for previous day, 0 for today and +1 for next day.
        \param horizontal_scroll_bar_position A horizontal scroll bar position.
        \param station_header_right           The right position of a station header.
        \param horizontal_scale               A horizontal scale.

        \return The horizontal position.
    */
    template <typename Left, typename Time, typename TimeSpan>
    Left time_to_left(
        const Time&     time,
        const TimeSpan& time_offset,
        const int       previous_or_next_day,
        const Left&     horizontal_scroll_bar_position,
        const Left&     station_header_right,
        const Left&     horizontal_scale
    )
    {
        typename Left::value_type left_value(time.seconds_from_midnight());
        left_value -= time_offset.seconds();
        if (left_value < 0)
            left_value += TimeSpan::seconds_of_whole_day();
        left_value += previous_or_next_day * TimeSpan::seconds_of_whole_day();
        left_value /= 180;
        left_value *= horizontal_scale.value();
        return Left(left_value) - horizontal_scroll_bar_position + station_header_right;
    }

    /*!
        \brief Calculates a vertical position by a station index.

        \tparam Top              A top type.
        \tparam StationPositions A station positions type.
        \tparam StationIndex     A station index type.

        \param station_positions            Station positions.
        \param station_index                A station index.
        \param vertical_scroll_bar_position A vertical scroll bar position.
        \param header_bottom                A header bottom.
        \param time_header_bottom           A time header bottom.

        \return The vertical position.
    */
    template <typename Top, typename StationPositions, typename StationIndex>
    Top station_index_to_top(
        const StationPositions& station_positions,
        const StationIndex      station_index,
        const Top&              vertical_scroll_bar_position,
        const Top&              header_bottom,
        const Top&              time_header_bottom
    )
    {
        const Top canvas_top = header_bottom + time_header_bottom;
        return station_positions[station_index] + canvas_top - vertical_scroll_bar_position;
    }


}}}


#endif
