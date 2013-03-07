/*! \file
    \brief The definition of bobura::view::diagram::utility.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_UTILITY_H)
#define BOBURA_VIEW_DIAGRAM_UTILITY_H

#include <utility>


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

    /*!
        \brief Returns the normal line width.

        \tparam Size A size type.

        \return The normal line width.
    */
    template <typename Size>
    Size normal_line_width()
    {
        return Size(typename Size::value_type(1, 12));
    }

    /*!
        \brief Returns the bold line width.

        \tparam Size A size type.

        \return The bold line width.
    */
    template <typename Size>
    Size bold_line_width()
    {
        return Size(typename Size::value_type(1, 6));
    }

    /*!
        \brief Returns the selected line margin.

        \tparam Size A size type.

        \return The selected line margin.
    */
    template <typename Size>
    Size selected_line_margin()
    {
        return Size(typename Size::value_type(1, 3));
    }

    /*!
        \brief Draws a selectable line.

        \tparam Canvas   A canvas type.
        \tparam Position A position type.

        \param canvas   A canvas.
        \param from     A start position.
        \param to       An end position.
        \param selected A selected status.
    */
    template <typename Canvas, typename Position>
    void draw_selectable_line(Canvas& canvas, const Position& from, const Position& to, const bool selected)
    {
        if (selected)
        {
            typedef typename Canvas::color_type color_type;
            typedef typename Canvas::line_style_type line_style_type;
            typedef typename Canvas::size_type size_type;

            color_type original_color = canvas.color();
            const typename line_style_type::enum_t original_line_style = canvas.line_style();
            size_type original_line_width = canvas.line_width();

            canvas.set_color(
                color_type(original_color.red(), original_color.green(), original_color.blue(), 0x20)
            );
            canvas.set_line_style(line_style_type::solid);

            canvas.set_line_width(original_line_width + selected_line_margin<size_type>() * 2);
            canvas.draw_line(from, to);

            canvas.set_line_width(original_line_width + selected_line_margin<size_type>());
            canvas.draw_line(from, to);

            canvas.set_color(std::move(original_color));
            canvas.set_line_style(original_line_style);
            canvas.set_line_width(std::move(original_line_width));
        }

        canvas.draw_line(from, to);
    }


}}}


#endif
